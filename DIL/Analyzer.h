//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun  7 03:28:02 2011 by ROOT version 5.27/06b
// from TTree HMTTree/TauTauTree
// found on file: ditau_nTuple.root
//////////////////////////////////////////////////////////

#ifndef DILAnalyzer_h
#define DILAnalyzer_h

#include "../Analyzer.h"
#include "Branches.h"

using namespace std;

class DILAnalyzer : public Analyzer {


	public:
		explicit DILAnalyzer(map<string,string> const &);
		virtual ~DILAnalyzer();


	private:
		void 					Reset();
		pair<double,double>		Loop(Branches*);
		pair<bool,bool>			ComboPassesCuts(DILBranches*, unsigned int);


	private:
		#include "Cuts_declarations.h"


};

#endif
