/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			11 Jun 2011
    Description:	Plot stacking class.
    Notes:

*/

#include "TMVASampler.h"

#define TTL_TMVASampler_cxx
using namespace std;

#define AT __LINE__

TTL_TMVASampler::TTL_TMVASampler(map<string,string>const & iParams) : TMVASampler(iParams){
	MakeTrainingSample(proPack);
}

// Default destructor
TTL_TMVASampler::~TTL_TMVASampler(){}


void TTL_TMVASampler::FillTree(TTree* iTree, Process const * iProcess){

	// Define variables going into the trees
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

	// Define branches
	iTree->Branch("Tau1Pt", &Tau1Pt);
	iTree->Branch("Tau2Pt", &Tau2Pt);
    iTree->Branch("Tau1DecayMode", &Tau1DecayMode);
    iTree->Branch("Tau2DecayMode", &Tau2DecayMode);
    iTree->Branch("Tau1IsolationIndex", &Tau1IsolationIndex);
    iTree->Branch("Tau2IsolationIndex", &Tau2IsolationIndex);
    iTree->Branch("Tau1LTPt", &Tau1LTPt);
    iTree->Branch("Tau2LTPt", &Tau2LTPt);
    iTree->Branch("Tau1NProngs", &Tau1NProngs);
    iTree->Branch("Tau2NProngs", &Tau2NProngs);
    iTree->Branch("DitauVisibleMass", &DitauVisibleMass);
    iTree->Branch("DeltaRTau1Tau2", &DeltaRTau1Tau2);
    iTree->Branch("DeltaRTau1Lepton", &DeltaRTau1Lepton);
    iTree->Branch("DeltaRTau2Lepton", &DeltaRTau2Lepton);
    iTree->Branch("DeltaRTau1LeadingJet", &DeltaRTau1LeadingJet);
    iTree->Branch("DeltaRTau2LeadingJet", &DeltaRTau2LeadingJet);
    iTree->Branch("DeltaRTau1SubleadingJet", &DeltaRTau1SubleadingJet);
    iTree->Branch("DeltaRTau2SubleadingJet", &DeltaRTau2SubleadingJet);
    iTree->Branch("DeltaRLeptonLeadingJet", &DeltaRLeptonLeadingJet);
    iTree->Branch("DeltaRLeptonSubleadingJet", &DeltaRLeptonSubleadingJet);
    iTree->Branch("LeadingJetSubleadingJetMass", &LeadingJetSubleadingJetMass);

	// Instantiante Branches to read events more easily
	TTLBranches* event = new TTLBranches(params, iProcess->GetNtuplePath());

	// Loop over good events
	vector<pair<int,int> > goodEventsForSignal = iProcess->GetGoodEventsForSignal();
	cout << "\n\tNow filling tree for " << iProcess->GetShortName() << endl;
	cout << "\t>>> OS, filling good events (total " << goodEventsForSignal.size() << "): "; cout.flush();
	stringstream goodEventsSS; goodEventsSS.str("");
	for(unsigned int i = 0; i < goodEventsForSignal.size(); i++){
		if(i>0 && (i%10) == 0){
			cout << string((goodEventsSS.str()).length(),'\b') << string((goodEventsSS.str()).length(),' ') << string((goodEventsSS.str()).length(),'\b'); cout.flush();
			goodEventsSS.str("");
			goodEventsSS << i;
			cout << goodEventsSS.str(); cout.flush();
		}

		event->GetEntry(goodEventsForSignal.at(i).first);
		event->SetBestCombo(goodEventsForSignal.at(i).second);
		unsigned int bestCombo = event->bestCombo;

		// Assign values
		Tau1Pt = event->TTL_Tau1Pt->at(bestCombo);
		Tau2Pt = event->TTL_Tau2Pt->at(bestCombo);
        Tau1DecayMode = event->TTL_Tau1DecayMode->at(bestCombo);
        Tau2DecayMode = event->TTL_Tau2DecayMode->at(bestCombo);
        Tau1IsolationIndex = event->GetTau1IsolationIndex(bestCombo);
        Tau2IsolationIndex = event->GetTau2IsolationIndex(bestCombo);
        Tau1LTPt = event->TTL_Tau1LTPt->at(bestCombo);
        Tau2LTPt = event->TTL_Tau2LTPt->at(bestCombo);
        Tau1NProngs = event->TTL_Tau1NProngs->at(bestCombo);
        Tau2NProngs = event->TTL_Tau2NProngs->at(bestCombo);
        DitauVisibleMass = event->TTL_DitauVisibleMass->at(bestCombo);

		float tau1eta	= event->TTL_Tau1Eta->at(bestCombo);
		float tau1phi	= event->TTL_Tau1Phi->at(bestCombo);
		float tau2eta	= event->TTL_Tau2Eta->at(bestCombo);
		float tau2phi	= event->TTL_Tau2Phi->at(bestCombo);
		float lepEta	= event->TTL_LeptonEta->at(bestCombo);
		float lepPhi	= event->TTL_LeptonPhi->at(bestCombo);

		float jet1eta = -99;
		float jet1phi = -99;
		float jet2eta = -99;
		float jet2phi = -99;

		DeltaRTau1Tau2 = DeltaR(tau1phi, tau1eta, tau2phi, tau2eta);
		DeltaRTau1Lepton = DeltaR(tau1phi, tau1eta, lepPhi, lepEta);
		DeltaRTau2Lepton = DeltaR(tau2phi, tau2eta, lepPhi, lepEta);

		DeltaRTau1LeadingJet		= -99;
		DeltaRTau2LeadingJet		= -99;
		DeltaRTau1SubleadingJet		= -99;
		DeltaRTau2SubleadingJet		= -99;
		DeltaRLeptonLeadingJet		= -99;
		DeltaRLeptonSubleadingJet	= -99;
		LeadingJetSubleadingJetMass	= -99;

		bool foundLeadingJet = false;
		for(unsigned int j = 0; j < event->J_Pt->size(); j++){
			float pt	= event->J_Pt->at(j);
			float eta	= event->J_Eta->at(j);
			float phi	= event->J_Phi->at(j);
			TLorentzVector leadingJet(0,0,0,0); TLorentzVector subleadingJet(0,0,0,0);
			if(DeltaR(phi, eta, tau1phi, tau1eta) < 0.25 || DeltaR(phi, eta, tau2phi, tau2eta) < 0.25 || DeltaR(phi, eta, lepPhi, lepEta) < 0.25){ continue; }
			if(!foundLeadingJet){ // Fill leading jet
				DeltaRTau1LeadingJet		= DeltaR(phi, eta, tau1phi, tau1eta);
				DeltaRTau2LeadingJet		= DeltaR(phi, eta, tau2phi, tau2eta);
				DeltaRLeptonLeadingJet		= DeltaR(phi, eta, lepPhi, lepEta);
				leadingJet.SetPtEtaPhiM(pt, eta, phi, 0);
				foundLeadingJet = true;
			}else{ // Fill subleading jet
				DeltaRTau1SubleadingJet		= DeltaR(phi, eta, tau1phi, tau1eta);
				DeltaRTau2SubleadingJet		= DeltaR(phi, eta, tau2phi, tau2eta);
				DeltaRLeptonSubleadingJet	= DeltaR(phi, eta, lepPhi, lepEta);
				subleadingJet.SetPtEtaPhiM(pt, eta, phi, 0);
				LeadingJetSubleadingJetMass = (leadingJet + subleadingJet).M();
				break;
			}
		}

		// Fill tree
		iTree->Fill();
	}
	cout << endl;
}
