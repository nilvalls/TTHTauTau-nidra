/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			07 Jun 2011
    Description:	Plotting macro for ditau analysis.
    Notes:

*/

#define Analyzer_cxx
#include "Analyzer.h"

using namespace std;

Analyzer::Analyzer(){

		event = NULL;
		fChain = NULL;
		tauTrigger = NULL;
		puCorrector = NULL;
		goodEventsForSignal.clear();
		goodEventsForQCD.clear();
}

// Default constructor
Analyzer::Analyzer(map<string,string> const & iParams){

	params = iParams;

	event = NULL;
	fChain = NULL;
	tauTrigger = NULL;
	puCorrector = NULL;
	goodEventsForSignal.clear();
	goodEventsForQCD.clear();

	cutFlow		= CutFlow(params["cutsToApply"]);
	cutFlow.Reset();

	#include "clarity/falseCuts.h"
	SetCutsToApply(params["cutsToApply"]);

	puCorrector			= new PUcorrector(params["puList"]);
	tauTrigger			= new Trigger(4600);

}


// Default destructor
Analyzer::~Analyzer(){

	if (!fChain) return;
	delete fChain->GetCurrentFile();

}

void Analyzer::Analyze(Process& iProcess){

	//Reset();

	cutFlow.Zero();
	cutFlow.SetPreCutForSignal("Read from DS", iProcess.GetNOEinDS());
	cutFlow.SetPreCutForQCD("Read from DS", iProcess.GetNOEinDS());
	cutFlow.SetPreCutForSignal("skimming + PAT", iProcess.GetNOEinPATuple());
	cutFlow.SetPreCutForQCD("skimming + PAT", iProcess.GetNOEinPATuple());
	goodEventsForSignal.clear();
	goodEventsForQCD.clear();

	applyTrigger		= (IsFlagThere("trigger") && iProcess.IsMC());
	applyPUreweighing	= (IsFlagThere("PUcorr") && iProcess.IsMC());

	Init(iProcess.GetNtuplePath());

	pair<double,double> loopResults = Loop();

	iProcess.SetGoodEventsForSignal(goodEventsForSignal);
	iProcess.SetGoodEventsForQCD(goodEventsForQCD);
	iProcess.SetNOEinNtuple(loopResults.first);
	iProcess.SetNOEanalyzed(loopResults.second);
	iProcess.SetCutFlow(cutFlow);

	event = NULL;

}

void Analyzer::Analyze(vector<Process>& iProcesses){
	for(unsigned int p=0; p<iProcesses.size(); p++){ Analyze(iProcesses.at(p)); }
}

void Analyzer::Reset(){
}

