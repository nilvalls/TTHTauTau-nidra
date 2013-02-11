#ifndef TTMAnalyzer_h
#define TTMAnalyzer_h

#include "../Analyzer.h"
#include "Branches.h"
#include "TMVAEvaluator.h"
//#include "GenHelper.h"

using namespace std;

class TTMAnalyzer : public Analyzer {


	public:
		explicit TTMAnalyzer(map<string,string> const &);
		virtual ~TTMAnalyzer();


	private:
		TTM_TMVAEvaluator*		mva;
		void 					Reset();
		pair<double,double>		Loop(Branches*);
		pair<bool,bool>			ComboPassesCuts(TTMBranches*, unsigned int);


	private:
		#include "Cuts_declarations.h"


};

#endif
