#ifndef DIL_TMVASampler_h
#define DIL_TMVASampler_h

#include "../TMVASampler.h"
#include "Branches.h"


using namespace std;

class DIL_TMVASampler : public TMVASampler {


	public:
		explicit DIL_TMVASampler(map<string,string> const &);
		virtual ~DIL_TMVASampler();


	private: 
	//	void MakeTrainingSample(ProPack*);
		void FillTree(TTree*, Process const *);

	protected:

};

#endif










