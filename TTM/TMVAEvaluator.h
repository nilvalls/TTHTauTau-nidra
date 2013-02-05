#ifndef TTM_TMVAEvaluator_h
#define TTM_TMVAEvaluator_h

#include "Branches.h"
#include "TMVA/Reader.h"
//#include "TMVA/Tools.h"

using namespace std;

class TTM_TMVAEvaluator {

	public:
		TTM_TMVAEvaluator(map<string,string> const &);
		virtual ~TTM_TMVAEvaluator();

		float Evaluate(TTMBranches const *, int);


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










