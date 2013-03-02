#ifndef _HELPER_h
#define _HELPER_h

#include "math.h"
#include "TLorentzVector.h"

inline float const NormalizedPhi(const float iPhi){
	float result = iPhi;
	while ( result < -M_PI ){ result += 2*M_PI; }
	while ( result >  M_PI ){ result -= 2*M_PI; }
	return result;
}

inline float const DeltaR(const float iEta1, const float iPhi1, const float iEta2, const float iPhi2) { return sqrt(pow((iEta1-iEta2),2) + pow(NormalizedPhi(iPhi1-iPhi2),2)); }


#endif
