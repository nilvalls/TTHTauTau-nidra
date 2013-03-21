/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			11 Jun 2011
    Description:	TMVA evaluating class
    Notes:

*/

#include "TLorentzVector.h"
#include "TMVA/Config.h"

#include "../Helper.h"
#include "../ProPack.h"
#include "GenHelper.h"
#include "TMVAEvaluator.h"

#define TTL_TMVAEvaluator_cxx
using namespace std;

extern ProPack *proPack;

#define AT __LINE__

// Default destructor
TTL_TMVAEvaluator::~TTL_TMVAEvaluator(){
	delete tmvaReader; tmvaReader = NULL;
}

// Constructor
TTL_TMVAEvaluator::TTL_TMVAEvaluator(){
	mvaBooked = false;
    tmvaReader = NULL;
}

TTL_TMVAEvaluator::TTL_TMVAEvaluator(map<string,string>const & iParams) : params(iParams){
	mvaBooked = false;
    tmvaReader = new TMVA::Reader( "!Color:!Silent" );
    SetupVariables(tmvaReader);
}

template<typename T> void TTL_TMVAEvaluator::SetupVariables(T* obj){

    AddVariable(obj, "CSR", 'F', csr);
    // AddVariable(obj, "HT", 'F', HT);
    AddVariable(obj, "Tau1Pt", 'F', Tau1Pt);
    AddVariable(obj, "Tau1Eta", 'F', Tau1Eta);
    AddVariable(obj, "Tau2Pt", 'F', Tau2Pt);
    AddVariable(obj, "Tau1DecayMode", 'I', Tau1DecayMode);
    AddVariable(obj, "Tau2DecayMode", 'I', Tau2DecayMode);
    AddVariable(obj, "Tau1IsolationIndex", 'I', Tau1IsolationIndex);
    AddVariable(obj, "Tau2IsolationIndex", 'I', Tau2IsolationIndex);
    //AddVariable(obj, "DeltaRTau1Tau2", 'F', DeltaRTau1Tau2);
    // AddVariable(obj, "DeltaRTau1Lepton", 'F', DeltaRTau1Lepton);
    // AddVariable(obj, "DeltaRTau2Lepton", 'F', DeltaRTau2Lepton);
    // AddVariable(obj, "DeltaRTau1LeadingJet", 'F', DeltaRTau1LeadingJet);
    // AddVariable(obj, "DeltaRTau2LeadingJet", 'F', DeltaRTau2LeadingJet);
    // AddVariable(obj, "DeltaRTau1SubleadingJet", 'F', DeltaRTau1SubleadingJet);
    // AddVariable(obj, "DeltaRTau2SubleadingJet", 'F', DeltaRTau2SubleadingJet);
    // AddVariable(obj, "DeltaRLeptonLeadingJet", 'F', DeltaRLeptonLeadingJet);
    // AddVariable(obj, "DeltaRLeptonSubleadingJet", 'F', DeltaRLeptonSubleadingJet);
    // AddVariable(obj, "LeadingJetSubleadingJetMass", 'F', LeadingJetSubleadingJetMass);
    // AddVariable(obj, "Tau1LTPt", 'F', Tau1LTPt);
    // AddVariable(obj, "Tau2LTPt", 'F', Tau2LTPt);
    // AddVariable(obj, "Tau1NProngs", 'I', Tau1NProngs);
    // AddVariable(obj, "Tau2NProngs", 'I', Tau2NProngs);
    AddVariable(obj, "LeadingJetPt", 'F', LeadingJetPt);
    // AddVariable(obj, "SubLeadingJetPt", 'F', SubLeadingJetPt);
    AddVariable(obj, "DitauVisibleMass", 'F', DitauVisibleMass);
}

void TTL_TMVAEvaluator::BookMVA() {
    tmvaReader->BookMVA(TString(params.find("MVAmethod")->second + " method") , TString(params.find("MVAweights")->second));
}

