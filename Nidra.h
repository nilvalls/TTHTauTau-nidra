#ifndef __Nidra_h
#define __Nidra_h

#include "CutFlow.h"
#include "Process.h"

namespace Nidra {
    template<typename T> void Analyze(Process&, const std::string&, const std::string&, const int&);
    void Combine(ProPack&);
}

template<typename T>
void
Nidra::Analyze(Process& proc, const std::string& cuts, const std::string& tree_name, const int& limit)
{
    CutFlow cflow(cuts);
    cflow.Reset();
    cflow.Zero();

    std::vector<Process::Event> good_events;

    T *event = new T(tree_name, proc.GetNtuplePaths());

    bool checkReality = proc.CheckReality();

    cflow.RegisterCut("Read from DS", 0);
    cflow.RegisterCut("skimming + PAT", 0);
    cflow.RegisterCut("nTuple making", 0);
    if (limit >= 0)
        cflow.RegisterCut("User event limit", 0);
	cflow.RegisterCut("AtLeastOneCombo", 0);


    cflow.SetCutCounts("Read from DS", proc.GetNOEinDS());
    cflow.SetCutCounts("skimming + PAT", proc.GetNoEreadByNUTter());

    int n_to_read = proc.GetNoEreadByNUTter();

    event->RegisterCuts(cflow);

    Long64_t nentries = event->GetEntries();
    if (nentries == 0) {
        cerr << "ERROR: process " << proc.GetShortName() << " has zero events to read" << endl;
        exit(1);
    } else if (nentries != n_to_read) {
        cerr << "WARNING: tree size does not match topology specification! "
            << nentries << " events found, " << n_to_read << " expected."  << endl;
    }

    cout << "\tAnalyzing " << proc.GetShortName() << endl;
    cout << "\t>>> Starting loop... " << " " << nentries << " entries available: ";
    cflow.SetCutCounts("nTuple making", nentries);

    if (limit <= 0 || limit >= nentries) {
        cout << "Processing all of them..." << string(14,'.') << " ";
    } else {
        cout << "Stopping at " << limit << " as per-user request" << string(14,'.') << " ";
    }
    cout.flush();

    //ofstream fout("events.txt");


    // Actual loop
    double NOEanalyzed = 0;
    double NOEwithAtLeastOneCombo = 0;
    for (Long64_t jentry=0; jentry<nentries; jentry++) {
        // Keep user informed of the number of events processed and if there is a termination due to reaching of the limit
        if ( limit > 0 && jentry >= (unsigned int)(limit)){ cout << "\n\t>>> INFO: Reached user-imposed event number limit (" << limit << "), skipping the rest." << endl; break; }

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
        event->GetEntry(jentry);

        if (event->GetNumCombos() > 0)
            NOEwithAtLeastOneCombo++;

        // Inform cflow that a new event is starting
        cflow.StartOfEvent();

        vector<int> combos;
		for (unsigned int i = 0; i < event->GetNumCombos(); ++i) {
			if (cflow.CheckCuts(event, i, !checkReality))
				combos.push_back(i);
		}


        // Fill good event vectors for signal analysis
        if (combos.size() > 0) {
            good_events.push_back(Process::Event(jentry, combos));
        }

        NOEanalyzed++;
    }

    if (limit >= 0)
        cflow.SetCutCounts("User event limit", NOEanalyzed);

	cflow.SetCutCounts("AtLeastOneCombo", NOEwithAtLeastOneCombo);

    cout << endl;

    proc.SetGoodEventsForSignal(good_events);
    proc.SetNOEinNtuple(nentries);
    proc.SetNOEanalyzed(NOEanalyzed);
    proc.SetCutFlow(cflow);

    delete event;
}

#endif
