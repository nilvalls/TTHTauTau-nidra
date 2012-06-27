/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			07 Jun 2011
    Description:	Plotting macro for ditau analysis.
    Notes:

*/

#define TTAnalyzer_cxx
#include "TTAnalyzer.h"

using namespace std;

TTAnalyzer::TTAnalyzer(){
		event = NULL;
		goodEventsForSignal.clear();
		goodEventsForQCD.clear();
		tmvaEvaluator = NULL;
}

// Default constructor
TTAnalyzer::TTAnalyzer(map<string,string> const & iParams){

	params = iParams;

	event = NULL;
	goodEventsForSignal.clear();
	goodEventsForQCD.clear();

	cutFlow		= CutFlow(params["cutsToApply"]);
	cutFlow.Reset();

	#include "clarity/cuts_false.h"
	SetCutsToApply(params["cutsToApply"]);

	// If a cut on the MVA is requested, initialize TMVA reader
	if(CutOn_MVA){ tmvaEvaluator = new TMVAEvaluator(iParams); }
	else{ tmvaEvaluator = NULL; }

}


// Default destructor
TTAnalyzer::~TTAnalyzer(){
	delete event; event = NULL;
	delete tmvaEvaluator; tmvaEvaluator = NULL;
}


void TTAnalyzer::AnalyzeAll(ProPack& iProPack){

	// Print processes to be analyzed and plotted
	cout << endl;
	cout << "\tTo be analyzed: " << iProPack.GetProccessNamesToAnalyze() << endl;
	cout << endl;

	map<string,Process> * processes = iProPack.GetPContainer()->GetContainer();
	for(map<string,Process>::iterator p = processes->begin(); p != processes->end(); p++){ Analyze((p)->second); }
}

void TTAnalyzer::Analyze(Process& iProcess){

	//Reset();
	cout << "\tNow analyzing " << iProcess.GetShortName() << endl;

	cutFlow.Zero();
	cutFlow.SetCutCounts("Read from DS", iProcess.GetNOEinDS(), iProcess.GetNOEinDS());
	cutFlow.SetCutCounts("skimming + PAT", iProcess.GetNOEinPATuple(), iProcess.GetNOEinPATuple());
	goodEventsForSignal.clear();
	goodEventsForQCD.clear();

	DitauBranches event2 = DitauBranches(params, ((params.find("ntuplesDir")->second) + (iProcess.GetNtuplePath())));
//	event = new DitauBranches(params, iProcess.GetNtuplePath());
	event = &event2;

	isSignal = iProcess.IsSignal();
	isMC = iProcess.IsMC();
	pair<double,double> loopResults = Loop();
	cout << endl;

	iProcess.SetGoodEventsForSignal(goodEventsForSignal);
	iProcess.SetGoodEventsForQCD(goodEventsForQCD);
	iProcess.SetNOEinNtuple(loopResults.first);
	iProcess.SetNOEanalyzed(loopResults.second);
	iProcess.SetCutFlow(cutFlow);

	//delete event;
	event = NULL;
}

void TTAnalyzer::Analyze(vector<Process>& iProcesses){
	for(unsigned int p=0; p<iProcesses.size(); p++){ Analyze(iProcesses.at(p)); }
}

void TTAnalyzer::Reset(){
}

pair<double,double> TTAnalyzer::Loop(){

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
 
	if(atoi((params["maxEvents"]).c_str()) >= 0){ cutFlow.SetCutCounts("User event limit", maxEvents, maxEvents); }

	// Actual loop
	double NOEanalyzed = 0;
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

		// Inform cutFlow that a new event is starting
		cutFlow.StartOfEvent();

		// Loop over all the combos
		for (unsigned int combo = 0; combo < event->TTM_NumCombos; combo++){

			// Obtain combo's mass
			float comboMass = event->TTM_DitauVisibleMass.at(combo);

			// Apply all selections here (do this first)
			if( comboMass <= 0 ){ continue; }

			// Rest of selections
			pair<bool,bool> combosTarget = ComboPassesCuts(combo);

			// Inform cutFlow that we've checked this combo against all cuts
			cutFlow.EndOfCombo(combosTarget, combo);

			// If we already have one good combo for signal and one for QCD, no need to check the rest since the heaviest combos come first
			if(cutFlow.HaveGoodCombos()){ break; }
		}

		// Inform cutFlow that we've checked all the combos
		cutFlow.EndOfEvent();

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

	result = make_pair(nentries, NOEanalyzed);
	return result;
}



