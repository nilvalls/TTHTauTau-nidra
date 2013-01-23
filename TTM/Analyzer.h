//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun  7 03:28:02 2011 by ROOT version 5.27/06b
// from TTree HMTTree/TauTauTree
// found on file: ditau_nTuple.root
//////////////////////////////////////////////////////////

#ifndef TTMAnalyzer_h
#define TTMAnalyzer_h

#include "../Analyzer.h"
#include "Branches.h"
#include "GenHelper.h"

using namespace std;

class TTMAnalyzer : public Analyzer {


	public:
		explicit TTMAnalyzer(map<string,string> const &);
		virtual ~TTMAnalyzer();


	private:
		void 					Reset();
		pair<double,double>		Loop(Branches*);
		pair<bool,bool>			ComboPassesCuts(TTMBranches*, unsigned int);


	private:
		#include "Cuts_declarations.h"


};

#endif
