
#define CutFlow_cxx
#include "CutFlow.h"

using namespace std;



// Default constructor
CutFlow::CutFlow(){}

CutFlow::CutFlow(string iCuts){
	cutsToApply = iCuts;
	minThresholds.clear();
	maxThresholds.clear();

}

CutFlow::CutFlow(CutFlow const &){

	preCutNames		= GetPreCutNames();
	cutNames		= GetCutNames();
	postCutNames	= GetPostCutNames();
	minThresholds	= GetMinThresholds();
	maxThresholds 	= GetMaxThresholds();

	thisCombosResults		= map<string, bool>();
	passedCombosForSignal	= map<string, float>();
	passedCombosForQCD		= map<string, float>();
	passedEventsForSignal	= GetPassedEventsForSignal();
	passedEventsForQCD		= GetPassedEventsForQCD();

	passedEventsForSignalPreCuts	= GetPassedEventsForSignalPreCuts();
	passedEventsForQCDPreCuts		= GetPassedEventsForQCDPreCuts();
	passedEventsForSignalPostCuts	= GetPassedEventsForSignalPostCuts();
	passedEventsForQCDPostCuts		= GetPassedEventsForQCDPostCuts();

	cutsToApply	= GetCutsToApply();

	eventForSignalPassed	= false;
	eventForQCDPassed		= false;
	comboIsForSignal		= false;
	comboIsForQCD			= false;

	heaviestComboForSignal	= -1;
	heaviestComboForQCD		= -1;
}


// Default destructor
CutFlow::~CutFlow(){}

void CutFlow::Reset(){

	cutNames.clear();
	preCutNames.clear();
	postCutNames.clear();
	minThresholds.clear();
	maxThresholds.clear();
	
	Zero();
}

void CutFlow::Zero(){
	thisCombosResults.clear();

	passedCombosForSignal.clear();
	passedCombosForQCD.clear();

	passedEventsForSignal.clear();
	passedEventsForQCD.clear();

	heaviestComboForSignal	= -1;
	heaviestComboForQCD		= -1;

	passedEventsForSignalPreCuts.clear();
	passedEventsForQCDPreCuts.clear();
	passedEventsForSignalPostCuts.clear();
	passedEventsForQCDPostCuts.clear();
}

void CutFlow::RegisterCut(string iName){
	cutNames.push_back(iName);

	passedEventsForSignal[iName]	= 0;
	passedEventsForQCD[iName]		= 0;

	pair<float,float> thresholds = ExtractCutThresholds(iName);
	minThresholds[iName] = (thresholds.first);
	maxThresholds[iName] = (thresholds.second);

}


void CutFlow::RegisterPreCut(string const iName){ RegisterPreCut(iName, 0); }
void CutFlow::RegisterPreCut(string const iName, double const iEvents){
	preCutNames.push_back(iName);
	passedEventsForSignalPreCuts[iName] = 0;
	passedEventsForQCDPreCuts[iName] = 0;
}

void CutFlow::RegisterPostCut(string const iName){ RegisterPostCut(iName, 0); }
void CutFlow::RegisterPostCut(string const iName, double const iEvents){
	postCutNames.push_back(iName);
	passedEventsForSignalPostCuts[iName] = 0;
	passedEventsForQCDPostCuts[iName] = 0;
}

void CutFlow::SetPreCutForSignal(string const iName, double const iEvents){ passedEventsForSignalPreCuts[iName] = iEvents; }
void CutFlow::SetPreCutForQCD(string const iName, double const iEvents){ passedEventsForQCDPreCuts[iName] = iEvents; }
void CutFlow::SetPostCutForSignal(string const iName, double const iEvents){ passedEventsForSignalPostCuts[iName] = iEvents; }
void CutFlow::SetPostCutForQCD(string const iName, double const iEvents){ passedEventsForQCDPostCuts[iName] = iEvents; }


void CutFlow::AddPreCutEventForSignal(string const iName, double const iWeight){	passedEventsForSignalPreCuts[iName]  += iWeight;	}
void CutFlow::AddPreCutEventForQCD(string const iName, double const iWeight){		passedEventsForQCDPreCuts[iName] 	 += iWeight;	}
void CutFlow::AddPostCutEventForSignal(string const iName, double const iWeight){	passedEventsForSignalPostCuts[iName] += iWeight;	}
void CutFlow::AddPostCutEventForQCD(string const iName, double const iWeight){		passedEventsForQCDPostCuts[iName]	 += iWeight;	}


