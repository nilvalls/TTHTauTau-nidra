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

using namespace std;

class Stacker : public Plotter {

	public:
		Stacker(map<string,string>*);
		virtual ~Stacker();
		void MakePlots(TopoPack*);

	private: 
		TH1*			collisions;
		vector<TH1*>*	backgrounds;
		vector<TH1*>*	signals;
		THStack*		stack;

		THStack* MakeStack(vector<TH1*>*);
		

};

#endif










