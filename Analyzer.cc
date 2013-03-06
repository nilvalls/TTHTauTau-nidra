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
		isBaseAnalyzer = true;
		goodEventsForSignal.clear();
		goodEventsForQCD.clear();
}

// Default constructor
Analyzer::Analyzer(map<string,string> const & iParams){
	isBaseAnalyzer = true;
	params = iParams;

	goodEventsForSignal.clear();
	goodEventsForQCD.clear();

	cutFlow	= CutFlow(params["cutsToApply"]);
	cutFlow.Reset();

}

// Default destructor
Analyzer::~Analyzer(){}

void Analyzer::AnalyzeAll(ProPack& iProPack){

	// Print processes to be analyzed and plotted
	cout << endl;
	cout << "\tTo be analyzed: " << iProPack.GetProccessNamesToAnalyze() << endl;
	cout << endl;

	map<string,Process> * processes = iProPack.GetPContainer()->GetContainer();
	for(map<string,Process>::iterator p = processes->begin(); p != processes->end(); p++){ Analyze((p)->second); }
}

void Analyzer::Analyze(Process& iProcess){

	//Reset();
	cout << "\tNow analyzing " << iProcess.GetShortName() << endl;

	cutFlow.Zero();
	cutFlow.SetCutCounts("Read from DS", iProcess.GetNOEinDS(), iProcess.GetNOEinDS());
	cutFlow.SetCutCounts("skimming + PAT", iProcess.GetNoEreadByNUTter(), iProcess.GetNoEreadByNUTter());
	goodEventsForSignal.clear();
	goodEventsForQCD.clear();

	Branches* event = NULL;

   if (params["channel"] == "TTM") {
      event = new TTMBranches(params, iProcess.GetNtuplePaths());
   } else if (params["channel"] == "TTE") {
      event = new TTEBranches(params, iProcess.GetNtuplePaths());
   } else if (params["channel"] == "TTL") {
      event = new TTLBranches(params, iProcess.GetNtuplePaths());
   }

	isSignal		= iProcess.IsSignal();
	checkReality	= iProcess.CheckReality();
	isMC			= iProcess.IsMC();
	pair<double,double> loopResults = Loop(event);
	cout << endl;

	iProcess.SetGoodEventsForSignal(goodEventsForSignal);
	iProcess.SetGoodEventsForQCD(goodEventsForQCD);
	iProcess.SetNOEinNtuple(loopResults.first);
	iProcess.SetNOEanalyzed(loopResults.second);
	iProcess.SetCutFlow(cutFlow);

	delete event;
	event = NULL;
}

void Analyzer::Analyze(vector<Process>& iProcesses){ for(unsigned int p=0; p<iProcesses.size(); p++){ Analyze(iProcesses.at(p)); } }


pair<double,double> Analyzer::Loop(Branches* iEvent){ return make_pair(0,0); }
pair<bool,bool> Analyzer::ComboPassesCuts(Branches* iEvent, unsigned int iCombo){ return make_pair(false, false); }

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

