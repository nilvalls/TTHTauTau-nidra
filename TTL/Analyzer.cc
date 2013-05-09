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

    cutFlow.RegisterCut("T1_MatchAbsId", 1, [](TTLBranches *& e, const int& idx) -> float {
            return abs((*e->TTL_Tau1GenMatchId)[idx]); }, true);
    cutFlow.RegisterCut("T2_MatchAbsId", 1, [](TTLBranches *& e, const int& idx) -> float {
            return abs((*e->TTL_Tau2GenMatchId)[idx]); }, true);
    cutFlow.RegisterCut("T1_ParentAbsId", 1, [](TTLBranches *& e, const int& idx) -> float {
            return abs((*e->TTL_Tau1GenMatchMother0Id)[idx]); }, true);
    cutFlow.RegisterCut("T2_ParentAbsId", 1, [](TTLBranches *& e, const int& idx) -> float {
            return abs((*e->TTL_Tau2GenMatchMother0Id)[idx]); }, true);

    cutFlow.RegisterCut("J_NumCSVL", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_NumCSVLbtagJets)[idx]; });
    cutFlow.RegisterCut("J_NumCSVM", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_NumCSVMbtagJets)[idx]; });
    cutFlow.RegisterCut("J_NumCSVT", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_NumCSVTbtagJets)[idx]; });
    cutFlow.RegisterCut("J_NumNonCSVL", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_NumNonCSVLbtagJets)[idx]; });
    cutFlow.RegisterCut("J_NumNonCSVM", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_NumNonCSVMbtagJets)[idx]; });
    cutFlow.RegisterCut("J_NumNonCSVT", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_NumNonCSVTbtagJets)[idx]; });
    cutFlow.RegisterCut("J_NumInclusive", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_NumCSVMbtagJets)[idx] + (*e->TTL_NumNonCSVMbtagJets)[idx]; });
    cutFlow.RegisterCut("J_NumCleanCSVL", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_NumCleanCSVLbtagJets)[idx]; });
    cutFlow.RegisterCut("J_NumCleanCSVM", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_NumCleanCSVMbtagJets)[idx]; });
    cutFlow.RegisterCut("J_NumCleanCSVT", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_NumCleanCSVTbtagJets)[idx]; });
    cutFlow.RegisterCut("J_NumCleanNonCSVL", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_NumCleanNonCSVLbtagJets)[idx]; });
    cutFlow.RegisterCut("J_NumCleanNonCSVM", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_NumCleanNonCSVMbtagJets)[idx]; });
    cutFlow.RegisterCut("J_NumCleanNonCSVT", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_NumCleanNonCSVTbtagJets)[idx]; });
    cutFlow.RegisterCut("J_NumCleanInclusive", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_NumCleanCSVMbtagJets)[idx] + (*e->TTL_NumCleanNonCSVMbtagJets)[idx]; });
    cutFlow.RegisterCut("NumTightLeptons", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_NumTightMuons)[idx] + (*e->TTL_NumTightElectrons)[idx]; });
    cutFlow.RegisterCut("NumTightMuons", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_NumTightMuons)[idx]; });
    cutFlow.RegisterCut("NumTightElectrons", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_NumTightElectrons)[idx]; });
    cutFlow.RegisterCut("NumLooseLeptons", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_NumLooseMuons)[idx] + (*e->TTL_NumLooseElectrons)[idx]; });
    cutFlow.RegisterCut("NumLooseMuons", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_NumLooseMuons)[idx]; });
    cutFlow.RegisterCut("NumLooseElectrons", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_NumLooseElectrons)[idx]; });
    cutFlow.RegisterCut("NumExLooseLeptons", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_NumExLooseMuons)[idx] + (*e->TTL_NumExLooseElectrons)[idx]; });
    cutFlow.RegisterCut("NumExLooseMuons", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_NumExLooseMuons)[idx]; });
    cutFlow.RegisterCut("NumExLooseElectrons", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_NumExLooseElectrons)[idx]; });

    cutFlow.RegisterCut("L_pT", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_LeptonPt)[idx]; });
    cutFlow.RegisterCut("L_Eta", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_LeptonEta)[idx]; });
    cutFlow.RegisterCut("L_IsLoose", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_LeptonIsLoose)[idx]; });
    cutFlow.RegisterCut("L_IsTight", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_LeptonIsTight)[idx]; });
    cutFlow.RegisterCut("L_RelIso", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_LeptonRelIso)[idx]; });

    cutFlow.RegisterCut("T1_pT", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_Tau1Pt)[idx]; });
    cutFlow.RegisterCut("T2_pT", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_Tau2Pt)[idx]; });
    cutFlow.RegisterCut("T1_Eta", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_Tau1Eta)[idx]; });
    cutFlow.RegisterCut("T2_Eta", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_Tau2Eta)[idx]; });
    cutFlow.RegisterCut("T1_InCracks", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_Tau1IsInTheCracks)[idx]; });
    cutFlow.RegisterCut("T2_InCracks", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_Tau2IsInTheCracks)[idx]; });

    cutFlow.RegisterCut("TT_DeltaR", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_DitauDeltaR)[idx]; });
    cutFlow.RegisterCut("T1L_DeltaR", 1, [](TTLBranches *& e, const int& idx) -> float {
            return DeltaR((*e->TTL_Tau1Eta)[idx], (*e->TTL_Tau1Phi)[idx],
                (*e->TTL_LeptonEta)[idx], (*e->TTL_LeptonPhi)[idx]); });
    cutFlow.RegisterCut("T2L_DeltaR", 1, [](TTLBranches *& e, const int& idx) -> float {
            return DeltaR((*e->TTL_Tau2Eta)[idx], (*e->TTL_Tau2Phi)[idx],
                (*e->TTL_LeptonEta)[idx], (*e->TTL_LeptonPhi)[idx]); });

    cutFlow.RegisterCut("T1_DecayModeFinding", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_Tau1HPSdecayModeFinding)[idx]; });
    cutFlow.RegisterCut("T2_DecayModeFinding", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_Tau2HPSdecayModeFinding)[idx]; });
    cutFlow.RegisterCut("T1_LTvalid", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_Tau1LTvalid)[idx]; });
    cutFlow.RegisterCut("T2_LTvalid", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_Tau2LTvalid)[idx]; });
    cutFlow.RegisterCut("T1_LTpT", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_Tau1LTPt)[idx]; });
    cutFlow.RegisterCut("T2_LTpT", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_Tau2LTPt)[idx]; });
    cutFlow.RegisterCut("T1_NumProngs", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_Tau1NProngs)[idx]; });
    cutFlow.RegisterCut("T2_NumProngs", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_Tau2NProngs)[idx]; });

    cutFlow.RegisterCut("T1_AntiElectronMVA", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_Tau1HPSagainstElectronMVA)[idx]; });
    cutFlow.RegisterCut("T2_AntiElectronMVA", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_Tau2HPSagainstElectronMVA)[idx]; });
    cutFlow.RegisterCut("T1_AntiElectronIndex", 1, [](TTLBranches *& e, const int& idx) -> float {
            return e->GetTau1AntiElectronIndex(idx); });
    cutFlow.RegisterCut("T2_AntiElectronIndex", 1, [](TTLBranches *& e, const int& idx) -> float {
            return e->GetTau2AntiElectronIndex(idx); });
    cutFlow.RegisterCut("T1_AntiMuonIndex", 1, [](TTLBranches *& e, const int& idx) -> float {
            return e->GetTau1AntiMuonIndex(idx); });
    cutFlow.RegisterCut("T2_AntiMuonIndex", 1, [](TTLBranches *& e, const int& idx) -> float {
            return e->GetTau2AntiMuonIndex(idx); });

    cutFlow.RegisterCut("T1_IsolationIndex", 1, [](TTLBranches *& e, const int& idx) -> float {
            return e->GetTau1IsolationIndex(idx); });
    cutFlow.RegisterCut("T2_IsolationIndex", 1, [](TTLBranches *& e, const int& idx) -> float {
            return e->GetTau2IsolationIndex(idx); });
    cutFlow.RegisterCut("T1_IsolationIndex3Hits", 1, [](TTLBranches *& e, const int& idx) -> float {
            return e->GetTau1IsolationIndex3Hits(idx); });
    cutFlow.RegisterCut("T2_IsolationIndex3Hits", 1, [](TTLBranches *& e, const int& idx) -> float {
            return e->GetTau2IsolationIndex3Hits(idx); });
    cutFlow.RegisterCut("T1_IsolationIndexMVA", 1, [](TTLBranches *& e, const int& idx) -> float {
            return e->GetTau1IsolationIndexMVA(idx); });
    cutFlow.RegisterCut("T2_IsolationIndexMVA", 1, [](TTLBranches *& e, const int& idx) -> float {
            return e->GetTau2IsolationIndexMVA(idx); });
    cutFlow.RegisterCut("T1_IsolationIndexMVA2", 1, [](TTLBranches *& e, const int& idx) -> float {
            return e->GetTau1IsolationIndexMVA2(idx); });
    cutFlow.RegisterCut("T2_IsolationIndexMVA2", 1, [](TTLBranches *& e, const int& idx) -> float {
            return e->GetTau2IsolationIndexMVA2(idx); });
    cutFlow.RegisterCut("T1_IsolationMVA2Raw", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_Tau1HPSbyIsolationMVA2raw)[idx]; });
    cutFlow.RegisterCut("T2_IsolationMVA2Raw", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_Tau2HPSbyIsolationMVA2raw)[idx]; });

    cutFlow.RegisterCut("TT_ChargeProduct", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_Tau1Charge)[idx] * (*e->TTL_Tau2Charge)[idx]; });

    cutFlow.RegisterCut("TT_VisMass", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_DitauVisibleMass)[idx]; });
    cutFlow.RegisterCut("TT_DeltaEta", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_Tau1Eta)[idx] - (*e->TTL_Tau2Eta)[idx]; });
    cutFlow.RegisterCut("TT_CosDeltaPhi", 1, [](TTLBranches *& e, const int& idx) -> float {
            return (*e->TTL_DitauCosDeltaPhi)[idx]; });
    cutFlow.RegisterCut("MET", 1, [](TTLBranches *& e, const int& idx) -> float {
            return e->Ev_MET; });
    cutFlow.RegisterCut("MVA", 1, [](TTLBranches *& e, const int& idx) -> float {
            return TTL_TMVAEvaluator::gMVA ? TTL_TMVAEvaluator::gMVA->Evaluate(e, idx) : 0.; });

    mva = TTL_TMVAEvaluator::gMVA;
    comboSelector = TTL_TMVAEvaluator::gComboMVA;
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

        vector<int> combos;
        for (unsigned int i = 0; i < event->TTL_NumCombos; ++i) {
            float comboMass = (*event->TTL_DitauVisibleMass)[i];
            if( comboMass <= 0 ){ cout << "WARNING: ditauMass < 0!" << endl;  continue; }

            if (cutFlow.CheckCuts(event, i, !checkReality))
                combos.push_back(i);
        }

        // Fill good event vectors for signal analysis
        if (combos.size() > 0) {
            goodEventsForSignal.push_back(Process::Event(jentry, combos));
        }

        NOEanalyzed++;
    }

    if(atoi((params["maxEvents"]).c_str()) >= 0){ cutFlow.SetCutCounts("User event limit", NOEanalyzed, NOEanalyzed); }
    cutFlow.SetCutCounts("TTL_AtLeastOneCombo", NOEwithAtLeastOneCombo, NOEwithAtLeastOneCombo);

    //fout.close();
    result = make_pair(nentries, NOEanalyzed);
    return result;
}
