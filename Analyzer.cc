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
		goodEventsForSignal.clear();
		goodEventsForQCD.clear();
		tmvaEvaluator = NULL;
}

// Default constructor
Analyzer::Analyzer(map<string,string> const & iParams){
	params = iParams;

	event = NULL;
	goodEventsForSignal.clear();
	goodEventsForQCD.clear();

	cutFlow		= CutFlow(params["cutsToApply"]);
	cutFlow.Reset();

	#include "clarity/cuts_false.h"
	SetCutsToApply(params["cutsToApply"]);

	// If a cut on the MVA is requested, initialize TMVA reader
	tmvaEvaluator = NULL;
	//if(CutOn_MVA){ tmvaEvaluator = new TMVAEvaluator(iParams); }
	//else{ tmvaEvaluator = NULL; }

}

// Default destructor
Analyzer::~Analyzer(){
	delete event; event = NULL;
	delete tmvaEvaluator; tmvaEvaluator = NULL;
}


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
	cutFlow.SetCutCounts("skimming + PAT", iProcess.GetNOEinPATuple(), iProcess.GetNOEinPATuple());
	goodEventsForSignal.clear();
	goodEventsForQCD.clear();

	event = new DitauBranches(params, ((params.find("ntuplesDir")->second) + (iProcess.GetNtuplePath())));

	isSignal = iProcess.IsSignal();
	isMC = iProcess.IsMC();
	pair<double,double> loopResults = Loop();
	cout << endl;

	iProcess.SetGoodEventsForSignal(goodEventsForSignal);
	iProcess.SetGoodEventsForQCD(goodEventsForQCD);
	iProcess.SetNOEinNtuple(loopResults.first);
	iProcess.SetNOEanalyzed(loopResults.second);
	iProcess.SetCutFlow(cutFlow);

	delete event;
	event = NULL;
}

void Analyzer::Analyze(vector<Process>& iProcesses){
	for(unsigned int p=0; p<iProcesses.size(); p++){ Analyze(iProcesses.at(p)); }
}

void Analyzer::Reset(){
}

pair<double,double> Analyzer::Loop(){
	cerr << "Calling Loop() from " << __FILE__ << " is not allowed. It must be called from a derived class." << endl; exit(1);
	pair<double,double> result = make_pair(0,0);
	return result;
}

pair<bool,bool> Analyzer::ComboPassesCuts(unsigned int iCombo){
	cerr << "Calling ComboPassesCuts() from " << __FILE__ << " is not allowed. It must be called from a derived class." << endl; exit(1);
	pair<bool,bool> target = make_pair(false, false);
	return target;
}



void Analyzer::SetCutsToApply(string iCutsToApply){
	#include "clarity/cuts_setCutsToApply.h"
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

