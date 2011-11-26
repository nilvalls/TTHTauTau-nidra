
#define HistoWrapper_cxx
#include "HistoWrapper.h"

using namespace std;



// Default constructor
HistoWrapper::HistoWrapper(){ histo = NULL; }

HistoWrapper::HistoWrapper(string iName, string iType, Config* iConfig){
	if(iType.compare("th1f") == 0){	histo = new TH1F(iName.c_str(), iName.c_str(),100,0,100); }
	else if(iType.compare("th2f") == 0){ histo = new TH2F(iName.c_str(), iName.c_str(),100,0,100,100,0,100); }
}

// Default destructor
HistoWrapper::~HistoWrapper(){}

TH1* HistoWrapper::GetHisto(){
	return histo;
}

void HistoWrapper::SetHisto(TH1* iHisto){
	histo = (TH1*)iHisto->Clone();
}

HistoWrapper* HistoWrapper::Clone(){
	HistoWrapper* result = new HistoWrapper(*this);
	result->SetHisto(histo);
	return result;
}

ClassImp(HistoWrapper)
