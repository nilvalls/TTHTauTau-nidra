//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun  7 03:28:02 2011 by ROOT version 5.27/06b
// from TTree HMTTree/TauTauTree
// found on file: ditau_nTuple.root
//////////////////////////////////////////////////////////

#ifndef Optimizer_h
#define Optimizer_h

#include "Plotter.h"
#include "THStack.h"
#include "TCanvas.h"
#include "TSystem.h"

#include "HMath.h"

using namespace std;

//struct TH1pair{
//	TH1* fromLeft;
//	TH1* fromRight;
//};

class Optimizer : public Plotter {

	public:
		Optimizer(map<string,string>*);
		virtual ~Optimizer();
//		void MakePlots(ProPack*, int iIntegral=0);

	private: 
	/*
		map<string,string> params;

		TH1*			collisions;
		vector<TH1*>*	backgrounds;
		vector<TH1*>*	signals;
		THStack*		stack;

	//	TLegend*	GetLegend(ProPack*);
		TH1*		GetSoSSB(TH1*, TH1*, int iIntegral = 0);

//*/

};

#endif










