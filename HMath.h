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

		HWrapper const & Integrated(HWrapper const &, bool const) const;
		TH1F const & Integrated(TH1F const &, bool const) const;

		HWrapper const & IntegratedFromLeft (HWrapper const &) const;
		HWrapper const & IntegratedFromRight(HWrapper const &) const;

		TH1F const & IntegratedFromLeft (TH1F const &) const;
		TH1F const & IntegratedFromRight(TH1F const &) const;

		TH1F const & StoRootB(TH1F const &, TH1F const &) const;
		TH1F const & RightIntegratedStoRootB(TH1F const &, TH1F const &) const;
		TH1F const & LeftIntegratedStoRootB(TH1F const &, TH1F const &) const;
		//*/

		ClassDef(HMath, 1);
};

#endif
