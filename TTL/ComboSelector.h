#ifndef TTL_ComboSelector_h
#define TTL_ComboSelector_h

#include <assert.h>
#include "Branches.h"
#include "TMVA/Factory.h"
#include "TMVA/Reader.h"
#include "TMVAEvaluator.h"
//#include "multimap"

using namespace std;

class TTL_ComboSelector : public TTL_TMVAEvaluator {

	public:
		TTL_ComboSelector(map<string,string> const &);
		virtual ~TTL_ComboSelector();

		multimap<double, unsigned int> GetSortedCombosByPt(Branches*);
		multimap<double, unsigned int> GetSortedCombos(Branches*);
		float Evaluate(TTLBranches const *, int);
        virtual void BookMVA();
        virtual void TrainMVA();


	private: 
        TFile *outfile;
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
        float LeadingJetPt;
        float SubLeadingJetPt;

	protected:
        template<typename T> void SetupVariables(T*);

};

#endif
