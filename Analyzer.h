//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun  7 03:28:02 2011 by ROOT version 5.27/06b
// from TTree HMTTree/TauTauTree
// found on file: ditau_nTuple.root
//////////////////////////////////////////////////////////

#ifndef Analyzer_h
#define Analyzer_h

#include <typeinfo>
#include "TROOT.h"
#include "TFile.h"
#include "TChain.h"
#include "configParser/config.h"
#include "Helper.h"
#include "HWrapper.h"
#include "Branches.h"
#include "CutFlow.h"
#include "Process.h"
#include "PContainer.h"
#include "ProPack.h"

#include "TTM/Branches.h"
#include "TTE/Branches.h"

using namespace std;

class Analyzer {

	private:
	
	protected:
		bool					isBaseAnalyzer;
		map<string,string>		params;
		vector<pair<int,int> >	goodEventsForSignal;
		vector<pair<int,int> >	goodEventsForQCD;
		CutFlow					cutFlow;
		bool					isSignal;
		bool					checkReality;
		bool					isMC;

	public:
		Analyzer();
		Analyzer(map<string,string> const &);
		virtual ~Analyzer();
		void	AnalyzeAll(ProPack&);


	protected:
		void	Analyze(Process&);
		void	Analyze(vector<Process>&);
		void	Reset();
		bool	ApplyThisCut(string);
		bool	IsFlagThere(string);
		virtual pair<double,double>		Loop(Branches*);
		virtual pair<bool,bool>			ComboPassesCuts(Branches*, unsigned int);

	private:



};

#endif
