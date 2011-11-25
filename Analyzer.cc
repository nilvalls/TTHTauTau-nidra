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

	cutFlow.Reset();
	cutFlowLS.Reset();

 	histoConfig			= new Config(params["histoCfg"]);
	puCorrector			= new PUcorrector(params["puList"]);

//	tauTrigger			= new Trigger();

	#include "clarity/falseCuts.h"

}


// Default destructor
Analyzer::~Analyzer(){
	if (!fChain) return;
	delete fChain->GetCurrentFile();
}

void Analyzer::Analyze(Topology* iTopology){
	Reset();

	Loop();

	iTopology->SetHistos(&histos);
	iTopology->SetHistosLS(&histosLS);
	iTopology->SetCutFlow(&cutFlow);
	iTopology->SetCutFlowLS(&cutFlowLS);
	iTopology->SetAnalyzed();
}

void Analyzer::Reset(){
	histos.clear();
	histosLS.clear();
	cutFlow.Reset();
	cutFlowLS.Reset();
}

void Analyzer::Loop(){

}


/*

void Analyzer::SetPassingEventsOutput(string iFile){
	passingEventsFile = iFile;
	fevents.open(passingEventsFile.c_str());
	/*fevents << "</html>";
	fevents << "<style type=\"text/css\">td{text-align: center; } </style>";
	fevents << "<html><table border=1 cellspacing=0><tr>";
	fevents << "<th>Topology</th>"
			<< "<th>Run</th>"
			<< "<th>LS</th>"
			<< "<th>Event</th>"
			<< "<th>TauTauVisPlusMetMass</th>"
			<< "<th>Tau1Pt</th>"
			<< "<th>Tau2Pt</th>"
			<< "<th>mEt</th>"
			<< "<th>Tau1LTPt</th>"
			<< "<th>Tau2LTPt</th>"
			<< "<th>Tau1Charge</th>"
			<< "<th>Tau2Charge</th>"
			<< "<th>Q(1)*Q(2)</th>"
			<< "<th>Tau1Eta</th>"
			<< "<th>Tau2Eta</th>"
			<< "<th>Tau1Phi</th>"
			<< "<th>Tau2Phi</th>"
			<< "<th>Tau1LTIpVtdxy</th>"
			<< "<th>Tau1LTIpVtxError</th>"
			<< "<th>Tau1LTValidHits</th>"
			<< "<th>Tau1LTNormChiSqrd</th>"
			<< "<th>Tau2LTIpVtdxy</th>"
			<< "<th>Tau2LTIpVtxError</th>"
			<< "<th>Tau2LTValidHits</th>"
			<< "<th>Tau2LTNormChiSqrd</th>"
			<< "<th>Tau1NProngs</th>"
			<< "<th>Tau2NProngs</th>"
			<< "<th>Tau1EmFraction</th>"
			<< "<th>Tau2EmFraction</th>"
/*			<< "<th>Tau1HcalTotOverPLead</th>"
			<< "<th>Tau2HcalTotOverPLead</th>"
			<< "<th>Tau1HCalMaxOverPLead</th>"
			<< "<th>Tau2HCalMaxOverPLead</th>"
			<< "<th>Tau1HCal3x3OverPLead</th>"
			<< "<th>Tau2HCal3x3OverPLead</th>"//*/
	/*		<< "<th>Tau1DiscAgainstElectron</th>"
			<< "<th>Tau2DiscAgainstElectron</th>"
			<< "<th>Tau1IsInTheCracks</th>"
			<< "<th>Tau2IsInTheCracks</th>"
			<< "<th>Tau1SumPtIsoTracks</th>"
			<< "<th>Tau2SumPtIsoTracks</th>"
			<< "<th>Tau1SumPtIsoGammas</th>"
			<< "<th>Tau2SumPtIsoGammas</th>"
			<< "<th>Tau1hpsPFTauDiscriminationAgainstTightElectron</th>"
			<< "<th>Tau2hpsPFTauDiscriminationAgainstTightElectron</th>"
			<< "<th>Tau1hpsPFTauDiscriminationAgainstMediumElectron</th>"
			<< "<th>Tau2hpsPFTauDiscriminationAgainstMediumElectron</th>"
			<< "<th>Tau1hpsPFTauDiscriminationAgainstLooseElectron</th>"
			<< "<th>Tau2hpsPFTauDiscriminationAgainstLooseElectron</th>"
			<< "<th>Tau1hpsPFTauDiscriminationAgainstTightMuon</th>"
			<< "<th>Tau2hpsPFTauDiscriminationAgainstTightMuon</th>"
			<< "<th>Tau1hpsPFTauDiscriminationAgainstLooseMuon</th>"
			<< "<th>Tau2hpsPFTauDiscriminationAgainstLooseMuon</th>"
			<< "<th>Tau1hpsPFTauDiscriminationByTightIsolation</th>"
			<< "<th>Tau2hpsPFTauDiscriminationByTightIsolation</th>"
			<< "<th>Tau1hpsPFTauDiscriminationByMediumIsolation</th>"
			<< "<th>Tau2hpsPFTauDiscriminationByMediumIsolation</th>"
			<< "<th>Tau1hpsPFTauDiscriminationByLooseIsolation</th>"
			<< "<th>Tau2hpsPFTauDiscriminationByLooseIsolation</th>"
			<< "<th>Tau1hpsPFTauDiscriminationByVLooseIsolation</th>"
			<< "<th>Tau2hpsPFTauDiscriminationByVLooseIsolation</th>"
			<< "<th>mEt</th>"
			<< "<th>TauTauVisibleMass</th>"
			<< "<th>TauTauVisPlusMetMass</th>"
			<< "<th>TauTauCosDPhi</th>"
			<< "<th>TauTauDeltaR</th>"
			<< "<th>TauTauPZeta</th>"
			<< "<th>TauTauPZetaVis</th>"
			<< "<th>Tau1MetCosDphi</th>"
			<< "<th>Tau2MetCosDphi</th>"
			<< "<th>nBtagsHiEffTrkCnt</th>"
			<< endl; //*/
