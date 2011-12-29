
#define PUcorrector_cxx
#include "PUcorrector.h"

using namespace std;



// Default constructor
PUcorrector::PUcorrector(){}

// Copy constructor
PUcorrector::PUcorrector(PUcorrector const & iPUcorrector){
}

// Default destructor
PUcorrector::~PUcorrector(){}

// Return the trigger weight given the pT
float const PUcorrector::GetWeight(float const iNumPV) const{
	float result = 1;

//	if(iNumPV>24){ return 0; }
//	else{ result = weight[iNumPV]; }

	return result;
}

