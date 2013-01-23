//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun  7 03:28:02 2011 by ROOT version 5.27/06b
// from TTree HMTTree/TauTauTree
// found on file: ditau_nTuple.root
//////////////////////////////////////////////////////////

#ifndef DILPlotter_h
#define DILPlotter_h

#include "Branches.h"
#include "../Plotter.h"

using namespace std;

class DILPlotter : public Plotter {

	public:
		DILPlotter(map<string,string> const &);
		~DILPlotter();

	protected:

	private:
		void	FillHistos(HContainer*, Branches*, bool const, Trigger const *, weightCounter *);

};

#endif