bool CutFlow::CheckCombo(string const iName, float const iValue){
	bool result = false;

	// If the value relevant for this cut is within thresholds, set results for this cut to true
	if( minThresholds[iName] <= iValue && iValue <= maxThresholds[iName] ){ result = true; }
	thisCombosResults[iName] = result;

	return result;
}

// This function is intended to save time if we have already one good combo for signal and one for QCD. Since the heaviest combos come first, no need to check the rest. This will tell the analyzer it's time to move on.
bool CutFlow::HaveGoodCombos(){
	return ((heaviestComboForSignal >= 0) && (heaviestComboForQCD >= 0));
}


void CutFlow::EndOfCombo(pair<bool, bool> iCombosTarget, int const iComboNumber){

	// At the end of the cutflow for this very combo, determine its target, and fill the signal/QCD combo counters accordingly
	bool comboIsForSignal	= iCombosTarget.first;
	bool comboIsForQCD		= iCombosTarget.second;

	// Provided that the each target has not yet been satisfied by any combo, assume the first combo to do so is good
	// Then assume that the first combo that satisfies the target is the heaviest. If there are registered cuts, they will change this if needed
	if(comboIsForSignal	&& (heaviestComboForSignal < 0)){ eventForSignalPassed	= true;	heaviestComboForSignal  = iComboNumber; }
	if(comboIsForQCD	&& (heaviestComboForQCD < 0)){	  eventForQCDPassed		= true;	heaviestComboForQCD  	= iComboNumber; }


	// Loop over all the cuts this combo has gone through
	for(unsigned int c=0; c<cutNames.size(); c++){
		string cutName = cutNames.at(c);

		// If this combo has not passed all the requested cuts, stop loop
		if(!thisCombosResults[cutName]){ break; }
		// else figure out its target...

		// If this combo is good for signal analysis, add the counts to the signal combo counter
		if(comboIsForSignal){
			passedCombosForSignal[cutName]++;
			
			// If no combo for signal has yet passed all the cuts and this one passes all the cuts, store its combo number
			if((heaviestComboForSignal < 0) && (c == cutNames.size()-1)){ heaviestComboForSignal = iComboNumber; }
		}

		// If this combo is good for QCD analysis, add the counts to the QCD combo counter
		if(comboIsForQCD){
			passedCombosForQCD[cutName]++;

			// If no combo for QCD has yet passed all the cuts and this one passes all the cuts, store its combo number
			if((heaviestComboForQCD < 0) && (c == cutNames.size()-1)){ heaviestComboForQCD = iComboNumber; }
		}
	}
}

// Reset counters relevant to the start of the event
void CutFlow::StartOfEvent(){

	heaviestComboForSignal	= -1;
	heaviestComboForQCD		= -1;

	eventForSignalPassed	= false;	
	eventForQCDPassed		= false;	

	for(unsigned int c=0; c<cutNames.size(); c++){
		string cutName = cutNames.at(c);
		passedCombosForSignal[cutName]	= 0;
		passedCombosForQCD[cutName]		= 0;
	}

}

// At the end of the event, loop over both combo counters (forSignal and forQCD) and check independently which combos have passed which cuts
void CutFlow::EndOfEvent(){

	// Loop over all the cuts
	for(unsigned int c=0; c<cutNames.size(); c++){
		string cutName = cutNames.at(c);

		// If at least one combo for signal has passed this cut, increase the event count in the "forSignal" cut map FOR THAT CUT only
		if(passedCombosForSignal[cutName] > 0){ passedEventsForSignal[cutName]++; }	

		// Wait for the last registered cut to determine the outcome of the event
		if(c == cutNames.size()-1){ eventForSignalPassed = (passedCombosForSignal[cutName] > 0); }

		// If at least one combo for QCD has passed this cut, increase the event count in the "forQCD" cut map FOR THAT CUT only
		if(passedCombosForSignal[cutName] > 0){ passedEventsForQCD[cutName]++; }	

		// Wait for the last registered cut to determine the outcome of the event
		if(c == cutNames.size()-1){ eventForQCDPassed = (passedCombosForQCD[cutName] > 0); }

		// Reset combo counter
		passedCombosForSignal[cutName]	= 0;
		passedCombosForQCD[cutName]		= 0;
	}

}