/*
	fevents << "</html>";
	fevents << "<style type=\"text/css\">td{text-align: center; } </style>";
	fevents << "<html><table border=1 cellspacing=0><tr>";
	fevents	<< "<th>Run:LS:Event</th>"
			<< "<th>Pair</th>"
			<< "<th>LL Pt</th>"
			<< "<th>LL Eta</th>"
			<< "<th>LL Phi</th>"
			<< "<th>SL Pt</th>"
			<< "<th>SL Eta</th>"
			<< "<th>SL Phi</th>"
			<< "<th>InvariantMass</th>"
			<< "<th>MET</th>"
			<< "<th>LL SumIsoT</th>"
			<< "<th>SL SumIsoT</th>"
			<< "<th>LL SumIsoG</th>"
			<< "<th>SL SumIsoG</th>"
			<< "<th>LL HPS L.Iso</th>"
			<< "<th>SL HPS L.Iso</th>"
			<< endl;

	fevents << "</tr>";
	fevents.close();

}



void Analyzer::Loop(){
	cout << ">>> Starting loop... "; cout.flush();
	if (fChain == 0){ cout << endl << "ERROR: empty TChain. Exiting."; return; }

	// Set up passing events output file
	fevents.open(passingEventsFile.c_str(), fstream::app);
	if (!fevents.is_open()){ cout << ">>> ERROR: Unable to open file" << endl; exit(1); }

	Long64_t nentries = fChain->GetEntries();
	numEvInNtuple	= nentries;
	cout << " " << nentries << " entries available: ";
	if(maxEvents <= 0 || maxEvents >= nentries){ cout << "Processing all of them..." << string(14,'.') << " "; }
	else{ cout << "Stopping at " << maxEvents << " as per-user request" << string(14,'.') << " "; }
	cout.flush();

	ResetCounters();
	Long64_t nbytes = 0, nb = 0;
	numEvAnalyzed=0;
	numEvPassing = 0;
	numEvPassingWithTrigger = 0;
	numEvPassingWithPURW = 0;
	int numGoodEv=0;
	int numEv2GoodPairs=0;
	int numEv1GoodPairs=0;
	int numMatched=0;
	int numEvHighestMassNoHighestPt = 0;

	if(isMC && IsFlagThere("MCnorm")){
			long double numEvToAnalyze;
			if(maxEvents <= 0 || maxEvents >= nentries){ numEvToAnalyze = nentries; }
			else{ numEvToAnalyze = maxEvents; }
			long double expectedEv = (effectiveLumi*crossSection);
			long double obtainedEv = (long double)numEvInDS*(numEvToAnalyze/(double)numEvInNtuple);
			calcNormalization = (expectedEv/obtainedEv)*otherSF*allMCscaleFactor;
	}else{
		calcNormalization = 1;
		normalization = 1;
	}

	if(IsFlagThere("MCnormStart")){ 
		normalization = calcNormalization;
	}

	// PU reweighing plots
	if(histoCollection->find("PUweights") != histoCollection->end()){
		for (unsigned int numPV=0; numPV < 30; numPV++){
			(*(histoCollection->find("PUweights"))).second->GetHisto()->Fill(numPV,puCorrector->GetWeight(numPV));
		//	cout << "numPV: " << numPV << " weight: " << puCorrector->GetWeight(numPV) << endl;
		}
	}

	// Actual loop
	for (Long64_t jentry=0; jentry<nentries; jentry++) {
		// Keep user informed of the number of events processed and if there is a termination due to reaching of the limit
		if ( maxEvents > 0 && jentry >= (unsigned int)(maxEvents)){ cout << "\n>>> INFO: Reached user-imposed event number limit (" << maxEvents << "), skipping the rest." << endl; break; }


		int prevLength = 0;
		if (jentry>0 && (jentry+1)%reportRate == 0){ 
			stringstream jentryss; jentryss.str("");
			jentryss << (jentry+1);
			cout << string((jentryss.str()).length(),'\b') << string((jentryss.str()).length(),' ') << string((jentryss.str()).length(),'\b') << jentryss.str(); cout.flush(); 
			prevLength = (jentryss.str()).length();
		}

		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;

		numEvAnalyzed++;

		// Loop through all the pairs in the event
		float lowestPairNum	= 999;
		float largestMass	= -1;
		int heaviestPair	= -1;
		bool PassesAllSelections = false;
		int numGoodPairs = 0;

		if(histoCollection->find("PUweightsAllEvents") != histoCollection->end()){
			(*(histoCollection->find("PUweightsAllEvents"))).second->GetHisto()->Fill(puCorrector->GetWeight(NumPV->at(0)));
		}

		// Loop over all the pairs
		for (unsigned int pair = 0; pair < Tau1Pt->size(); pair++){

			// Obtain pair's mass
			float pairMass = TauTauVisPlusMetMass->at(pair);

			// Apply all selections here (do this first)
			if( pairMass <= 0 ){ continue; }
			//UpPairsForCut("positiveMass");

			// Rest of selections
			PassesAllSelections	= PassesCuts(pair);

			// Keep track of highest pT on each leg
			if( PassesAllSelections && (pair < lowestPairNum ) ){
				lowestPairNum = pair;
			}

			// Keep track of the heaviest pair (always do this last)
			if( PassesAllSelections && (pairMass > largestMass) ){
				numGoodPairs++;
				largestMass		= pairMass;
				heaviestPair	= pair;
			}
		}

		// Increase counters for those events with at least one pair passing the individual cuts
		for(unsigned int c=0; c<cutsByOrder.size(); c++){
			string cutstring = cutsByOrder.at(c);
			int pairsPassing = numberOfPairsPassing[cutstring];
			if (pairsPassing > 0){ numberOfEventsPassing[cutstring]+=cutIncrease[cutstring]; }
			numberOfPairsPassing[cutstring] = 0;
		}


		// Fill all histos for the heaviest pair passing all selections
		//heaviestPair = lowestPairNum;
		if ( 0 <= heaviestPair && (unsigned int)heaviestPair < Tau1Pt->size() ){
			if(heaviestPair!=lowestPairNum){ numEvHighestMassNoHighestPt++; }
			numGoodEv++;
			if(numGoodPairs==1){ numEv1GoodPairs++; }
			if(numGoodPairs==2){ numEv2GoodPairs++; }
			if( (!IsFlagThere("PrintAllPairs")) ){ FillHistos(heaviestPair); }
			FillEvents(heaviestPair); 

		}


	}

	cutFlow->AddEvents("User event limit", numEvInNtuple, numEvAnalyzed);
	cutFlow->AddEvents("nTuple making", numEvInPAT, numEvInNtuple);
	cutFlow->AddEvents("skimming + PAT", numEvInDS, numEvInPAT);
	cutFlow->AddEvents("ReadFromDS", numEvInDS, numEvInDS);

	numberOfEventsPassing["User event limit"]	= numEvAnalyzed;
	numberOfEventsPassing["nTuple making"]	= numEvInNtuple;
	numberOfEventsPassing["skimming + PAT"]	= numEvInPAT;
	numberOfEventsPassing["ReadFromDS"]		= numEvInDS;

	if(IsFlagThere("triggerBins") || IsFlagThere("triggerFunc") ||IsFlagThere("triggerConf")){ numberOfEventsPassing["Trigger"]		= numEvPassingWithTrigger; }
	if(IsFlagThere("PUcorr")){ numberOfEventsPassing["PU reweighing"]	= numEvPassingWithPURW; }

	if(IsFlagThere("MCnormEnd")){ 
		normalization = calcNormalization;
		numberOfEventsPassing["Lumi norm"]		= numEvPassingWithPURW*normalization;
	}

	cout << endl;

	fevents.close();
}

// Fill vector to process only selected events
void Analyzer::SetSelectEvents(string iSelectedEvents){

	selectedEvents.clear();

	if(iSelectedEvents.length()>0){
		string line;
		ifstream eventsFile(iSelectedEvents.c_str());
		if (eventsFile.is_open()){
			while ( eventsFile.good() ){
				getline (eventsFile,line);
				if(line.length()>0){ selectedEvents.push_back(line); }
			}
			eventsFile.close();
		}else{
			cout << "Unable to open file\"" << iSelectedEvents << "\" to select events." << endl; exit(1);
		}
	}
}

void Analyzer::SetCutsToApply(string iCutsToApply){

	cutsToApply = iCutsToApply;
																											RegisterCut("ReadFromDS",		false);
																											RegisterCut("skimming + PAT",	false);
																											RegisterCut("nTuple making",	false);
																											RegisterCut("User event limit",	false);		

	 if(ApplyThisCut("RunNumber",					iCutsToApply)){ CutOn_RunNumber					= 	true; RegisterCut("RunNumber");					}
	 if(ApplyThisCut("LumiSection",					iCutsToApply)){ CutOn_LumiSection				= 	true; RegisterCut("LumiSection");				}
	 if(ApplyThisCut("EventNumber",					iCutsToApply)){ CutOn_EventNumber				= 	true; RegisterCut("EventNumber");				}
	 if(ApplyThisCut("GenMatching",					iCutsToApply)){ CutOn_GenMatching				= 	true; RegisterCut("GenMatching");				}
																			if(selectedEvents.size() > 0){	  RegisterCut("Run:LS:Event",	false);		}
																			if(IsFlagThere("MCnormStart")){	  RegisterCut("Lumi norm",		false);		}
																											  RegisterCut("LS for QCD",		false);		
	 if(ApplyThisCut("InvariantMass",				iCutsToApply)){ CutOn_InvariantMass				= 	true; RegisterCut("InvariantMass");				}
	 if(ApplyThisCut("VisibleMass",					iCutsToApply)){ CutOn_VisibleMass				= 	true; RegisterCut("VisibleMass");				}
	 if(ApplyThisCut("LL_pT",						iCutsToApply)){ CutOn_LL_pT						= 	true; RegisterCut("LL_pT");						}
	 if(ApplyThisCut("SL_pT",						iCutsToApply)){ CutOn_SL_pT						= 	true; RegisterCut("SL_pT");						}
	 if(ApplyThisCut("LL_Eta",						iCutsToApply)){ CutOn_LL_Eta					= 	true; RegisterCut("LL_Eta");					}
	 if(ApplyThisCut("SL_Eta",						iCutsToApply)){ CutOn_SL_Eta					= 	true; RegisterCut("SL_Eta");					}
	 if(ApplyThisCut("DeltaR",						iCutsToApply)){ CutOn_DeltaR					= 	true; RegisterCut("DeltaR");					}
	 if(ApplyThisCut("LL_LTpT",						iCutsToApply)){ CutOn_LL_LTpT					= 	true; RegisterCut("LL_LTpT");					}
	 if(ApplyThisCut("SL_LTpT",						iCutsToApply)){ CutOn_SL_LTpT					= 	true; RegisterCut("SL_LTpT");					}
	 if(ApplyThisCut("LL_LTHits",					iCutsToApply)){ CutOn_LL_LTHits					= 	true; RegisterCut("LL_LTHits");					}
	 if(ApplyThisCut("SL_LTHits",					iCutsToApply)){ CutOn_SL_LTHits					= 	true; RegisterCut("SL_LTHits");					}
	 if(ApplyThisCut("LL_H3x3overP",				iCutsToApply)){ CutOn_LL_H3x3overP				= 	true; RegisterCut("LL_H3x3overP");				}
	 if(ApplyThisCut("SL_H3x3overP",				iCutsToApply)){ CutOn_SL_H3x3overP				= 	true; RegisterCut("SL_H3x3overP");				}
	 if(ApplyThisCut("LL_InCracks",					iCutsToApply)){ CutOn_LL_InCracks				= 	true; RegisterCut("LL_InCracks");				}
	 if(ApplyThisCut("SL_InCracks",					iCutsToApply)){ CutOn_SL_InCracks				= 	true; RegisterCut("SL_InCracks");				}
	 if(ApplyThisCut("LL_AgainstTightElectron",		iCutsToApply)){ CutOn_LL_AgainstTightElectron	= 	true; RegisterCut("LL_AgainstTightElectron");	}
else if(ApplyThisCut("LL_AgainstMediumElectron",	iCutsToApply)){ CutOn_LL_AgainstMediumElectron	= 	true; RegisterCut("LL_AgainstMediumElectron");	}
else if(ApplyThisCut("LL_AgainstLooseElectron", 	iCutsToApply)){ CutOn_LL_AgainstLooseElectron	= 	true; RegisterCut("LL_AgainstLooseElectron");	}
	 if(ApplyThisCut("SL_AgainstTightElectron",		iCutsToApply)){ CutOn_SL_AgainstTightElectron	= 	true; RegisterCut("SL_AgainstTightElectron");	}
else if(ApplyThisCut("SL_AgainstMediumElectron",	iCutsToApply)){ CutOn_SL_AgainstMediumElectron	= 	true; RegisterCut("SL_AgainstMediumElectron");	}
else if(ApplyThisCut("SL_AgainstLooseElectron", 	iCutsToApply)){ CutOn_SL_AgainstLooseElectron	= 	true; RegisterCut("SL_AgainstLooseElectron");	}
	 if(ApplyThisCut("LL_AgainstTightMuon", 		iCutsToApply)){ CutOn_LL_AgainstTightMuon		= 	true; RegisterCut("LL_AgainstTightMuon");		}
else if(ApplyThisCut("LL_AgainstLooseMuon", 		iCutsToApply)){ CutOn_LL_AgainstLooseMuon		= 	true; RegisterCut("LL_AgainstLooseMuon");		}
	 if(ApplyThisCut("SL_AgainstTightMuon", 		iCutsToApply)){ CutOn_SL_AgainstTightMuon		= 	true; RegisterCut("SL_AgainstTightMuon");		}
else if(ApplyThisCut("SL_AgainstLooseMuon", 		iCutsToApply)){ CutOn_SL_AgainstLooseMuon		= 	true; RegisterCut("SL_AgainstLooseMuon");		}
	 if(ApplyThisCut("LL_TightIso",					iCutsToApply)){ CutOn_LL_TightIso				= 	true; RegisterCut("LL_TightIso");				}
else if(ApplyThisCut("LL_MediumIso",				iCutsToApply)){ CutOn_LL_MediumIso				= 	true; RegisterCut("LL_MediumIso");				}
else if(ApplyThisCut("LL_LooseIso",					iCutsToApply)){ CutOn_LL_LooseIso				= 	true; RegisterCut("LL_LooseIso");				}
else if(ApplyThisCut("LL_VLooseIso",				iCutsToApply)){ CutOn_LL_VLooseIso				= 	true; RegisterCut("LL_VLooseIso");				}
	 if(ApplyThisCut("SL_TightIso",					iCutsToApply)){ CutOn_SL_TightIso				= 	true; RegisterCut("SL_TightIso");				}
else if(ApplyThisCut("SL_MediumIso",				iCutsToApply)){ CutOn_SL_MediumIso				= 	true; RegisterCut("SL_MediumIso");				}
else if(ApplyThisCut("SL_LooseIso",					iCutsToApply)){ CutOn_SL_LooseIso				= 	true; RegisterCut("SL_LooseIso");				}
else if(ApplyThisCut("SL_VLooseIso",				iCutsToApply)){ CutOn_SL_VLooseIso				= 	true; RegisterCut("SL_VLooseIso");				}
	 if(ApplyThisCut("LL_DecayModeFinding",			iCutsToApply)){ CutOn_LL_DecayModeFinding		= 	true; RegisterCut("LL_DecayModeFinding");		}
	 if(ApplyThisCut("SL_DecayModeFinding",			iCutsToApply)){ CutOn_SL_DecayModeFinding		= 	true; RegisterCut("SL_DecayModeFinding");		}
	 if(ApplyThisCut("LL_DecayMode",				iCutsToApply)){ CutOn_LL_DecayMode				= 	true; RegisterCut("LL_DecayMode");				}
	 if(ApplyThisCut("SL_DecayMode",				iCutsToApply)){ CutOn_SL_DecayMode				= 	true; RegisterCut("SL_DecayMode");				}
	 if(ApplyThisCut("LL_NumProngs",				iCutsToApply)){ CutOn_LL_NumProngs				= 	true; RegisterCut("LL_NumProngs");				}
	 if(ApplyThisCut("SL_NumProngs",				iCutsToApply)){ CutOn_SL_NumProngs				= 	true; RegisterCut("SL_NumProngs");				}
	 if(ApplyThisCut("ChargeProduct",				iCutsToApply)){ CutOn_ChargeProduct				= 	true; RegisterCut("ChargeProduct");				}
	 if(ApplyThisCut("CosDeltaPhi",					iCutsToApply)){ CutOn_CosDeltaPhi				= 	true; RegisterCut("CosDeltaPhi");				}
	 if(ApplyThisCut("MET",							iCutsToApply)){ CutOn_MET						= 	true; RegisterCut("MET");						}
	 if(ApplyThisCut("Zeta",						iCutsToApply)){ CutOn_Zeta						= 	true; RegisterCut("Zeta");						}
	 if(ApplyThisCut("Btags",						iCutsToApply)){ CutOn_Btags						= 	true; RegisterCut("Btags");						}
	 //NEWCUT

																					if(IsFlagThere("PUcorr")){ RegisterCut("Trigger",			false); }
																					if(IsFlagThere("trigger")){ RegisterCut("PU reweighing",		false); }
																				if(IsFlagThere("MCnormEnd")){	  RegisterCut("Lumi norm",		false);		}


	MakeCutsPave();

}

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

pair<float,float> Analyzer::ExtractCutThresholds(string iCutString){
	pair<float,float> result = make_pair(-FLT_MAX,FLT_MAX);

	string cutsToApplyTmp = " " + cutsToApply + " ";

	size_t foundNDef	= cutsToApplyTmp.find(" " + iCutString + ":");
	size_t length		= cutsToApplyTmp.length();

	if ( 0 <= foundNDef && foundNDef <= length ){
		string thresholds = cutsToApplyTmp.substr(foundNDef+iCutString.length()+2);
		thresholds = thresholds.substr(0,thresholds.find(" "));

		if(thresholds.find(":") >= thresholds.length()){
			cout << "ERROR: Cut named \"" << iCutString << "\" is missing a colon in its non-default threshold definition." << endl; exit(1);
		}

		float min, max;
		string smin = thresholds.substr(0,thresholds.find(":"));
		string smax = string(thresholds.substr(thresholds.find(":")+1));

		if(smin.compare("") == 0){ min = -FLT_MAX; }
		else{ min = atof(smin.c_str()); }

		if(smax.compare("") == 0){ max = FLT_MAX; }
		else{ max = atof(smax.c_str()); }

		if( min > max ){
			cout << "ERROR: Min threshold in cut named \"" << iCutString << "\" has a greater value than the max." << endl; exit(1);
		}

		result = make_pair(min,max);

	}else{
			cout << "ERROR: Cut named \"" << iCutString << "\" is missing threshold definition." << endl; exit(1);
	}

	return result;

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

bool Analyzer::ApplyThisCut(string thisCut, string iCutsToApply){

	bool result = false;

	string cutsToApply = iCutsToApply;
	cutsToApply = " " + cutsToApply + " ";

	size_t foundNDef = cutsToApply.find(" " + thisCut + ":");
	size_t length = cutsToApply.length();

	if ( 0 <= foundNDef && foundNDef <= length ){ result = true; }
	else{ result = false; }

	return result;

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

	// Transverse momentum
	if(CutOn_LL_pT){
		if (OutOfRange(Tau1Pt->at(iPair), Min_LL_pT, Max_LL_pT)){ return false; }
		UpPairsForCut("LL_pT",normalization);
	}
	if(CutOn_SL_pT){
		if (OutOfRange(Tau2Pt->at(iPair), Min_SL_pT, Max_SL_pT)){ return false; }
		UpPairsForCut("SL_pT",normalization);
	}

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

TChain* Analyzer::GetTChain(string iPath, string iTreeName){

	// Text file to sore the list of .root files in given directory 'iPath'
	TRandom ran;
	stringstream tempListSS; tempListSS.str("");
	tempListSS << ".fileListForTChain" << ran.Uniform() << ".tmp";

	string tempList = tempListSS.str();

	// Chain to return
	TChain* result = new TChain(iTreeName.c_str());

	/*
	// Make use of bash to store list of root files in 'iPath' in a text file (to be read in afterward)
	TString sysCommand = "ls -1 " + iPath + "/*.root > " + tempList;
	if(gSystem->Exec(sysCommand) > 0){ cout << ">>> ERROR: Unable to list path " << iPath << "  making TChain." << endl; exit(1); }// exit(0);
	// Set up file reader
	ifstream iFile(tempList.c_str());
	if (iFile.is_open()){
		while ( iFile.good() ){
			
			string line;
			getline (iFile,line); // Read next line
			if (line.length() <= 0){ continue; }    // The last line may be blank. Skip any blank lines.
			result->Add(line.c_str()); // Otherwise add the file to the TChain
		}   
		iFile.close(); // Close text file
	}else{ cout << ">>> ERROR: Unable to open list file " + tempList + " for making TChain."; exit(1); } 

	// Remove temp file containing list of .root files now that they are all added to the TChain
	if(gSystem->Exec(TString("rm -f " + tempList)) > 0){ cout << ">>> WARNING: Could not remove temporary file list ("+tempList+")." << endl; }
	//*/

