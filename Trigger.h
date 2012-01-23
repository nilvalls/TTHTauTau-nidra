#ifndef Trigger_h
#define Trigger_h

#include <iostream>
#include <utility>
#include <sstream>
#include <algorithm>
#include "TF1.h"
#include "TMath.h"
#include "configParser/config.h"

using namespace std;

struct trigger{
	int startRun;
	int endRun;
	TF1* efficiency;
};


class Trigger{
	private:
	vector<float> lowEdge;
	vector<float> weight;

	vector<trigger*>* L1HLTriggers;
	vector<trigger*>* HLTriggers;
	vector<trigger*>* L1Triggers;

	TF1* function;
	TF1* eduMuTau;
	TF1* eduElectron;
	double counter;

	Config*				triggerConfig;

	public:
		~Trigger();
		Trigger(float);
		Trigger(string);
		Trigger(string, string);
		void SetEfficiency(std::string, std::string);
		void SetEfficiency(string);
		void ParseCSV(const string&, char,vector<float>&) ;
		float const GetWeightFromFunc(float const) const;
		float GetWeightFromFuncE(float);
		float GetWeightFromBins(float);
		float GetWeightFromConf(float,int);

		float GetXTriggerWeight(vector<trigger*>*,float,int);

		void ParseConfig(string);
		void InsertTrigger(vector<trigger*>*, string, int, int, string, double, double, double);
		virtual string Replace(string, string, string);

};

#endif