pair<bool,bool> TTAnalyzer::ComboPassesCuts(unsigned int iCombo){

	///***/// LS QCD business, this is a bit tricky... ///***///
	bool isForSignal = true;
	bool isForQCD = false;

	int chargeProduct = (event->TTM_Tau1Charge.at(iCombo))*(event->TTM_Tau2Charge.at(iCombo));
	isForQCD = (chargeProduct == 1);

	pair<bool,bool> target = make_pair(true, isForQCD);
	///***/// 	End of LS/QCD business	 ///***///



	// ============================= Generator Cuts ============================= //
	// Number of hadronic taus
	if(CutOn_NumHadronicGenTaus){
		//if(isMC){
		if(isSignal){
			if(cutFlow.CheckComboAndStop("NumHadronicGenTaus", event->NumberOfHadronicGenTaus, target)){ return target; }
		}else{
			cutFlow.ComboIsGood("NumHadronicGenTaus");
		}
	}

	// ============================= Acceptance Cuts ============================= //

	// Invariant mass
	if(CutOn_InvariantMass){ if(cutFlow.CheckComboAndStop("InvariantMass", event->TauTauVisPlusMetMass->at(iCombo), target)){ return target; }}

	// Transverse momentum
	if(CutOn_LL_pT){ if(cutFlow.CheckComboAndStop("LL_pT", event->Tau1Pt->at(iCombo), target)){ return target; }}
	if(CutOn_SL_pT){ if(cutFlow.CheckComboAndStop("SL_pT", event->Tau2Pt->at(iCombo), target)){ return target; }}

	// Pseudorapidity
	if(CutOn_LL_Eta){ if(cutFlow.CheckComboAndStop("LL_Eta", event->Tau1Eta->at(iCombo), target)){ return target; }}
	if(CutOn_SL_Eta){ if(cutFlow.CheckComboAndStop("SL_Eta", event->Tau2Eta->at(iCombo), target)){ return target; }}

	// Delta R
	if(CutOn_DeltaR){ if(cutFlow.CheckComboAndStop("DeltaR", event->TauTauDeltaR->at(iCombo), target)){ return target; }}


	// ============================= Tau-ID Cuts ============================= //

	// DitauDecayModeIndex
	if(CutOn_DDMI){
		int DDMI = -1;
		if(event->Tau1DecayMode->at(iCombo)<0 || event->Tau2DecayMode->at(iCombo)<0){ DDMI = -1; }
		else if(event->Tau1DecayMode->at(iCombo)==0 && event->Tau2DecayMode->at(iCombo)==0){ DDMI = 0; }
		else if(
				(event->Tau1DecayMode->at(iCombo)==0 && event->Tau2DecayMode->at(iCombo) == 1) ||
				(event->Tau1DecayMode->at(iCombo)==0 && event->Tau2DecayMode->at(iCombo) == 2) ||
				(event->Tau1DecayMode->at(iCombo)==0 && event->Tau2DecayMode->at(iCombo) == 3) ||
				(event->Tau1DecayMode->at(iCombo)==0 && event->Tau2DecayMode->at(iCombo) == 4) ||
				(event->Tau1DecayMode->at(iCombo)==1 && event->Tau2DecayMode->at(iCombo) == 0) ||
				(event->Tau1DecayMode->at(iCombo)==2 && event->Tau2DecayMode->at(iCombo) == 0) ||
				(event->Tau1DecayMode->at(iCombo)==3 && event->Tau2DecayMode->at(iCombo) == 0) ||
				(event->Tau1DecayMode->at(iCombo)==4 && event->Tau2DecayMode->at(iCombo) == 0) ){ DDMI = 1; }
		else if(
				(event->Tau1DecayMode->at(iCombo)==0 && event->Tau2DecayMode->at(iCombo)>=10) ||
				(event->Tau1DecayMode->at(iCombo)>=10 && event->Tau2DecayMode->at(iCombo)==0) ){ DDMI = 2; }
		else{ DDMI = 3; }

		if(cutFlow.CheckComboAndStop("DDMI", DDMI, target)){ return target; }
	}

	// Dievent->TauTrackMultiplicityIndex
	if(CutOn_DTMI){
		int DTMI = -1;
		if((event->Tau1NProngs->at(iCombo)<1) || (event->Tau2NProngs->at(iCombo)<1)){ DTMI = -1; }
		else if(event->Tau1NProngs->at(iCombo)==1 && event->Tau2NProngs->at(iCombo)==1){ DTMI = 0; }
		else if((event->Tau1NProngs->at(iCombo)==1 && event->Tau2NProngs->at(iCombo)==3) || (event->Tau2NProngs->at(iCombo)==1 && event->Tau1NProngs->at(iCombo)==3)){ DTMI = 1; }
		else if(event->Tau1NProngs->at(iCombo)==3 && event->Tau2NProngs->at(iCombo)==3){ DTMI = 2; }
		else{ DTMI = 3; }

		if(cutFlow.CheckComboAndStop("DTMI", DTMI, target)){ return target; }
	}

	// Leading track transverse momentum
	if(CutOn_LL_LTvalid){ if(cutFlow.CheckComboAndStop("LL_LTvalid", event->Tau1LTvalid->at(iCombo), target)){ return target; }}
	if(CutOn_SL_LTvalid){ if(cutFlow.CheckComboAndStop("SL_LTvalid", event->Tau2LTvalid->at(iCombo), target)){ return target; }}
	
	// Leading track transverse momentum
	if(CutOn_LL_LTpT){ if(cutFlow.CheckComboAndStop("LL_LTpT", event->Tau1LTPt->at(iCombo), target)){ return target; }}
	if(CutOn_SL_LTpT){ if(cutFlow.CheckComboAndStop("SL_LTpT", event->Tau2LTPt->at(iCombo), target)){ return target; }}

	// Leading track number of hits
	if(CutOn_LL_LTHits){ if(cutFlow.CheckComboAndStop("LL_LThits", event->Tau1LTValidHits->at(iCombo), target)){ return target; }}
	if(CutOn_SL_LTHits){ if(cutFlow.CheckComboAndStop("SL_LThits", event->Tau2LTValidHits->at(iCombo), target)){ return target; }}

	// Crack veto
	if(CutOn_LL_InCracks){ if(cutFlow.CheckComboAndStop("LL_InCracks", event->Tau1IsInTheCracks->at(iCombo), target)){ return target; }}
	if(CutOn_SL_InCracks){ if(cutFlow.CheckComboAndStop("SL_InCracks", event->Tau2IsInTheCracks->at(iCombo), target)){ return target; }}

	// Against Electron
	if( CutOn_LL_AgainstTightElectron ){ if(cutFlow.CheckComboAndStop("LL_AgainstTightElectron",
		event->Tau1hpsPFTauDiscriminationAgainstTightElectron->at(iCombo), target)){ return target; }}
	else if( CutOn_LL_AgainstMediumElectron ){ if(cutFlow.CheckComboAndStop("LL_AgainstMediumElectron",
		event->Tau1hpsPFTauDiscriminationAgainstMediumElectron->at(iCombo), target)){ return target; }}
	else if( CutOn_LL_AgainstLooseElectron ){ if(cutFlow.CheckComboAndStop("LL_AgainstLooseElectron",
		event->Tau1hpsPFTauDiscriminationAgainstLooseElectron->at(iCombo), target)){ return target; }}
	
	if( CutOn_SL_AgainstTightElectron ){ if(cutFlow.CheckComboAndStop("SL_AgainstTightElectron",
		event->Tau2hpsPFTauDiscriminationAgainstTightElectron->at(iCombo), target)){ return target; }}
	else if( CutOn_SL_AgainstMediumElectron ){ if(cutFlow.CheckComboAndStop("SL_AgainstMediumElectron",
		event->Tau2hpsPFTauDiscriminationAgainstMediumElectron->at(iCombo), target)){ return target; }}
	else if( CutOn_SL_AgainstLooseElectron ){ if(cutFlow.CheckComboAndStop("SL_AgainstLooseElectron",
		event->Tau2hpsPFTauDiscriminationAgainstLooseElectron->at(iCombo), target)){ return target; }}


	// Against Muon
	if( CutOn_LL_AgainstTightMuon ){ if(cutFlow.CheckComboAndStop("LL_AgainstTightMuon",
		event->Tau1hpsPFTauDiscriminationAgainstTightMuon->at(iCombo), target)){ return target; }}
	else if( CutOn_LL_AgainstLooseMuon ){ if(cutFlow.CheckComboAndStop("LL_AgainstLooseMuon",
		event->Tau1hpsPFTauDiscriminationAgainstLooseMuon->at(iCombo), target)){ return target; }}

	if( CutOn_SL_AgainstTightMuon ){ if(cutFlow.CheckComboAndStop("SL_AgainstTightMuon",
		event->Tau2hpsPFTauDiscriminationAgainstTightMuon->at(iCombo), target)){ return target; }}
	else if( CutOn_SL_AgainstLooseMuon ){ if(cutFlow.CheckComboAndStop("SL_AgainstLooseMuon",
		event->Tau2hpsPFTauDiscriminationAgainstLooseMuon->at(iCombo), target)){ return target; }}


	// Isolation
	if( CutOn_LL_TightIso){ if(cutFlow.CheckComboAndStop("LL_TightIso",
		event->Tau1hpsPFTauDiscriminationByTightIsolation->at(iCombo), target)){ return target; }}
	else if( CutOn_LL_MediumIso){ if(cutFlow.CheckComboAndStop("LL_MediumIso",
		event->Tau1hpsPFTauDiscriminationByMediumIsolation->at(iCombo), target)){ return target; }}
	else if( CutOn_LL_LooseIso){ if(cutFlow.CheckComboAndStop("LL_LooseIso",
		event->Tau1hpsPFTauDiscriminationByLooseIsolation->at(iCombo), target)){ return target; }}
	else if( CutOn_LL_VLooseIso){ if(cutFlow.CheckComboAndStop("LL_VLooseIso",
		event->Tau1hpsPFTauDiscriminationByVLooseIsolation->at(iCombo), target)){ return target; }}

	if( CutOn_SL_TightIso){ if(cutFlow.CheckComboAndStop("SL_TightIso",
		event->Tau2hpsPFTauDiscriminationByTightIsolation->at(iCombo), target)){ return target; }}
	else if( CutOn_SL_MediumIso){ if(cutFlow.CheckComboAndStop("SL_MediumIso",
		event->Tau2hpsPFTauDiscriminationByMediumIsolation->at(iCombo), target)){ return target; }}
	else if( CutOn_SL_LooseIso){ if(cutFlow.CheckComboAndStop("SL_LooseIso",
		event->Tau2hpsPFTauDiscriminationByLooseIsolation->at(iCombo), target)){ return target; }}
	else if( CutOn_SL_VLooseIso){ if(cutFlow.CheckComboAndStop("SL_VLooseIso",
		event->Tau2hpsPFTauDiscriminationByVLooseIsolation->at(iCombo), target)){ return target; }}


	// Decay mode
	if(CutOn_LL_DecayModeFinding){ if(cutFlow.CheckComboAndStop("LL_DecayModeFinding", event->Tau1hpsPFTauDiscriminationByDecayModeFinding->at(iCombo), target)){ return target; }}
	if(CutOn_SL_DecayModeFinding){ if(cutFlow.CheckComboAndStop("SL_DecayModeFinding", event->Tau2hpsPFTauDiscriminationByDecayModeFinding->at(iCombo), target)){ return target; }}
	if(CutOn_LL_DecayMode){ if(cutFlow.CheckComboAndStop("LL_DecayMode", event->Tau1DecayMode->at(iCombo), target)){ return target; }}
	if(CutOn_SL_DecayMode){ if(cutFlow.CheckComboAndStop("SL_DecayMode", event->Tau2DecayMode->at(iCombo), target)){ return target; }}

	// Signal track multiplicity
	if(CutOn_LL_NumProngs){ if(cutFlow.CheckComboAndStop("LL_NumProngs", event->Tau1NProngs->at(iCombo), target)){ return target; }}
	if(CutOn_SL_NumProngs){ if(cutFlow.CheckComboAndStop("SL_NumProngs", event->Tau2NProngs->at(iCombo), target)){ return target; }}

	// ============================= Topological Cuts ============================= //

	// Charge product
	if(CutOn_ChargeProduct){
		target = make_pair(cutFlow.CheckComboDiscretely("ChargeProduct", chargeProduct), isForQCD);
		if(cutFlow.CheckComboAndStop("ChargeProduct", chargeProduct, target, true)){ return target; }
	}

	// Delta eta between taus
	if(CutOn_DeltaEta){ if(cutFlow.CheckComboAndStop("DeltaEta", event->Tau1Eta->at(iCombo)-event->Tau2Eta->at(iCombo), target)){ return target; }}

	// Cosine Delta phi
	if(CutOn_CosDeltaPhi){ if(cutFlow.CheckComboAndStop("CosDeltaPhi", event->TauTauCosDPhi->at(iCombo), target)){ return target; }}

	// Missing transverse energy
	if(CutOn_MET){ if(cutFlow.CheckComboAndStop("MET", event->MET->at(iCombo), target)){ return target; }}

	// Zeta
	if(CutOn_Zeta){ 
		float zeta = event->TauTauPZeta->at(iCombo)-0.875*event->TauTauPZetaVis->at(iCombo);
		if(cutFlow.CheckComboAndStop("Zeta",zeta, target)){ return target; }
	}

	// Btags
	if(CutOn_Btags){ if(cutFlow.CheckComboAndStop("Btags",event->nBtagsHiEffTrkCnt->at(iCombo), target)){ return target; }}

	// Valid SVFit solution
	if(CutOn_SVFitStatus){ if(cutFlow.CheckComboAndStop("SVFitStatus",event->NSVFitStatus->at(iCombo), target)){ return target; }}

	// Valid SVFit solution
	if(CutOn_MVA){ if(cutFlow.CheckComboAndStop("MVA", tmvaEvaluator->Evaluate(event, iCombo), target)){ return target; }}

	// Return target, first element is for signal analysis, second is for QCD
	return target;
}



void TTAnalyzer::SetCutsToApply(string iCutsToApply){
	#include "clarity/cuts_setCutsToApply.h"
}





bool TTAnalyzer::ApplyThisCut(string thisCut){

	bool result = false;

	string cutsToApply = params["cutsToApply"];
	cutsToApply = " " + cutsToApply + " ";

	size_t foundNDef = cutsToApply.find(" " + thisCut + ":");
	size_t length = cutsToApply.length();

	if ( 0 <= foundNDef && foundNDef <= length ){ result = true; }
	else{ result = false; }

	return result;

}


bool TTAnalyzer::IsFlagThere(string iFlag){
	string flags = params["flags"];
	size_t found = flags.find(iFlag);
	return ((0 <= found) && (found < flags.length()));
}

