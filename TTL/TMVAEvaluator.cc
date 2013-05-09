/*
    Author:			Nil Valls <nil.valls@cern.ch>, Matthias Wolf <matthias.wolf@cern.ch>
    Date:			11 Jun 2011
    Description:	TMVA evaluating class
    Notes:

*/

#include <fstream>

#include "boost/filesystem/operations.hpp"

#include "TLorentzVector.h"
#include "TMVA/Config.h"

#include "../Helper.h"
#include "GenHelper.h"
#include "TMVAEvaluator.h"

using namespace std;

map<string, TTL_TMVAEvaluator*> TTL_TMVAEvaluator::gMVA;
map<string, TTL_TMVAEvaluator*> TTL_TMVAEvaluator::gComboMVA;

TTL_TMVAEvaluator::~TTL_TMVAEvaluator()
{
    delete reader;
}

TTL_TMVAEvaluator::TTL_TMVAEvaluator(const std::string& dir,
        const std::vector<std::string>& vars, const int rnk) :
    basedir(dir),
    method(),
    variables(vars),
    rank(rnk)
{
    reader = new TMVA::Reader( "!Color:Silent:!V" );

    log_filename = basedir + "/tmva.log";
    output_filename = basedir + "/tmva.root";
    sample_filename = basedir + "/sample.root";

    SetupVariables(reader);
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
    AddVariableConditionally(obj, "Tau1IsolationIndexMVA2", 'I', Tau1IsolationIndexMVA2);
    AddVariableConditionally(obj, "Tau1IsolationMVA2Raw", 'F', Tau1IsolationMVA2Raw);
    AddVariableConditionally(obj, "Tau2IsolationIndex", 'I', Tau2IsolationIndex);
    AddVariableConditionally(obj, "Tau2IsolationIndexMVA2", 'I', Tau2IsolationIndexMVA2);
    AddVariableConditionally(obj, "Tau2IsolationMVA2Raw", 'F', Tau2IsolationMVA2Raw);
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

bool
TTL_TMVAEvaluator::BookMVA(const string& method)
{
    using namespace boost::filesystem;

    this->method = method;

    string weight_filename = basedir + "/TMVAClassification_" + method + ".weights.xml";
    if (exists(path(weight_filename, &boost::filesystem::native))) {
        reader->BookMVA(method + " method", weight_filename);
        return true;
    }
    return false;
}

void
TTL_TMVAEvaluator::CreateTrainingSample(const std::string& sample,
        ProPack* propack)
{
    TFile outfile(sample_filename.c_str(), "RECREATE");
    outfile.cd();

    TTree* sig_tree = new TTree("TreeS","TreeS");
    TTree* bkg_tree = new TTree("TreeB","TreeB");
    cout << "\tSame sample MVA" << std::endl;
    FillTree(sig_tree, bkg_tree, propack->GetProcess(sample));
    sig_tree->Write();
    bkg_tree->Write();

    cout << "\tSignal tree contains " << sig_tree->GetEntries() << " events." << endl;
    cout << "\tBackground tree contains " << bkg_tree->GetEntries() << " events." << endl;
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

    this->backgrounds.clear();
    for (const auto& bkg: Helper::SplitString(backgrounds)) {
        Process *proc = propack->GetProcess(bkg);
        double weight = propack->GetPContainer()->Get(bkg)->GetCrossSection();
        string name = "TreeB_" + proc->GetShortName();

        TTree* backgroundTree = new TTree(name.c_str(), name.c_str());
        FillTree(backgroundTree, proc);
        backgroundTree->Write();

        this->backgrounds[name] = weight;

        cout << "\tBackground tree contains " << backgroundTree->GetEntries() << " events." << endl;

        delete backgroundTree;
    }
}

void
TTL_TMVAEvaluator::FillTree(TTree *tree, const Process *process)
{
    SetupVariables(tree);

    TTLBranches* event = new TTLBranches(process->GetParams(), process->GetNtuplePaths());

    auto goodEventsForSignal = process->GetGoodEventsForSignal();
    for (unsigned int i = 0; i < goodEventsForSignal.size(); i++) {
        event->GetEntry(goodEventsForSignal.at(i).entry);
        int combo = goodEventsForSignal[i].combos[0];
        FillVariables(event, combo);

        tree->Fill();
    }
}

void
TTL_TMVAEvaluator::FillTree(TTree *sig, TTree *bkg, const Process *process)
{
    SetupVariables(sig);
    SetupVariables(bkg);

    TTLBranches* event = new TTLBranches(process->GetParams(), process->GetNtuplePaths());

    auto goodEventsForSignal = process->GetGoodEventsForSignal();
    for (unsigned int i = 0; i < goodEventsForSignal.size(); i++) {
        event->GetEntry(goodEventsForSignal.at(i).entry);

        int combo = -1;
        for (const auto& c: goodEventsForSignal[i].combos) {
            if (event->IsGoodGenMatch(c)) {
                combo = c;
                break;
            }
        }

        if (combo == -1)
            continue;

        for (unsigned int i = 0; i < event->TTL_NumCombos; ++i) {
            FillVariables(event, i);

            if (int(i) == combo)
                sig->Fill();
            else
                bkg->Fill();
        }
    }

    backgrounds.clear();
    backgrounds["TreeB"] = 1.0;
}

void
TTL_TMVAEvaluator::TrainMVA(const map<string, string>& setup)
{
    TMVA::gConfig().GetIONames().fWeightFileDir = basedir;

    ofstream tmp_out(log_filename);
    // streambuf* old_buf = cout.rdbuf();
    // cout.rdbuf(tmp_out.rdbuf());

    TFile outfile(output_filename.c_str(), "UPDATE");
    TMVA::Factory *factory = new TMVA::Factory("TMVAClassification", &outfile,
            "!V:Silent:Transformations=I;D;P;G,D:AnalysisType=Classification");
            //"!V:!Silent:Transformations=I;D;P;G,D:AnalysisType=Classification");

    SetupVariables(factory);

    TTree *stree;
    TFile infile(sample_filename.c_str());

    infile.GetObject("TreeS", stree);
    factory->AddSignalTree(stree, 1.);

    for (const auto& bkg: backgrounds) {
        TTree *btree;
        infile.GetObject(bkg.first.c_str(), btree);

        if (btree->GetEntries() > 0)
            factory->AddBackgroundTree(btree, bkg.second);
        else
            cerr << "WARNING: skipping " << bkg.first << " for MVA training (no events)" << endl;
    }

    factory->PrepareTrainingAndTestTree("", "", "SplitMode=Random:NormMode=NumEvents:!V");

    // the following can be copied from TMVAClassification.C
    // factory->BookMethod(TMVA::Types::kCuts, "Cuts",
            // "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart");
    for (const auto& m: setup) {
        if (m.first.find("BDT") != string::npos)
            factory->BookMethod(TMVA::Types::kBDT, m.first, m.second);
        else if (m.first == "CFMlpANN")
            factory->BookMethod(TMVA::Types::kCFMlpANN, m.first, m.second);
        else
            cerr << "ERROR: can't train " << m.first << endl;
    }

    cerr << "TRAINING" << endl;
    factory->TrainAllMethods();
    factory->TestAllMethods();
    factory->EvaluateAllMethods();

    delete factory;

    // cout.rdbuf(old_buf);
}

void
TTL_TMVAEvaluator::FillVariables(TTLBranches *event, const int combo)
{
    if (rank > 0 && gComboMVA["BDT"]) {
        csr = gComboMVA["BDT"]->Evaluate(event, combo);
    } else {
        csr = 0.;
    }

    HT = (*event->TTL_HT)[combo];
    Tau1Pt = (*event->TTL_Tau1Pt)[combo];
    Tau1Eta = abs((*event->TTL_Tau1Eta)[combo]);
    Tau2Pt = (*event->TTL_Tau2Pt)[combo];
    Tau1DecayMode = (*event->TTL_Tau1DecayMode)[combo];
    Tau2DecayMode = (*event->TTL_Tau2DecayMode)[combo];
    Tau1IsolationIndex = event->GetTau1IsolationIndex(combo);
    Tau1IsolationIndexMVA2 = event->GetTau1IsolationIndexMVA2(combo);
    Tau1IsolationMVA2Raw = (*event->TTL_Tau1HPSbyIsolationMVA2raw)[combo];
    Tau2IsolationIndex = event->GetTau2IsolationIndex(combo);
    Tau2IsolationIndexMVA2 = event->GetTau2IsolationIndexMVA2(combo);
    Tau2IsolationMVA2Raw = (*event->TTL_Tau2HPSbyIsolationMVA2raw)[combo];
    Tau1LTPt = (*event->TTL_Tau1LTPt)[combo];
    Tau2LTPt = (*event->TTL_Tau2LTPt)[combo];
    Tau1NProngs = (*event->TTL_Tau1NProngs)[combo];
    Tau2NProngs = (*event->TTL_Tau2NProngs)[combo];
    DitauVisibleMass = (*event->TTL_DitauVisibleMass)[combo];

    // Leading and subleading jets are not always present!
    LeadingJetPt = 0.;
    SubLeadingJetPt = 0.;
    try {
        LeadingJetPt = event->J_Pt->at(event->GetJetIndex(combo, 0));
        SubLeadingJetPt = event->J_Pt->at(event->GetJetIndex(combo, 1));
    } catch (...) {
        // std::cerr << combo << "\t" << event->J_Pt->size() << endl;
    }

    float tau1eta	= (*event->TTL_Tau1Eta)[combo];
    float tau1phi	= (*event->TTL_Tau1Phi)[combo];
    float tau2eta	= (*event->TTL_Tau2Eta)[combo];
    float tau2phi	= (*event->TTL_Tau2Phi)[combo];
    float lepEta	= (*event->TTL_LeptonEta)[combo];
    float lepPhi	= (*event->TTL_LeptonPhi)[combo];

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
        float pt	= (*event->J_Pt)[j];
        float eta	= (*event->J_Eta)[j];
        float phi	= (*event->J_Phi)[j];
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
    return reader->EvaluateMVA(method + " method");
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