pair<double,double> Analyzer::Loop(){

	pair<double,double> result = make_pair(0,0);
	int maxEvents = atoi((params["maxEvents"]).c_str());

	cout << ">>> Starting loop... "; cout.flush();

	if (fChain == 0){ cout << endl << "ERROR: empty TChain. Exiting."; return result; }

	Long64_t nentries = fChain->GetEntries(); 
	if(nentries == 0){ cerr << "ERROR: this process has zero events to read" << endl; exit(1); }
	cout << " " << nentries << " entries available: ";
	cutFlow.SetPreCutForSignal("nTuple making", nentries);
	cutFlow.SetPreCutForQCD("nTuple making", nentries);
	if(maxEvents <= 0 || maxEvents >= nentries){ cout << "Processing all of them..." << string(14,'.') << " "; }
	else{ cout << "Stopping at " << maxEvents << " as per-user request" << string(14,'.') << " "; }
	cout.flush();

	cutFlow.SetPreCutForSignal("User event limit", maxEvents);
	cutFlow.SetPreCutForQCD("User event limit", maxEvents);

	// Actual loop
	double NOEanalyzed = 0;
	for (Long64_t jentry=0; jentry<nentries; jentry++) {
		// Keep user informed of the number of events processed and if there is a termination due to reaching of the limit
		if ( maxEvents > 0 && jentry >= (unsigned int)(maxEvents)){ cout << "\n>>> INFO: Reached user-imposed event number limit (" << maxEvents << "), skipping the rest." << endl; break; }

		int prevLength = 0;
		if (jentry>0 && (jentry+1)%1000==0){ 
			stringstream jentryss; jentryss.str("");
			jentryss << (jentry+1);
			cout << string((jentryss.str()).length(),'\b') << string((jentryss.str()).length(),' ') << string((jentryss.str()).length(),'\b') << jentryss.str(); cout.flush(); 
			prevLength = (jentryss.str()).length();
		}

		// Get a new entry
		event->AlienGetEntry(jentry);

		// Inform cutFlow that a new event is starting
		cutFlow.StartOfEvent();

		// Loop over all the combos
		for (unsigned int combo = 0; combo < event->Tau1Pt->size(); combo++){
			// Obtain combo's mass
			float comboMass = event->TauTauVisPlusMetMass->at(combo);
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

			float puWeight			= GetPUweight(heaviestComboForSignal);
			float tau1TriggerWeight	= GetTau1TriggerWeight(heaviestComboForSignal);
			float tau2TriggerWeight	= GetTau2TriggerWeight(heaviestComboForSignal);

			cutFlow.AddPostCutEventForSignal("PU reweighing", puWeight);
			cutFlow.AddPostCutEventForSignal("LL trigger", puWeight*tau1TriggerWeight);
			cutFlow.AddPostCutEventForSignal("SL trigger", puWeight*tau1TriggerWeight*tau2TriggerWeight);

			event->SetPUweight(puWeight);
			event->SetTriggerWeights(tau1TriggerWeight,tau2TriggerWeight);
			event->SetBestCombo(heaviestComboForSignal);
			goodEventsForSignal.push_back(make_pair(jentry, heaviestComboForSignal));

		}

		// Fill good event vectors for QCD analysis
		if(cutFlow.EventForQCDPassed()){
			int heaviestComboForQCD = cutFlow.GetHeaviestComboForQCD();

			float puWeight			= GetPUweight(heaviestComboForQCD);
			float tau1TriggerWeight	= GetTau1TriggerWeight(heaviestComboForQCD);
			float tau2TriggerWeight	= GetTau2TriggerWeight(heaviestComboForQCD);

			cutFlow.AddPostCutEventForQCD("PU reweighing", puWeight);
			cutFlow.AddPostCutEventForQCD("LL trigger", puWeight*tau1TriggerWeight);
			cutFlow.AddPostCutEventForQCD("SL trigger", puWeight*tau1TriggerWeight*tau2TriggerWeight);

			event->SetPUweight(puWeight);
			event->SetTriggerWeights(tau1TriggerWeight,tau2TriggerWeight);
			event->SetBestCombo(heaviestComboForQCD);
			goodEventsForQCD.push_back(make_pair(jentry, heaviestComboForQCD));

		}

		NOEanalyzed++;
	}

	result = make_pair(nentries, NOEanalyzed);
	return result;
}



