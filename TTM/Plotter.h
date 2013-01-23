//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun  7 03:28:02 2011 by ROOT version 5.27/06b
// from TTree HMTTree/TauTauTree
// found on file: ditau_nTuple.root
//////////////////////////////////////////////////////////

#ifndef TTMPlotter_h
#define TTMPlotter_h

#include "Branches.h"
#include "GenHelper.h"
#include "../Plotter.h"

using namespace std;

class TTMPlotter : public Plotter {

	public:
		TTMPlotter(map<string,string> const &);
		~TTMPlotter();

	protected:

	private:
		void	FillHistos(HContainer*, Branches*, bool const, Trigger const *, weightCounter *);

};

#endif










