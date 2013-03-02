/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			11 Jun 2011
    Description:	TMVA evaluating class
    Notes:

*/

#include "TLorentzVector.h"

#include "GenHelper.h"
#include "TMVAEvaluator.h"

#define TTE_TMVAEvaluator_cxx
using namespace std;

#define AT __LINE__

// Default destructor
TTE_TMVAEvaluator::~TTE_TMVAEvaluator(){
	delete tmvaReader; tmvaReader = NULL;
}

// Constructor
TTE_TMVAEvaluator::TTE_TMVAEvaluator(map<string,string>const & iParams){
	params = iParams;

	tmvaReader = new TMVA::Reader( "!Color:!Silent" );

	// Tell tmva what variables to consider
	tmvaReader->AddVariable("Tau1Pt", &Tau1Pt);
	tmvaReader->AddVariable("Tau2Pt", &Tau2Pt);
    tmvaReader->AddVariable("Tau1DecayMode", &Tau1DecayMode);
    // tmvaReader->AddVariable("Tau2DecayMode", &Tau2DecayMode);
    tmvaReader->AddVariable("Tau1IsolationIndex", &Tau1IsolationIndex);
    // tmvaReader->AddVariable("Tau2IsolationIndex", &Tau2IsolationIndex);
    tmvaReader->AddVariable("DeltaRTau1Tau2", &DeltaRTau1Tau2);
    tmvaReader->AddVariable("DeltaRTau1Lepton", &DeltaRTau1Lepton);
    // tmvaReader->AddVariable("DeltaRTau2Lepton", &DeltaRTau2Lepton);
    tmvaReader->AddVariable("DeltaRTau1LeadingJet", &DeltaRTau1LeadingJet);
    tmvaReader->AddVariable("DeltaRTau2LeadingJet", &DeltaRTau2LeadingJet);
    // tmvaReader->AddVariable("DeltaRTau1SubleadingJet", &DeltaRTau1SubleadingJet);
    // tmvaReader->AddVariable("DeltaRTau2SubleadingJet", &DeltaRTau2SubleadingJet);
    // tmvaReader->AddVariable("DeltaRLeptonLeadingJet", &DeltaRLeptonLeadingJet);
    // tmvaReader->AddVariable("DeltaRLeptonSubleadingJet", &DeltaRLeptonSubleadingJet);
    // tmvaReader->AddVariable("LeadingJetSubleadingJetMass", &LeadingJetSubleadingJetMass);
    // tmvaReader->AddVariable("Tau1LTPt", &Tau1LTPt);
    // tmvaReader->AddVariable("Tau2LTPt", &Tau2LTPt);
    // tmvaReader->AddVariable("Tau1NProngs", &Tau1NProngs);
    // tmvaReader->AddVariable("Tau2NProngs", &Tau2NProngs);
    tmvaReader->AddVariable("DitauVisibleMass", &DitauVisibleMass);

	// Book TMVA
	tmvaReader->BookMVA(TString(params.find("MVAmethod")->second + " method") , TString(params.find("MVAweights")->second));
}


// Evaluate each event
float TTE_TMVAEvaluator::Evaluate(TTEBranches const * iEvent, int iCombo){

	if (iCombo < 0){ cerr << "ERROR: 'iCombo' is " << iCombo << "." << endl; exit(1); }

    Tau1Pt = iEvent->TTE_Tau1Pt->at(iCombo);
    Tau2Pt = iEvent->TTE_Tau2Pt->at(iCombo);
    Tau1DecayMode = iEvent->TTE_Tau1DecayMode->at(iCombo);
    Tau2DecayMode = iEvent->TTE_Tau2DecayMode->at(iCombo);
    Tau1IsolationIndex = iEvent->GetTau1IsolationIndex(iCombo);
    Tau2IsolationIndex = iEvent->GetTau2IsolationIndex(iCombo);
    Tau1LTPt = iEvent->TTE_Tau1LTPt->at(iCombo);
    Tau2LTPt = iEvent->TTE_Tau2LTPt->at(iCombo);
    Tau1NProngs = iEvent->TTE_Tau1NProngs->at(iCombo);
    Tau2NProngs = iEvent->TTE_Tau2NProngs->at(iCombo);
    DitauVisibleMass = iEvent->TTE_DitauVisibleMass->at(iCombo);

    float tau1eta	= iEvent->TTE_Tau1Eta->at(iCombo);
    float tau1phi	= iEvent->TTE_Tau1Phi->at(iCombo);
    float tau2eta	= iEvent->TTE_Tau2Eta->at(iCombo);
    float tau2phi	= iEvent->TTE_Tau2Phi->at(iCombo);
    float lepEta	= iEvent->TTE_ElectronEta->at(iCombo);
    float lepPhi	= iEvent->TTE_ElectronPhi->at(iCombo);

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
    for(unsigned int j = 0; j < iEvent->J_Pt->size(); j++){
        float pt	= iEvent->J_Pt->at(j);
        float eta	= iEvent->J_Eta->at(j);
        float phi	= iEvent->J_Phi->at(j);
        TLorentzVector leadingJet(0,0,0,0); TLorentzVector subleadingJet(0,0,0,0);
        if(DeltaR(eta, phi, tau1eta, tau1phi) < 0.25 || DeltaR(eta, phi, tau2eta, tau2phi) < 0.25 || DeltaR(eta, phi, lepEta, lepPhi) < 0.25){ continue; }
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

	return tmvaReader->EvaluateMVA(TString(params.find("MVAmethod")->second + " method"));
}