/*

	string pathToRootFiles = iPath + "/*.root";
	result->Add(pathToRootFiles.c_str());

	// Return TChain
	return result;
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

// This function fills all the histograms for the selected pair
void Analyzer::FillHistos(int pair){

	// Event weights (trigger)
	float eventWeight	= 1.0;
	float tau1Weight	= 1.0;
	float tau2Weight	= 1.0;
	float triggerWeight = 1.0;
	float PUweight		= 1.0;

	if (isMC && IsFlagThere("triggerConf")){
		tau1Weight		 = tauTrigger->GetWeightFromConf(Tau1Pt->at(pair), runNumber);
		tau2Weight		 = tauTrigger->GetWeightFromConf(Tau2Pt->at(pair), runNumber);
		triggerWeight	*= (tau1Weight*tau2Weight);
	}else if (isMC && IsFlagThere("triggerFunc")){
		tau1Weight 		 = tauTrigger->GetWeightFromFunc(Tau1Pt->at(pair));
		tau2Weight 		 = tauTrigger->GetWeightFromFunc(Tau2Pt->at(pair));
		triggerWeight	*= (tau1Weight*tau2Weight);
	}else if (isMC && IsFlagThere("triggerFuncE")){
		tau1Weight 		 = tauTrigger->GetWeightFromFuncE(Tau1Pt->at(pair));
		tau2Weight 		 = tauTrigger->GetWeightFromFuncE(Tau2Pt->at(pair));
		triggerWeight	*= (tau1Weight*tau2Weight);
	}else if (isMC && IsFlagThere("triggerBins")){
		tau1Weight		 = tauTrigger->GetWeightFromBins(Tau1Pt->at(pair));
		tau2Weight		 = tauTrigger->GetWeightFromBins(Tau2Pt->at(pair));
		triggerWeight	*= (tau1Weight*tau2Weight);
	}

	// Event weights (pileup)
	if(isMC && IsFlagThere("PUcorr")){ 
		PUweight	*= puCorrector->GetWeight(numInteractionsBX0);
		tau1Weight	*= puCorrector->GetWeight(numInteractionsBX0);
		tau2Weight	*= puCorrector->GetWeight(numInteractionsBX0);
	}


	// Net event weight
	eventWeight = triggerWeight * PUweight;

	numEvPassing			+=1.0;
	numEvPassingWithTrigger	+=triggerWeight;
	numEvPassingWithPURW	+=(triggerWeight*PUweight);


	if(histoCollection->find("NumPV_b4RW") != histoCollection->end()){
		(*(histoCollection->find("NumPV_b4RW"))).second->GetHisto()->Fill(NumPV->at(pair));
	}

	if(histoCollection->find("NumPV_afRW") != histoCollection->end()){
		(*(histoCollection->find("NumPV_afRW"))).second->GetHisto()->Fill(NumPV->at(pair), puCorrector->GetWeight(numInteractionsBX0));
	}

	if(histoCollection->find("NumInteractionsBX0_b4RW") != histoCollection->end()){
		(*(histoCollection->find("NumInteractionsBX0_b4RW"))).second->GetHisto()->Fill(numInteractionsBX0);
	}

	if(histoCollection->find("NumInteractionsBX0_afRW") != histoCollection->end()){
		(*(histoCollection->find("NumInteractionsBX0_afRW"))).second->GetHisto()->Fill(numInteractionsBX0, puCorrector->GetWeight(numInteractionsBX0));
	}

	// Filling of histos
	if(histoCollection->find("InvariantMass_LSM") != histoCollection->end()){
		(*(histoCollection->find("InvariantMass_LSM"))).second->GetHisto()->Fill(TauTauVisPlusMetMass->at(pair), eventWeight);
	}
	if(histoCollection->find("InvariantMass_LSM_forTTbar") != histoCollection->end()){
		(*(histoCollection->find("InvariantMass_LSM_forTTbar"))).second->GetHisto()->Fill(TauTauVisPlusMetMass->at(pair), eventWeight);
	}
	if(histoCollection->find("InvariantMass_LSM_forNote1") != histoCollection->end()){
		(*(histoCollection->find("InvariantMass_LSM_forNote1"))).second->GetHisto()->Fill(TauTauVisPlusMetMass->at(pair), eventWeight);
	}
	if(histoCollection->find("InvariantMass_LSM_forNote2") != histoCollection->end()){
		(*(histoCollection->find("InvariantMass_LSM_forNote2"))).second->GetHisto()->Fill(TauTauVisPlusMetMass->at(pair), eventWeight);
	}

	if(histoCollection->find("VisibleMass_LS") != histoCollection->end()){
		(*(histoCollection->find("VisibleMass_LS"))).second->GetHisto()->Fill(TauTauVisibleMass->at(pair), eventWeight);
	}

	if(histoCollection->find("VisibleMass_LS_forNote1") != histoCollection->end()){
		(*(histoCollection->find("VisibleMass_LS_forNote1"))).second->GetHisto()->Fill(TauTauVisibleMass->at(pair), eventWeight);
	}
	if(histoCollection->find("VisibleMass_LS_forNote2") != histoCollection->end()){
		(*(histoCollection->find("VisibleMass_LS_forNote2"))).second->GetHisto()->Fill(TauTauVisibleMass->at(pair), eventWeight);
	}

	if(histoCollection->find("MET_M") != histoCollection->end()){
		(*(histoCollection->find("MET_M"))).second->GetHisto()->Fill(mEt->at(pair), eventWeight);
	}

	if(histoCollection->find("MET_M_forNote") != histoCollection->end()){
		(*(histoCollection->find("MET_M_forNote"))).second->GetHisto()->Fill(mEt->at(pair), eventWeight);
	}

	if(FoundHisto("VSumPt_LS")){ 
		float cosdphi	= TauTauCosDPhi->at(pair);
		float sindphi	= sin(acos(cosdphi));
		float sumptx	= Tau1Pt->at(pair) + (Tau2Pt->at(pair))*cosdphi;
		float sumpty	= 					 (Tau2Pt->at(pair))*sindphi;
		float sumPt		= sqrt(pow(sumptx,2) + pow(sumpty,2));
		GetHisto("VSumPt_LS")->Fill(sumPt, eventWeight);
	}


	if(histoCollection->find("TransverseMass_LM") != histoCollection->end()){
		(*(histoCollection->find("TransverseMass_LM"))).second->GetHisto()->Fill(Tau1MetMt->at(pair), eventWeight);
	}
	if(histoCollection->find("TransverseMass_LM_forNote") != histoCollection->end()){
		(*(histoCollection->find("TransverseMass_LM_forNote"))).second->GetHisto()->Fill(Tau1MetMt->at(pair), eventWeight);
	}

	if(histoCollection->find("TransverseMass_legTrigger_LM") != histoCollection->end()){
		(*(histoCollection->find("TransverseMass_legTrigger_LM"))).second->GetHisto()->Fill(Tau1MetMt->at(pair), tau1Weight);
	}
	if(histoCollection->find("TransverseMass_legTrigger_log_LM") != histoCollection->end()){
		(*(histoCollection->find("TransverseMass_legTrigger_log_LM"))).second->GetHisto()->Fill(Tau1MetMt->at(pair), tau1Weight);
	}

	if(histoCollection->find("TransverseMass_SM") != histoCollection->end()){
		(*(histoCollection->find("TransverseMass_SM"))).second->GetHisto()->Fill(Tau2MetMt->at(pair), eventWeight);
	}
	if(histoCollection->find("TransverseMass_SM_forNote") != histoCollection->end()){
		(*(histoCollection->find("TransverseMass_SM_forNote"))).second->GetHisto()->Fill(Tau2MetMt->at(pair), eventWeight);
	}

	if(histoCollection->find("NumPV") != histoCollection->end()){
		(*(histoCollection->find("NumPV"))).second->GetHisto()->Fill(NumPV->at(pair), eventWeight);
	}
	
	if(histoCollection->find("HPSIsolation_LS") != histoCollection->end()){
		if(Tau1hpsPFTauDiscriminationByTightIsolation->at(pair) ){ (*(histoCollection->find("HPSIsolation_LS"))).second->GetHisto()->Fill(4.0, eventWeight); }
		if(Tau1hpsPFTauDiscriminationByMediumIsolation->at(pair)){ (*(histoCollection->find("HPSIsolation_LS"))).second->GetHisto()->Fill(3.0, eventWeight); }
		if(Tau1hpsPFTauDiscriminationByLooseIsolation->at(pair) ){ (*(histoCollection->find("HPSIsolation_LS"))).second->GetHisto()->Fill(2.0, eventWeight); }
		if(Tau1hpsPFTauDiscriminationByVLooseIsolation->at(pair)){ (*(histoCollection->find("HPSIsolation_LS"))).second->GetHisto()->Fill(1.0, eventWeight); }
		else{														(*(histoCollection->find("HPSIsolation_LS"))).second->GetHisto()->Fill(0.0, eventWeight); }

		if(Tau2hpsPFTauDiscriminationByTightIsolation->at(pair) ){ (*(histoCollection->find("HPSIsolation_LS"))).second->GetHisto()->Fill(4.0, eventWeight); }
		if(Tau2hpsPFTauDiscriminationByMediumIsolation->at(pair)){ (*(histoCollection->find("HPSIsolation_LS"))).second->GetHisto()->Fill(3.0, eventWeight); }
		if(Tau2hpsPFTauDiscriminationByLooseIsolation->at(pair) ){ (*(histoCollection->find("HPSIsolation_LS"))).second->GetHisto()->Fill(2.0, eventWeight); }
		if(Tau2hpsPFTauDiscriminationByVLooseIsolation->at(pair)){ (*(histoCollection->find("HPSIsolation_LS"))).second->GetHisto()->Fill(1.0, eventWeight); }
		else{														(*(histoCollection->find("HPSIsolation_LS"))).second->GetHisto()->Fill(0.0, eventWeight); }
	}

	if(histoCollection->find("HPSIsolation_L") != histoCollection->end()){
		if(Tau1hpsPFTauDiscriminationByTightIsolation->at(pair) ){ (*(histoCollection->find("HPSIsolation_L"))).second->GetHisto()->Fill(4.0, eventWeight); }
		if(Tau1hpsPFTauDiscriminationByMediumIsolation->at(pair)){ (*(histoCollection->find("HPSIsolation_L"))).second->GetHisto()->Fill(3.0, eventWeight); }
		if(Tau1hpsPFTauDiscriminationByLooseIsolation->at(pair) ){ (*(histoCollection->find("HPSIsolation_L"))).second->GetHisto()->Fill(2.0, eventWeight); }
		if(Tau1hpsPFTauDiscriminationByVLooseIsolation->at(pair)){ (*(histoCollection->find("HPSIsolation_L"))).second->GetHisto()->Fill(1.0, eventWeight); }
		else{														(*(histoCollection->find("HPSIsolation_L"))).second->GetHisto()->Fill(0.0, eventWeight); }
	}

	if(histoCollection->find("HPSIsolation_S") != histoCollection->end()){
		if(Tau2hpsPFTauDiscriminationByTightIsolation->at(pair) ){ (*(histoCollection->find("HPSIsolation_S"))).second->GetHisto()->Fill(4.0, eventWeight); }
		if(Tau2hpsPFTauDiscriminationByMediumIsolation->at(pair)){ (*(histoCollection->find("HPSIsolation_S"))).second->GetHisto()->Fill(3.0, eventWeight); }
		if(Tau2hpsPFTauDiscriminationByLooseIsolation->at(pair) ){ (*(histoCollection->find("HPSIsolation_S"))).second->GetHisto()->Fill(2.0, eventWeight); }
		if(Tau2hpsPFTauDiscriminationByVLooseIsolation->at(pair)){ (*(histoCollection->find("HPSIsolation_S"))).second->GetHisto()->Fill(1.0, eventWeight); }
		else{														(*(histoCollection->find("HPSIsolation_S"))).second->GetHisto()->Fill(0.0, eventWeight); }
	}

	if(histoCollection->find("HPSDiscAgainstElectron_LS") != histoCollection->end()){
		if(Tau1hpsPFTauDiscriminationAgainstTightElectron->at(pair) ){ (*(histoCollection->find("HPSDiscAgainstElectron_LS"))).second->GetHisto()->Fill(3.0, eventWeight); }
		if(Tau1hpsPFTauDiscriminationAgainstMediumElectron->at(pair)){ (*(histoCollection->find("HPSDiscAgainstElectron_LS"))).second->GetHisto()->Fill(2.0, eventWeight); }
		if(Tau1hpsPFTauDiscriminationAgainstLooseElectron->at(pair) ){ (*(histoCollection->find("HPSDiscAgainstElectron_LS"))).second->GetHisto()->Fill(1.0, eventWeight); }
		else{														(*(histoCollection->find("HPSDiscAgainstElectron_LS"))).second->GetHisto()->Fill(0.0, eventWeight); }

		if(Tau2hpsPFTauDiscriminationAgainstTightElectron->at(pair) ){ (*(histoCollection->find("HPSDiscAgainstElectron_LS"))).second->GetHisto()->Fill(3.0, eventWeight); }
		if(Tau2hpsPFTauDiscriminationAgainstMediumElectron->at(pair)){ (*(histoCollection->find("HPSDiscAgainstElectron_LS"))).second->GetHisto()->Fill(2.0, eventWeight); }
		if(Tau2hpsPFTauDiscriminationAgainstLooseElectron->at(pair) ){ (*(histoCollection->find("HPSDiscAgainstElectron_LS"))).second->GetHisto()->Fill(1.0, eventWeight); }
		else{														(*(histoCollection->find("HPSDiscAgainstElectron_LS"))).second->GetHisto()->Fill(0.0, eventWeight); }
	}

	if(histoCollection->find("HPSDiscAgainstElectron_L") != histoCollection->end()){
		if(Tau1hpsPFTauDiscriminationAgainstTightElectron->at(pair) ){ (*(histoCollection->find("HPSDiscAgainstElectron_L"))).second->GetHisto()->Fill(3.0, eventWeight); }
		if(Tau1hpsPFTauDiscriminationAgainstMediumElectron->at(pair)){ (*(histoCollection->find("HPSDiscAgainstElectron_L"))).second->GetHisto()->Fill(2.0, eventWeight); }
		if(Tau1hpsPFTauDiscriminationAgainstLooseElectron->at(pair) ){ (*(histoCollection->find("HPSDiscAgainstElectron_L"))).second->GetHisto()->Fill(1.0, eventWeight); }
		else{														(*(histoCollection->find("HPSDiscAgainstElectron_L"))).second->GetHisto()->Fill(0.0, eventWeight); }
	}

	if(histoCollection->find("HPSDiscAgainstElectron_s") != histoCollection->end()){
		if(Tau2hpsPFTauDiscriminationAgainstTightElectron->at(pair) ){ (*(histoCollection->find("HPSDiscAgainstElectron_s"))).second->GetHisto()->Fill(3.0, eventWeight); }
		if(Tau2hpsPFTauDiscriminationAgainstMediumElectron->at(pair)){ (*(histoCollection->find("HPSDiscAgainstElectron_s"))).second->GetHisto()->Fill(2.0, eventWeight); }
		if(Tau2hpsPFTauDiscriminationAgainstLooseElectron->at(pair) ){ (*(histoCollection->find("HPSDiscAgainstElectron_s"))).second->GetHisto()->Fill(1.0, eventWeight); }
		else{														(*(histoCollection->find("HPSDiscAgainstElectron_s"))).second->GetHisto()->Fill(0.0, eventWeight); }
	}

	if(histoCollection->find("HPSDiscAgainstMuon_LS") != histoCollection->end()){
		if(Tau1hpsPFTauDiscriminationAgainstTightMuon->at(pair) ){ (*(histoCollection->find("HPSDiscAgainstMuon_LS"))).second->GetHisto()->Fill(2.0, eventWeight); }
		if(Tau1hpsPFTauDiscriminationAgainstLooseMuon->at(pair) ){ (*(histoCollection->find("HPSDiscAgainstMuon_LS"))).second->GetHisto()->Fill(1.0, eventWeight); }
		else{														(*(histoCollection->find("HPSDiscAgainstMuon_LS"))).second->GetHisto()->Fill(0.0, eventWeight); }

		if(Tau2hpsPFTauDiscriminationAgainstTightMuon->at(pair) ){ (*(histoCollection->find("HPSDiscAgainstMuon_LS"))).second->GetHisto()->Fill(2.0, eventWeight); }
		if(Tau2hpsPFTauDiscriminationAgainstLooseMuon->at(pair) ){ (*(histoCollection->find("HPSDiscAgainstMuon_LS"))).second->GetHisto()->Fill(1.0, eventWeight); }
		else{														(*(histoCollection->find("HPSDiscAgainstMuon_LS"))).second->GetHisto()->Fill(0.0, eventWeight); }
	}

	if(histoCollection->find("HPSDiscAgainstMuon_L") != histoCollection->end()){
		if(Tau1hpsPFTauDiscriminationAgainstTightMuon->at(pair) ){ (*(histoCollection->find("HPSDiscAgainstMuon_L"))).second->GetHisto()->Fill(2.0, eventWeight); }
		if(Tau1hpsPFTauDiscriminationAgainstLooseMuon->at(pair) ){ (*(histoCollection->find("HPSDiscAgainstMuon_L"))).second->GetHisto()->Fill(1.0, eventWeight); }
		else{														(*(histoCollection->find("HPSDiscAgainstMuon_L"))).second->GetHisto()->Fill(0.0, eventWeight); }
	}

	if(histoCollection->find("HPSDiscAgainstMuon_S") != histoCollection->end()){
		if(Tau2hpsPFTauDiscriminationAgainstTightMuon->at(pair) ){ (*(histoCollection->find("HPSDiscAgainstMuon_S"))).second->GetHisto()->Fill(2.0, eventWeight); }
		if(Tau2hpsPFTauDiscriminationAgainstLooseMuon->at(pair) ){ (*(histoCollection->find("HPSDiscAgainstMuon_S"))).second->GetHisto()->Fill(1.0, eventWeight); }
		else{														(*(histoCollection->find("HPSDiscAgainstMuon_S"))).second->GetHisto()->Fill(0.0, eventWeight); }
	}

	/*
	if(histoCollection->find("DecayMode_LS") != histoCollection->end()){
		(*(histoCollection->find("DecayMode_LS"))).second->GetHisto()->Fill(Tau1DecayMode->at(pair), eventWeight );
		(*(histoCollection->find("DecayMode_LS"))).second->GetHisto()->Fill(Tau2DecayMode->at(pair), eventWeight );
	}

	if(histoCollection->find("DecayMode_L") != histoCollection->end()){
		(*(histoCollection->find("DecayMode_L"))).second->GetHisto()->Fill(Tau1DecayMode->at(pair), eventWeight );
	}

	if(histoCollection->find("DecayMode_S") != histoCollection->end()){
		(*(histoCollection->find("DecayMode_S"))).second->GetHisto()->Fill(Tau2DecayMode->at(pair), eventWeight );
	}

	if(histoCollection->find("DecayModeFinding_LS") != histoCollection->end()){
		(*(histoCollection->find("DecayModeFinding_LS"))).second->GetHisto()->Fill(Tau1hpsPFTauDiscriminationByDecayModeFinding->at(pair), eventWeight );
		(*(histoCollection->find("DecayModeFinding_LS"))).second->GetHisto()->Fill(Tau2hpsPFTauDiscriminationByDecayModeFinding->at(pair), eventWeight );
	}

	if(histoCollection->find("DecayModeFinding_L") != histoCollection->end()){
		(*(histoCollection->find("DecayModeFinding_L"))).second->GetHisto()->Fill(Tau1hpsPFTauDiscriminationByDecayModeFinding->at(pair), eventWeight );
	}

	if(histoCollection->find("DecayModeFinding_S") != histoCollection->end()){
		(*(histoCollection->find("DecayModeFinding_S"))).second->GetHisto()->Fill(Tau2hpsPFTauDiscriminationByDecayModeFinding->at(pair), eventWeight );
	}
	//*/

