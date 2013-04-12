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
#include "ComboSelector.h"

TTL_ComboSelector* TTL_ComboSelector::gComboMVA = 0;

using namespace std;

TTL_ComboSelector::~TTL_ComboSelector()
{
    delete tmvaReader;
}

// Constructor
TTL_ComboSelector::TTL_ComboSelector(const std::string& dir, const std::string& mthd,
        const std::string& opts, const std::vector<std::string>& vars) :
    TTL_TMVAEvaluator(dir, mthd, opts, vars)
{
    want_csr = false;
}

void
TTL_ComboSelector::InitiateTrainingSample()
{
    ofile = new TFile(sample_filename.c_str(), "RECREATE");
    ofile->cd();

    sig = new TTree("TreeS", "TreeS");
    SetupVariables(sig);
    bkg = new TTree("TreeB", "TreeB");
    SetupVariables(bkg);
}

void
TTL_ComboSelector::FinalizeTrainingSample()
{
    ofile->cd();
    sig->Write();
    bkg->Write();
    ofile->Close();

    // Don't delete trees, as they are not in memory anymore?
    // delete bkg;
    // delete sig;
    delete ofile;
}

void
TTL_ComboSelector::FillTrees(TTLBranches *event)
{
    for (unsigned int combo = 0; combo < event->TTL_Tau1Pt->size(); ++combo) {
        FillVariables(event, combo);

        if (abs(event->TTL_Tau1GenMatchId->at(combo)) == 15 &&
                abs(event->TTL_Tau2GenMatchId->at(combo)) == 15 &&
                abs(event->TTL_Tau1GenMatchMother0Id->at(combo)) == 25 &&
                abs(event->TTL_Tau2GenMatchMother0Id->at(combo)) == 25) {
            sig->Fill();
        } else {
            bkg->Fill();
        }
    }
}

void
TTL_ComboSelector::TrainMVA()
{
    TMVA::gConfig().GetIONames().fWeightFileDir = basedir;

    ofstream tmp_out(log_filename);
    streambuf* old_buf = cout.rdbuf();
    cout.rdbuf(tmp_out.rdbuf());

    TFile outfile(output_filename.c_str(), "RECREATE");
    TMVA::Factory *factory = new TMVA::Factory("TMVAClassification", &outfile,
            "!V:Silent:Transformations=I;D;P;G,D:AnalysisType=Classification");
            //"!V:!Silent:Transformations=I;D;P;G,D:AnalysisType=Classification");

    SetupVariables(factory);

    TTree *stree;
    TFile infile(sample_filename.c_str());

    infile.GetObject("TreeS", stree);
    factory->AddSignalTree(stree, 1.);

    TTree *btree;
    infile.GetObject("TreeB", btree);
    factory->AddBackgroundTree(btree, 1.);

    factory->PrepareTrainingAndTestTree("", "", "SplitMode=Random:NormMode=NumEvents:!V");
    factory->PrepareTrainingAndTestTree("", "", "SplitMode=Random:NormMode=NumEvents:!V");

    // the following can be copied from TMVAClassification.C
    // factory->BookMethod(TMVA::Types::kCuts, "Cuts",
            // "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart");
    // factory->BookMethod(TMVA::Types::kCFMlpANN, "CFMlpANN",
            // "!H:!V:NCycles=2000:HiddenLayers=N+1,N"); // n_cycles:#nodes:#nodes:...
    factory->BookMethod(TMVA::Types::kBDT, "BDT",
            "!H:!V:NTrees=850:nEventsMin=150:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning");

    factory->TrainAllMethods();
    factory->TestAllMethods();
    factory->EvaluateAllMethods();

    delete factory;

    cout.rdbuf(old_buf);
}

multimap<double, unsigned int> TTL_ComboSelector::GetSortedCombosByPt(Branches* iEvent){
    multimap<double, unsigned int> result;
    TTLBranches* event = (TTLBranches*)iEvent;

    for (unsigned int combo = event->TTL_NumCombos; combo --> 0; ){ 
        result.insert(pair<double, unsigned int>(0, combo));
    }

    return result;
}

multimap<double, unsigned int> TTL_ComboSelector::GetSortedCombos(Branches* iEvent){
    multimap<double, unsigned int> result;
    TTLBranches* event = (TTLBranches*)iEvent;

    for (unsigned int combo = 0; combo < event->TTL_NumCombos; combo++){ 
        double response = Evaluate(event, combo);
        result.insert(pair<double, unsigned int>(response, combo));
    }

    return result;
}
