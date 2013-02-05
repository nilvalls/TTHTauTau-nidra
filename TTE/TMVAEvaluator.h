#ifndef TTE_TMVAEvaluator_h
#define TTE_TMVAEvaluator_h

#include "Branches.h"
#include "TMVA/Reader.h"
//#include "TMVA/Tools.h"

using namespace std;

class TTE_TMVAEvaluator {

	public:
		TTE_TMVAEvaluator(map<string,string> const &);
		virtual ~TTE_TMVAEvaluator();

		float Evaluate(TTEBranches const *, int);


	private: 
		TMVA::Reader* tmvaReader;

		float Tau1Pt;
		float Tau2Pt;
		float Tau1AbsEta;
		float Tau2AbsEta;

	protected:
		map<string,string>	params;

};

#endif










