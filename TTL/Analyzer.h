#ifndef TTLAnalyzer_h
#define TTLAnalyzer_h

#include "../Analyzer.h"
#include "Branches.h"
#include "TMVAEvaluator.h"
//#include "GenHelper.h"

using namespace std;

class TTLAnalyzer : public Analyzer {


	public:
		explicit TTLAnalyzer(map<string,string> const &);
		virtual ~TTLAnalyzer();


	private:
		TTL_TMVAEvaluator*		mva;
		void 					Reset();
		pair<double,double>		Loop(Branches*);
		pair<bool,bool>			ComboPassesCuts(TTLBranches*, unsigned int);


	private:
		#include "Cuts_declarations.h"


};

#endif