pair<bool,bool> Analyzer::ComboPassesCuts(unsigned int iCombo){

	///***/// LS QCD business, this is a bit tricky... ///***///
	bool isLS = false;
	bool satisfiesChargeProduct = false;

	int chargeProduct = (event->Tau1Charge->at(iCombo))*(event->Tau2Charge->at(iCombo));
	if(CutOn_ChargeProduct){ satisfiesChargeProduct = cutFlow.CheckCombo("ChargeProduct", chargeProduct); }
	isLS = (chargeProduct == 1);

	bool isForSignal = ((!CutOn_ChargeProduct) || (satisfiesChargeProduct)); //*/
	//pair<bool,bool> result = make_pair(isForSignal, isLS);
	pair<bool,bool> result = make_pair(true, isLS);
	///***/// 	End of LS/QCD business	 ///***///

	// ============================= Acceptance Cuts ============================= //

	// Transverse momentum
	if(CutOn_LL_pT){ if(!cutFlow.CheckCombo("LL_pT", event->Tau1Pt->at(iCombo))){ return result; }}
	if(CutOn_SL_pT){ if(!cutFlow.CheckCombo("SL_pT", event->Tau2Pt->at(iCombo))){ return result; }}

	// Pseudorapidity
	if(CutOn_LL_Eta){ if(!cutFlow.CheckCombo("LL_Eta", event->Tau1Eta->at(iCombo))){ return result; }}
	if(CutOn_SL_Eta){ if(!cutFlow.CheckCombo("SL_Eta", event->Tau2Eta->at(iCombo))){ return result; }}

	// Delta R
	if(CutOn_DeltaR){ if(!cutFlow.CheckCombo("DeltaR", event->TauTauDeltaR->at(iCombo))){ return result; }}


	// ============================= Tau-ID Cuts ============================= //
	
	// Leading track transverse momentum
	if(CutOn_LL_LTpT){ if(!cutFlow.CheckCombo("LL_LTpT", event->Tau1LTPt->at(iCombo))){ return result; }}
	if(CutOn_SL_LTpT){ if(!cutFlow.CheckCombo("SL_LTpT", event->Tau2LTPt->at(iCombo))){ return result; }}

	// Leading track number of hits
	if(CutOn_LL_LTHits){ if(!cutFlow.CheckCombo("LL_LThits", event->Tau1LTValidHits->at(iCombo))){ return result; }}
	if(CutOn_SL_LTHits){ if(!cutFlow.CheckCombo("SL_LThits", event->Tau2LTValidHits->at(iCombo))){ return result; }}

	// Crack veto
	if(CutOn_LL_InCracks){ if(!cutFlow.CheckCombo("LL_InCracks", event->Tau1IsInTheCracks->at(iCombo))){ return result; }}
	if(CutOn_SL_InCracks){ if(!cutFlow.CheckCombo("SL_InCracks", event->Tau2IsInTheCracks->at(iCombo))){ return result; }}

	// Against Electron
	if( CutOn_LL_AgainstTightElectron ){ if(!cutFlow.CheckCombo("LL_AgainstTightElectron",
		event->Tau1hpsPFTauDiscriminationAgainstTightElectron->at(iCombo))){ return result; }}
	else if( CutOn_LL_AgainstMediumElectron ){ if(!cutFlow.CheckCombo("LL_AgainstMediumElectron",
		event->Tau1hpsPFTauDiscriminationAgainstMediumElectron->at(iCombo))){ return result; }}
	else if( CutOn_LL_AgainstLooseElectron ){ if(!cutFlow.CheckCombo("LL_AgainstLooseElectron",
		event->Tau1hpsPFTauDiscriminationAgainstLooseElectron->at(iCombo))){ return result; }}
	
	if( CutOn_SL_AgainstTightElectron ){ if(!cutFlow.CheckCombo("SL_AgainstTightElectron",
		event->Tau2hpsPFTauDiscriminationAgainstTightElectron->at(iCombo))){ return result; }}
	else if( CutOn_SL_AgainstMediumElectron ){ if(!cutFlow.CheckCombo("SL_AgainstMediumElectron",
		event->Tau2hpsPFTauDiscriminationAgainstMediumElectron->at(iCombo))){ return result; }}
	else if( CutOn_SL_AgainstLooseElectron ){ if(!cutFlow.CheckCombo("SL_AgainstLooseElectron",
		event->Tau2hpsPFTauDiscriminationAgainstLooseElectron->at(iCombo))){ return result; }}


	// Against Muon
	if( CutOn_LL_AgainstTightMuon ){ if(!cutFlow.CheckCombo("LL_AgainstTightMuon",
		event->Tau1hpsPFTauDiscriminationAgainstTightMuon->at(iCombo))){ return result; }}
	else if( CutOn_LL_AgainstLooseMuon ){ if(!cutFlow.CheckCombo("LL_AgainstLooseMuon",
		event->Tau1hpsPFTauDiscriminationAgainstLooseMuon->at(iCombo))){ return result; }}

	if( CutOn_SL_AgainstTightMuon ){ if(!cutFlow.CheckCombo("SL_AgainstTightMuon",
		event->Tau2hpsPFTauDiscriminationAgainstTightMuon->at(iCombo))){ return result; }}
	else if( CutOn_SL_AgainstLooseMuon ){ if(!cutFlow.CheckCombo("SL_AgainstLooseMuon",
		event->Tau2hpsPFTauDiscriminationAgainstLooseMuon->at(iCombo))){ return result; }}


	// Isolation
	if( CutOn_LL_TightIso){ if(!cutFlow.CheckCombo("LL_TightIso",
		event->Tau1hpsPFTauDiscriminationByTightIsolation->at(iCombo))){ return result; }}
	else if( CutOn_LL_MediumIso){ if(!cutFlow.CheckCombo("LL_MediumIso",
		event->Tau1hpsPFTauDiscriminationByMediumIsolation->at(iCombo))){ return result; }}
	else if( CutOn_LL_LooseIso){ if(!cutFlow.CheckCombo("LL_LooseIso",
		event->Tau1hpsPFTauDiscriminationByLooseIsolation->at(iCombo))){ return result; }}
	else if( CutOn_LL_VLooseIso){ if(!cutFlow.CheckCombo("LL_VLooseIso",
		event->Tau1hpsPFTauDiscriminationByVLooseIsolation->at(iCombo))){ return result; }}

	if( CutOn_SL_TightIso){ if(!cutFlow.CheckCombo("SL_TightIso",
		event->Tau2hpsPFTauDiscriminationByTightIsolation->at(iCombo))){ return result; }}
	else if( CutOn_SL_MediumIso){ if(!cutFlow.CheckCombo("SL_MediumIso",
		event->Tau2hpsPFTauDiscriminationByMediumIsolation->at(iCombo))){ return result; }}
	else if( CutOn_SL_LooseIso){ if(!cutFlow.CheckCombo("SL_LooseIso",
		event->Tau2hpsPFTauDiscriminationByLooseIsolation->at(iCombo))){ return result; }}
	else if( CutOn_SL_VLooseIso){ if(!cutFlow.CheckCombo("SL_VLooseIso",
		event->Tau2hpsPFTauDiscriminationByVLooseIsolation->at(iCombo))){ return result; }}


	// Decay mode
	if(CutOn_LL_DecayModeFinding){ if(!cutFlow.CheckCombo("LL_DecayModeFinding", event->Tau1hpsPFTauDiscriminationByDecayModeFinding->at(iCombo))){ return result; }}
	if(CutOn_SL_DecayModeFinding){ if(!cutFlow.CheckCombo("SL_DecayModeFinding", event->Tau2hpsPFTauDiscriminationByDecayModeFinding->at(iCombo))){ return result; }}
	if(CutOn_LL_DecayMode){ if(!cutFlow.CheckCombo("LL_DecayMode", event->Tau1DecayMode->at(iCombo))){ return result; }}
	if(CutOn_SL_DecayMode){ if(!cutFlow.CheckCombo("SL_DecayMode", event->Tau2DecayMode->at(iCombo))){ return result; }}

	// Signal track multiplicity
	if(CutOn_LL_NumProngs){ if(!cutFlow.CheckCombo("LL_NumProngs", event->Tau1NProngs->at(iCombo))){ return result; }}
	if(CutOn_SL_NumProngs){ if(!cutFlow.CheckCombo("SL_NumProngs", event->Tau2NProngs->at(iCombo))){ return result; }}

	// ============================= Topological Cuts ============================= //

	// Cosine Delta phi
	if(CutOn_CosDeltaPhi){ if(!cutFlow.CheckCombo("CosDeltaPhi", event->TauTauCosDPhi->at(iCombo))){ return result; }}

	// Missing transverse energy
	if(CutOn_MET){ if(!cutFlow.CheckCombo("MET", event->MET->at(iCombo))){ return result; }}

	// Zeta
	if(CutOn_Zeta){ 
		float zeta = event->TauTauPZeta->at(iCombo)-0.875*event->TauTauPZetaVis->at(iCombo);
		if(!cutFlow.CheckCombo("Zeta",zeta)){ return result; }
	}

	// Btags
	if(CutOn_Btags){ if(!cutFlow.CheckCombo("Btags",event->nBtagsHiEffTrkCnt->at(iCombo))){ return result; }}

	//*/
	// Return target, first element is for signal analysis, second is for QCD
	return result;
}



