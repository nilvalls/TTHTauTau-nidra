#ifndef TTM_TMVASampler_h
#define TTM_TMVASampler_h

#include "../TMVASampler.h"
#include "Branches.h"


using namespace std;

class TTM_TMVASampler : public TMVASampler {


	public:
		explicit TTM_TMVASampler(map<string,string> const &);
		virtual ~TTM_TMVASampler();


	private: 
	//	void MakeTrainingSample(ProPack*);
		void FillTree(TTree*, Process const *);

	protected:

};

#endif










