
#define RootFileMaker_cxx
#include "RootFileMaker.h"

using namespace std;

RootFileMaker::RootFileMaker(){}

RootFileMaker::~RootFileMaker(){}

void RootFileMaker::MakeFile(TopoPack* iTopologies, string iOutputFile){

	TFile* file = new TFile(iOutputFile.c_str(), "RECREATE");
	file->cd();

	TTree *tree = new TTree("nidraTree","nidraTree");

	tree->Branch("topologies","TopoPack", &iTopologies);

	tree->Fill();
	tree->Write();
	file->Close();

}



