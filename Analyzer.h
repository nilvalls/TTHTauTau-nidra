//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun  7 03:28:02 2011 by ROOT version 5.27/06b
// from TTree HMTTree/TauTauTree
// found on file: ditau_nTuple.root
//////////////////////////////////////////////////////////

#ifndef Analyzer_h
#define Analyzer_h

#include "TChain.h"

#include "configParser/config.h"

#include "TTree.h"

#include "Trigger.h"
#include "PUcorrector.h"
#include "HWrapper.h"
#include "DitauBranches.h"
#include "CutFlow.h"
#include "Process.h"
#include "ProPack.h"

using namespace std;

class Analyzer {

	private:
		map<string,string>		params;
		TChain*          		fChain;
		Int_t           		fCurrent;
		Trigger*				tauTrigger;
		vector<pair<int,int> >	goodEventsForSignal;
		vector<pair<int,int> >	goodEventsForQCD;
		DitauBranches*			event;
		PUcorrector*			puCorrector;
	
		#include "clarity/cuts.h"
		CutFlow						cutFlow;

		bool applyPUreweighing;
		bool applyTrigger;

		double GetPUweight(int);
		double GetTau1TriggerWeight(int);
		double GetTau2TriggerWeight(int);

	public:
		Analyzer();
		Analyzer(map<string,string> const &);
		virtual ~Analyzer();

		void					Analyze(Process&);
		void					Analyze(vector<Process>&);
		void					AnalyzeAll(ProPack&);
		DitauBranches const *	GetDitauBranches(double) const;
		void					Reset();
		pair<double,double>		Loop();
		void					Init(string);
		Long64_t				LoadTree(Long64_t entry);
		TChain*					GetTChain(string);
		pair<bool,bool>			ComboPassesCuts(unsigned int);
		void					SetCutsToApply(string);
		bool					ApplyThisCut(string);
		bool					IsFlagThere(string);


};

#endif
