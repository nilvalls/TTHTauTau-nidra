//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun  7 03:28:02 2011 by ROOT version 5.27/06b
// from TTree HMTTree/TauTauTree
// found on file: ditau_nTuple.root
//////////////////////////////////////////////////////////

#ifndef TTPlotter_h
#define TTPlotter_h

#include "Plotter.h"

using namespace std;

class TTPlotter : public Plotter {

	public:
		TTPlotter(map<string,string> const &);
		~TTPlotter();

	protected:
		virtual void	FillHistos(HContainer*, DitauBranches*, bool const, Trigger const *, PUcorrector const *, weightCounter *);

};

#endif










