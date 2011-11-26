
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


// Default destructor
CutFlow::~CutFlow(){}

void CutFlow::Reset(){

	cutNames.clear();
	minThresholds.clear();
	maxThresholds.clear();

	thisCombosResults.clear();

	passedCombosForSignal.clear();
	passedCombosForQCD.clear();

	passedEventsForSignal.clear();
	passedEventsForQCD.clear();

	heaviestComboForSignal	= -1;
	heaviestComboForQCD		= -1;

}

void CutFlow::RegisterCut(string iName){
	cutNames.push_back(iName);

	passedEventsForSignal[iName]	= 0;
	passedEventsForQCD[iName]		= 0;

	pair<float,float> thresholds = ExtractCutThresholds(iName);
	minThresholds[iName] = (thresholds.first);
	maxThresholds[iName] = (thresholds.second);
}


bool CutFlow::CheckCombo(string iName, float iValue){

	// If the value relevant for this cut is within thresholds, increase counter
	if( minThresholds[iName] <= iValue && iValue <= maxThresholds[iName] ){
		thisCombosResults[iName]++;
		
		return true;
	}

	return false;
}

// This function is intended to save time if we have already one good combo for signal and one for QCD. Since the heaviest combos come first, no need to check the rest. This will tell the analyzer it's time to move on.
bool CutFlow::HaveGoodCombos(){
	return ((heaviestComboForSignal >= 0) && (heaviestComboForQCD >= 0));
}


void CutFlow::EndOfCombo(pair<bool,bool> iCombosTarget, int iComboNumber){

	// At the end of the cutflow for this very combo, determine its target, and fill the signal/QCD combo counters accordingly
	bool comboIsForSignal	= iCombosTarget.first;
	bool comboIsForQCD		= iCombosTarget.second;

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

		// Reset the temporary combo counter
		thisCombosResults[cutName] == 0;
	}
}

// At the end of the event, loop over both combo counters (forSignal and forQCD) and check independently which combos have passed which cuts
void CutFlow::EndOfEvent(){

	eventForSignalPassed = false;	
	eventForQCDPassed = false;	

	// Loop over all the cuts
	for(unsigned int c=0; c<cutNames.size(); c++){

		// If at least one combo for signal has passed this cut, increase the event count in the "forSignal" cut map FOR THAT CUT only
		if(passedCombosForSignal[cutNames.at(c)] > 0){ passedEventsForSignal[cutNames.at(c)]++; }	

		// If at least one combo for signal has made it all the way through all the cuts (i.e. if this is the last cut), then indicate we have a "good event for signal"
		if((c == cutNames.size()-1) && passedCombosForSignal[cutNames.at(c)] > 0){ eventForSignalPassed = true; }

		// If at least one combo for QCD has passed this cut, increase the event count in the "forQCD" cut map FOR THAT CUT only
		if(passedCombosForSignal[cutNames.at(c)] > 0){ passedEventsForSignal[cutNames.at(c)]++; }	

		// If at least one combo for QCD has made it all the way through all the cuts (i.e. if this is the last cut), then indicate we have a "good QCD event for QCD"
		if((c == cutNames.size()-1) && passedCombosForQCD[cutNames.at(c)] > 0){ eventForQCDPassed = true; }
	}

	// Clean up things to get them ready for next event
	heaviestComboForSignal	= -1;
	heaviestComboForQCD		= -1;
}

bool CutFlow::EventForSignalPassed(){ return eventForSignalPassed; }

bool CutFlow::EventForQCDPassed(){ return eventForQCDPassed; }

int CutFlow::GetHeaviestComboForSignal(){
	if(!eventForSignalPassed){ cerr << "ERROR: trying to obtain highest combo in event for signal, but no event for signal has passed all the cuts" << endl; exit(1); }
	return heaviestComboForSignal;
}

int CutFlow::GetHeaviestComboForQCD(){
	if(!eventForQCDPassed){ cerr << "ERROR: trying to obtain highest combo in event for QCD, but no event for QCD has passed all the cuts" << endl; exit(1); }
	return heaviestComboForQCD;
}




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

// Check whether iValue is within range (useful for selection cuts)
bool CutFlow::OutOfRange(float iValue, float iMin, float iMax){
	return ((iValue < iMin) || (iMax < iValue));
}


//ClassImp(CutFlow)