void Analyzer::SetCutsToApply(string iCutsToApply){

	#include "clarity/setCutsToApply.h"

//	MakeCutsPave();
}


void Analyzer::AnalyzeAll(ProPack& iProPack){

	if(iProPack.HaveCollisions()){									Analyze(*iProPack.GetCollisions());		}
	if(iProPack.HaveMCbackgrounds()){								Analyze(*iProPack.GetMCbackgrounds());	}
	if(iProPack.HaveSignals()){										Analyze(*iProPack.GetSignals());			}

	iProPack.SetAnalyzed();
}

DitauBranches const * Analyzer::GetDitauBranches(double iEntry) const {
	if(fChain == NULL){ cerr << "ERROR: trying to obtain DitauBranches but fChain has not been initialized" << endl; exit(1); }	
	if(iEntry < 0){ cerr << "ERROR: trying to obtain a negative entry (" << iEntry << ") from tree" << endl; exit(1); }
	if(iEntry > fChain->GetEntries()){ cerr << "ERROR: trying to obtain entry " << iEntry << " but TChain only contains " << fChain->GetEntries() << endl; exit(1); }

	event->AlienGetEntry(iEntry);

	return event;
}

TChain* Analyzer::GetTChain(string iPath){

	// Chain to return
	TChain* result = new TChain((params["treeName"]).c_str());

	// Add all *.root files in iPath
	string pathToRootFiles = iPath + "/*.root";
	result->Add(pathToRootFiles.c_str());

	// Return TChain
	return result;
}


