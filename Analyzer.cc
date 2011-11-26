/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			07 Jun 2011
    Description:	Plotting macro for ditau analysis.
    Notes:

*/

#define Analyzer_cxx
#include "Analyzer.h"

using namespace std;


// Default constructor
Analyzer::Analyzer(map<string,string>* iParams){

	if(iParams == NULL){ cerr << "ERROR: null paramter set passed to analyzer" << endl; exit(1); }

	params = map<string,string>(*iParams);

	cutFlow		= CutFlow(params["cutsToApply"]);
	cutFlow.Reset();

	#include "clarity/falseCuts.h"
	SetCutsToApply(params["cutsToApply"]);

 	histoConfig			= new Config(params["histoCfg"]);
	puCorrector			= new PUcorrector(params["puList"]);

	tauTrigger			= new Trigger(4600);


}


// Default destructor
Analyzer::~Analyzer(){
	if (!fChain) return;
	delete fChain->GetCurrentFile();
}

void Analyzer::Analyze(Topology* iTopology){

	Reset();

	BookHistos(&histosForSignal);
	BookHistos(&histosForQCD);

	Init(iTopology->GetNtuplePath());

	Loop();
	MakeHistoWrapperVector(&histosForSignal);

	iTopology->SetHistosForSignal(MakeHistoWrapperVector(&histosForSignal));
	iTopology->SetHistosForQCD(MakeHistoWrapperVector(&histosForQCD));
	iTopology->SetCutFlow(&cutFlow);
	iTopology->SetAnalyzed();
}

void Analyzer::Analyze(vector<Topology*>* iTopologies){
	for(unsigned int t=0; t<iTopologies->size(); t++){ Analyze(iTopologies->at(t)); }
}

void Analyzer::Reset(){
	histosForSignal.clear();
	histosForQCD.clear();
//	cutFlow.Reset();
//	cutFlowLS.Reset();
}

void Analyzer::Loop(){

	int maxEvents = atoi((params["maxEvents"]).c_str());

	cout << ">>> Starting loop... "; cout.flush();

	if (fChain == 0){ cout << endl << "ERROR: empty TChain. Exiting."; return; }

	Long64_t nentries = fChain->GetEntries(); cout << " " << nentries << " entries available: ";
	if(maxEvents <= 0 || maxEvents >= nentries){ cout << "Processing all of them..." << string(14,'.') << " "; }
	else{ cout << "Stopping at " << maxEvents << " as per-user request" << string(14,'.') << " "; }
	cout.flush();

	// Actual loop
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

		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		fChain->GetEntry(jentry);

		// Loop over all the combos
		for (unsigned int combo = 0; combo < Tau1Pt->size(); combo++){
			// Obtain combo's mass
			float comboMass = TauTauVisPlusMetMass->at(combo);
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

		// Fill histos for regular passed event
		if(cutFlow.EventForSignalPassed()){
			int heaviestComboForSignal = cutFlow.GetHeaviestComboForSignal();
			FillHistosForSignal(heaviestComboForSignal);
		}

		// Fill histos for LS passed event
		if(cutFlow.EventForQCDPassed()){
			int heaviestComboForQCD = cutFlow.GetHeaviestComboForQCD();
			FillHistosForQCD(heaviestComboForQCD);
		}

	}
}



pair<bool,bool> Analyzer::ComboPassesCuts(unsigned int iCombo){

	///***/// LS QCD business, this is a bit tricky... ///***///

	bool isLS = false;
	bool satisfiesChargeProduct = false;

	int chargeProduct = (Tau1Charge->at(iCombo))*(Tau2Charge->at(iCombo));
	if(CutOn_ChargeProduct){
		satisfiesChargeProduct = cutFlow.CheckCombo("ChargeProduct", chargeProduct);
	}
	isLS = (chargeProduct == 1);

	bool isForSignal = ((!CutOn_ChargeProduct) || (satisfiesChargeProduct));
	pair<bool,bool> result = make_pair(isForSignal, isLS);

	///***/// 	End of LS/QCD business	 ///***///

	// Transverse momentum
	if(CutOn_LL_pT){ if(!cutFlow.CheckCombo("LL_pT",Tau1Pt->at(iCombo))){ return result; }; }
	if(CutOn_SL_pT){ if(!cutFlow.CheckCombo("SL_pT",Tau2Pt->at(iCombo))){ return result; }; }


	// Return target
	return result;
}



void Analyzer::SetCutsToApply(string iCutsToApply){

	#include "clarity/setCutsToApply.h"

//	MakeCutsPave();
}


void Analyzer::FillHistosForSignal(int iCombo){ FillHistos(&histosForSignal, iCombo); }

void Analyzer::FillHistosForQCD(int iCombo){ FillHistos(&histosForQCD, iCombo); }

void Analyzer::FillHistos(map<string, HistoWrapper*>* iHistos, int iCombo){
	#include "clarity/fillHistos.h"
}

