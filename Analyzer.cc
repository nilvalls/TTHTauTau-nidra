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
}

// Default constructor
Analyzer::Analyzer(map<string,string> const & iParams){
	isBaseAnalyzer = true;
	params = iParams;

	goodEventsForSignal.clear();

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

void Analyzer::SampleComboSelectorSampler(Process& iProcess){
	Analyze(iProcess, true);
}

void Analyzer::Analyze(Process& iProcess, const bool iTrainComboSelectorSampler)
{
	//Reset();
	cout << "\tNow analyzing " << iProcess.GetShortName() << endl;

	cutFlow.Zero();
	cutFlow.SetCutCounts("Read from DS", iProcess.GetNOEinDS());
	cutFlow.SetCutCounts("skimming + PAT", iProcess.GetNoEreadByNUTter());
	goodEventsForSignal.clear();

	Branches* event = NULL;

   if (params["channel"] == "TTL") {
      event = new TTLBranches(params, iProcess.GetNtuplePaths());
   }

	isSignal		= iProcess.IsSignal();
	checkReality	= iProcess.CheckReality();
	isMC			= iProcess.IsMC();
	pair<double,double> loopResults = Loop(event, iProcess, iTrainComboSelectorSampler);
	cout << endl;

	if(!iTrainComboSelectorSampler){ 
		iProcess.SetGoodEventsForSignal(goodEventsForSignal);
		iProcess.SetNOEinNtuple(loopResults.first);
		iProcess.SetNOEanalyzed(loopResults.second);
		iProcess.SetCutFlow(cutFlow);
	}

	delete event;
	event = NULL;
}

void Analyzer::Analyze(vector<Process>& iProcesses){ for(unsigned int p=0; p<iProcesses.size(); p++){ Analyze(iProcesses.at(p)); } }

bool Analyzer::IsFlagThere(string iFlag)
{
    string flags = params["flags"];
    return (flags.find(iFlag) != string::npos);
}

