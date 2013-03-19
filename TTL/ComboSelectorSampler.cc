/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			11 Jun 2011
    Description:	Plot stacking class.
    Notes:

*/

#include "ComboSelectorSampler.h"
#include "TMVA/Config.h"
#include "TMVA/Factory.h"
#include "TMVA/Reader.h"


#define TTL_ComboSelectorSampler_cxx
using namespace std;

#define AT __LINE__

TTL_ComboSelectorSampler::TTL_ComboSelectorSampler(map<string,string>const & iParams) : TMVASampler(){
	params = iParams;

	output		= new TFile((params["comboSelector_sample"]).c_str(), "RECREATE");
	output->cd();
	signal		= new TTree("TreeS","TreeS");
	background	= new TTree("TreeB","TreeB");
	output->cd();

	SetUpTree(signal);
	SetUpTree(background);

}

// Default destructor
TTL_ComboSelectorSampler::~TTL_ComboSelectorSampler(){
	if(output->IsOpen()){
		output->cd();
		signal->Write();
		background->Write();
		output->Close();
	}
}

void TTL_ComboSelectorSampler::SetUpTree(TTree* iTree){

	// Define branches
	iTree->Branch("HT", &HT);
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
    iTree->Branch("LeadingJetPt", &LeadingJetPt);
    iTree->Branch("SubLeadingJetPt", &SubLeadingJetPt);
}

void TTL_ComboSelectorSampler::FillTrees(TTLBranches* iEvent){

	// Instantiante Branches to read events more easily
	TTLBranches* event = iEvent;

	// Loop over good events
	for(unsigned int combo = 0; combo < iEvent->TTL_Tau1Pt->size(); ++combo){

		// Assign values
		HT = event->TTL_HT->at(combo);
		Tau1Pt = event->TTL_Tau1Pt->at(combo);
		Tau2Pt = event->TTL_Tau2Pt->at(combo);
        Tau1DecayMode = event->TTL_Tau1DecayMode->at(combo);
        Tau2DecayMode = event->TTL_Tau2DecayMode->at(combo);
        Tau1IsolationIndex = event->GetTau1IsolationIndex(combo);
        Tau2IsolationIndex = event->GetTau2IsolationIndex(combo);
        Tau1LTPt = event->TTL_Tau1LTPt->at(combo);
        Tau2LTPt = event->TTL_Tau2LTPt->at(combo);
        Tau1NProngs = event->TTL_Tau1NProngs->at(combo);
        Tau2NProngs = event->TTL_Tau2NProngs->at(combo);
        DitauVisibleMass = event->TTL_DitauVisibleMass->at(combo);

        float conesize = 0.25;
        LeadingJetPt = 0.;
        SubLeadingJetPt = 0.;
        for (unsigned int i = 0, c = 0; c < 2 and i < event->J_Pt->size(); i++) {
            if ((DeltaR(event->J_Eta->at(i),
                            event->J_Phi->at(i),
                            event->TTL_Tau1Eta->at(combo),
                            event->TTL_Tau1Phi->at(combo)) > conesize) &&
                    (DeltaR(event->J_Eta->at(i),
                            event->J_Phi->at(i),
                            event->TTL_Tau2Eta->at(combo),
                            event->TTL_Tau2Phi->at(combo)) > conesize) &&
                    (DeltaR(event->J_Eta->at(i),
                            event->J_Phi->at(i),
                            event->TTL_LeptonEta->at(combo),
                            event->TTL_LeptonPhi->at(combo)) > conesize)) {
                if (c == 0)
                    LeadingJetPt = event->J_Pt->at(i);
                else if (c == 1)
                    SubLeadingJetPt = event->J_Pt->at(i);
                ++c;
            }
        }

		float tau1eta	= event->TTL_Tau1Eta->at(combo);
		float tau1phi	= event->TTL_Tau1Phi->at(combo);
		float tau2eta	= event->TTL_Tau2Eta->at(combo);
		float tau2phi	= event->TTL_Tau2Phi->at(combo);
		float lepEta	= event->TTL_LeptonEta->at(combo);
		float lepPhi	= event->TTL_LeptonPhi->at(combo);

		float jet1eta = -99;
		float jet1phi = -99;
		float jet2eta = -99;
		float jet2phi = -99;

		DeltaRTau1Tau2 = DeltaR(tau1eta, tau1phi, tau2eta, tau2phi);
		DeltaRTau1Lepton = DeltaR(tau1eta, tau1phi, lepEta, lepPhi);
		DeltaRTau2Lepton = DeltaR(tau2eta, tau2phi, lepEta, lepPhi);

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
			if(DeltaR(eta, phi, tau1eta, tau1phi) < 0.25 || DeltaR(eta, phi, tau2eta, tau2phi) < 0.25 || DeltaR(eta, phi, eta, lepPhi) < 0.25){ continue; }
			if(!foundLeadingJet){ // Fill leading jet
				DeltaRTau1LeadingJet		= DeltaR(eta, phi, tau1eta, tau1phi);
				DeltaRTau2LeadingJet		= DeltaR(eta, phi, tau2eta, tau2phi);
				DeltaRLeptonLeadingJet		= DeltaR(eta, phi, lepEta, lepPhi);
				leadingJet.SetPtEtaPhiM(pt, eta, phi, 0);
				foundLeadingJet = true;
			}else{ // Fill subleading jet
				DeltaRTau1SubleadingJet		= DeltaR(eta, phi, tau1eta, tau1phi);
				DeltaRTau2SubleadingJet		= DeltaR(eta, phi, tau2eta, tau2phi);
				DeltaRLeptonSubleadingJet	= DeltaR(eta, phi, lepEta, lepPhi);
				subleadingJet.SetPtEtaPhiM(pt, eta, phi, 0);
				LeadingJetSubleadingJetMass = (leadingJet + subleadingJet).M();
				break;
			}
		}

		// Fill trees
		if(
			abs(event->TTL_Tau1GenMatchId->at(combo)) == 15 &&
			abs(event->TTL_Tau2GenMatchId->at(combo)) == 15 &&
			abs(event->TTL_Tau1GenMatchMother0Id->at(combo)) == 25 &&
			abs(event->TTL_Tau2GenMatchMother0Id->at(combo)) == 25
		){	signal->Fill();		}
		else{					background->Fill();	}
	}
}