void TTL_TMVAEvaluator::TrainMVA() {
    TMVA::gConfig().GetIONames().fWeightFileDir = params["MVAdir"];

    TFile outfile(params["MVAoutput"].c_str(), "RECREATE");
    TMVA::Factory *factory = new TMVA::Factory("TMVAClassification", &outfile,
            "!V:!Silent:Transformations=I;D;P;G,D:AnalysisType=Classification");

    SetupVariables(factory);

    TTree *stree;
    TFile infile(params["MVAinput"].c_str());

    infile.GetObject("TreeS", stree);
    factory->AddSignalTree(stree, 1.);

    for (const auto& bkg: Helper::SplitString(params["MVAbackground"])) {
        TTree *btree;
        string name = "TreeB_" + bkg;
        double weight = proPack->GetPContainer()->Get(bkg)->GetCrossSection();

        infile.GetObject(name.c_str(), btree);

        if (btree->GetEntries() > 0)
            factory->AddBackgroundTree(btree, weight);
        else
            cerr << "WARNING: skipping " << bkg << " for MVA training (no events)" << endl;
    }

    factory->PrepareTrainingAndTestTree("", "", "SplitMode=Random:NormMode=NumEvents:!V");

    // the following can be copied from TMVAClassification.C
    factory->BookMethod(TMVA::Types::kCuts, "Cuts",
            "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart");
    // factory->BookMethod(TMVA::Types::kMLP, "MLP",
            // "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:!UseRegulator");
    // factory->BookMethod(TMVA::Types::kMLP, "MLPBFGS",
            // "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS:!UseRegulator");
    factory->BookMethod(TMVA::Types::kMLP, "MLPBNN",
            "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS:UseRegulator"); // BFGS training with bayesian regulators
    factory->BookMethod(TMVA::Types::kCFMlpANN, "CFMlpANN",
            "!H:!V:NCycles=2000:HiddenLayers=N+1,N"); // n_cycles:#nodes:#nodes:...
    // factory->BookMethod(TMVA::Types::kTMlpANN, "TMlpANN",
            // "!H:!V:NCycles=200:HiddenLayers=N+1,N:LearningMethod=BFGS:ValidationFraction=0.3"); // n_cycles:#nodes:#nodes:...
    factory->BookMethod(TMVA::Types::kBDT, "BDT",
            "!H:!V:NTrees=850:nEventsMin=150:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning");

    factory->TrainAllMethods();
    factory->TestAllMethods();
    factory->EvaluateAllMethods();

    delete factory;
}

