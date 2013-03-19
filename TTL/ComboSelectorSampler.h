#ifndef TTL_ComboSelectorSampler_h
#define TTL_ComboSelectorSampler_h

#include "../TMVASampler.h"
#include "Branches.h"


using namespace std;

class TTL_ComboSelectorSampler : public TMVASampler {


	public:
		explicit TTL_ComboSelectorSampler(map<string,string> const &);
		virtual ~TTL_ComboSelectorSampler();
		void FillTrees(TTLBranches*);


	private: 
	//	void MakeTrainingSample(ProPack*);
		void SetUpTree(TTree*);

	protected:

	private:
		TFile* output;
		TTree* signal;
		TTree* background;


		// Define variables going into the trees
		float HT;
		float Tau1Pt;
		float Tau2Pt;
		unsigned int Tau1DecayMode;
		unsigned int Tau2DecayMode;
		unsigned int Tau1IsolationIndex;
		unsigned int Tau2IsolationIndex;
		float Tau1LTPt;
		float Tau2LTPt;
		unsigned int Tau1NProngs;
		unsigned int Tau2NProngs;
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

};

#endif










