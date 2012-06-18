//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun  7 03:28:02 2011 by ROOT version 5.27/06b
// from TTree HMTTree/TauTauTree
// found on file: ditau_nTuple.root
//////////////////////////////////////////////////////////

#ifndef Stamper_h
#define Stamper_h

#include "Plotter.h"
#include "THStack.h"
#include "TCanvas.h"
#include "TSystem.h"

using namespace std;

class Stamper : public Plotter {

	public:
		Stamper(map<string,string> const &);
		virtual ~Stamper();
		void MakePlots(ProPack *) ;

	private: 
		map<string,string> params;

		TLegend*		GetLegend(Process const *, Process const *);
		double const	GetMaximum(ProPack const *, string const, bool const) const;
		double const	GetMaximum(ProPack const *, string const) const;
		double const	GetMaximumWithError(ProPack const *, string const) const;

};

#endif










