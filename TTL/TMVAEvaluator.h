#ifndef TTL_TMVAEvaluator_h
#define TTL_TMVAEvaluator_h

#include "Branches.h"
#include "TMVA/Factory.h"
#include "TMVA/Reader.h"
//#include "TMVA/Tools.h"

using namespace std;

class TTL_TMVAEvaluator {

	public:
		TTL_TMVAEvaluator();
		TTL_TMVAEvaluator(map<string,string> const &);
		virtual ~TTL_TMVAEvaluator();

		float Evaluate(TTLBranches const *, int);
        virtual void BookMVA();
        virtual void TrainMVA();

	protected:
		bool mvaBooked;


	private: 
        TFile *outfile;
		TMVA::Reader* tmvaReader;

        float HT;
        float Tau1Pt;
        float Tau1Eta;
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
        float LeadingJetPt;
        float SubLeadingJetPt;


	protected:
        template<typename T> void SetupVariables(T*);
        template<typename T> void AddVariable(TMVA::Factory*, const string&, const char&, T&);
        template<typename T> void AddVariable(TMVA::Reader*, const string&, const char&, T&);
		map<string,string> params;

};

#endif
