#ifndef HMath_h
#define HMath_h

#include <iostream>
#include <utility>
#include "HWrapper.h"
#include "TH1F.h"

using namespace std;

class HMath{
	public:
		HMath();
		HMath(HMath const &);
		~HMath();

		HWrapper  * Integrated(HWrapper  *, bool ) ;
		TH1F  * Integrated(TH1F* , bool ) ;

		HWrapper  * IntegratedFromLeft (HWrapper  *) ;
		HWrapper  * IntegratedFromRight(HWrapper  *) ;

		TH1F  * IntegratedFromLeft (TH1F  *) ;
		TH1F  * IntegratedFromRight(TH1F  *) ;

		TH1F * StoRootB(TH1F  *, TH1F  *) ;
		TH1F  * RightIntegratedStoRootB(TH1F  *, TH1F  *) ;
		TH1F  * LeftIntegratedStoRootB(TH1F  *, TH1F  *) ;

};

#endif
