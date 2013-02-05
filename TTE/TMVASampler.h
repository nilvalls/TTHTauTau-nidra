#ifndef TTE_TMVASampler_h
#define TTE_TMVASampler_h

#include "../TMVASampler.h"
#include "Branches.h"


using namespace std;

class TTE_TMVASampler : public TMVASampler {


	public:
		explicit TTE_TMVASampler(map<string,string> const &);
		virtual ~TTE_TMVASampler();


	private: 
	//	void MakeTrainingSample(ProPack*);
		void FillTree(TTree*, Process const *);

	protected:

};

#endif