bool CutFlow::EventForSignalPassed(){ 
	if(eventForSignalPassed && (heaviestComboForSignal==-1)){ cerr << "ERROR: about to return true EventForSignalPassed() but heaviestCombo is -1" << endl; exit(1); }
	return eventForSignalPassed;
}

bool CutFlow::EventForQCDPassed(){
	if(eventForQCDPassed && (heaviestComboForQCD==-1)){ cerr << "ERROR: about to return true EventForQCDPassed() but heaviestCombo is -1" << endl; exit(1); }
	return eventForQCDPassed;
}

int CutFlow::GetHeaviestComboForSignal(){
	if(!eventForSignalPassed){ cerr << "ERROR: trying to obtain highest combo in event for signal, but no event for signal has passed all the cuts" << endl; exit(1); }
	return heaviestComboForSignal;
}

int CutFlow::GetHeaviestComboForQCD(){
	if(!eventForQCDPassed){ cerr << "ERROR: trying to obtain highest combo in event for QCD, but no event for QCD has passed all the cuts" << endl; exit(1); }
	return heaviestComboForQCD;
}


void CutFlow::PrintTest(){
	
	for(unsigned int c=0; c<preCutNames.size(); c++){	cout << preCutNames.at(c) << "\t" << passedEventsForSignalPreCuts[preCutNames.at(c)] << endl; }
	for(unsigned int c=0; c<cutNames.size(); c++){		cout << cutNames.at(c) << "\t" << passedEventsForSignal[cutNames.at(c)] << endl; }
	for(unsigned int c=0; c<postCutNames.size(); c++){	cout << postCutNames.at(c) << "\t" << passedEventsForSignalPostCuts[postCutNames.at(c)] << endl; }
}


vector<string> const		CutFlow::GetPreCutNames() const { return preCutNames; }
vector<string> const		CutFlow::GetCutNames() const { return cutNames; }
vector<string> const		CutFlow::GetPostCutNames() const { return postCutNames; }
map<string, float> const	CutFlow::GetMinThresholds() const { return minThresholds; }
map<string, float> const	CutFlow::GetMaxThresholds() const { return maxThresholds; }
map<string, float> const	CutFlow::GetPassedEventsForSignal() const { return passedEventsForSignal; }
map<string, float> const	CutFlow::GetPassedEventsForQCD() const { return passedEventsForQCD; }
map<string, float> const	CutFlow::GetPassedEventsForSignalPreCuts() const { return passedEventsForSignalPreCuts; }
map<string, float> const	CutFlow::GetPassedEventsForQCDPreCuts() const { return passedEventsForQCDPreCuts; }
map<string, float> const	CutFlow::GetPassedEventsForSignalPostCuts() const { return passedEventsForQCDPostCuts ; }
map<string, float> const	CutFlow::GetPassedEventsForQCDPostCuts() const { return passedEventsForQCDPostCuts; }
string const				CutFlow::GetCutsToApply() const { return cutsToApply; }






