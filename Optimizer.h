#ifndef Optimizer_h
#define Optimizer_h

#include "Plotter.h"
#include "Process.h"
#include "ProPack.h"
#include "TCanvas.h"
#include "TSystem.h"

#include "TH1F.h"
#include "HMath.h"

using namespace std;

class Optimizer : public Plotter {

	public:
		Optimizer(map<string,string> const &);
		virtual ~Optimizer();

	private: 
		map<string,string> params;
		void MakePlots(ProPack *);
		void MakeLeftIntegratedSoverB(Process const *, Process const *);
		void MakeRightIntegratedSoverB(Process const *, Process const *);
		void MakeIntegratedSoverB(Process const *, Process const *, int);
//		void MakeSoverB(Process const *, Process const *);
		void Overlap2D(Process const *, Process const *);


};

#endif










