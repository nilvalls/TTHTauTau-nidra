/*
    Author:			Nil Valls <nil.valls@cern.ch>, Matthias Wolf <matthias.wolf@cern.ch>
    Date:			11 Jun 2011
    Description:	TMVA evaluating class
    Notes:

*/

#include <fstream>

#include "TLorentzVector.h"
#include "TMVA/Config.h"

#include "../Helper.h"
#include "GenHelper.h"
#include "TMVAEvaluator.h"

using namespace std;

TTL_TMVAEvaluator* TTL_TMVAEvaluator::gMVA = 0;

TTL_TMVAEvaluator::~TTL_TMVAEvaluator()
{
    delete tmvaReader;
}

TTL_TMVAEvaluator::TTL_TMVAEvaluator(const std::string& dir, const std::string& mthd,
        const std::string& opts, const std::vector<std::string>& vars) :
    want_csr(true),
    basedir(dir),
    variables(vars),
    method(mthd),
    method_options(opts)
{
    tmvaReader = new TMVA::Reader( "!Color:Silent:!V" );

    log_filename = basedir + "/tmva.log";
    output_filename = basedir + "/tmva.root";
    sample_filename = basedir + "/sample.root";
    weight_filename = basedir + "/TMVAClassification_" + method + ".weights.xml";

    SetupVariables(tmvaReader);
}

template<typename T> void
TTL_TMVAEvaluator::SetupVariables(T* obj)
{
    AddVariableConditionally(obj, "CSR", 'F', csr);
    AddVariableConditionally(obj, "HT", 'F', HT);
    AddVariableConditionally(obj, "Tau1Pt", 'F', Tau1Pt);
    AddVariableConditionally(obj, "Tau1Eta", 'F', Tau1Eta);
    AddVariableConditionally(obj, "Tau2Pt", 'F', Tau2Pt);
    AddVariableConditionally(obj, "Tau1DecayMode", 'I', Tau1DecayMode);
    AddVariableConditionally(obj, "Tau2DecayMode", 'I', Tau2DecayMode);
    AddVariableConditionally(obj, "Tau1IsolationIndex", 'I', Tau1IsolationIndex);
    AddVariableConditionally(obj, "Tau2IsolationIndex", 'I', Tau2IsolationIndex);
    AddVariableConditionally(obj, "DeltaRTau1Tau2", 'F', DeltaRTau1Tau2);
    AddVariableConditionally(obj, "DeltaRTau1Lepton", 'F', DeltaRTau1Lepton);
    AddVariableConditionally(obj, "DeltaRTau2Lepton", 'F', DeltaRTau2Lepton);
    AddVariableConditionally(obj, "DeltaRTau1LeadingJet", 'F', DeltaRTau1LeadingJet);
    AddVariableConditionally(obj, "DeltaRTau2LeadingJet", 'F', DeltaRTau2LeadingJet);
    AddVariableConditionally(obj, "DeltaRTau1SubleadingJet", 'F', DeltaRTau1SubleadingJet);
    AddVariableConditionally(obj, "DeltaRTau2SubleadingJet", 'F', DeltaRTau2SubleadingJet);
    AddVariableConditionally(obj, "DeltaRLeptonLeadingJet", 'F', DeltaRLeptonLeadingJet);
    AddVariableConditionally(obj, "DeltaRLeptonSubleadingJet", 'F', DeltaRLeptonSubleadingJet);
    AddVariableConditionally(obj, "LeadingJetSubleadingJetMass", 'F', LeadingJetSubleadingJetMass);
    AddVariableConditionally(obj, "Tau1LTPt", 'F', Tau1LTPt);
    AddVariableConditionally(obj, "Tau2LTPt", 'F', Tau2LTPt);
    AddVariableConditionally(obj, "Tau1NProngs", 'I', Tau1NProngs);
    AddVariableConditionally(obj, "Tau2NProngs", 'I', Tau2NProngs);
    AddVariableConditionally(obj, "LeadingJetPt", 'F', LeadingJetPt);
    AddVariableConditionally(obj, "SubLeadingJetPt", 'F', SubLeadingJetPt);
    AddVariableConditionally(obj, "DitauVisibleMass", 'F', DitauVisibleMass);
}

void
TTL_TMVAEvaluator::BookMVA()
{
    tmvaReader->BookMVA(method + " method", weight_filename);
}

void
TTL_TMVAEvaluator::CreateTrainingSample(const std::string& signal, const std::string& backgrounds,
        ProPack* propack)
{
    TFile outfile(sample_filename.c_str(), "RECREATE");
    outfile.cd();

    TTree* signalTree = new TTree("TreeS","TreeS");
    FillTree(signalTree, propack->GetProcess(signal));
    signalTree->Write();

    cout << "\tSignal tree contains " << signalTree->GetEntries() << " events." << endl;

    delete signalTree;

    for (const auto& bkg: Helper::SplitString(backgrounds)) {
        Process *proc = propack->GetProcess(bkg);
        string name = "TreeB_" + proc->GetShortName();

        TTree* backgroundTree = new TTree(name.c_str(), name.c_str());
        FillTree(backgroundTree, proc);
        backgroundTree->Write();

        cout << "\tBackground tree contains " << backgroundTree->GetEntries() << " events." << endl;

        delete backgroundTree;
    }
}

