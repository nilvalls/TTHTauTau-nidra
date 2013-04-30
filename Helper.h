#ifndef _HELPER_h
#define _HELPER_h

#include <cmath>
#include <string>
#include <vector>

#include "TLorentzVector.h"

inline float const NormalizedPhi(const float& iPhi){
	float result = iPhi;
	while ( result < -M_PI ){ result += 2*M_PI; }
	while ( result >  M_PI ){ result -= 2*M_PI; }
	return result;
}

inline float
DeltaRSquared(const float& eta1, const float& phi1, const float& eta2, const float& phi2)
{
    float p = NormalizedPhi(phi1 - phi2);
    return (eta1 - eta2) * (eta1 - eta2) + p * p;
}

inline float
DeltaR(const float& eta1, const float& phi1, const float& eta2, const float& phi2)
{
    return std::sqrt(DeltaRSquared(eta1, phi1, eta2, phi2));
}

// remove this when porting to JSON
namespace Helper {
   std::vector<std::string> SplitString(const std::string&);
}

#endif
