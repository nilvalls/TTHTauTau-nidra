//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun  7 03:28:02 2011 by ROOT version 5.27/06b
// from TTree HMTTree/TauTauTree
// found on file: ditau_nTuple.root
//////////////////////////////////////////////////////////

#ifndef TTAnalyzer_h
#define TTAnalyzer_h

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
#include "TMVAEvaluator.h"

using namespace std;

class TTAnalyzer {

	private:
		map<string,string>		params;
		vector<pair<int,int> >	goodEventsForSignal;
		vector<pair<int,int> >	goodEventsForQCD;
		bool					isSignal;
		bool					isMC;
	
		#include "clarity/cuts_declarations.h"
		CutFlow					cutFlow;
		TMVAEvaluator*			tmvaEvaluator;

	public:
		DitauBranches*			event;
		TTAnalyzer();
		TTAnalyzer(map<string,string> const &);
		virtual ~TTAnalyzer();

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
