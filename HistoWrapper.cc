
#define HistoWrapper_cxx
#include "HistoWrapper.h"

using namespace std;



// Default constructor
HistoWrapper::HistoWrapper(){
	
	test = NULL;
	histo1F = NULL;
	histo2F = NULL;

	a = 5;
}


// Default destructor
HistoWrapper::~HistoWrapper(){
}

int HistoWrapper::GetNum(){
	return a;
}

ClassImp(HistoWrapper)
