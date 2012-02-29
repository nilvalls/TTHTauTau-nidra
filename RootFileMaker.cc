
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

	iProPack->Write((params.find("propack_name")->second).c_str());

	file->Close();

	delete file;
}



