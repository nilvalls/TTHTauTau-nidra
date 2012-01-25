//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun  7 03:28:02 2011 by ROOT version 5.27/06b
// from TTree HMTTree/TauTauTree
// found on file: ditau_nTuple.root
//////////////////////////////////////////////////////////

#ifndef Analyzer_h
#define Analyzer_h

#include "TROOT.h"
#include "TFile.h"
#include "TChain.h"
#include "configParser/config.h"
#include "HWrapper.h"
#include "DitauBranches.h"
#include "CutFlow.h"
#include "Process.h"
#include "PContainer.h"
#include "ProPack.h"

using namespace std;

class Analyzer {

	private:
		map<string,string>		params;
		vector<pair<int,int> >	goodEventsForSignal;
		vector<pair<int,int> >	goodEventsForQCD;
	
		#include "clarity/cuts.h"
		CutFlow					cutFlow;

	public:
		DitauBranches*			event;
		Analyzer();
		Analyzer(map<string,string> const &);
		virtual ~Analyzer();

		void					Analyze(Process&);
		void					Analyze(vector<Process>&);
		void					AnalyzeAll(ProPack&);
		DitauBranches const *	GetDitauBranches(double) const;
		void					Reset();
		pair<double,double>		Loop();
		pair<bool,bool>			ComboPassesCuts(unsigned int);
		void					SetCutsToApply(string);
		bool					ApplyThisCut(string);
		bool					IsFlagThere(string);


};

#endif
