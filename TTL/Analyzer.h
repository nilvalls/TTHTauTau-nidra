#ifndef TTLAnalyzer_h
#define TTLAnalyzer_h

#include "../Analyzer.h"
#include "Branches.h"
#include "TMVAEvaluator.h"
#include "ComboSelector.h"
//#include "GenHelper.h"

using namespace std;

class TTLAnalyzer : public Analyzer {


	public:
		explicit TTLAnalyzer(map<string,string> const &);
		virtual ~TTLAnalyzer();
		vector<unsigned int> GetComboVector(Branches*);


	private:
		TTL_TMVAEvaluator*		mva;
		TTL_ComboSelector*		comboSelector;
		void 					Reset();
		pair<double,double>		Loop(Branches*, Process const &, const bool iTrainComboSelectorSampler=false);
		pair<bool,bool>			ComboPassesCuts(TTLBranches*, unsigned int);


	private:
		#include "Cuts_declarations.h"


};

#endif