void
TTL_TMVAEvaluator::FillTree(TTree *tree, const Process *process)
{
    SetupVariables(tree);

    TTLBranches* event = new TTLBranches(process->GetParams(), process->GetNtuplePaths());

    vector< pair<int, int> > goodEventsForSignal = process->GetGoodEventsForSignal();
    for (unsigned int i = 0; i < goodEventsForSignal.size(); i++) {
        event->GetEntry(goodEventsForSignal.at(i).first);
        event->SetBestCombo(goodEventsForSignal.at(i).second);
        unsigned int bestCombo = event->GetBestCombo();

        FillVariables(event, bestCombo);

        tree->Fill();
    }
}

void
TTL_TMVAEvaluator::TrainMVA(const std::string& backgrounds, ProPack *propack)
{
    TMVA::gConfig().GetIONames().fWeightFileDir = basedir;

    ofstream tmp_out(log_filename);
    // streambuf* old_buf = cout.rdbuf();
    // cout.rdbuf(tmp_out.rdbuf());

    TFile outfile(output_filename.c_str(), "RECREATE");
    TMVA::Factory *factory = new TMVA::Factory("TMVAClassification", &outfile,
            "!V:Silent:Transformations=I;D;P;G,D:AnalysisType=Classification");
            //"!V:!Silent:Transformations=I;D;P;G,D:AnalysisType=Classification");

    SetupVariables(factory);

    TTree *stree;
    TFile infile(sample_filename.c_str());

    infile.GetObject("TreeS", stree);
    factory->AddSignalTree(stree, 1.);

    for (const auto& bkg: Helper::SplitString(backgrounds)) {
        TTree *btree;
        string name = "TreeB_" + bkg;
        double weight = propack->GetPContainer()->Get(bkg)->GetCrossSection();

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
    factory->BookMethod(TMVA::Types::kCFMlpANN, "CFMlpANN",
            "!H:!V:NCycles=2000:HiddenLayers=N+1,N"); // n_cycles:#nodes:#nodes:...
    factory->BookMethod(TMVA::Types::kBDT, "BDT",
            "!H:!V:NTrees=850:nEventsMin=150:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning");

    factory->TrainAllMethods();
    factory->TestAllMethods();
    factory->EvaluateAllMethods();

    delete factory;

    // cout.rdbuf(old_buf);
}

void
TTL_TMVAEvaluator::FillVariables(TTLBranches *event, const int combo)
{
    try {
        if (want_csr) {
            csr = event->GetComboSelectorResponse(combo);
        } else {
            csr = 0.;
        }
    } catch (...) {
        csr = 0.;
    }
    HT = event->TTL_HT->at(combo);
    Tau1Pt = event->TTL_Tau1Pt->at(combo);
    Tau1Eta = event->TTL_Tau1Eta->at(combo);
    Tau2Pt = event->TTL_Tau2Pt->at(combo);
    Tau1DecayMode = event->TTL_Tau1DecayMode->at(combo);
    Tau2DecayMode = event->TTL_Tau2DecayMode->at(combo);
    Tau1IsolationIndex = event->GetTau1IsolationIndex(combo);
    Tau2IsolationIndex = event->GetTau2IsolationIndex(combo);
    Tau1LTPt = event->TTL_Tau1LTPt->at(combo);
    Tau2LTPt = event->TTL_Tau2LTPt->at(combo);
    Tau1NProngs = event->TTL_Tau1NProngs->at(combo);
    Tau2NProngs = event->TTL_Tau2NProngs->at(combo);
    DitauVisibleMass = event->TTL_DitauVisibleMass->at(combo);

    // Leading and subleading jets are not always present!
    LeadingJetPt = 0.;
    SubLeadingJetPt = 0.;
    try {
        LeadingJetPt = event->J_Pt->at(event->GetJetIndex(combo, 0));
        SubLeadingJetPt = event->J_Pt->at(event->GetJetIndex(combo, 1));
    } catch (...) {
        // std::cerr << combo << "\t" << event->J_Pt->size() << endl;
    }

    float tau1eta	= event->TTL_Tau1Eta->at(combo);
    float tau1phi	= event->TTL_Tau1Phi->at(combo);
    float tau2eta	= event->TTL_Tau2Eta->at(combo);
    float tau2phi	= event->TTL_Tau2Phi->at(combo);
    float lepEta	= event->TTL_LeptonEta->at(combo);
    float lepPhi	= event->TTL_LeptonPhi->at(combo);

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
    for(unsigned int j = 0; j < event->J_Pt->size(); j++){
        float pt	= event->J_Pt->at(j);
        float eta	= event->J_Eta->at(j);
        float phi	= event->J_Phi->at(j);
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
}

float
TTL_TMVAEvaluator::Evaluate(TTLBranches* event, int combo)
{
    FillVariables(event, combo);
    return tmvaReader->EvaluateMVA(method + " method");
}

template<typename W, typename T>
void
TTL_TMVAEvaluator::AddVariableConditionally(W* obj, const string& name, const char& type, T& var)
{
    // FIXME should actually be the other way around:  go through variables
    // and add them
    if (find(variables.begin(), variables.end(), name) != variables.end())
        AddVariable(obj, name, type, var);
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

template<typename T>
void
TTL_TMVAEvaluator::AddVariable(TTree *tree, const string& name, const char& type, T& var)
{
    tree->Branch(name.c_str(), &var);
}