/*
void Analyzer::RegisterCut(string iCut, bool iPrint){
	vector<string>::const_iterator found = find(cutsByOrder.begin(), cutsByOrder.end(), iCut);
	if( found == cutsByOrder.end() ){ // If not found already in the vector of cuts...
		cutResult* cutToInsert = new cutResult();
		cutToInsert->cutName	= iCut;
		cutToInsert->preName	= "";
		cutToInsert->postName	= "";
		cutsByOrder.push_back(iCut);

		if(iPrint){
			SetCutThresholds(iCut);

			pair<string,string> thresholdStrings = GetThresholdStrings(iCut);
			cutToInsert->preName	= thresholdStrings.first;
			cutToInsert->postName	= thresholdStrings.second;

			// Print list of cuts to screen
			cout << GetCutStringWithThresholds(iCut) << endl;

			// Add cut to list of cuts to be printed as TPaveText
			pair<float, float> thresholds = ExtractCutThresholds(iCut);
			AddCutToList(iCut,thresholds.first,thresholds.second);
		}

		cutsByOrderExtra.push_back(cutToInsert);
	}
}

pair<string,string> Analyzer::GetThresholdStrings(string iCut){
	pair<float,float> thresholds = ExtractCutThresholds(iCut);
	float cutMin = thresholds.first;
	float cutMax = thresholds.second;

	stringstream ssmin;		ssmin.str("");
	stringstream ssmax;		ssmax.str("");

	if(cutMin == cutMax){
		ssmax << " == " << cutMax;
	}else{
		if( cutMin > -FLT_MAX)	{	ssmin << cutMin << " <= "; }
		if( cutMax < FLT_MAX)	{	ssmax << " <= " << cutMax; }
	}

	return make_pair<string,string>(ssmin.str(),ssmax.str());

}


string Analyzer::GetCutStringWithThresholds(string iCut, bool iPadding){
	pair<float,float> thresholds = ExtractCutThresholds(iCut);

	float cutMin = thresholds.first;
	float cutMax = thresholds.second;

	stringstream ssmin;		ssmin.str("");
	stringstream ssmax;		ssmax.str("");
	stringstream output;	output.str("");
	int leftPad		= 20;
	int cenPad		= 15;
	int rightPad	= leftPad+cenPad+13;

	if(cutMin == cutMax){
		ssmax << " == " << cutMax;
		if(iPadding){ SpacePad(output, leftPad-(ssmin.str()).length()); }
		output << ssmin.str();
		if(iPadding){ SpacePad(output, cenPad-0.5*(iCut.length())); }
		output << iCut; 
		if(iPadding){ SpacePad(output, rightPad-(output.str()).length()); }
		output << ssmax.str();
	}else{
		if( cutMin > -FLT_MAX)	{	ssmin << cutMin << " <= "; }
		if( cutMax < FLT_MAX)	{	ssmax << " <= " << cutMax; }

		if(iPadding){ SpacePad(output, leftPad-(ssmin.str()).length()); }
		output << ssmin.str();
		if(iPadding){ SpacePad(output, cenPad-0.5*(iCut.length())); }
		output << iCut; 
		if(iPadding){ SpacePad(output, rightPad-(output.str()).length()); }
		output << ssmax.str();
	}

	return (output.str());
}

void Analyzer::SetCutThresholds(string iCut){
	pair<float,float> thresholds = ExtractCutThresholds(iCut);
	float iMin = thresholds.first;
	float iMax = thresholds.second;

	if( iCut.compare("RunNumber")					== 0 ){ Min_RunNumber					= iMin; Max_RunNumber					= iMax; }
	if( iCut.compare("LumiSection")					== 0 ){ Min_LumiSection					= iMin; Max_LumiSection					= iMax; }
	if( iCut.compare("EventNumber")					== 0 ){ Min_EventNumber					= iMin; Max_EventNumber					= iMax; }
	if( iCut.compare("GenMatching")					== 0 ){ Min_GenMatching					= iMin; Max_GenMatching					= iMax; }
	if( iCut.compare("InvariantMass")				== 0 ){ Min_InvariantMass				= iMin; Max_InvariantMass				= iMax; }
	if( iCut.compare("VisibleMass")					== 0 ){ Min_VisibleMass					= iMin; Max_VisibleMass					= iMax; }
	if( iCut.compare("LL_pT")						== 0 ){ Min_LL_pT						= iMin; Max_LL_pT						= iMax; }
	if( iCut.compare("SL_pT")						== 0 ){ Min_SL_pT						= iMin; Max_SL_pT						= iMax; }
	if( iCut.compare("LL_Eta")						== 0 ){ Min_LL_Eta						= iMin; Max_LL_Eta						= iMax; }
	if( iCut.compare("SL_Eta")						== 0 ){ Min_SL_Eta						= iMin; Max_SL_Eta						= iMax; }
	if( iCut.compare("DeltaR")						== 0 ){ Min_DeltaR						= iMin; Max_DeltaR						= iMax; }
	if( iCut.compare("LL_LTpT")						== 0 ){ Min_LL_LTpT						= iMin; Max_LL_LTpT						= iMax; }
	if( iCut.compare("SL_LTpT")						== 0 ){ Min_SL_LTpT						= iMin; Max_SL_LTpT						= iMax; }
	if( iCut.compare("LL_LTHits")					== 0 ){ Min_LL_LTHits					= iMin; Max_LL_LTHits					= iMax; }
	if( iCut.compare("SL_LTHits")					== 0 ){ Min_SL_LTHits					= iMin; Max_SL_LTHits					= iMax; }
	if( iCut.compare("LL_H3x3overP")				== 0 ){ Min_LL_H3x3overP				= iMin; Max_LL_H3x3overP				= iMax; }
	if( iCut.compare("SL_H3x3overP")				== 0 ){ Min_SL_H3x3overP				= iMin; Max_SL_H3x3overP				= iMax; }
	if( iCut.compare("LL_InCracks")					== 0 ){ Min_LL_InCracks					= iMin; Max_LL_InCracks					= iMax; }
	if( iCut.compare("SL_InCracks")					== 0 ){ Min_SL_InCracks					= iMin; Max_SL_InCracks					= iMax; }
	if( iCut.compare("LL_AgainstTightElectron")		== 0 ){ Min_LL_AgainstTightElectron		= iMin; Max_LL_AgainstTightElectron		= iMax; }
	if( iCut.compare("LL_AgainstMediumElectron")	== 0 ){ Min_LL_AgainstMediumElectron	= iMin; Max_LL_AgainstMediumElectron	= iMax; }
	if( iCut.compare("LL_AgainstLooseElectron")		== 0 ){ Min_LL_AgainstLooseElectron		= iMin; Max_LL_AgainstLooseElectron		= iMax; }
	if( iCut.compare("SL_AgainstTightElectron")		== 0 ){ Min_SL_AgainstTightElectron		= iMin; Max_SL_AgainstTightElectron		= iMax; }
	if( iCut.compare("SL_AgainstMediumElectron")	== 0 ){ Min_SL_AgainstMediumElectron	= iMin; Max_SL_AgainstMediumElectron	= iMax; }
	if( iCut.compare("SL_AgainstLooseElectron")		== 0 ){ Min_SL_AgainstLooseElectron		= iMin; Max_SL_AgainstLooseElectron		= iMax; }
	if( iCut.compare("LL_AgainstTightMuon")			== 0 ){ Min_LL_AgainstTightMuon			= iMin; Max_LL_AgainstTightMuon			= iMax; }
	if( iCut.compare("LL_AgainstLooseMuon")			== 0 ){ Min_LL_AgainstLooseMuon			= iMin; Max_LL_AgainstLooseMuon			= iMax; }
	if( iCut.compare("SL_AgainstTightMuon")			== 0 ){ Min_SL_AgainstTightMuon			= iMin; Max_SL_AgainstTightMuon			= iMax; }
	if( iCut.compare("SL_AgainstLooseMuon")			== 0 ){ Min_SL_AgainstLooseMuon			= iMin; Max_SL_AgainstLooseMuon			= iMax; }
	if( iCut.compare("LL_TightIso")					== 0 ){ Min_LL_TightIso					= iMin; Max_LL_TightIso					= iMax; }
	if( iCut.compare("LL_MediumIso")				== 0 ){ Min_LL_MediumIso				= iMin; Max_LL_MediumIso				= iMax; }
	if( iCut.compare("LL_LooseIso")					== 0 ){ Min_LL_LooseIso					= iMin; Max_LL_LooseIso					= iMax; }
	if( iCut.compare("LL_VLooseIso")				== 0 ){ Min_LL_VLooseIso				= iMin; Max_LL_VLooseIso				= iMax; }
	if( iCut.compare("SL_TightIso")					== 0 ){ Min_SL_TightIso					= iMin; Max_SL_TightIso					= iMax; }
	if( iCut.compare("SL_MediumIso")				== 0 ){ Min_SL_MediumIso				= iMin; Max_SL_MediumIso				= iMax; }
	if( iCut.compare("SL_LooseIso")					== 0 ){ Min_SL_LooseIso					= iMin; Max_SL_LooseIso					= iMax; }
	if( iCut.compare("SL_VLooseIso")				== 0 ){ Min_SL_VLooseIso				= iMin; Max_SL_VLooseIso				= iMax; }
	if( iCut.compare("LL_DecayModeFinding")			== 0 ){ Min_LL_DecayModeFinding			= iMin; Max_LL_DecayModeFinding			= iMax; }
	if( iCut.compare("SL_DecayModeFinding")			== 0 ){ Min_SL_DecayModeFinding			= iMin; Max_SL_DecayModeFinding			= iMax; }
	if( iCut.compare("LL_DecayMode")				== 0 ){ Min_LL_DecayMode				= iMin; Max_LL_DecayMode				= iMax; }
	if( iCut.compare("SL_DecayMode")				== 0 ){ Min_SL_DecayMode				= iMin; Max_SL_DecayMode				= iMax; }
	if( iCut.compare("LL_NumProngs")				== 0 ){ Min_LL_NumProngs				= iMin; Max_LL_NumProngs				= iMax; }
	if( iCut.compare("SL_NumProngs")				== 0 ){ Min_SL_NumProngs				= iMin; Max_SL_NumProngs				= iMax; }
	if( iCut.compare("ChargeProduct")				== 0 ){ Min_ChargeProduct				= iMin; Max_ChargeProduct				= iMax; }
	if( iCut.compare("CosDeltaPhi")					== 0 ){ Min_CosDeltaPhi					= iMin; Max_CosDeltaPhi					= iMax; }
	if( iCut.compare("MET")							== 0 ){ Min_MET							= iMin; Max_MET							= iMax; }
	if( iCut.compare("Zeta")						== 0 ){ Min_Zeta						= iMin; Max_Zeta						= iMax; }
	if( iCut.compare("Btags")						== 0 ){ Min_Btags						= iMin; Max_Btags						= iMax; }
	//NEWCUT

}

void Analyzer::UpPairsForCut(string iCut){
	numberOfPairsPassing[iCut]++;
	cutIncrease[iCut] = 1.0;
}

void Analyzer::UpPairsForCut(string iCut, double iWeight){
	numberOfPairsPassing[iCut]++;
	cutIncrease[iCut] = iWeight;
}

bool Analyzer::PassesCuts(unsigned int iPair){




	// Run/LS/event selection
	if(CutOn_RunNumber){
		if(!isMC){ if (OutOfRange(runNumber, Min_RunNumber, Max_RunNumber)){ return false; } }
		UpPairsForCut("RunNumber");
	}
	if(CutOn_LumiSection){
		if(!isMC){ if (OutOfRange(lumiBlock, Min_LumiSection, Max_LumiSection)){ return false; } }
		UpPairsForCut("LumiSection");
	}
	if(CutOn_EventNumber){
		if(!isMC){ if (OutOfRange(eventNumber, Min_EventNumber, Max_EventNumber)){ return false; } }
		UpPairsForCut("EventNumber");
	}
	if(selectedEvents.size() > 0){
		if(!ProcessThisEvent()){ return false; }
		UpPairsForCut("Run:LS:Event");
	}	

	if(CutOn_GenMatching){
		int GenMatching; 
		if(StringContains(topology,"Zee")){
			GenMatching = (Tau1_ZeMatched->at(iPair) && Tau2_ZeMatched->at(iPair));
			if (OutOfRange(GenMatching, Min_GenMatching, Max_GenMatching)){ return false; }
		}else if(StringContains(topology,"Ztautau")){
			GenMatching = (Tau1_ZtauMatched->at(iPair) && Tau2_ZtauMatched->at(iPair));
			if (OutOfRange(GenMatching, Min_GenMatching, Max_GenMatching)){ return false; }
		}else if(StringContains(topology,"Zprime")){
			GenMatching = (Tau1_ParentTauMatched->at(iPair) && Tau2_ParentTauMatched->at(iPair));
			if (OutOfRange(GenMatching, Min_GenMatching, Max_GenMatching)){ return false; }
		}

		UpPairsForCut("GenMatching");
	}


	if(IsFlagThere("MCnormStart") ){ 
		UpPairsForCut("Lumi norm",normalization);
	}
	// QCD LS selector
	if(isQCD){
		int chargeProduct = ((Tau1Charge->at(iPair))*(Tau2Charge->at(iPair)));
		if(chargeProduct==-1){ return false; }
	}
	UpPairsForCut("LS for QCD",normalization); // Keep outide of if(isQCD) statement: non-QCD must remain unaffected by this cut

	if(CutOn_InvariantMass){
		if (OutOfRange(TauTauVisPlusMetMass->at(iPair), Min_InvariantMass, Max_InvariantMass)){ return false; }
		UpPairsForCut("InvariantMass",normalization);
	}

	if(CutOn_VisibleMass){
		if (OutOfRange(TauTauVisibleMass->at(iPair), Min_VisibleMass, Max_VisibleMass)){ return false; }
		UpPairsForCut("VisibleMass",normalization);
	}



	// ============================= Acceptance Cuts ============================= //


	// Pseudorapidity
	if(CutOn_LL_Eta){
		if (OutOfRange((Tau1Eta->at(iPair)), Min_LL_Eta, Max_LL_Eta)){ return false; }
		UpPairsForCut("LL_Eta",normalization);
	}
	if(CutOn_SL_Eta){
		if (OutOfRange((Tau2Eta->at(iPair)), Min_SL_Eta, Max_SL_Eta)){ return false; }
		UpPairsForCut("SL_Eta",normalization);
	}

	
	// Delta R
	if(CutOn_DeltaR){
		if (OutOfRange(TauTauDeltaR->at(iPair), Min_DeltaR, Max_DeltaR)){ return false; }
		UpPairsForCut("DeltaR",normalization);
	}


	// ============================= Tau-ID Cuts ============================= //
	
	// Leading track transverse momentum
	if(CutOn_LL_LTpT){
		if (OutOfRange(Tau1LTPt->at(iPair), Min_LL_LTpT, Max_LL_LTpT)){ return false; }
		UpPairsForCut("LL_LTpT",normalization);
	}
	if(CutOn_SL_LTpT){
		if (OutOfRange(Tau2LTPt->at(iPair), Min_SL_LTpT, Max_SL_LTpT)){ return false; }
		UpPairsForCut("SL_LTpT",normalization);
	}

	// Leading track number of hits
	if(CutOn_LL_LTHits){
		if (OutOfRange(Tau1LTValidHits->at(iPair), Min_LL_LTHits, Max_LL_LTHits)){ return false; }
		UpPairsForCut("LL_LThits",normalization);
	}
	if(CutOn_SL_LTHits){
		if (OutOfRange(Tau2LTValidHits->at(iPair), Min_SL_LTHits, Max_SL_LTHits)){ return false; }
		UpPairsForCut("SL_LThits",normalization);
	}

	// Crack veto
	if(CutOn_LL_InCracks){
		if (OutOfRange((Tau1IsInTheCracks->at(iPair)), Min_LL_InCracks, Max_LL_InCracks)){ return false; }
		UpPairsForCut("LL_InCracks",normalization);
	}
	if(CutOn_SL_InCracks){
		if (OutOfRange((Tau2IsInTheCracks->at(iPair)), Min_SL_InCracks, Max_SL_InCracks)){ return false; }
		UpPairsForCut("SL_InCracks",normalization);
	}
	// Against Electron
	if( CutOn_LL_AgainstTightElectron ){
		if(OutOfRange(Tau1hpsPFTauDiscriminationAgainstTightElectron->at(iPair), Min_LL_AgainstTightElectron, Max_LL_AgainstTightElectron)){ return false; };
		UpPairsForCut("LL_AgainstTightElectron",normalization);
	}else if( CutOn_LL_AgainstMediumElectron ){
		if(OutOfRange(Tau1hpsPFTauDiscriminationAgainstMediumElectron->at(iPair), Min_LL_AgainstMediumElectron, Max_LL_AgainstMediumElectron)){ return false; };
		UpPairsForCut("LL_AgainstMediumElectron",normalization);
	}else if( CutOn_LL_AgainstLooseElectron ){
		if(OutOfRange(Tau1hpsPFTauDiscriminationAgainstLooseElectron->at(iPair), Min_LL_AgainstLooseElectron, Max_LL_AgainstLooseElectron)){ return false; };
		UpPairsForCut("LL_AgainstLooseElectron",normalization);
	}
	if( CutOn_SL_AgainstTightElectron ){
		if(OutOfRange(Tau2hpsPFTauDiscriminationAgainstTightElectron->at(iPair), Min_SL_AgainstTightElectron, Max_SL_AgainstTightElectron)){ return false; };
		UpPairsForCut("SL_AgainstTightElectron",normalization);
	}else if( CutOn_SL_AgainstMediumElectron ){
		if(OutOfRange(Tau2hpsPFTauDiscriminationAgainstMediumElectron->at(iPair), Min_SL_AgainstMediumElectron, Max_SL_AgainstMediumElectron)){ return false; };
		UpPairsForCut("SL_AgainstMediumElectron",normalization);
	}else if( CutOn_SL_AgainstLooseElectron ){
		if(OutOfRange(Tau2hpsPFTauDiscriminationAgainstLooseElectron->at(iPair), Min_SL_AgainstLooseElectron, Max_SL_AgainstLooseElectron)){ return false; };
		UpPairsForCut("SL_AgainstLooseElectron",normalization);
	}

	// Against Muon
	if( CutOn_LL_AgainstTightMuon ){
		if(OutOfRange(Tau1hpsPFTauDiscriminationAgainstTightMuon->at(iPair), Min_LL_AgainstTightMuon, Max_LL_AgainstTightMuon)){ return false; };
		UpPairsForCut("LL_AgainstTightMuon",normalization);
	}else if( CutOn_LL_AgainstLooseMuon ){
		if(OutOfRange(Tau1hpsPFTauDiscriminationAgainstLooseMuon->at(iPair), Min_LL_AgainstLooseMuon, Max_LL_AgainstLooseMuon)){ return false; };
		UpPairsForCut("LL_AgainstLooseMuon",normalization);
	}
	if( CutOn_SL_AgainstTightMuon ){
		if(OutOfRange(Tau2hpsPFTauDiscriminationAgainstTightMuon->at(iPair), Min_SL_AgainstTightMuon, Max_SL_AgainstTightMuon)){ return false; };
		UpPairsForCut("SL_AgainstTightMuon",normalization);
	}else if( CutOn_SL_AgainstLooseMuon ){
		if(OutOfRange(Tau2hpsPFTauDiscriminationAgainstLooseMuon->at(iPair), Min_SL_AgainstLooseMuon, Max_SL_AgainstLooseMuon)){ return false; };
		UpPairsForCut("SL_AgainstLooseMuon",normalization);
	}

	// Isolation
	if( CutOn_LL_TightIso){
		if(OutOfRange(Tau1hpsPFTauDiscriminationByTightIsolation->at(iPair), Min_LL_TightIso, Max_LL_TightIso)){ return false; };
		UpPairsForCut("LL_TightIso",normalization);
	}else if( CutOn_LL_MediumIso){
		if(OutOfRange(Tau1hpsPFTauDiscriminationByMediumIsolation->at(iPair), Min_LL_MediumIso, Max_LL_MediumIso)){ return false; };
		UpPairsForCut("LL_MediumIso",normalization);
	}else if( CutOn_LL_LooseIso){
		if(OutOfRange(Tau1hpsPFTauDiscriminationByLooseIsolation->at(iPair), Min_LL_LooseIso, Max_LL_LooseIso)){ return false; };
		UpPairsForCut("LL_LooseIso",normalization);
	}else if( CutOn_LL_VLooseIso){
		if(OutOfRange(Tau1hpsPFTauDiscriminationByVLooseIsolation->at(iPair), Min_LL_VLooseIso, Max_LL_VLooseIso)){ return false; };
		UpPairsForCut("LL_VLooseIso",normalization);
	}
	if( CutOn_SL_TightIso){
		if(OutOfRange(Tau2hpsPFTauDiscriminationByTightIsolation->at(iPair), Min_SL_TightIso, Max_SL_TightIso)){ return false; };
		UpPairsForCut("SL_TightIso",normalization);
	}else if( CutOn_SL_MediumIso){
		if(OutOfRange(Tau2hpsPFTauDiscriminationByMediumIsolation->at(iPair), Min_SL_MediumIso, Max_SL_MediumIso)){ return false; };
		UpPairsForCut("SL_MediumIso",normalization);
	}else if( CutOn_SL_LooseIso){
		if(OutOfRange(Tau2hpsPFTauDiscriminationByLooseIsolation->at(iPair), Min_SL_LooseIso, Max_SL_LooseIso)){ return false; };
		UpPairsForCut("SL_LooseIso",normalization);
	}else if( CutOn_SL_VLooseIso){
		if(OutOfRange(Tau2hpsPFTauDiscriminationByVLooseIsolation->at(iPair), Min_SL_VLooseIso, Max_SL_VLooseIso)){ return false; };
		UpPairsForCut("SL_VLooseIso",normalization);
	}

	// Decay mode
	if(CutOn_LL_DecayModeFinding){
		if (OutOfRange(Tau1hpsPFTauDiscriminationByDecayModeFinding->at(iPair), Min_LL_DecayModeFinding, Max_LL_DecayModeFinding)){ return false; }
		UpPairsForCut("LL_DecayModeFinding",normalization);
	}
	if(CutOn_SL_DecayModeFinding){
		if (OutOfRange(Tau2hpsPFTauDiscriminationByDecayModeFinding->at(iPair), Min_SL_DecayModeFinding, Max_SL_DecayModeFinding)){ return false; }
		UpPairsForCut("SL_DecayModeFinding",normalization);
	}
	if(CutOn_LL_DecayMode){
		if (OutOfRange(Tau1DecayMode->at(iPair), Min_LL_DecayMode, Max_LL_DecayMode)){ return false; }
		UpPairsForCut("LL_DecayMode",normalization);
	}
	if(CutOn_SL_DecayMode){
		if (OutOfRange(Tau2DecayMode->at(iPair), Min_SL_DecayMode, Max_SL_DecayMode)){ return false; }
		UpPairsForCut("SL_DecayMode",normalization);
	}

	// Signal track multiplicity
	if(CutOn_LL_NumProngs){
		if (OutOfRange(Tau1NProngs->at(iPair), Min_LL_NumProngs, Max_LL_NumProngs)){ return false; }
		UpPairsForCut("LL_NumProngs",normalization);
	}
	if(CutOn_SL_NumProngs){
		if (OutOfRange(Tau2NProngs->at(iPair), Min_SL_NumProngs, Max_SL_NumProngs)){ return false; }
		UpPairsForCut("SL_NumProngs",normalization);
	}

	// ============================= Topological Cuts ============================= //

	// Charge product
	if(CutOn_ChargeProduct){
		if(!isQCD){
			int chargeProduct = ((Tau1Charge->at(iPair))*(Tau2Charge->at(iPair)));
			if (OutOfRange(chargeProduct, Min_ChargeProduct, Max_ChargeProduct)){ return false; }
		}
		UpPairsForCut("ChargeProduct",normalization);
	}

	// Cosine Delta phi
	if(CutOn_CosDeltaPhi){
		if (OutOfRange(TauTauCosDPhi->at(iPair), Min_CosDeltaPhi, Max_CosDeltaPhi)){ return false; }
		UpPairsForCut("CosDeltaPhi",normalization);
	}

	// Missing transverse energy
	if(CutOn_MET){
		if (OutOfRange(mEt->at(iPair), Min_MET, Max_MET)){ return false; }
		UpPairsForCut("MET",normalization);
	}

	if(CutOn_Zeta){
		float zeta = TauTauPZeta->at(iPair)-0.875*TauTauPZetaVis->at(iPair);
		if(OutOfRange(zeta, Min_Zeta, Max_Zeta)){ return false; }
		UpPairsForCut("Zeta",normalization);
	}

	if(CutOn_Btags){
		if(OutOfRange(nBtagsHiEffTrkCnt->at(iPair), Min_Btags, Max_Btags)){ return false; } 
		UpPairsForCut("Btags",normalization);
	}

	//NEWCUT

	return true;
}

void  Analyzer::SetMaxEvents(int iMaxEvents){
	maxEvents = iMaxEvents;
}

float Analyzer::GetEffectiveLumi(string iPath, string iTreeName, float targetLumi){

	float result = 0;

	fChain = GetTChain(iPath, iTreeName);
	int fChainEntries = fChain->GetEntries();

	if( 0 <= maxEvents && maxEvents < fChainEntries ){ result = (maxEvents/(double)fChainEntries)*targetLumi; }
	else{ result = targetLumi; }
	

	effectiveLumi = result;
	return result;
}

void Analyzer::SetEffectiveLumi(float iLumi){
	effectiveLumi = iLumi;
}


void Analyzer::MakeNewCutFlows(){
	numberOfPairsPassing.clear();
	numberOfEventsPassing.clear();
	cutIncrease.clear();
}

void Analyzer::ResetCounters(){
	for(map<string, int>::iterator cut = numberOfPairsPassing.begin(); cut != numberOfPairsPassing.end(); ++cut){ (*cut).second = 0; }
	for(map<string, double>::iterator cut = numberOfEventsPassing.begin(); cut != numberOfEventsPassing.end(); ++cut){ (*cut).second = 0; }
	for(map<string, double>::iterator cut = cutIncrease.begin(); cut != cutIncrease.end(); ++cut){ (*cut).second = 1; }
}



vector<HistoWrapper*>* Analyzer::GetPlots(string iPath, bool iIsMC, bool iIsSignal){

	BookHistos();
	isMC = iIsMC;

	vector<HistoWrapper*>* result = new vector<HistoWrapper*>();
	MakeNewCutFlows();

	fChain = GetTChain(iPath, "analyzeHiMassTau/HMTTree");
	Init();

	normalization = 1.0;
	Loop();

	for (map<string,HistoWrapper*>::iterator it = histoCollection->begin(); it != histoCollection->end(); it++ ){
		HistoWrapper* returnWrapper = ((*it).second);
		returnWrapper->SetMC(iIsMC);
		returnWrapper->SetCutsApplied(cutsToApply);
		returnWrapper->SetNumEvAnalyzed(numEvAnalyzed);
		returnWrapper->SetNumEvInNtuple(numEvInNtuple);
		returnWrapper->SetNumEvInDS(numEvInDS);
		returnWrapper->SetCrossSection(crossSection);
		returnWrapper->SetEffectiveLumi(effectiveLumi);
		returnWrapper->Normalize();
		result->push_back(returnWrapper);

		// Generate integrated mass distributions
		
		if((string(returnWrapper->GetHisto()->GetName())).compare("InvariantMass_LSM")==0){
			result->push_back(histoIntegrator->IntegrateFromLeft(returnWrapper));
			result->push_back(histoIntegrator->IntegrateFromRight(returnWrapper));
		}

	}

	return result;
}

// Make and return all plots
vector<HistoWrapper*>* Analyzer::GetOSPlots(string iPath, bool iIsMC, bool iIsSignal, long long iNumEvInPAT, long long iNumEvInDS, float iOtherSF, float iAllMCscaleFactor){
				numEvInPAT			= iNumEvInPAT;
				numEvInDS			= iNumEvInDS;
				otherSF				= iOtherSF;
	if(iIsMC){	allMCscaleFactor	= iAllMCscaleFactor; }
	else{		allMCscaleFactor	= 1.0; }
	
	vector<HistoWrapper*>* result = GetPlots(iPath,iIsMC, iIsSignal);
	//cutFlow->AddTopology(topology, GetCutResults());
	return result;
}

// Set method for OS2LS ratio
void Analyzer::SetOS2LS(float iOS2LS){
	OS2LS = iOS2LS;
}

vector<HistoWrapper*>* Analyzer::GetQCDPlots(string iPath, bool iIsMC, bool iIsSignal, long long iNumEvInPAT, long long iNumEvInDS, float iOtherSF, float iAllMCscaleFactor){
				numEvInPAT			= iNumEvInPAT;
				numEvInDS			= iNumEvInDS;
				otherSF				= iOtherSF;
	if(iIsMC){	allMCscaleFactor	= iAllMCscaleFactor; }
	else{		allMCscaleFactor	= 1.0; }

	vector<HistoWrapper*>* result;

	// Original cuts string (to be restored after getting these plots)
	//string preQCDcuts = cutsToApply;

	// If a charge product is already required, drop it form the cuts string so we can add the LS requirement. The original cuts string will be restore later
	//size_t found = cutsToApply.find("ChargeProduct");
	//if( (0 <= found) && (found < cutsToApply.length()) ){
	//	size_t foundSpace = min(cutsToApply.length(), cutsToApply.find(" ", found));
	//	cutsToApply = string(cutsToApply.substr(0,found-1) + " " + cutsToApply.substr(min(cutsToApply.length(),foundSpace+1)));
	//}
	//cutsToApply = cutsToApply + " ChargeProduct:1:1 "; SetCutsToApply(cutsToApply);

	// Obtain plots with LS, independently of the original charge product cut
	isQCD = true;
	result = GetPlots(iPath, iIsMC, iIsSignal);
//	cutFlow->AddTopology_LS(topology, GetCutResults());

	isQCD = false;

	// Restore the original cuts
	//SetCutsToApply(preQCDcuts); 

	return result;
}


// This function returns a vector with all the info from each cut, useful to compute efficiencies.
vector< cutResult* >* Analyzer::GetCutResults(){

	vector< cutResult* >* result = new vector< cutResult* >();
	result->clear();
	
	for(unsigned int cut = 1; cut < cutsByOrderExtra.size(); cut++){
		cutResult* toAdd	= new cutResult();

		toAdd->cutName			= cutsByOrderExtra.at(cut)->preName + " " + cutsByOrderExtra.at(cut)->cutName + " " + cutsByOrderExtra.at(cut)->postName;
		toAdd->preEvents		= numberOfEventsPassing[(cutsByOrderExtra.at(cut-1))->cutName];
		toAdd->postEvents		= numberOfEventsPassing[(cutsByOrderExtra.at(cut))->cutName];
		toAdd->oriEvents		= numberOfEventsPassing["ReadFromDS"];
		//cout << toAdd->cutName << string(40-(toAdd->cutName).length(),' ') << toAdd->preEvents << "\t\t" << toAdd->postEvents << endl;

		result->push_back(toAdd);
	}

	return result;
}



// This function fills all the histograms for the selected pair
void Analyzer::FillEvents(int pair){
	fevents << topology << " " << isQCD << " " << setprecision(10) << runNumber << " " << lumiBlock << " " << eventNumber << endl;
}


Int_t Analyzer::GetEntry(Long64_t entry){
	// Read contents of entry.
	if (!fChain) return 0;
	return fChain->GetEntry(entry);
}

// Set up non-default trigger efficiencies as function of pT
void Analyzer::SetTrigger(string binLowEdges, string binWeights){
	if(tauTrigger == NULL){ tauTrigger =  new Trigger(); }
	tauTrigger->SetEfficiency(binLowEdges, binWeights);
}

void Analyzer::SetTrigger(string iFunction){
	if(tauTrigger == NULL){ tauTrigger =  new Trigger(); }
	tauTrigger->SetEfficiency(iFunction);
}

// Set MET scale factors
void Analyzer::SetMETSF(string binLowEdges, string binWeights){
	metScaler=  new Trigger(binLowEdges, binWeights);
}

// Set up analysis flags
void Analyzer::SetFlags(string iFlags){
	flags = iFlags;
	MakeFlagsPave();
}


// Set up PU corrector from file
void Analyzer::LoadPuFile(string iPuFile){
	puCorrector		= new PUcorrector(iPuFile);
}

// Set up trigger config file
void Analyzer::LoadTriggerConfig(string iTriggerConfig){
	tauTrigger		= new Trigger(iTriggerConfig);
}


// Add cut names to the list of cuts for printing
void Analyzer::AddCutToList(string thisCut, float cutMin, float cutMax){
	map<string,string>  niceLabels;	

	niceLabels["RunNumber"]					= "Run number";
	niceLabels["LumiSection"]				= "Lumi section";
	niceLabels["EventNumber"]				= "Event number";
	niceLabels["GenMatching"]				= "Generator matching";
	niceLabels["InvariantMass"]				= "Invariant mass";
	niceLabels["VisibleMass"]				= "Visible mass";
	niceLabels["LL_pT"]						= "LL p_{T}";
	niceLabels["SL_pT"]						= "SL p_{T}";
	niceLabels["LL_Eta"]					= "LL #eta";
	niceLabels["SL_Eta"]					= "SL #eta";
	niceLabels["DeltaR"]					= "#Delta R(LL,SL)";
	niceLabels["LL_LTpT"]					= "LL leading track p_{T}";
	niceLabels["SL_LTpT"]					= "SL leading track p_{T}";
	niceLabels["LL_LTHits"]					= "LL leading track num hits";
	niceLabels["SL_LTHits"]					= "SL leading track num hits";
	niceLabels["LL_H3x3overP"]				= "LL H3x3/p";
	niceLabels["SL_H3x3overP"]				= "SL H3x3/p";
	niceLabels["LL_InCracks"]				= "LL InCracks";
	niceLabels["SL_InCracks"]				= "SL InCracks";
	niceLabels["LL_AgainstTightElectron"]	= "LL against tight electron";
	niceLabels["LL_AgainstMediumElectron"]	= "LL against medium electron";
	niceLabels["LL_AgainstLooseElectron"]	= "LL against loose electron";
	niceLabels["SL_AgainstTightElectron"]	= "SL against tight electron";
	niceLabels["SL_AgainstMediumElectron"]	= "SL against medium electron";
	niceLabels["SL_AgainstLooseElectron"]	= "SL against loose electron";
	niceLabels["LL_AgainstTightMuon"]		= "LL against tight muon";
	niceLabels["LL_AgainstLooseMuon"]		= "LL against loose muon";
	niceLabels["SL_AgainstTightMuon"]		= "SL against tight muon";
	niceLabels["SL_AgainstLooseMuon"]		= "SL against loose muon";
	niceLabels["LL_TightIso"]				= "LL tight iso";
	niceLabels["LL_MediumIso"]				= "LL medium iso";
	niceLabels["LL_LooseIso"]				= "LL loose iso";
	niceLabels["LL_VLooseIso"]				= "LL vloose iso";
	niceLabels["SL_TightIso"]				= "SL tight iso";
	niceLabels["SL_MediumIso"]				= "SL medium iso";
	niceLabels["SL_LooseIso"]				= "SL loose iso";
	niceLabels["SL_VLooseIso"]				= "SL vloose iso";
	niceLabels["LL_NumProngs"]				= "LL num prongs";
	niceLabels["SL_NumProngs"]				= "SL num prongs";
	niceLabels["ChargeProduct"]				= "Q(LL)*Q(SL)";
	niceLabels["CosDeltaPhi"]				= "cos(#Delta #phi(LL,SL))";
	niceLabels["MET"]						= "Missing E_{T}";
	niceLabels["Zeta"]						= "#zeta";
	niceLabels["Btags"]						= "Num b-tags";

	stringstream toAdd; toAdd.str("");

	if(cutMin == cutMax){
		toAdd << niceLabels[thisCut] << " = " << cutMin;
	}else{
		toAdd << niceLabels[thisCut];
		if(cutMin > -FLT_MAX){
			if(cutMax <  FLT_MAX){
				toAdd << " #in [" << cutMin << ", " << cutMax << "]";
			}else{
				toAdd << " #geq " << cutMin;
			}
		}else{
			if(cutMax <  FLT_MAX){
				toAdd << " #leq " << cutMax;
			}else{
				toAdd << " ERROR " << endl;
			}
		}
	}

	listOfCutsPave->AddText((toAdd.str()).c_str());
	numberOfCuts++;

}

void Analyzer::MakeCutsPave(){
	listOfCutsPave->AddText("");
	if(numberOfCuts==0){
		numberOfCuts=4;
		listOfCutsPave->AddText("(no cuts)");
	listOfCutsPave->AddText("");
	}
	TCanvas* cutsCanvas = new TCanvas("cutsCanvas", "cutsCanvas",300,((numberOfCuts)*30)); 
	cutsCanvas->cd();
	listOfCutsPave->SetFillColor(kWhite);
	listOfCutsPave->Draw();
	cutsCanvas->SaveAs((string(outputCuts)).c_str());
}

void Analyzer::MakeFlagsPave(){
	TPaveText* listOfFlagsPave = new TPaveText(0,0,1,1);
	listOfFlagsPave->AddText("");
	vector<string>* flagsVector = ParseString(flags,' ');
	float paveItems = 0;
	if(flagsVector->size() == 0){
		listOfFlagsPave->AddText("(no flags)");
		listOfFlagsPave->AddText("");
		paveItems = 4;
	}else{
		paveItems = flagsVector->size(); 
	}

	for (int f=0; f<flagsVector->size(); f++){
		listOfFlagsPave->AddText((flagsVector->at(f)).c_str());
	}

	TCanvas* FlagsCanvas = new TCanvas("FlagsCanvas", "FlagsCanvas",200,((paveItems+2)*30)); 
	FlagsCanvas->cd();
	listOfFlagsPave->SetFillColor(kWhite);
	listOfFlagsPave->Draw();
	FlagsCanvas->SaveAs((string(outputFlags+"flags.png")).c_str());
}


vector<string>* Analyzer::ParseString(const string& iS, char c) {
	vector<string>* v = new vector<string>(); v->clear();

	string s = string(iS);
	s=Replace(s,"\n","");

	string::size_type curr = 0;
	string::size_type next = min(s.find(c), s.length());
	while (next < s.length()){
		string toAdd = string(s.substr(curr, next-curr));
		v->push_back(toAdd);

		curr = next+1;
		next = s.find(c, next+1);
	}
	if(s.length()>0){
		v->push_back(s.substr(curr, next-curr));
	}

	return v;
}

bool Analyzer::FoundHisto(string iName){
	return (histoCollection->find(iName) != histoCollection->end());
}

TH1* Analyzer::GetHisto(string iName){
		return ((*(histoCollection->find(iName))).second->GetHisto());
}

bool Analyzer::FindStringInFile(std::string iHaystack, string iNeedle){
	std::string match(iNeedle);
	return (match==iHaystack);
}

bool Analyzer::ProcessThisEvent(){
	bool result = false;
	if(selectedEvents.size() > 0){
		stringstream thisRunLSevent; thisRunLSevent.str("");	
		thisRunLSevent << setprecision(15) << runNumber << ":" << lumiBlock << ":" << eventNumber;
		vector<string>::const_iterator found = find(selectedEvents.begin(), selectedEvents.end(), thisRunLSevent.str());
		result = (!(found == selectedEvents.end()));
	}else{
		result = true;	
	}
	return result;
}

string Analyzer::GetRunLSevent(){
		stringstream thisRunLSevent; thisRunLSevent.str("");	
		thisRunLSevent << setprecision(15) << runNumber << ":" << lumiBlock << ":" << eventNumber;
		return (thisRunLSevent.str());
}



void Analyzer::PrintEfficienciesHTML(string iOutputFile){
	//if(cutFlow != NULL){ cutFlow->PrintEfficienciesHTML(iOutputFile); }
}

string Analyzer::Replace(string input, string oldStr, string newStr){
	string toReturn = string(input);
	size_t pos = 0;
	while((pos = toReturn.find(oldStr, pos)) != std::string::npos){
		toReturn.replace(pos, oldStr.length(), newStr);
		pos += newStr.length();
	}

	return toReturn;
}

bool Analyzer::StringContains(string haystack, string needle){
	size_t found	= haystack.find(needle);
	size_t length	= haystack.length();

	return ( 0 <= found && found <= length );
}

// Parse comma-separated string
unsigned int Analyzer::ParseCSV(const string& iS, char c, float iArray[]) {

	string s = string(iS);

	// Put every number in the vector
	int count = 0;
	string::size_type curr = 0;
	string::size_type next = min(s.find(c), s.length());
	while (next < s.length()){
		string toAdd = string(s.substr(curr, next-curr));
		iArray[count] = atof((s.substr(curr, next-curr)).c_str()); count++;
		curr = next+1;
		next = s.find(c, next+1);
	}
	// Overflow bin
	iArray[count] = atof((s.substr(curr, next-curr)).c_str()); count++;

	if(count<1){ cout << "ERROR: tried to initialize a variable bin width histogram but could not read at least two bin edges." << endl; exit(1); }

	return (count-1);
}
//*/

