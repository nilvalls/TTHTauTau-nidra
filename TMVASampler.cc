/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			11 Jun 2011
    Description:	Plot stacking class.
    Notes:

*/

#include "TMVASampler.h"

#define TMVASampler_cxx
using namespace std;

// Default constructor
TMVASampler::TMVASampler(){
	file = NULL;
	proPack = NULL;
}

// Default destructor
TMVASampler::~TMVASampler(){
	if(file!=NULL){ file->Close(); }
	delete file; file = NULL;
	delete proPack; proPack = NULL;
}

TMVASampler::TMVASampler(map<string,string>const & iParams){
	params = iParams;
	Long_t *id,*size,*flags,*mt; id=NULL; size=NULL;flags=NULL;mt=NULL;
	bool badFile = gSystem->GetPathInfo((params["process_file"]).c_str(),id,size,flags,mt);
	if(badFile){ cerr << "ERROR: trying to make TMVA training sample but proPack file does not exist. Please run the event analysis first" << endl; exit(1); }

	file = new TFile((params["process_file"]).c_str(), "READ");
	file->cd();

	proPack = (ProPack*)file->Get((params["propack_name"]).c_str());
}


void TMVASampler::MakeTrainingSample(){
	ProPack* iProPack = proPack;
    string outputName = params["MVAinput"];
	string signalName = iProPack->GetProcess(params.find("MVAsignal")->second)->GetShortName();

	TFile* output = new TFile(outputName.c_str(), "RECREATE");
    output->cd();

	// Signal
	TTree* signalTree = new TTree("TreeS","TreeS");
	FillTree(signalTree, iProPack->GetProcess(signalName));
	output->cd();
	signalTree->Write();
	cout << "\tSignal tree contains " << signalTree->GetEntries() << " events." << endl;
	delete signalTree;

    for (const auto& bkg: Helper::SplitString(params["MVAbackground"])) {
        Process *proc = iProPack->GetProcess(bkg);
        string name = "TreeB_" + proc->GetShortName();
        // Background
        TTree* backgroundTree = new TTree(name.c_str(), name.c_str());
        FillTree(backgroundTree, proc);
        output->cd();
        backgroundTree->Write();
        cout << "\tBackground tree contains " << backgroundTree->GetEntries() << " events." << endl;
        delete backgroundTree;
    }

	output->Close();
	cout << "\n\tTMVA training sample: " << outputName << endl;

}

void TMVASampler::FillTree(TTree* iTree, Process const * iProcess){
	cerr << "Calling FillTree(...) from " << __FILE__ << " is not allowed. It must be called from a derived class." << endl; exit(1);
}