/*
	if(histoCollection->find("Pt_LS") != histoCollection->end()){
		(*(histoCollection->find("Pt_LS"))).second->GetHisto()->Fill(Tau1Pt->at(pair), eventWeight );
		(*(histoCollection->find("Pt_LS"))).second->GetHisto()->Fill(Tau2Pt->at(pair), eventWeight );
	}
	if(histoCollection->find("Pt_LS_forNote") != histoCollection->end()){
		(*(histoCollection->find("Pt_LS_forNote"))).second->GetHisto()->Fill(Tau1Pt->at(pair), eventWeight );
		(*(histoCollection->find("Pt_LS_forNote"))).second->GetHisto()->Fill(Tau2Pt->at(pair), eventWeight );
	}

	if(histoCollection->find("Pt_L") != histoCollection->end()){
		(*(histoCollection->find("Pt_L"))).second->GetHisto()->Fill(Tau1Pt->at(pair), eventWeight );
	}
	if(histoCollection->find("Pt_legTrigger_LS") != histoCollection->end()){
		(*(histoCollection->find("Pt_legTrigger_LS"))).second->GetHisto()->Fill(Tau1Pt->at(pair), tau1Weight );
		(*(histoCollection->find("Pt_legTrigger_LS"))).second->GetHisto()->Fill(Tau2Pt->at(pair), tau2Weight );
	}

	if(histoCollection->find("Pt_noTrigger_LS") != histoCollection->end()){
		(*(histoCollection->find("Pt_noTrigger_LS"))).second->GetHisto()->Fill(Tau1Pt->at(pair), PUweight );
		(*(histoCollection->find("Pt_noTrigger_LS"))).second->GetHisto()->Fill(Tau2Pt->at(pair), PUweight );
	}

	if(histoCollection->find("Pt_S") != histoCollection->end()){
		(*(histoCollection->find("Pt_S"))).second->GetHisto()->Fill(Tau2Pt->at(pair), eventWeight );
	}

	if(histoCollection->find("LTpT_LS") != histoCollection->end()){
		(*(histoCollection->find("LTpT_LS"))).second->GetHisto()->Fill(Tau1LTPt->at(pair), eventWeight );
		(*(histoCollection->find("LTpT_LS"))).second->GetHisto()->Fill(Tau2LTPt->at(pair), eventWeight );
	}

	if(histoCollection->find("LTpT_L") != histoCollection->end()){
		(*(histoCollection->find("LTpT_L"))).second->GetHisto()->Fill(Tau1LTPt->at(pair), eventWeight );
	}

	if(histoCollection->find("LTpT_S") != histoCollection->end()){
		(*(histoCollection->find("LTpT_S"))).second->GetHisto()->Fill(Tau2LTPt->at(pair), eventWeight );
	}

	if(histoCollection->find("NumProngs_LS") != histoCollection->end()){
		(*(histoCollection->find("NumProngs_LS"))).second->GetHisto()->Fill(Tau1NProngs->at(pair), eventWeight );
		(*(histoCollection->find("NumProngs_LS"))).second->GetHisto()->Fill(Tau2NProngs->at(pair), eventWeight );
	}

	if(histoCollection->find("NumProngs_L") != histoCollection->end()){
		(*(histoCollection->find("NumProngs_L"))).second->GetHisto()->Fill(Tau1NProngs->at(pair), eventWeight );
	}
	
	if(histoCollection->find("NumProngs_S") != histoCollection->end()){
		(*(histoCollection->find("NumProngs_S"))).second->GetHisto()->Fill(Tau2NProngs->at(pair), eventWeight );
	}

	if(histoCollection->find("CosDeltaPhi_LM") != histoCollection->end()){
		(*(histoCollection->find("CosDeltaPhi_LM"))).second->GetHisto()->Fill(Tau1MetCosDphi->at(pair), eventWeight );
	}

	if(histoCollection->find("CosDeltaPhi_SM") != histoCollection->end()){
		(*(histoCollection->find("CosDeltaPhi_SM"))).second->GetHisto()->Fill(Tau2MetCosDphi->at(pair), eventWeight );
	}

	if(histoCollection->find("DeltaPhi_LM") != histoCollection->end()){
		(*(histoCollection->find("DeltaPhi_LM"))).second->GetHisto()->Fill(acos(Tau1MetCosDphi->at(pair)), eventWeight );
	}

	if(histoCollection->find("DeltaPhi_SM") != histoCollection->end()){
		(*(histoCollection->find("DeltaPhi_SM"))).second->GetHisto()->Fill(acos(Tau2MetCosDphi->at(pair)), eventWeight );
	}

	if(histoCollection->find("SumETotherJets") != histoCollection->end()){
		(*(histoCollection->find("SumETotherJets"))).second->GetHisto()->Fill(jetSumEt->at(pair), eventWeight);
	}

	if(histoCollection->find("SumETotherJetsPlusMET") != histoCollection->end()){
		(*(histoCollection->find("SumETotherJetsPlusMET"))).second->GetHisto()->Fill(jetMETSumEt->at(pair), eventWeight);
	}

	if(histoCollection->find("NumOtherJets") != histoCollection->end()){
		(*(histoCollection->find("NumOtherJets"))).second->GetHisto()->Fill(nJets->at(pair), eventWeight);
	}

	if(histoCollection->find("EmFraction_LS") != histoCollection->end()){
		(*(histoCollection->find("EmFraction_LS"))).second->GetHisto()->Fill(Tau1EmFraction->at(pair), eventWeight );
		(*(histoCollection->find("EmFraction_LS"))).second->GetHisto()->Fill(Tau2EmFraction->at(pair), eventWeight );
	}

	if(histoCollection->find("ChargeProduct_LS") != histoCollection->end()){
		(*(histoCollection->find("ChargeProduct_LS"))).second->GetHisto()->Fill((Tau1Charge->at(pair) * Tau2Charge->at(pair)), eventWeight );
	}

	if(histoCollection->find("SumPtIsoGammas_LS") != histoCollection->end()){
		(*(histoCollection->find("SumPtIsoGammas_LS"))).second->GetHisto()->Fill(Tau1SumPtIsoGammas->at(pair), eventWeight );
		(*(histoCollection->find("SumPtIsoGammas_LS"))).second->GetHisto()->Fill(Tau2SumPtIsoGammas->at(pair), eventWeight );
	}

	if(histoCollection->find("SumPtIsoGammas_L") != histoCollection->end()){
		(*(histoCollection->find("SumPtIsoGammas_L"))).second->GetHisto()->Fill(Tau1SumPtIsoGammas->at(pair), eventWeight );
	}
	
	if(histoCollection->find("SumPtIsoGammas_S") != histoCollection->end()){
		(*(histoCollection->find("SumPtIsoGammas_S"))).second->GetHisto()->Fill(Tau1SumPtIsoGammas->at(pair), eventWeight );
	}

	if(histoCollection->find("SumPtIsoTracks_LS") != histoCollection->end()){
		(*(histoCollection->find("SumPtIsoTracks_LS"))).second->GetHisto()->Fill(Tau1SumPtIsoTracks->at(pair), eventWeight );
		(*(histoCollection->find("SumPtIsoTracks_LS"))).second->GetHisto()->Fill(Tau2SumPtIsoTracks->at(pair), eventWeight );
	}

	if(histoCollection->find("SumPtIsoTracks_L") != histoCollection->end()){
		(*(histoCollection->find("SumPtIsoTracks_L"))).second->GetHisto()->Fill(Tau1SumPtIsoTracks->at(pair), eventWeight );
	}

	if(histoCollection->find("SumPtIsoTracks_s") != histoCollection->end()){
		(*(histoCollection->find("SumPtIsoTracks_s"))).second->GetHisto()->Fill(Tau2SumPtIsoTracks->at(pair), eventWeight );
	}

	if(histoCollection->find("Eta_LS") != histoCollection->end()){
		(*(histoCollection->find("Eta_LS"))).second->GetHisto()->Fill(Tau1Eta->at(pair), eventWeight );
		(*(histoCollection->find("Eta_LS"))).second->GetHisto()->Fill(Tau2Eta->at(pair), eventWeight );
	}
	
	if(histoCollection->find("Eta_L") != histoCollection->end()){
		(*(histoCollection->find("Eta_L"))).second->GetHisto()->Fill(Tau1Eta->at(pair), eventWeight );
	}

	if(histoCollection->find("Eta_S") != histoCollection->end()){
		(*(histoCollection->find("Eta_S"))).second->GetHisto()->Fill(Tau2Eta->at(pair), eventWeight );
	}

	if(histoCollection->find("Phi_LS") != histoCollection->end()){
		(*(histoCollection->find("Phi_LS"))).second->GetHisto()->Fill(Tau1Phi->at(pair), eventWeight );
		(*(histoCollection->find("Phi_LS"))).second->GetHisto()->Fill(Tau2Phi->at(pair), eventWeight );
	}

	if(histoCollection->find("Phi_L") != histoCollection->end()){
		(*(histoCollection->find("Phi_L"))).second->GetHisto()->Fill(Tau1Phi->at(pair), eventWeight );
	}

	if(histoCollection->find("Phi_S") != histoCollection->end()){
		(*(histoCollection->find("Phi_S"))).second->GetHisto()->Fill(Tau2Phi->at(pair), eventWeight );
	}

	if(histoCollection->find("CosDeltaPhi_LS") != histoCollection->end()){
		(*(histoCollection->find("CosDeltaPhi_LS"))).second->GetHisto()->Fill(TauTauCosDPhi->at(pair), eventWeight);
	}
	if(histoCollection->find("CosDeltaEta_LS") != histoCollection->end()){
		(*(histoCollection->find("CosDeltaEta_LS"))).second->GetHisto()->Fill(cos(fabs(Tau1Eta->at(pair)-Tau2Eta->at(pair))), eventWeight);
	}
	if(histoCollection->find("DeltaPhi_LS") != histoCollection->end()){
		(*(histoCollection->find("DeltaPhi_LS"))).second->GetHisto()->Fill((acos(cos(Tau1Phi->at(pair)-Tau2Phi->at(pair)))), eventWeight);
	}

	if(histoCollection->find("DeltaEta_LS") != histoCollection->end()){
		(*(histoCollection->find("DeltaEta_LS"))).second->GetHisto()->Fill(fabs(Tau1Eta->at(pair)-Tau2Eta->at(pair)), eventWeight);
	}

	if(histoCollection->find("DeltaR_LS") != histoCollection->end()){
		(*(histoCollection->find("DeltaR_LS"))).second->GetHisto()->Fill(TauTauDeltaR->at(pair), eventWeight);
	}

	if(histoCollection->find("LTNumHits_LS") != histoCollection->end()){
		(*(histoCollection->find("LTNumHits_LS"))).second->GetHisto()->Fill(Tau1LTValidHits->at(pair), eventWeight );
		(*(histoCollection->find("LTNumHits_LS"))).second->GetHisto()->Fill(Tau2LTValidHits->at(pair), eventWeight );
	}

	if(histoCollection->find("PZeta_LSM") != histoCollection->end()){
		(*(histoCollection->find("PZeta_LSM"))).second->GetHisto()->Fill(TauTauPZeta->at(pair), eventWeight );
	}

	if(histoCollection->find("PZetaVis_LSM") != histoCollection->end()){
		(*(histoCollection->find("PZetaVis_LSM"))).second->GetHisto()->Fill(TauTauPZetaVis->at(pair), eventWeight );
	}

	if(histoCollection->find("Zeta_LSM") != histoCollection->end()){
		(*(histoCollection->find("Zeta_LSM"))).second->GetHisto()->Fill((TauTauPZeta->at(pair)-0.875*TauTauPZetaVis->at(pair)), eventWeight );
	}

	if(histoCollection->find("Btags") != histoCollection->end()){
		(*(histoCollection->find("Btags"))).second->GetHisto()->Fill(nBtagsHiEffTrkCnt->at(pair), eventWeight );
	}

	if(histoCollection->find("PtVsPt_LS") != histoCollection->end()){
		((TH2F*)((*(histoCollection->find("PtVsPt_LS"))).second->GetHisto()))->Fill(Tau2Pt->at(pair), Tau1Pt->at(pair), eventWeight );
	}

	if(histoCollection->find("PtVsEta_LS") != histoCollection->end()){
		((TH2F*)((*(histoCollection->find("PtVsEta_LS"))).second->GetHisto()))->Fill((Tau1Eta->at(pair)), Tau1Pt->at(pair), eventWeight );
		((TH2F*)((*(histoCollection->find("PtVsEta_LS"))).second->GetHisto()))->Fill((Tau2Eta->at(pair)), Tau2Pt->at(pair), eventWeight );
	}
	if(histoCollection->find("PtVsEta_L") != histoCollection->end()){
		((TH2F*)((*(histoCollection->find("PtVsEta_L"))).second->GetHisto()))->Fill((Tau1Eta->at(pair)), Tau1Pt->at(pair), eventWeight );
	}
	if(histoCollection->find("PtVsEta_S") != histoCollection->end()){
		((TH2F*)((*(histoCollection->find("PtVsEta_S"))).second->GetHisto()))->Fill((Tau2Eta->at(pair)), Tau2Pt->at(pair), eventWeight );
	}


	if(histoCollection->find("PhiVsEta_LS") != histoCollection->end()){
		float phi = Tau1Phi->at(pair);
		int laps = floor(fabs(phi)/(2*TMath::Pi()));
		if(phi<0){ laps++; }
		phi+=(laps*2*TMath::Pi());
		((TH2F*)((*(histoCollection->find("PhiVsEta_LS"))).second->GetHisto()))->Fill((Tau1Eta->at(pair)), phi, eventWeight );

		phi = Tau2Phi->at(pair);
		laps = floor(fabs(phi)/(2*TMath::Pi()));
		if(phi<0){ laps++; }
		phi+=(laps*2*TMath::Pi());

		((TH2F*)((*(histoCollection->find("PhiVsEta_LS"))).second->GetHisto()))->Fill((Tau2Eta->at(pair)), phi, eventWeight );
	}

	if(histoCollection->find("PhiVsEta_L") != histoCollection->end()){
		float phi = Tau1Phi->at(pair);
		int laps = floor(fabs(phi)/(2*TMath::Pi()));
		if(phi<0){ laps++; }
		phi+=(laps*2*TMath::Pi());
		((TH2F*)((*(histoCollection->find("PhiVsEta_L"))).second->GetHisto()))->Fill((Tau1Eta->at(pair)), phi, eventWeight );
	}

	if(histoCollection->find("PhiVsEta_S") != histoCollection->end()){
		float phi = Tau2Phi->at(pair);
		int laps = floor(fabs(phi)/(2*TMath::Pi()));
		if(phi<0){ laps++; }
		phi+=(laps*2*TMath::Pi());
		((TH2F*)((*(histoCollection->find("PhiVsEta_S"))).second->GetHisto()))->Fill((Tau2Eta->at(pair)), phi, eventWeight );
	}

	if(histoCollection->find("EtaVsEta_LS") != histoCollection->end()){
		((TH2F*)((*(histoCollection->find("EtaVsEta_LS"))).second->GetHisto()))->Fill(Tau2Eta->at(pair), Tau1Eta->at(pair), eventWeight );
	}

	if(histoCollection->find("DeltaPhiVsDeltaEta_LS") != histoCollection->end()){
		((TH2F*)((*(histoCollection->find("DeltaPhiVsDeltaEta_LS"))).second->GetHisto()))->Fill(fabs(Tau1Eta->at(pair)-Tau2Eta->at(pair)), acos(cos(Tau1Phi->at(pair)-Tau2Phi->at(pair))), eventWeight );
	}
	
	if(histoCollection->find("CosDeltaPhiVsCosDeltaEta_LS") != histoCollection->end()){
		((TH2F*)((*(histoCollection->find("CosDeltaPhiVsCosDeltaEta_LS"))).second->GetHisto()))->Fill(cos(Tau1Eta->at(pair)-Tau2Eta->at(pair)), cos(Tau1Phi->at(pair)-Tau2Phi->at(pair)), eventWeight );
	}

	if(histoCollection->find("EtaVSNumPV_L") != histoCollection->end()){
		((TH2F*)((*(histoCollection->find("EtaVSNumPV_L"))).second->GetHisto()))->Fill(NumPV->at(pair),fabs(Tau1Eta->at(pair)), eventWeight );
	}
	if(histoCollection->find("EtaVSNumPV_S") != histoCollection->end()){
		((TH2F*)((*(histoCollection->find("EtaVSNumPV_S"))).second->GetHisto()))->Fill(NumPV->at(pair),fabs(Tau2Eta->at(pair)), eventWeight );
	}
	if(histoCollection->find("PtVSNumPV_L") != histoCollection->end()){
		((TH2F*)((*(histoCollection->find("PtVSNumPV_L"))).second->GetHisto()))->Fill(NumPV->at(pair),Tau1Pt->at(pair), eventWeight );
	}
	if(histoCollection->find("PtVSNumPV_S") != histoCollection->end()){
		((TH2F*)((*(histoCollection->find("PtVSNumPV_S"))).second->GetHisto()))->Fill(NumPV->at(pair),Tau2Pt->at(pair), eventWeight );
	}
	if(histoCollection->find("CosDeltaPhiVSNumPV_LS") != histoCollection->end()){
		((TH2F*)((*(histoCollection->find("CosDeltaPhiVSNumPV_LS"))).second->GetHisto()))->Fill(NumPV->at(pair),TauTauCosDPhi->at(pair), eventWeight );
	}




	// ===================== Tau-Electron matching plots ========================= //
	/*
	if(histoCollection->find("MatchedElecPt_L") != histoCollection->end()){
		(*(histoCollection->find("MatchedElecPt_L"))).second->GetHisto()->Fill(Tau1MElecPt->at(pair), eventWeight );
	}
	if(histoCollection->find("MatchedElecPt_S") != histoCollection->end()){
		(*(histoCollection->find("MatchedElecPt_S"))).second->GetHisto()->Fill(Tau2MElecPt->at(pair), eventWeight );
	}

	if(histoCollection->find("MatchedElecPtDiff_L") != histoCollection->end()){
		(*(histoCollection->find("MatchedElecPtDiff_L"))).second->GetHisto()->Fill(Tau1MElecPt->at(pair)-Tau1Pt->at(pair), eventWeight );
	}
	if(histoCollection->find("MatchedElecPtDiff_S") != histoCollection->end()){
		(*(histoCollection->find("MatchedElecPtDiff_S"))).second->GetHisto()->Fill(Tau2MElecPt->at(pair)-Tau2Pt->at(pair), eventWeight );
	}

	if(histoCollection->find("MatchedElecDeltaR_L") != histoCollection->end()){
		(*(histoCollection->find("MatchedElecDeltaR_L"))).second->GetHisto()->Fill(Tau1MElecDeltaR->at(pair), eventWeight );
	}
	if(histoCollection->find("MatchedElecDeltaR_S") != histoCollection->end()){
		(*(histoCollection->find("MatchedElecDeltaR_S"))).second->GetHisto()->Fill(Tau2MElecDeltaR->at(pair), eventWeight );
	}


	// Isolation
	if(histoCollection->find("MatchedElecIsoTrkSumPt_L") != histoCollection->end()){
		(*(histoCollection->find("MatchedElecIsoTrkSumPt_L"))).second->GetHisto()->Fill(Tau1MElecTrkSumPt->at(pair), eventWeight );
	}
	if(histoCollection->find("MatchedElecIsoTrkSumPt_S") != histoCollection->end()){
		(*(histoCollection->find("MatchedElecIsoTrkSumPt_S"))).second->GetHisto()->Fill(Tau2MElecTrkSumPt->at(pair), eventWeight );
	}
	if(histoCollection->find("MatchedElecEcalIsoRecHitSumEt_L") != histoCollection->end()){
		(*(histoCollection->find("MatchedElecEcalIsoRecHitSumEt_L"))).second->GetHisto()->Fill(Tau1MElecEcalRecHitSumEt->at(pair), eventWeight );
	}
	if(histoCollection->find("MatchedElecEcalIsoRecHitSumEt_S") != histoCollection->end()){
		(*(histoCollection->find("MatchedElecEcalIsoRecHitSumEt_S"))).second->GetHisto()->Fill(Tau2MElecEcalRecHitSumEt->at(pair), eventWeight );
	}

	// Isolation diff
	if(histoCollection->find("MatchedElecIsoTrkSumPtDiff_L") != histoCollection->end()){
		(*(histoCollection->find("MatchedElecIsoTrkSumPtDiff_L"))).second->GetHisto()->Fill(Tau1SumPtIsoTracks->at(pair)-Tau1MElecTrkSumPt->at(pair), eventWeight );
	}
	if(histoCollection->find("MatchedElecIsoTrkSumPtDiff_S") != histoCollection->end()){
		(*(histoCollection->find("MatchedElecIsoTrkSumPtDiff_S"))).second->GetHisto()->Fill(Tau2SumPtIsoTracks->at(pair)-Tau2MElecTrkSumPt->at(pair), eventWeight );
	}
	if(histoCollection->find("MatchedElecEcalIsoRecHitSumEtDiff_L") != histoCollection->end()){
		(*(histoCollection->find("MatchedElecEcalIsoRecHitSumEtDiff_L"))).second->GetHisto()->Fill(Tau1SumPtIsoGammas->at(pair)-Tau1MElecEcalRecHitSumEt->at(pair), eventWeight );
	}
	if(histoCollection->find("MatchedElecEcalIsoRecHitSumEtDiff_S") != histoCollection->end()){
		(*(histoCollection->find("MatchedElecEcalIsoRecHitSumEtDiff_S"))).second->GetHisto()->Fill(Tau2SumPtIsoGammas->at(pair)-Tau2MElecEcalRecHitSumEt->at(pair), eventWeight );
	}//*/

