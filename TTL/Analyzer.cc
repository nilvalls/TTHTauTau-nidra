/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			07 Jun 2011
    Description:	Plotting macro for ditau analysis.
    Notes:

*/

#include <unistd.h>

#include "Analyzer.h"

using namespace std;

// Default constructor
TTLAnalyzer::TTLAnalyzer(map<string,string> const & iParams) : Analyzer(iParams){
    isBaseAnalyzer	= false;

    cutFlow.RegisterCut("Read from DS", 0);
    cutFlow.RegisterCut("skimming + PAT", 0);
    cutFlow.RegisterCut("nTuple making", 0);

    if (atoi((params["maxEvents"]).c_str()) >= 0) {
        cutFlow.RegisterCut("User event limit", 0);
    }

    cutFlow.RegisterCut("TTL_AtLeastOneCombo", 0);

    // if(ApplyThisCut("RunNumber"    )){ CutOn_RunNumber     =  true; cutFlow.RegisterCut("RunNumber", 1);     }
    // if(ApplyThisCut("LumiSection"    )){ CutOn_LumiSection    =  true; cutFlow.RegisterCut("LumiSection", 1);    }
    // if(ApplyThisCut("EventNumber"    )){ CutOn_EventNumber    =  true; cutFlow.RegisterCut("EventNumber", 1);    }
    // if(ApplyThisCut("GenMatching"    )){ CutOn_GenMatching    =  true; cutFlow.RegisterCut("GenMatching", 1);    }
    // if(ApplyThisCut("NumHadronicGenTaus"  )){ CutOn_NumHadronicGenTaus  =  true; cutFlow.RegisterCut("NumHadronicGenTaus", 1);   }
    //   if(selectedEvents.size() > 0){   cutFlow.RegisterCut("Run:LS:Event", 1);  }
    // if(ApplyThisCut("InvariantMass"   )){ CutOn_InvariantMass    =  true; cutFlow.RegisterCut("InvariantMass", 1);    }
    // if(ApplyThisCut("VisibleMass"    )){ CutOn_VisibleMass    =  true; cutFlow.RegisterCut("VisibleMass", 1);    }

    // if(ApplyThisCut("G_NumGenHadTausFromH"  )){ CutOn_G_NumGenHadTausFromH  =  true; cutFlow.RegisterCut("G_NumGenHadTausFromH", 1);  }

    cutFlow.RegisterCut("J_NumCSVL", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_NumCSVLbtagJets->at(idx); });
    cutFlow.RegisterCut("J_NumCSVM", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_NumCSVMbtagJets->at(idx); });
    cutFlow.RegisterCut("J_NumCSVT", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_NumCSVTbtagJets->at(idx); });
    cutFlow.RegisterCut("J_NumNonCSVL", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_NumNonCSVLbtagJets->at(idx); });
    cutFlow.RegisterCut("J_NumNonCSVM", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_NumNonCSVMbtagJets->at(idx); });
    cutFlow.RegisterCut("J_NumNonCSVT", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_NumNonCSVTbtagJets->at(idx); });
    cutFlow.RegisterCut("J_NumInclusive", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_NumCSVMbtagJets->at(idx) + e->TTL_NumNonCSVMbtagJets->at(idx); });
    cutFlow.RegisterCut("J_NumCleanCSVL", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_NumCleanCSVLbtagJets->at(idx); });
    cutFlow.RegisterCut("J_NumCleanCSVM", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_NumCleanCSVMbtagJets->at(idx); });
    cutFlow.RegisterCut("J_NumCleanCSVT", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_NumCleanCSVTbtagJets->at(idx); });
    cutFlow.RegisterCut("J_NumCleanNonCSVL", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_NumCleanNonCSVLbtagJets->at(idx); });
    cutFlow.RegisterCut("J_NumCleanNonCSVM", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_NumCleanNonCSVMbtagJets->at(idx); });
    cutFlow.RegisterCut("J_NumCleanNonCSVT", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_NumCleanNonCSVTbtagJets->at(idx); });
    cutFlow.RegisterCut("J_NumCleanInclusive", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_NumCleanCSVMbtagJets->at(idx) + e->TTL_NumCleanNonCSVMbtagJets->at(idx); });
    cutFlow.RegisterCut("NumTightLeptons", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_NumTightMuons->at(idx) + e->TTL_NumTightElectrons->at(idx); });
    cutFlow.RegisterCut("NumTightMuons", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_NumTightMuons->at(idx); });
    cutFlow.RegisterCut("NumTightElectrons", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_NumTightElectrons->at(idx); });
    cutFlow.RegisterCut("NumLooseLeptons", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_NumLooseMuons->at(idx) + e->TTL_NumLooseElectrons->at(idx); });
    cutFlow.RegisterCut("NumLooseMuons", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_NumLooseMuons->at(idx); });
    cutFlow.RegisterCut("NumLooseElectrons", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_NumLooseElectrons->at(idx); });
    cutFlow.RegisterCut("NumExLooseLeptons", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_NumExLooseMuons->at(idx) + e->TTL_NumExLooseElectrons->at(idx); });
    cutFlow.RegisterCut("NumExLooseMuons", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_NumExLooseMuons->at(idx); });
    cutFlow.RegisterCut("NumExLooseElectrons", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_NumExLooseElectrons->at(idx); });

    cutFlow.RegisterCut("L_pT", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_LeptonPt->at(idx); });
    cutFlow.RegisterCut("L_Eta", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_LeptonEta->at(idx); });
    cutFlow.RegisterCut("L_IsLoose", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_LeptonIsLoose->at(idx); });
    cutFlow.RegisterCut("L_IsTight", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_LeptonIsTight->at(idx); });
    cutFlow.RegisterCut("L_RelIso", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_LeptonRelIso->at(idx); });

    cutFlow.RegisterCut("T1_MatchAbsId", 1, [](TTLBranches *e, const int idx) -> float {
            return abs(e->TTL_Tau1GenMatchId->at(idx)); }, true);
    cutFlow.RegisterCut("T2_MatchAbsId", 1, [](TTLBranches *e, const int idx) -> float {
            return abs(e->TTL_Tau2GenMatchId->at(idx)); }, true);
    cutFlow.RegisterCut("T1_ParentAbsId", 1, [](TTLBranches *e, const int idx) -> float {
            return abs(e->TTL_Tau1GenMatchMother0Id->at(idx)); }, true);
    cutFlow.RegisterCut("T2_ParentAbsId", 1, [](TTLBranches *e, const int idx) -> float {
            return abs(e->TTL_Tau2GenMatchMother0Id->at(idx)); }, true);

    cutFlow.RegisterCut("T1_pT", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_Tau1Pt->at(idx); });
    cutFlow.RegisterCut("T2_pT", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_Tau2Pt->at(idx); });
    cutFlow.RegisterCut("T1_Eta", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_Tau1Eta->at(idx); });
    cutFlow.RegisterCut("T2_Eta", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_Tau2Eta->at(idx); });
    cutFlow.RegisterCut("T1_InCracks", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_Tau1IsInTheCracks->at(idx); });
    cutFlow.RegisterCut("T2_InCracks", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_Tau2IsInTheCracks->at(idx); });

    cutFlow.RegisterCut("TT_DeltaR", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_DitauDeltaR->at(idx); });
    cutFlow.RegisterCut("T1L_DeltaR", 1, [](TTLBranches *e, const int idx) -> float {
            return DeltaR(e->TTL_Tau1Eta->at(idx), e->TTL_Tau1Phi->at(idx),
                e->TTL_LeptonEta->at(idx), e->TTL_LeptonPhi->at(idx)); });
    cutFlow.RegisterCut("T2L_DeltaR", 1, [](TTLBranches *e, const int idx) -> float {
            return DeltaR(e->TTL_Tau2Eta->at(idx), e->TTL_Tau2Phi->at(idx),
                e->TTL_LeptonEta->at(idx), e->TTL_LeptonPhi->at(idx)); });

    cutFlow.RegisterCut("T1_DecayModeFinding", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_Tau1HPSdecayModeFinding->at(idx); });
    cutFlow.RegisterCut("T2_DecayModeFinding", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_Tau2HPSdecayModeFinding->at(idx); });
    cutFlow.RegisterCut("T1_LTvalid", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_Tau1LTvalid->at(idx); });
    cutFlow.RegisterCut("T2_LTvalid", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_Tau2LTvalid->at(idx); });
    cutFlow.RegisterCut("T1_LTpT", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_Tau1LTPt->at(idx); });
    cutFlow.RegisterCut("T2_LTpT", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_Tau2LTPt->at(idx); });
    cutFlow.RegisterCut("T1_NumProngs", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_Tau1NProngs->at(idx); });
    cutFlow.RegisterCut("T2_NumProngs", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_Tau2NProngs->at(idx); });

    cutFlow.RegisterCut("T1_AntiElectronMVA", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_Tau1HPSagainstElectronMVA->at(idx); });
    cutFlow.RegisterCut("T2_AntiElectronMVA", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_Tau2HPSagainstElectronMVA->at(idx); });
    cutFlow.RegisterCut("T1_AntiElectronIndex", 1, [](TTLBranches *e, const int idx) -> float {
            return e->GetTau1AntiElectronIndex(idx); });
    cutFlow.RegisterCut("T2_AntiElectronIndex", 1, [](TTLBranches *e, const int idx) -> float {
            return e->GetTau2AntiElectronIndex(idx); });
    cutFlow.RegisterCut("T1_AntiMuonIndex", 1, [](TTLBranches *e, const int idx) -> float {
            return e->GetTau1AntiMuonIndex(idx); });
    cutFlow.RegisterCut("T2_AntiMuonIndex", 1, [](TTLBranches *e, const int idx) -> float {
            return e->GetTau2AntiMuonIndex(idx); });
    cutFlow.RegisterCut("T1_IsolationIndex", 1, [](TTLBranches *e, const int idx) -> float {
            return e->GetTau1IsolationIndex(idx); });
    cutFlow.RegisterCut("T2_IsolationIndex", 1, [](TTLBranches *e, const int idx) -> float {
            return e->GetTau2IsolationIndex(idx); });
    cutFlow.RegisterCut("T1_IsolationMVA2Raw", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_Tau1HPSbyIsolationMVA2raw->at(idx); });
    cutFlow.RegisterCut("T2_IsolationMVA2Raw", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_Tau2HPSbyIsolationMVA2raw->at(idx); });

    cutFlow.RegisterCut("TT_ChargeProduct", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_Tau1Charge->at(idx) * e->TTL_Tau2Charge->at(idx); });

    cutFlow.RegisterCut("TT_VisMass", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_DitauVisibleMass->at(idx); });
    cutFlow.RegisterCut("TT_DeltaEta", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_Tau1Eta->at(idx) - e->TTL_Tau2Eta->at(idx); });
    cutFlow.RegisterCut("TT_CosDeltaPhi", 1, [](TTLBranches *e, const int idx) -> float {
            return e->TTL_DitauCosDeltaPhi->at(idx); });
    cutFlow.RegisterCut("MET", 1, [](TTLBranches *e, const int idx) -> float {
            return e->Ev_MET; });
    cutFlow.RegisterCut("MVA", 1, [](TTLBranches *e, const int idx) -> float {
            return TTL_TMVAEvaluator::gMVA ? TTL_TMVAEvaluator::gMVA->Evaluate(e, idx) : 0.; });

    mva = TTL_TMVAEvaluator::gMVA;
    comboSelector = TTL_ComboSelector::gComboMVA;
}

