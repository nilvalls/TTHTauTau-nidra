//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun  7 03:28:02 2011 by ROOT version 5.27/06b
// from TTree HMTTree/TauTauTree
// found on file: ditau_nTuple.root
//////////////////////////////////////////////////////////

#ifndef Stacker_h
#define Stacker_h

#include "Plotter.h"
#include "THStack.h"
#include "TCanvas.h"
#include "TSystem.h"

using namespace std;

class Stacker : public Plotter {

	public:
		Stacker(map<string,string> const &);
		virtual ~Stacker();
		void MakePlots(ProPack const *) ;

	private: 
		map<string,string> params;

		TLegend*		GetLegend(ProPack const *);
		THStack*		GetBackgroundStack(ProPack const *, string const) const;
		double const	GetMaximum(ProPack const *, string const, bool const) const;
		double const	GetMaximum(ProPack const *, string const) const;
		double const	GetMaximumWithError(ProPack const *, string const) const;

};

#endif










