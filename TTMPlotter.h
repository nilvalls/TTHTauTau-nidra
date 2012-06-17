//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun  7 03:28:02 2011 by ROOT version 5.27/06b
// from TTree HMTTree/TauTauTree
// found on file: ditau_nTuple.root
//////////////////////////////////////////////////////////

#ifndef TTMPlotter_h
#define TTMPlotter_h

#include "Plotter.h"

using namespace std;

class TTMPlotter : public Plotter {

	public:
		TTMPlotter(map<string,string> const &);
		~TTMPlotter();

	protected:
		virtual void	FillHistos(HContainer*, DitauBranches*, bool const, Trigger const *, PUcorrector const *, weightCounter *);

};

#endif