/*

long int CutFlow::GetEventsBeforeCut(string iName){
	return ((*eventsBeforeCut)[iName]);	
}

long int CutFlow::GetEventsBeforeCut(int iPos){
	return ((*eventsBeforeCut)[(cutNames->at(iPos))]);	
}

long int CutFlow::GetEventsAfterCut(string iName){
	return ((*eventsAfterCut)[iName]);	
}

long int CutFlow::GetEventsAfterCut(int iPos){
	return ((*eventsAfterCut)[(cutNames->at(iPos))]);	
}

float CutFlow::GetRelativeEfficiency(string iName){
	float result = 0;
	result = GetEventsAfterCut(iName)/GetEventsBeforeCut(iName);
	return result;
}

float CutFlow::GetRelativeEfficiencyError(string iName){
	float result = 0;
	result = GetRelativeEfficiency(iName)*sqrt(1/(double)GetEventsAfterCut(iName) - 1/(double)GetEventsBeforeCut(iName) ); // Binomial!!
	return result;
}

float CutFlow::GetRelativeEfficiency(int iPos){
	float result = 0;
	result = GetEventsAfterCut(iPos)/GetEventsBeforeCut(iPos);
	return result;
}

float CutFlow::GetRelativeEfficiencyError(int iPos){
	float result = 0;
	result = GetRelativeEfficiency(iPos)*sqrt(1/(double)GetEventsAfterCut(iPos) - 1/(double)GetEventsBeforeCut(iPos)); // Binomial!!
	return result;
}

float CutFlow::GetCumulativeEfficiency(string iName){
	float result = 0;
	result = GetEventsAfterCut(iName)/GetEventsBeforeCut(cutNames->front());
	return result;
}

float CutFlow::GetCumulativeEfficiencyError(string iName){
	float result = 0;
	result = GetCumulativeEfficiency(iName)*sqrt(1/(double)GetEventsAfterCut(iName) - 1/(double)GetEventsBeforeCut(cutNames->front()) ); // Binomial!!
	return result;
}

float CutFlow::GetCumulativeEfficiency(int iPos){
	float result = 0;
	result = GetEventsAfterCut(iPos)/GetEventsBeforeCut(iPos);
	return result;
}

float CutFlow::GetCumulativeEfficiencyError(int iPos){
	float result = 0;
	result = GetCumulativeEfficiency(iPos)*sqrt(1/(double)GetEventsAfterCut(iPos) - 1/(double)GetEventsBeforeCut(0)); // Binomial!!
	return result;
}

CutFlow* CutFlow::Clone(){
	CutFlow* result		= new CutFlow(*this);
	result->cutNames				= new vector<string>(*cutNames);
	result->eventsBeforeCut			= new map<string, double>(*eventsBeforeCut);
	result->eventsAfterCut			= new map<string, double>(*eventsAfterCut);
	result->eventsBeforeCutError	= new map<string, double>(*eventsBeforeCutError);
	result->eventsAfterCutError		= new map<string, double>(*eventsAfterCutError);
	result->scaleFactors			= new map<string, float>(*scaleFactors);
	result->scaleFactorsError		= new map<string, float>(*scaleFactorsError);
}

//*/

pair<float,float> CutFlow::ExtractCutThresholds(string iCutString){
	pair<float,float> result = make_pair(-FLT_MAX,FLT_MAX);

	string cutsToApplyTmp = " " + cutsToApply + " ";

	size_t foundNDef	= cutsToApplyTmp.find(" " + iCutString);
	size_t length		= cutsToApplyTmp.length();

	if ( !(0 <= foundNDef && foundNDef <= length) ){ return result; }



	// Now check if thresholds are there
	foundNDef	= cutsToApplyTmp.find(" " + iCutString + ":");
	length		= cutsToApplyTmp.length();

	if ( 0 <= foundNDef && foundNDef <= length ){
		string thresholds = cutsToApplyTmp.substr(foundNDef+iCutString.length()+2);
		thresholds = thresholds.substr(0,thresholds.find(" "));

		if(thresholds.find(":") >= thresholds.length()){
			cerr << "ERROR: Cut named \"" << iCutString << "\" is missing a colon in its non-default threshold definition." << endl; exit(1);
		}

		float min, max;
		string smin = thresholds.substr(0,thresholds.find(":"));
		string smax = string(thresholds.substr(thresholds.find(":")+1));

		if(smin.compare("") == 0){ min = -FLT_MAX; }
		else{ min = atof(smin.c_str()); }

		if(smax.compare("") == 0){ max = FLT_MAX; }
		else{ max = atof(smax.c_str()); }

		if( min > max ){
			cerr << "ERROR: Min threshold in cut named \"" << iCutString << "\" has a greater value than the max." << endl; exit(1);
		}

		result = make_pair(min,max);

	}else{
			cerr << "ERROR: Cut named \"" << iCutString << "\" is missing threshold definition." << endl; exit(1);
	}

	return result;

}

// Check whether iValue is within range (useful for selection cuts)
bool CutFlow::OutOfRange(float iValue, float iMin, float iMax){
	return ((iValue < iMin) || (iMax < iValue));
}


ClassImp(CutFlow)