// Default destructor
TTLAnalyzer::~TTLAnalyzer() {}

void TTLAnalyzer::Reset() {}

pair<double,double> TTLAnalyzer::Loop(Branches* iEvent, Process const & iProcess, const bool iTrainComboSelectorSampler){
	int n_to_read = iProcess.GetNoEreadByNUTter();
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

		multimap<double, unsigned int> combos;
        if ((params["comboSelectorProcess"] == iProcess.GetShortName() && iTrainComboSelectorSampler)
                || params["selectComboBy"] == "pt"){
            combos = comboSelector->GetSortedCombosByPt(event);
        } else {
            combos = comboSelector->GetSortedCombos(event);
        }

        int bestComboForSignal = -1;
		for(multimap<double, unsigned int>::reverse_iterator combo = combos.rbegin(); combo != combos.rend(); ++combo){

			// Obtain combo's mass
			float comboMass = event->TTL_DitauVisibleMass->at(combo->second);
			if( comboMass <= 0 ){ cout << "WARNING: ditauMass < 0!" << endl;  continue; }

			// If we already have one good combo for signal and one for QCD, no need to check the rest since the heaviest combos come first
            if (cutFlow.CheckCuts(event, combo->second, !checkReality)) {
                bestComboForSignal = combo->second;
                break;
            }
		}

		// Inform cutFlow that we've checked all the combos
        // cutFlow.EndOfEvent();
		//cutFlow.PrintTable() ;

		// Fill good event vectors for signal analysis
		if (bestComboForSignal >= 0) {
			event->SetBestCombo(bestComboForSignal);
			goodEventsForSignal.push_back(make_pair(jentry, bestComboForSignal));

            if (params["comboSelectorProcess"] == iProcess.GetShortName() &&
                    iTrainComboSelectorSampler)
                TTL_ComboSelector::gComboMVA->FillTrees(event);
		}

		NOEanalyzed++;
	}

	if(atoi((params["maxEvents"]).c_str()) >= 0){ cutFlow.SetCutCounts("User event limit", NOEanalyzed, NOEanalyzed); }
	cutFlow.SetCutCounts("TTL_AtLeastOneCombo", NOEwithAtLeastOneCombo, NOEwithAtLeastOneCombo);

	//fout.close();
	result = make_pair(nentries, NOEanalyzed);
	return result;
}
