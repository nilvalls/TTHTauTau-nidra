/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			07 Jun 2011
    Description:	Plotting macro for ditau analysis.
    Notes:

*/

#define TTEAnalyzer_cxx
#include "Analyzer.h"

using namespace std;

// Default constructor
TTEAnalyzer::TTEAnalyzer(map<string,string> const & iParams) : Analyzer(iParams){
	isBaseAnalyzer	= false;
	
	#include "Cuts_false.h"

	string cutsToApply = params["cutsToApply"];
	#include "Cuts_setCutsToApply.h"

}

// Default destructor
TTEAnalyzer::~TTEAnalyzer(){}


void TTEAnalyzer::Reset(){}


pair<double,double> TTEAnalyzer::Loop(Branches* iEvent){
	TTEBranches* event = (TTEBranches*)iEvent;


	pair<double,double> result = make_pair(0,0);
	int maxEvents = atoi((params["maxEvents"]).c_str());

	cout << "\t>>> Starting loop... "; cout.flush();

	Long64_t nentries = event->GetEntries(); 
	if(nentries == 0){ cerr << "ERROR: this process has zero events to read" << endl; exit(1); }
	cout << " " << nentries << " entries available: ";
	cutFlow.SetCutCounts("nTuple making", nentries, nentries);
	if(maxEvents <= 0 || maxEvents >= nentries){ cout << "Processing all of them..." << string(14,'.') << " "; }
	else{ cout << "Stopping at " << maxEvents << " as per-user request" << string(14,'.') << " "; }
	cout.flush();

	ofstream fout("events.txt");
 

	// Actual loop
	double NOEanalyzed = 0;
	double NOEwithAtLeastOneCombo = 0;
	double NOEwithTwoRealTaus = 0;
	double NOEwithoutTwoRealTaus = 0;
	for (Long64_t jentry=0; jentry<nentries; jentry++) {
		// Keep user informed of the number of events processed and if there is a termination due to reaching of the limit
		if ( maxEvents > 0 && jentry >= (unsigned int)(maxEvents)){ cout << "\n\t>>> INFO: Reached user-imposed event number limit (" << maxEvents << "), skipping the rest." << endl; break; }

		int prevLength = 0;
		if (jentry>0 && (jentry+1)%1000==0){ 
			stringstream jentryss; jentryss.str("");
			jentryss << (jentry+1);
			cout << string((jentryss.str()).length(),'\b') << string((jentryss.str()).length(),' ') << string((jentryss.str()).length(),'\b') << jentryss.str(); cout.flush(); 
			prevLength = (jentryss.str()).length();
		}

		// Get a new entry
		event->GetEntry(jentry);

		//cout << "===== new event ====" << endl;
		if(event->TTE_NumCombos > 0){ NOEwithAtLeastOneCombo++; }

		// Inform cutFlow that a new event is starting
		cutFlow.StartOfEvent();


		// Loop over all the combos
		//cout << "new event; " << event->TTE_NumCombos << " combos" <<  endl;
		bool comboHasTwoRealTaus = false;
		int realTauCombo = -1;
		for (unsigned int combo = 0; combo < event->TTE_NumCombos; combo++){

			// Obtain combo's mass
			float comboMass = event->TTE_DitauVisibleMass->at(combo);
			if( comboMass <= 0 ){ cout << "WARNING: ditauMass < 0!" << endl;  continue; }


			// Rest of selections
			pair<bool,bool> combosTarget = ComboPassesCuts(event, combo);
			if( event->IsRealDitauCombo(combo) ){ comboHasTwoRealTaus = true; realTauCombo = combo; }
			//else{ event->PrintDitauReality(combo); }

			// Inform cutFlow that we've checked this combo against all cuts
			cutFlow.EndOfCombo(combosTarget, combo);

			// If we already have one good combo for signal and one for QCD, no need to check the rest since the heaviest combos come first
			//if(cutFlow.HaveGoodCombos()){ cout << "break here" << endl; }//break; }
			if(cutFlow.HaveGoodCombos()){ break; }
		}

		if(comboHasTwoRealTaus){ NOEwithTwoRealTaus++; }
		else{ NOEwithoutTwoRealTaus++; }

		// Inform cutFlow that we've checked all the combos
		cutFlow.EndOfEvent();
		//cutFlow.PrintTable() ;

		// Fill good event vectors for signal analysis
		//cout << "cutFlow.EventForSignalPassed(): " << cutFlow.EventForSignalPassed() << endl;
		if(cutFlow.EventForSignalPassed()){
			int heaviestComboForSignal = cutFlow.GetHeaviestComboForSignal();
			event->SetBestCombo(heaviestComboForSignal);
			goodEventsForSignal.push_back(make_pair(jentry, heaviestComboForSignal));
		}else{ 
			fout << event->Ev_runNumber << ":" << event->Ev_lumiBlock << ":" << event->Ev_eventNumber;
			if(realTauCombo >= 0){
				fout << " | " << event->TTE_Tau1Eta->at(realTauCombo) << " " << event->TTE_Tau1Phi->at(realTauCombo) << " :: " << event->TTE_Tau1HPSagainstMuonLoose->at(realTauCombo)
					 << " | " << event->TTE_Tau2Eta->at(realTauCombo) << " " << event->TTE_Tau2Phi->at(realTauCombo) << " :: " << event->TTE_Tau2HPSagainstMuonLoose->at(realTauCombo);
			}
			fout << endl;
		}
		//cout << "size: " << goodEventsForSignal.size() << endl;

		// Fill good event vectors for QCD analysis
		if(cutFlow.EventForQCDPassed()){
			int heaviestComboForQCD = cutFlow.GetHeaviestComboForQCD();
			event->SetBestCombo(heaviestComboForQCD);
			goodEventsForQCD.push_back(make_pair(jentry, heaviestComboForQCD));

		}

		NOEanalyzed++;
	}

//	cout << "NOEwithTwoRealTaus: " << setprecision(6) << NOEwithTwoRealTaus << " " << NOEwithoutTwoRealTaus << " " << (NOEwithTwoRealTaus+NOEwithoutTwoRealTaus) << endl;

	if(atoi((params["maxEvents"]).c_str()) >= 0){ cutFlow.SetCutCounts("User event limit", NOEanalyzed, NOEanalyzed); }
	cutFlow.SetCutCounts("TTE_AtLeastOneCombo", NOEwithAtLeastOneCombo, NOEwithAtLeastOneCombo);


	fout.close();
	result = make_pair(nentries, NOEanalyzed);
	return result;
}