void Analyzer::AnalyzeAll(TopoPack* iTopologies){
	if(iTopologies->HaveCollisions()){		Analyze(iTopologies->GetCollisions());		}
	if(iTopologies->HaveMCbackgrounds()){	Analyze(iTopologies->GetMCbackgrounds());	}
	if(iTopologies->HaveQCD()){				iTopologies->BuildQCD();					}
	if(iTopologies->HaveSignals()){			Analyze(iTopologies->GetSignals());			}

	// Set analyzed flag in topoPack to true
	iTopologies->SetAnalyzed();
	
}

TChain* Analyzer::GetTChain(string iPath){

	// Chain to return
	TChain* result = new TChain("analyzeHiMassTau/HMTTree");

	// Add all *.root files in iPath
	string pathToRootFiles = iPath + "/*.root";
	result->Add(pathToRootFiles.c_str());

	// Return TChain
	return result;
}


void Analyzer::Init(string iPath){

	fChain = GetTChain(iPath);

	#include "clarity/zeroBranches.h"

	// Set branch addresses and branch pointers
	if (!fChain) return;
	fCurrent = -1; 
	fChain->SetMakeClass(1);

	#include "clarity/setBranchAddresses.h"

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

vector<HistoWrapper*>*	Analyzer::MakeHistoWrapperVector(map<string, HistoWrapper*>* iMap){
	vector<HistoWrapper*>* result = new vector<HistoWrapper*>(); result->clear();

	map<string, HistoWrapper*>::iterator mapIt;
	for(mapIt = iMap->begin(); mapIt != iMap->end(); mapIt++) {
		result->push_back((mapIt->second)->Clone());
	}

	return result;

}

void Analyzer::BookHistos(map<string, HistoWrapper*>* iHistos){

	iHistos->clear();

	Config histosConfig(params["histoCfg"]);

	map<string, Config*> histo = histosConfig.getGroups();

	string th1fPrefix = "th1f_";
	string th2fPrefix = "th2f_";
	for (map<string, Config*>::iterator i = histo.begin(); i != histo.end(); ++i){
		string groupName = i->first;
		Config* histoConfig = i->second;

		if (groupName.substr(0,th1fPrefix.length()) == th1fPrefix) {
			string name	= groupName.substr(th1fPrefix.length());
			iHistos->insert(pair<string, HistoWrapper*>(name, new HistoWrapper(name, "th1f", histoConfig)));
		}else if (groupName.substr(0,th2fPrefix.length()) == th2fPrefix){
			string name	= groupName.substr(th2fPrefix.length());
			iHistos->insert(pair<string, HistoWrapper*>(name, new HistoWrapper(name, "th2f", histoConfig)));
		}else{ continue; }
	}

}
