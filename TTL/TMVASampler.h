#ifndef TTL_TMVASampler_h
#define TTL_TMVASampler_h

#include "../TMVASampler.h"
#include "Branches.h"


using namespace std;

class TTL_TMVASampler : public TMVASampler {


	public:
		explicit TTL_TMVASampler(map<string,string> const &);
		virtual ~TTL_TMVASampler();


	private: 
	//	void MakeTrainingSample(ProPack*);
		void FillTree(TTree*, Process const *);

	protected:

};

#endif