pair<bool,bool> TTEAnalyzer::ComboPassesCuts(TTEBranches* iEvent, unsigned int iCombo){

	TTEBranches* event = iEvent;

	///***/// LS QCD business, this is a bit tricky... ///***///
	bool isForSignal = true;
	bool isForQCD = false;

	int chargeProduct = (event->TTE_Tau1Charge->at(iCombo))*(event->TTE_Tau2Charge->at(iCombo));
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
	if(CutOn_J_NumCSVL){ if(cutFlow.CheckComboAndStop("J_NumCSVL",event->TTE_NumCSVLbtagJets->at(iCombo), target)){ return target; }}
	if(CutOn_J_NumCSVM){ if(cutFlow.CheckComboAndStop("J_NumCSVM",event->TTE_NumCSVMbtagJets->at(iCombo), target)){ return target; }}
	if(CutOn_J_NumCSVT){ if(cutFlow.CheckComboAndStop("J_NumCSVT",event->TTE_NumCSVTbtagJets->at(iCombo), target)){ return target; }}
	if(CutOn_J_NumNonCSVL){ if(cutFlow.CheckComboAndStop("J_NumNonCSVL",event->TTE_NumNonCSVLbtagJets->at(iCombo), target)){ return target; }}
	if(CutOn_J_NumNonCSVM){ if(cutFlow.CheckComboAndStop("J_NumNonCSVM",event->TTE_NumNonCSVMbtagJets->at(iCombo), target)){ return target; }}
	if(CutOn_J_NumNonCSVT){ if(cutFlow.CheckComboAndStop("J_NumNonCSVT",event->TTE_NumNonCSVTbtagJets->at(iCombo), target)){ return target; }}
	if(CutOn_J_NumInclusive){ if(cutFlow.CheckComboAndStop("J_NumInclusive",event->TTE_NumNonCSVMbtagJets->at(iCombo)+event->TTE_NumCSVMbtagJets->at(iCombo), target)){ return target; }}

	
	// ============================= Muon Cuts ============================= //
	if(CutOn_E_pT){				if(cutFlow.CheckComboAndStop("M_pT", event->TTE_ElectronPt->at(iCombo), target)){					return target; }}
	if(CutOn_E_Eta){			if(cutFlow.CheckComboAndStop("M_Eta", event->TTE_ElectronEta->at(iCombo), target)){					return target; }}
	if(CutOn_E_IsLooseElectron){	if(cutFlow.CheckComboAndStop("M_IsLooseElectron", event->TTE_ElectronIsLooseElectron->at(iCombo), target)){	return target; }}
	if(CutOn_E_IsTightElectron){	if(cutFlow.CheckComboAndStop("M_IsTightElectron", event->TTE_ElectronIsTightElectron->at(iCombo), target)){	return target; }}
	if(CutOn_E_RelIso){			if(cutFlow.CheckComboAndStop("M_RelIso", event->TTE_ElectronRelIso->at(iCombo), target)){			return target; }}

	// *** Tau Reality *** //
	if (isSignal){
		if(CutOn_T1_Reality){		if(cutFlow.CheckComboAndStop("T1_Reality", Tau1Reality(event, iCombo), target)){			return target; }}
		if(CutOn_T2_Reality){		if(cutFlow.CheckComboAndStop("T2_Reality", Tau2Reality(event, iCombo), target)){			return target; }}
		if(CutOn_TT_Reality){		if(cutFlow.CheckComboAndStop("TT_Reality", event->IsRealDitauCombo(iCombo), target)){		return target; }}
		if(CutOn_G_NumTauHad){		if(cutFlow.CheckComboAndStop("G_NumTauHad", NumGenTauHad(event), target)){					return target; }}
	}


	// ============================= Acceptance Cuts ============================= //

	// Invariant mass
//	if(CutOn_InvariantMass){ if(cutFlow.CheckComboAndStop("InvariantMass", event->TauTauVisPlusMetMass->at(iCombo), target)){ return target; }}

	// Transverse momentum
	if(CutOn_T1_pT){ if(cutFlow.CheckComboAndStop("T1_pT", event->TTE_Tau1Pt->at(iCombo), target)){ return target; }}
	if(CutOn_T2_pT){ if(cutFlow.CheckComboAndStop("T2_pT", event->TTE_Tau2Pt->at(iCombo), target)){ return target; }}

	// Pseudorapidity
	if(CutOn_T1_Eta){ if(cutFlow.CheckComboAndStop("T1_Eta", event->TTE_Tau1Eta->at(iCombo), target)){ return target; }}
	if(CutOn_T2_Eta){ if(cutFlow.CheckComboAndStop("T2_Eta", event->TTE_Tau2Eta->at(iCombo), target)){ return target; }}

	// Crack veto
	if(CutOn_T1_InCracks){ if(cutFlow.CheckComboAndStop("T1_InCracks", event->TTE_Tau1IsInTheCracks->at(iCombo), target)){ return target; }}
	if(CutOn_T2_InCracks){ if(cutFlow.CheckComboAndStop("T2_InCracks", event->TTE_Tau2IsInTheCracks->at(iCombo), target)){ return target; }}


	// Delta R
	if(CutOn_TT_DeltaR){ if(cutFlow.CheckComboAndStop("TT_DeltaR", event->TTE_DitauDeltaR->at(iCombo), target)){ return target; }}


	// ============================= Tau-ID Cuts ============================= //

	// Decay mode finding
	if(CutOn_T1_DecayModeFinding){ if(cutFlow.CheckComboAndStop("T1_DecayModeFinding", event->TTE_Tau1HPSdecayModeFinding->at(iCombo), target)){ return target; }}
	if(CutOn_T2_DecayModeFinding){ if(cutFlow.CheckComboAndStop("T2_DecayModeFinding", event->TTE_Tau2HPSdecayModeFinding->at(iCombo), target)){ return target; }}

	// Leading track transverse momentum
	if(CutOn_T1_LTvalid){ if(cutFlow.CheckComboAndStop("T1_LTvalid", event->TTE_Tau1LTvalid->at(iCombo), target)){ return target; }}
	if(CutOn_T2_LTvalid){ if(cutFlow.CheckComboAndStop("T2_LTvalid", event->TTE_Tau2LTvalid->at(iCombo), target)){ return target; }}
	
	// Leading track transverse momentum
	if(CutOn_T1_LTpT){ if(cutFlow.CheckComboAndStop("T1_LTpT", event->TTE_Tau1LTPt->at(iCombo), target)){ return target; }}
	if(CutOn_T2_LTpT){ if(cutFlow.CheckComboAndStop("T2_LTpT", event->TTE_Tau2LTPt->at(iCombo), target)){ return target; }}

	// Signal track multiplicity
	if(CutOn_T1_NumProngs){ if(cutFlow.CheckComboAndStop("T1_NumProngs", event->TTE_Tau1NProngs->at(iCombo), target)){ return target; }}
	if(CutOn_T2_NumProngs){ if(cutFlow.CheckComboAndStop("T2_NumProngs", event->TTE_Tau2NProngs->at(iCombo), target)){ return target; }}

	// Anti electron
	if(CutOn_T1_AntiElectronMVA){ if(cutFlow.CheckComboAndStop("T1_AntiElectronMVA", event->TTE_Tau1HPSagainstElectronMVA->at(iCombo), target)){ return target; }}
	if(CutOn_T1_AntiElectronIndex){ if(cutFlow.CheckComboAndStop("T1_AntiElectronIndex", event->GetTau1AntiElectronIndex(iCombo), target)){ return target; }}
	if(CutOn_T2_AntiElectronMVA){ if(cutFlow.CheckComboAndStop("T2_AntiElectronMVA", event->TTE_Tau2HPSagainstElectronMVA->at(iCombo), target)){ return target; }}
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
	if(CutOn_TT_DeltaEta){ if(cutFlow.CheckComboAndStop("TT_DeltaEta", event->TTE_Tau1Eta->at(iCombo)-event->TTE_Tau2Eta->at(iCombo), target)){ return target; }}

	// TT_Cosine Delta phi
	if(CutOn_TT_CosDeltaPhi){ if(cutFlow.CheckComboAndStop("TT_CosDeltaPhi", event->TTE_DitauCosDeltaPhi->at(iCombo), target)){ return target; }}

	// Missing transverse energy
	if(CutOn_MET){ if(cutFlow.CheckComboAndStop("MET", event->Ev_MET, target)){ return target; }}


	// Return target, first element is for signal analysis, second is for QCD
	return target;
}

