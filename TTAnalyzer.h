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
#include "Analyzer.h"

using namespace std;

class TTAnalyzer : public Analyzer {

	private:

	public:
		explicit TTAnalyzer(map<string,string> const &);
		virtual ~TTAnalyzer();

		DitauBranches const *	GetDitauBranches(double) const;
		void					Reset();
		pair<double,double>		Loop();
		pair<bool,bool>			ComboPassesCuts(unsigned int);
		void					SetCutsToApply(string);

	private:


};

#endif
