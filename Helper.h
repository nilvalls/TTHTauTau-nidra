#ifndef _HELPER_h
#define _HELPER_h

#include "math.h"
#include "TLorentzVector.h"

inline float const DeltaR(const float iPhi1, const float iEta1, const float iPhi2, const float iEta2) { return sqrt(pow((iPhi1-iPhi2),2)+pow((iEta1-iEta2),2)); }

#endif
