/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			07 Jun 2011
    Description:	Plotting macro for ditau analysis.
    Notes:

*/

#define DILAnalyzer_cxx
#include "Analyzer.h"

using namespace std;

// Default constructor
DILAnalyzer::DILAnalyzer(map<string,string> const & iParams) : Analyzer(iParams){
	isBaseAnalyzer	= false;
	
	#include "Cuts_false.h"

	string cutsToApply = params["cutsToApply"];
	#include "Cuts_setCutsToApply.h"

}

// Default destructor
DILAnalyzer::~DILAnalyzer(){}


void DILAnalyzer::Reset(){}


pair<double,double> DILAnalyzer::Loop(Branches* iEvent){
	DILBranches* event = (DILBranches*)iEvent;


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

	//ofstream fout("events.txt");
 

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
		if(event->Test_LeadingJetPt >= 0){ NOEwithAtLeastOneCombo++; }

		// Inform cutFlow that a new event is starting
		cutFlow.StartOfEvent();


		// Loop over all the combos
		//cout << "new event; " << event->DIL_NumCombos << " combos" <<  endl;
		bool comboHasTwoRealTaus = false;
		int realTauCombo = -1;
	//	for (unsigned int combo = 0; combo < event->DIL_NumCombos; combo++){

			// Rest of selections
			pair<bool,bool> combosTarget = ComboPassesCuts(event, 0);

			// Inform cutFlow that we've checked this combo against all cuts
			cutFlow.EndOfCombo(combosTarget, 0);

			// If we already have one good combo for signal and one for QCD, no need to check the rest since the heaviest combos come first
			//if(cutFlow.HaveGoodCombos()){ cout << "break here" << endl; }//break; }
	//		if(cutFlow.HaveGoodCombos()){ break; }
		//}

		if(comboHasTwoRealTaus){ NOEwithTwoRealTaus++; }
		else{ NOEwithoutTwoRealTaus++; }

		// Inform cutFlow that we've checked all the combos
		cutFlow.EndOfEvent();
		//cutFlow.PrintTable() ;

		// Fill good event vectors for signal analysis
		//cout << "cutFlow.EventForSignalPassed(): " << cutFlow.EventForSignalPassed() << endl;
		if(cutFlow.EventForSignalPassed()){
			event->SetBestCombo(0);
			goodEventsForSignal.push_back(make_pair(jentry, 0));
		}

		// Fill good event vectors for QCD analysis
		if(cutFlow.EventForQCDPassed()){
			event->SetBestCombo(-1);
			goodEventsForQCD.push_back(make_pair(jentry, -1));

		}

		NOEanalyzed++;
	}

//	cout << "NOEwithTwoRealTaus: " << setprecision(6) << NOEwithTwoRealTaus << " " << NOEwithoutTwoRealTaus << " " << (NOEwithTwoRealTaus+NOEwithoutTwoRealTaus) << endl;

	if(atoi((params["maxEvents"]).c_str()) >= 0){ cutFlow.SetCutCounts("User event limit", NOEanalyzed, NOEanalyzed); }
	cutFlow.SetCutCounts("DIL_AtLeastOneCombo", NOEwithAtLeastOneCombo, NOEwithAtLeastOneCombo);


	//fout.close();
	result = make_pair(nentries, NOEanalyzed);
	return result;
}



pair<bool,bool> DILAnalyzer::ComboPassesCuts(DILBranches* iEvent, unsigned int iCombo){

	DILBranches* event = iEvent;

	pair<bool,bool> target = make_pair(true, false);

	if(CutOn_Trigger){	if(cutFlow.CheckComboAndStop("Trigger",event->Test_Trigger, target)){ return target; }}
	if(CutOn_NumJets){	if(cutFlow.CheckComboAndStop("NumJets",event->Test_NumJets, target)){ return target; }}
	if(CutOn_NumCSVM){	if(cutFlow.CheckComboAndStop("NumCSVM",event->Test_NumCSVM, target)){ return target; }}
	if(CutOn_DIL){		if(cutFlow.CheckComboAndStop("DIL",(event->Test_PassesTMLE || event->Test_PassesTMTE || event->Test_PassesLMTE), target)){ return target; }}


	// Return target, first element is for signal analysis, second is for QCD
	return target;
}