void Analyzer::Init(string iPath){

	fChain = GetTChain(iPath);
	event = new DitauBranches();

	// Set branch addresses and branch pointers
	if (!fChain) return;
	fCurrent = -1; 
	fChain->SetMakeClass(1);

	event->AlienSetChain(fChain);
	event->AlienInit();
}

Long64_t Analyzer::LoadTree(Long64_t entry){
	// Set the environment to read one entry
	if (!fChain) return -5;
	Long64_t centry = fChain->LoadTree(entry);
	if (centry < 0) return centry;
	if (!fChain->InheritsFrom(TChain::Class()))  return centry;
	TChain *chain = (TChain*)fChain;
	if (chain->GetTreeNumber() != fCurrent) {
		fCurrent = chain->GetTreeNumber();
	}
	return centry;
}



bool Analyzer::ApplyThisCut(string thisCut){

	bool result = false;

	string cutsToApply = params["cutsToApply"];
	cutsToApply = " " + cutsToApply + " ";

	size_t foundNDef = cutsToApply.find(" " + thisCut + ":");
	size_t length = cutsToApply.length();

	if ( 0 <= foundNDef && foundNDef <= length ){ result = true; }
	else{ result = false; }

	return result;

}


bool Analyzer::IsFlagThere(string iFlag){
	string flags = params["flags"];
	size_t found = flags.find(iFlag);
	return ((0 <= found) && (found < flags.length()));
}

double Analyzer::GetPUweight(int iCombo){ 
	if(!applyPUreweighing){ return 1.0; }
	return 1;
	return puCorrector->GetWeight(event->numInteractionsBX0);
}

double Analyzer::GetTau1TriggerWeight(int iCombo){ 
	if(!applyTrigger){ return 1.0; }
	return 1;
	//return tauTrigger->GetWeightFromFunc(event->Tau1Pt->at(iCombo));
}

double Analyzer::GetTau2TriggerWeight(int iCombo){ 
	if(!applyTrigger){ return 1.0; }
	return 1;
	//return tauTrigger->GetWeightFromFunc(event->Tau2Pt->at(iCombo));
}


