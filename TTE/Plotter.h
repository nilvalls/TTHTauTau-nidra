//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun  7 03:28:02 2011 by ROOT version 5.27/06b
// from TTree HMTTree/TauTauTree
// found on file: ditau_nTuple.root
//////////////////////////////////////////////////////////

#ifndef TTEPlotter_h
#define TTEPlotter_h

#include "Branches.h"
#include "../Plotter.h"

using namespace std;

class TTEPlotter : public Plotter {

	public:
		TTEPlotter(map<string,string> const &);
		~TTEPlotter();

	protected:

	private:
		void	FillHistos(HContainer*, Branches*, bool const, Trigger const *, weightCounter *);

};

#endif










