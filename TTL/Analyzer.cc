/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			07 Jun 2011
    Description:	Plotting macro for ditau analysis.
    Notes:

*/

#include <unistd.h>

#define TTLAnalyzer_cxx
#include "Analyzer.h"

using namespace std;

// Default constructor
TTLAnalyzer::TTLAnalyzer(map<string,string> const & iParams) : Analyzer(iParams){
	isBaseAnalyzer	= false;
	
	#include "Cuts_false.h"

	string cutsToApply = params["cutsToApply"];
	#include "Cuts_setCutsToApply.h"

    if (CutOn_MVA) {
        mva = new TTL_TMVAEvaluator(iParams);
        mva->BookMVA();
    } else {
        mva = NULL;
    }

}

// Default destructor
TTLAnalyzer::~TTLAnalyzer(){
	if(mva != NULL){ delete mva; mva = NULL; }
}


void TTLAnalyzer::Reset(){}


pair<double,double> TTLAnalyzer::Loop(Branches* iEvent, const int& n_to_read){
	TTLBranches* event = (TTLBranches*)iEvent;

	pair<double,double> result = make_pair(0,0);
	int maxEvents = atoi((params["maxEvents"]).c_str());

	Long64_t nentries = event->GetEntries(); 
    if (nentries == 0) {
        cerr << "ERROR: this process has zero events to read" << endl;
        exit(1);
    } else if (nentries != n_to_read) {
        cerr << "WARNING: tree size does not match topology specification! "
            << nentries << " events found, " << n_to_read << " expected."  << endl;
    }

    cout << "\t>>> Starting loop... " << " " << nentries << " entries available: ";
    cutFlow.SetCutCounts("nTuple making", nentries, nentries);

    if (maxEvents <= 0 || maxEvents >= nentries) {
        cout << "Processing all of them..." << string(14,'.') << " ";
    } else {
        cout << "Stopping at " << maxEvents << " as per-user request" << string(14,'.') << " ";
    }
	cout.flush();

	//ofstream fout("events.txt");
 

	// Actual loop
	double NOEanalyzed = 0;
	double NOEwithAtLeastOneCombo = 0;
	for (Long64_t jentry=0; jentry<nentries; jentry++) {
		// Keep user informed of the number of events processed and if there is a termination due to reaching of the limit
		if ( maxEvents > 0 && jentry >= (unsigned int)(maxEvents)){ cout << "\n\t>>> INFO: Reached user-imposed event number limit (" << maxEvents << "), skipping the rest." << endl; break; }

        if (jentry > 0 && (jentry + 1) % 1000 == 0) { 
            if (isatty(fileno(stdout))) {
                ostringstream o;
                o << (jentry - 999);
                cout << string(o.str().length(), '\b') << (jentry + 1);
            } else if ((jentry + 1) % 10000 == 0) {
                cout << " " << jentry + 1;
            }
            cout.flush();
        }

		// Get a new entry
		event->GetEntry(jentry);

		//cout << "===== new event ====" << endl;
      // cerr << "combos: " << event->TTL_NumCombos << endl;
		if(event->TTL_NumCombos > 0){ NOEwithAtLeastOneCombo++; }

		// Inform cutFlow that a new event is starting
		cutFlow.StartOfEvent();

		// Loop over all the combos
		for (unsigned int combo = 0; combo < event->TTL_NumCombos; combo++){

			// Obtain combo's mass
			float comboMass = event->TTL_DitauVisibleMass->at(combo);
			if( comboMass <= 0 ){ cout << "WARNING: ditauMass < 0!" << endl;  continue; }


			// Rest of selections
			pair<bool,bool> combosTarget = ComboPassesCuts(event, combo);

			// Inform cutFlow that we've checked this combo against all cuts
			cutFlow.EndOfCombo(combosTarget, combo);

			// If we already have one good combo for signal and one for QCD, no need to check the rest since the heaviest combos come first
			if(cutFlow.HaveGoodCombos()){ break; }
		}

		// Inform cutFlow that we've checked all the combos
		cutFlow.EndOfEvent();
		//cutFlow.PrintTable() ;

		// Fill good event vectors for signal analysis
		if(cutFlow.EventForSignalPassed()){
			int heaviestComboForSignal = cutFlow.GetHeaviestComboForSignal();
			event->SetBestCombo(heaviestComboForSignal);
			goodEventsForSignal.push_back(make_pair(jentry, heaviestComboForSignal));
		}

		// Fill good event vectors for QCD analysis
		if(cutFlow.EventForQCDPassed()){
			int heaviestComboForQCD = cutFlow.GetHeaviestComboForQCD();
			event->SetBestCombo(heaviestComboForQCD);
			goodEventsForQCD.push_back(make_pair(jentry, heaviestComboForQCD));

		}

		NOEanalyzed++;
	}

	if(atoi((params["maxEvents"]).c_str()) >= 0){ cutFlow.SetCutCounts("User event limit", NOEanalyzed, NOEanalyzed); }
	cutFlow.SetCutCounts("TTL_AtLeastOneCombo", NOEwithAtLeastOneCombo, NOEwithAtLeastOneCombo);


	//fout.close();
	result = make_pair(nentries, NOEanalyzed);
	return result;
}



