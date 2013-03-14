#ifndef TTL_TMVAEvaluator_h
#define TTL_TMVAEvaluator_h

#include "Branches.h"
#include "TMVA/Factory.h"
#include "TMVA/Reader.h"
//#include "TMVA/Tools.h"

using namespace std;

class TTL_TMVAEvaluator {

	public:
		TTL_TMVAEvaluator(map<string,string> const &);
		virtual ~TTL_TMVAEvaluator();

		float Evaluate(TTLBranches const *, int);
        void BookMVA();
        void TrainMVA();


	private: 
        TFile *outfile;
        TMVA::Factory *factory;
		TMVA::Reader* tmvaReader;

        float HT;
        float Tau1Pt;
        float Tau2Pt;
        float Tau1DecayMode;
        float Tau2DecayMode;
        float Tau1IsolationIndex;
        float Tau2IsolationIndex;
        float Tau1LTPt;
        float Tau2LTPt;
        float Tau1NProngs;
        float Tau2NProngs;
        float DitauVisibleMass;
        float DeltaRTau1Tau2;
        float DeltaRTau1Lepton;
        float DeltaRTau2Lepton;
        float DeltaRTau1LeadingJet;
        float DeltaRTau2LeadingJet;
        float DeltaRTau1SubleadingJet;
        float DeltaRTau2SubleadingJet;
        float DeltaRLeptonLeadingJet;
        float DeltaRLeptonSubleadingJet;
        float LeadingJetSubleadingJetMass;

        template<typename T>
        void AddVariable(const string&, const char&, T&);

	protected:
		map<string,string>	params;

};

#endif
