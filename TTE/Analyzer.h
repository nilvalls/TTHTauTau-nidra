//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun  7 03:28:02 2011 by ROOT version 5.27/06b
// from TTree HMTTree/TauTauTree
// found on file: ditau_nTuple.root
//////////////////////////////////////////////////////////

#ifndef TTEAnalyzer_h
#define TTEAnalyzer_h

#include "../Analyzer.h"
#include "Branches.h"
#include "TMVAEvaluator.h"
#include "GenHelper.h"

using namespace std;

class TTEAnalyzer : public Analyzer {


	public:
		explicit TTEAnalyzer(map<string,string> const &);
		virtual ~TTEAnalyzer();


	private:
		TTE_TMVAEvaluator*		mva;
		void 					Reset();
		pair<double,double>		Loop(Branches*);
		pair<bool,bool>			ComboPassesCuts(TTEBranches*, unsigned int);


	private:
		#include "Cuts_declarations.h"


};

#endif