pair<bool,bool> TTLAnalyzer::ComboPassesCuts(TTLBranches* iEvent, unsigned int iCombo){

	TTLBranches* event = iEvent;

	///***/// LS QCD business, this is a bit tricky... ///***///
	bool isForSignal = true;
	bool isForQCD = false;

	int chargeProduct = (event->TTL_Tau1Charge->at(iCombo))*(event->TTL_Tau2Charge->at(iCombo));
	isForQCD = (chargeProduct == 1);

	//pair<bool,bool> target = make_pair(true, isForQCD);
	pair<bool,bool> target = make_pair(true, true);
	///***/// 	End of LS/QCD business	 ///***///

/*

	// ============================= Generator Cuts ============================= //
	// Number of hadronic taus
	if(CutOn_NumHadronicGenTaus){
		//if(isMC){
		if(isSignal){
			if(cutFlow.CheckComboAndStop("NumHadronicGenTaus", event->NumberOfHadronicGenTaus, target)){ return target; }
		}else{
			cutFlow.ComboIsGood("NumHadronicGenTaus");
		}
		//}
	}

*/


	// =============================  Jet Cuts ============================= //
	if(CutOn_J_NumCSVL){ if(cutFlow.CheckComboAndStop("J_NumCSVL",event->TTL_NumCSVLbtagJets->at(iCombo), target)){ return target; }}
	if(CutOn_J_NumCSVM){ if(cutFlow.CheckComboAndStop("J_NumCSVM",event->TTL_NumCSVMbtagJets->at(iCombo), target)){ return target; }}
	if(CutOn_J_NumCSVT){ if(cutFlow.CheckComboAndStop("J_NumCSVT",event->TTL_NumCSVTbtagJets->at(iCombo), target)){ return target; }}
	if(CutOn_J_NumNonCSVL){ if(cutFlow.CheckComboAndStop("J_NumNonCSVL",event->TTL_NumNonCSVLbtagJets->at(iCombo), target)){ return target; }}
	if(CutOn_J_NumNonCSVM){ if(cutFlow.CheckComboAndStop("J_NumNonCSVM",event->TTL_NumNonCSVMbtagJets->at(iCombo), target)){ return target; }}
	if(CutOn_J_NumNonCSVT){ if(cutFlow.CheckComboAndStop("J_NumNonCSVT",event->TTL_NumNonCSVTbtagJets->at(iCombo), target)){ return target; }}
	if(CutOn_J_NumInclusive){ if(cutFlow.CheckComboAndStop("J_NumInclusive",event->TTL_NumNonCSVMbtagJets->at(iCombo)+event->TTL_NumCSVMbtagJets->at(iCombo), target)){ return target; }}
	if(CutOn_J_NumCleanCSVL){ if(cutFlow.CheckComboAndStop("J_NumCleanCSVL",event->TTL_NumCleanCSVLbtagJets->at(iCombo), target)){ return target; }}
	if(CutOn_J_NumCleanCSVM){ if(cutFlow.CheckComboAndStop("J_NumCleanCSVM",event->TTL_NumCleanCSVMbtagJets->at(iCombo), target)){ return target; }}
	if(CutOn_J_NumCleanCSVT){ if(cutFlow.CheckComboAndStop("J_NumCleanCSVT",event->TTL_NumCleanCSVTbtagJets->at(iCombo), target)){ return target; }}
	if(CutOn_J_NumCleanNonCSVL){ if(cutFlow.CheckComboAndStop("J_NumCleanNonCSVL",event->TTL_NumCleanNonCSVLbtagJets->at(iCombo), target)){ return target; }}
	if(CutOn_J_NumCleanNonCSVM){ if(cutFlow.CheckComboAndStop("J_NumCleanNonCSVM",event->TTL_NumCleanNonCSVMbtagJets->at(iCombo), target)){ return target; }}
	if(CutOn_J_NumCleanNonCSVT){ if(cutFlow.CheckComboAndStop("J_NumCleanNonCSVT",event->TTL_NumCleanNonCSVTbtagJets->at(iCombo), target)){ return target; }}
	if(CutOn_J_NumCleanInclusive){ if(cutFlow.CheckComboAndStop("J_NumCleanInclusive",event->TTL_NumCleanNonCSVMbtagJets->at(iCombo)+event->TTL_NumCleanCSVMbtagJets->at(iCombo), target)){ return target; }}

	
	// ============================= Lepton Cuts ============================= //

	if(CutOn_NumTightLeptons){			if(cutFlow.CheckComboAndStop("NumTightLeptons", event->TTL_NumTightMuons->at(iCombo)+event->TTL_NumTightElectrons->at(iCombo), target)){ return target; }}
	if(CutOn_NumTightMuons){			if(cutFlow.CheckComboAndStop("NumTightMuons", event->TTL_NumTightMuons->at(iCombo), target)){				return target; }}
	if(CutOn_NumTightElectrons){		if(cutFlow.CheckComboAndStop("NumTightElectrons", event->TTL_NumTightElectrons->at(iCombo), target)){		return target; }}

	if(CutOn_NumLooseLeptons){			if(cutFlow.CheckComboAndStop("NumLooseLeptons", event->TTL_NumLooseMuons->at(iCombo)+event->TTL_NumLooseElectrons->at(iCombo), target)){ return target; }}
	if(CutOn_NumLooseMuons){			if(cutFlow.CheckComboAndStop("NumLooseMuons", event->TTL_NumLooseMuons->at(iCombo), target)){				return target; }}
	if(CutOn_NumLooseElectrons){		if(cutFlow.CheckComboAndStop("NumLooseElectrons", event->TTL_NumLooseElectrons->at(iCombo), target)){		return target; }}

	if(CutOn_NumExLooseLeptons){		if(cutFlow.CheckComboAndStop("NumExLooseLeptons", event->TTL_NumExLooseMuons->at(iCombo)+event->TTL_NumExLooseElectrons->at(iCombo), target)){ return target; }}
	if(CutOn_NumExLooseMuons){			if(cutFlow.CheckComboAndStop("NumExLooseMuons", event->TTL_NumExLooseMuons->at(iCombo), target)){			return target; }}
	if(CutOn_NumExLooseElectrons){		if(cutFlow.CheckComboAndStop("NumExLooseElectrons", event->TTL_NumExLooseElectrons->at(iCombo), target)){	return target; }}

	if(CutOn_L_pT){				if(cutFlow.CheckComboAndStop("L_pT", event->TTL_LeptonPt->at(iCombo), target)){					return target; }}
	if(CutOn_L_Eta){			if(cutFlow.CheckComboAndStop("L_Eta", event->TTL_LeptonEta->at(iCombo), target)){					return target; }}
	if(CutOn_L_IsLoose){	if(cutFlow.CheckComboAndStop("L_IsLooseLepton", event->TTL_LeptonIsLoose->at(iCombo), target)){	return target; }}
	if(CutOn_L_IsTight){	if(cutFlow.CheckComboAndStop("L_IsTightLepton", event->TTL_LeptonIsTight->at(iCombo), target)){	return target; }}
	if(CutOn_L_RelIso){			if(cutFlow.CheckComboAndStop("L_RelIso", event->TTL_LeptonRelIso->at(iCombo), target)){			return target; }}

	// *** Tau Reality *** //
	if(!checkReality){
		if(CutOn_T1_MatchAbsId){ 	cutFlow.ComboIsGood("T1_MatchAbsId");	}
		if(CutOn_T2_MatchAbsId){ 	cutFlow.ComboIsGood("T2_MatchAbsId");	}
		if(CutOn_T1_ParentAbsId){	cutFlow.ComboIsGood("T1_ParentAbsId");	}
		if(CutOn_T2_ParentAbsId){	cutFlow.ComboIsGood("T2_ParentAbsId");	}
	}else{
		if(CutOn_T1_MatchAbsId){	if(cutFlow.CheckComboAndStop("T1_MatchAbsId", abs(event->TTL_Tau1GenMatchId->at(iCombo)), target)){			return target; }}
		if(CutOn_T2_MatchAbsId){	if(cutFlow.CheckComboAndStop("T2_MatchAbsId", abs(event->TTL_Tau2GenMatchId->at(iCombo)), target)){			return target; }}
		if(CutOn_T1_ParentAbsId){	if(cutFlow.CheckComboAndStop("T1_ParentAbsId", abs(event->TTL_Tau1GenMatchMother0Id->at(iCombo)), target)){	return target; }}
		if(CutOn_T2_ParentAbsId){	if(cutFlow.CheckComboAndStop("T2_ParentAbsId", abs(event->TTL_Tau2GenMatchMother0Id->at(iCombo)), target)){	return target; }}
	}


	// ============================= Acceptance Cuts ============================= //

	// Transverse momentum
	if(CutOn_T1_pT){ if(cutFlow.CheckComboAndStop("T1_pT", event->TTL_Tau1Pt->at(iCombo), target)){ return target; }}
	if(CutOn_T2_pT){ if(cutFlow.CheckComboAndStop("T2_pT", event->TTL_Tau2Pt->at(iCombo), target)){ return target; }}

	// Pseudorapidity
	if(CutOn_T1_Eta){ if(cutFlow.CheckComboAndStop("T1_Eta", event->TTL_Tau1Eta->at(iCombo), target)){ return target; }}
	if(CutOn_T2_Eta){ if(cutFlow.CheckComboAndStop("T2_Eta", event->TTL_Tau2Eta->at(iCombo), target)){ return target; }}

	// Crack veto
	if(CutOn_T1_InCracks){ if(cutFlow.CheckComboAndStop("T1_InCracks", event->TTL_Tau1IsInTheCracks->at(iCombo), target)){ return target; }}
	if(CutOn_T2_InCracks){ if(cutFlow.CheckComboAndStop("T2_InCracks", event->TTL_Tau2IsInTheCracks->at(iCombo), target)){ return target; }}


	// Delta R
	if(CutOn_TT_DeltaR){ if(cutFlow.CheckComboAndStop("TT_DeltaR", event->TTL_DitauDeltaR->at(iCombo), target)){ return target; }}
	if(CutOn_T1L_DeltaR){ if(cutFlow.CheckComboAndStop("T1L_DeltaR",DeltaR(
																			event->TTL_Tau1Eta->at(iCombo),
																			event->TTL_Tau1Phi->at(iCombo),
																			event->TTL_LeptonEta->at(iCombo),
																			event->TTL_LeptonPhi->at(iCombo)
																			), target)){ return target; }}
	if(CutOn_T2L_DeltaR){ if(cutFlow.CheckComboAndStop("T2L_DeltaR",DeltaR( 
																			event->TTL_Tau2Eta->at(iCombo),
																			event->TTL_Tau2Phi->at(iCombo),
																			event->TTL_LeptonEta->at(iCombo),
																			event->TTL_LeptonPhi->at(iCombo)
																			), target)){ return target; }}


	// ============================= Tau-ID Cuts ============================= //

	// Decay mode finding
	if(CutOn_T1_DecayModeFinding){ if(cutFlow.CheckComboAndStop("T1_DecayModeFinding", event->TTL_Tau1HPSdecayModeFinding->at(iCombo), target)){ return target; }}
	if(CutOn_T2_DecayModeFinding){ if(cutFlow.CheckComboAndStop("T2_DecayModeFinding", event->TTL_Tau2HPSdecayModeFinding->at(iCombo), target)){ return target; }}

	// Leading track transverse momentum
	if(CutOn_T1_LTvalid){ if(cutFlow.CheckComboAndStop("T1_LTvalid", event->TTL_Tau1LTvalid->at(iCombo), target)){ return target; }}
	if(CutOn_T2_LTvalid){ if(cutFlow.CheckComboAndStop("T2_LTvalid", event->TTL_Tau2LTvalid->at(iCombo), target)){ return target; }}
	
	// Leading track transverse momentum
	if(CutOn_T1_LTpT){ if(cutFlow.CheckComboAndStop("T1_LTpT", event->TTL_Tau1LTPt->at(iCombo), target)){ return target; }}
	if(CutOn_T2_LTpT){ if(cutFlow.CheckComboAndStop("T2_LTpT", event->TTL_Tau2LTPt->at(iCombo), target)){ return target; }}

	// Signal track multiplicity
	if(CutOn_T1_NumProngs){ if(cutFlow.CheckComboAndStop("T1_NumProngs", event->TTL_Tau1NProngs->at(iCombo), target)){ return target; }}
	if(CutOn_T2_NumProngs){ if(cutFlow.CheckComboAndStop("T2_NumProngs", event->TTL_Tau2NProngs->at(iCombo), target)){ return target; }}

	// Anti electron
	if(CutOn_T1_AntiElectronMVA){ if(cutFlow.CheckComboAndStop("T1_AntiElectronMVA", event->TTL_Tau1HPSagainstElectronMVA->at(iCombo), target)){ return target; }}
	if(CutOn_T1_AntiElectronIndex){ if(cutFlow.CheckComboAndStop("T1_AntiElectronIndex", event->GetTau1AntiElectronIndex(iCombo), target)){ return target; }}
	if(CutOn_T2_AntiElectronMVA){ if(cutFlow.CheckComboAndStop("T2_AntiElectronMVA", event->TTL_Tau2HPSagainstElectronMVA->at(iCombo), target)){ return target; }}
	if(CutOn_T2_AntiElectronIndex){ if(cutFlow.CheckComboAndStop("T2_AntiElectronIndex", event->GetTau2AntiElectronIndex(iCombo), target)){ return target; }}

	// Anti muon
	if(CutOn_T1_AntiMuonIndex){ if(cutFlow.CheckComboAndStop("T1_AntiMuonIndex", event->GetTau1AntiMuonIndex(iCombo), target)){ return target; }}
	if(CutOn_T2_AntiMuonIndex){ if(cutFlow.CheckComboAndStop("T2_AntiMuonIndex", event->GetTau2AntiMuonIndex(iCombo), target)){ return target; }}

	// Isolation
//	cout << "Min tau1-gen deltaR: " << MinGenTau1DeltaR(event, iCombo) << endl;
	if(CutOn_T1_IsolationIndex){ if(cutFlow.CheckComboAndStop("T1_IsolationIndex", event->GetTau1IsolationIndex(iCombo), target)){ return target; }}
	if(CutOn_T2_IsolationIndex){ if(cutFlow.CheckComboAndStop("T2_IsolationIndex", event->GetTau2IsolationIndex(iCombo), target)){ return target; }}

	// ============================= Topological Cuts ============================= //

	// Charge product
	if(CutOn_TT_ChargeProduct){
		target = make_pair(cutFlow.CheckComboDiscretely("TT_ChargeProduct", chargeProduct), isForQCD);
		if(cutFlow.CheckComboAndStop("TT_ChargeProduct", chargeProduct, target, true)){ return target; }
	}

	// Delta eta between taus
	if(CutOn_TT_DeltaEta){ if(cutFlow.CheckComboAndStop("TT_DeltaEta", event->TTL_Tau1Eta->at(iCombo)-event->TTL_Tau2Eta->at(iCombo), target)){ return target; }}

	// TT_Cosine Delta phi
	if(CutOn_TT_CosDeltaPhi){ if(cutFlow.CheckComboAndStop("TT_CosDeltaPhi", event->TTL_DitauCosDeltaPhi->at(iCombo), target)){ return target; }}

	// Missing transverse energy
	if(CutOn_MET){ if(cutFlow.CheckComboAndStop("MET", event->Ev_MET, target)){ return target; }}

	// MVA
	if(CutOn_MVA){ if(cutFlow.CheckComboAndStop("MVA", mva->Evaluate(event, iCombo), target)){ return target; }}


	// Return target, first element is for signal analysis, second is for QCD
	return target;
}


