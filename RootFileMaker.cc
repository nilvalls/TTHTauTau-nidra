
#define RootFileMaker_cxx
#include "RootFileMaker.h"

using namespace std;

RootFileMaker::RootFileMaker(){}

RootFileMaker::RootFileMaker(map<string,string> const & iParams){
	params = iParams;
}

RootFileMaker::~RootFileMaker(){}

void RootFileMaker::MakeFile(ProPack* iProPack, string iOutputFile){

	TFile* file = new TFile(iOutputFile.c_str(), "RECREATE");
	file->cd();

	iProPack->Write((params["propack_name"]).c_str());

	file->Close();

	delete file;
}