// Evaluate each event
float TTL_TMVAEvaluator::Evaluate(TTLBranches * iEvent, int iCombo){

	if (iCombo < 0){ cerr << "ERROR: 'iCombo' is " << iCombo << "." << endl; exit(1); }

    try {
        csr = iEvent->GetComboSelectorResponse(iCombo);
    } catch (...) {
        csr = 0.;
    }
    HT = iEvent->TTL_HT->at(iCombo);
    Tau1Pt = iEvent->TTL_Tau1Pt->at(iCombo);
    Tau1Eta = iEvent->TTL_Tau1Eta->at(iCombo);
    Tau2Pt = iEvent->TTL_Tau2Pt->at(iCombo);
    Tau1DecayMode = iEvent->TTL_Tau1DecayMode->at(iCombo);
    Tau2DecayMode = iEvent->TTL_Tau2DecayMode->at(iCombo);
    Tau1IsolationIndex = iEvent->GetTau1IsolationIndex(iCombo);
    Tau2IsolationIndex = iEvent->GetTau2IsolationIndex(iCombo);
    Tau1LTPt = iEvent->TTL_Tau1LTPt->at(iCombo);
    Tau2LTPt = iEvent->TTL_Tau2LTPt->at(iCombo);
    Tau1NProngs = iEvent->TTL_Tau1NProngs->at(iCombo);
    Tau2NProngs = iEvent->TTL_Tau2NProngs->at(iCombo);
    DitauVisibleMass = iEvent->TTL_DitauVisibleMass->at(iCombo);

    LeadingJetPt = iEvent->J_Pt->at(iEvent->GetJetIndex(iCombo, 0));
    SubLeadingJetPt = iEvent->J_Pt->at(iEvent->GetJetIndex(iCombo, 1));

    float tau1eta	= iEvent->TTL_Tau1Eta->at(iCombo);
    float tau1phi	= iEvent->TTL_Tau1Phi->at(iCombo);
    float tau2eta	= iEvent->TTL_Tau2Eta->at(iCombo);
    float tau2phi	= iEvent->TTL_Tau2Phi->at(iCombo);
    float lepEta	= iEvent->TTL_LeptonEta->at(iCombo);
    float lepPhi	= iEvent->TTL_LeptonPhi->at(iCombo);

    float jet1eta = -99;
    float jet1phi = -99;
    float jet2eta = -99;
    float jet2phi = -99;

    DeltaRTau1Tau2 = DeltaR(tau1eta, tau1phi, tau2eta, tau2phi);
    DeltaRTau1Lepton = DeltaR(tau1eta, tau1phi, lepEta, lepPhi);
    DeltaRTau2Lepton = DeltaR(tau2eta, tau2phi, lepEta, lepPhi);

    DeltaRTau1LeadingJet		= -99;
    DeltaRTau2LeadingJet		= -99;
    DeltaRTau1SubleadingJet		= -99;
    DeltaRTau2SubleadingJet		= -99;
    DeltaRLeptonLeadingJet		= -99;
    DeltaRLeptonSubleadingJet	= -99;
    LeadingJetSubleadingJetMass	= -99;

    bool foundLeadingJet = false;
    for(unsigned int j = 0; j < iEvent->J_Pt->size(); j++){
        float pt	= iEvent->J_Pt->at(j);
        float eta	= iEvent->J_Eta->at(j);
        float phi	= iEvent->J_Phi->at(j);
        TLorentzVector leadingJet(0,0,0,0); TLorentzVector subleadingJet(0,0,0,0);
        if(DeltaR(eta, phi, tau1eta, tau1phi) < 0.25 || DeltaR(eta, phi, tau2eta, tau2phi) < 0.25 || DeltaR(eta, phi, lepEta, lepPhi) < 0.25){ continue; }
        if(!foundLeadingJet){ // Fill leading jet
            DeltaRTau1LeadingJet		= DeltaR(eta, phi, tau1eta, tau1phi);
            DeltaRTau2LeadingJet		= DeltaR(eta, phi, tau2eta, tau2phi);
            DeltaRLeptonLeadingJet		= DeltaR(eta, phi, lepEta, lepPhi);
            leadingJet.SetPtEtaPhiM(pt, eta, phi, 0);
            foundLeadingJet = true;
        }else{ // Fill subleading jet
            DeltaRTau1SubleadingJet		= DeltaR(eta, phi, tau1eta, tau1phi);
            DeltaRTau2SubleadingJet		= DeltaR(eta, phi, tau2eta, tau2phi);
            DeltaRLeptonSubleadingJet	= DeltaR(eta, phi, lepEta, lepPhi);
            subleadingJet.SetPtEtaPhiM(pt, eta, phi, 0);
            LeadingJetSubleadingJetMass = (leadingJet + subleadingJet).M();
            break;
        }
    }

    return tmvaReader->EvaluateMVA(TString(params.find("MVAmethod")->second + " method"));
}

template<typename T>
void
TTL_TMVAEvaluator::AddVariable(TMVA::Factory *factory, const string& name, const char& type, T& var)
{
    factory->AddVariable(name, type);
}

template<typename T>
void
TTL_TMVAEvaluator::AddVariable(TMVA::Reader *reader, const string& name, const char& type, T& var)
{
    reader->AddVariable(name, &var);
}