/*
	if(isMC && IsFlagThere("PUcorr")){ 
		if(histoCollection->find("PUweightsPassingEvents") != histoCollection->end()){
			(*(histoCollection->find("PUweightsPassingEvents"))).second->GetHisto()->Fill(puCorrector->GetWeight(NumPV->at(pair)));
		}
	}

}

Int_t Analyzer::GetEntry(Long64_t entry){
	// Read contents of entry.
	if (!fChain) return 0;
	return fChain->GetEntry(entry);
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
		Notify();
	}
	return centry;
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

bool Analyzer::IsFlagThere(string iFlag){
	size_t found = flags.find(iFlag);
	return ((0 <= found) && (found < flags.length()));
}

// Set up PU corrector from file
void Analyzer::LoadPuFile(string iPuFile){
	puCorrector		= new PUcorrector(iPuFile);
}

// Set up trigger config file
void Analyzer::LoadTriggerConfig(string iTriggerConfig){
	tauTrigger		= new Trigger(iTriggerConfig);
}

// Check whether iValue is within range (useful for selection cuts)
bool Analyzer::OutOfRange(float iValue, float iMin, float iMax){
	return ((iValue < iMin) || (iMax < iValue));
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

/*
	SetEffectiveLumi(iTopologies->GetEffectiveLumi());

	// Collisions
	cout << ">>> Processing collisions..." << endl;
	if(iTopologies->DoCollisions()){
		iTopologies->GetCollisions()->SetHistos(	GetOSPlots(
														iTopologies->GetCollisions()->GetPathToNtuples(),
														false, false,
														iTopologies->GetCollisions()->GetNumEvInDS(),
														iTopologies->GetCollisions()->GetNumEvInPAT(),
														iTopologies->GetCollisions()->GetOtherSF(),
														1.0
													)
												);	
		iTopologies->GetCollisions()->SetCutResults(cutFlow);
	}

	// MC backgrounds
	if(iTopologies->DoMCbackgrounds()){
		vector<Topology*>* MCbackgrounds = iTopologies->GetMCbackgrounds();
		for(unsigned int b = 0; b < MCbackgrounds->size(); b++){
			cout << ">>> Processing " << MCbackgrounds->at(b)->GetName() << "..." << endl;
			MCbackgrounds->at(b)->SetHistos(	GetOSPlots(
														MCbackgrounds->at(b)->GetPathToNtuples(),
														true, false,
														MCbackgrounds->at(b)->GetNumEvInDS(),
														MCbackgrounds->at(b)->GetNumEvInPAT(),
														MCbackgrounds->at(b)->GetOtherSF(),
														1.0
												)
											);
		}
	}

	// QCD => LS collisions & LS MC backgrounds
	if(iTopologies->DoQCD()){

		// LS collisions
		iTopologies->GetCollisions()->SetLSHistos(	GetQCDPlots(
														iTopologies->GetCollisions()->GetPathToNtuples(),
														false, false,
														iTopologies->GetCollisions()->GetNumEvInDS(),
														iTopologies->GetCollisions()->GetNumEvInPAT(),
														iTopologies->GetCollisions()->GetOtherSF(),
														1.0
													)
												);	

		// LS MC backgrounds
		vector<Topology*>* MCbackgrounds = iTopologies->GetMCbackgrounds();
		for(unsigned int b = 0; b < MCbackgrounds->size(); b++){
			cout << ">>> Processing LS " << MCbackgrounds->at(b)->GetName() << "..." << endl;
			MCbackgrounds->at(b)->SetLSHistos(		GetQCDPlots(
														MCbackgrounds->at(b)->GetPathToNtuples(),
														true, false,
														MCbackgrounds->at(b)->GetNumEvInDS(),
														MCbackgrounds->at(b)->GetNumEvInPAT(),
														MCbackgrounds->at(b)->GetOtherSF(),
														1.0
												)
											);
		}

		// Build it!
		iTopologies->BuildQCD();
	}

	// Signals
	if(iTopologies->DoSignals()){
		vector<Topology*>* signals = iTopologies->GetSignals();
		for(unsigned int s = 0; s < signals->size(); s++){
			cout << ">>> Processing " << signals->at(s)->GetName() << "..." << endl;
			signals->at(s)->SetHistos(	GetOSPlots(
											signals->at(s)->GetPathToNtuples(),
											true, true,
											signals->at(s)->GetNumEvInDS(),
											signals->at(s)->GetNumEvInPAT(),
											signals->at(s)->GetOtherSF(),
											1.0
										)
									);
		}
	}

	//*/

	// Set analyzed flag in topoPack to true
	iTopologies->SetAnalyzed();
	
}

//*/
