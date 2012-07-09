
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

CutFlow::CutFlow(CutFlow const & iCutFlow){

	cutNames			= iCutFlow.GetCutNames();
	cutRanks			= iCutFlow.GetCutRanks();
	UpdateCutNamesMap();
	minThresholds		= iCutFlow.GetMinThresholds();
	maxThresholds 		= iCutFlow.GetMaxThresholds();

	thisCombosResultsForSignal	= map<string, bool>();
	thisCombosResultsForQCD		= map<string, bool>();
	passedCombosForSignal		= map<string, float>();
	passedCombosForQCD			= map<string, float>();
	passedEventsForSignal		= iCutFlow.GetPassedEventsForSignal();
	passedEventsForQCD			= iCutFlow.GetPassedEventsForQCD();

	cutsToApply	= iCutFlow.GetCutsToApply();

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
	cutRanks.clear();
	minThresholds.clear();
	maxThresholds.clear();
	
	Zero();

}

void CutFlow::Zero(){
	thisCombosResultsForSignal.clear();
	thisCombosResultsForQCD.clear();

	passedCombosForSignal.clear();
	passedCombosForQCD.clear();

	passedEventsForSignal.clear();
	passedEventsForQCD.clear();

	heaviestComboForSignal	= -1;
	heaviestComboForQCD		= -1;

	eventForSignalPassed	= false;
	eventForQCDPassed		= false;
	comboIsForSignal		= false;
	comboIsForQCD			= false;

	heaviestComboForSignal	= -1;
	heaviestComboForQCD		= -1;

}

int const CutFlow::size() const { return cutNames.size(); }

void CutFlow::InvertSignalAndQCD(){
		map<string, float>	temp = passedEventsForSignal;
		passedEventsForSignal	= passedEventsForQCD;
		passedEventsForQCD		= temp;
}

void CutFlow::RegisterCut(string const iName, int const iRank){
	cutNames.push_back(iName);
	if( (iRank < 0) || 2 < (iRank)){ cerr << "ERROR: Cut named \"" << iName << "\" is trying to be registered with rank " << iRank << " but rank can only be 0, 1, or 2." << endl; exit(1); }
	cutRanks[iName] = iRank;

	passedEventsForSignal[iName]	= 0.0;
	passedEventsForQCD[iName]		= 0.0;

	if(iRank==1){
		pair<float,float> thresholds = ExtractCutThresholds(iName);
		minThresholds[iName] = (thresholds.first);
		maxThresholds[iName] = (thresholds.second);
	}else{
		minThresholds[iName] = 0;
		maxThresholds[iName] = 0;
	}

	UpdateCutNamesMap();

}

void CutFlow::RegisterCut(string const iName, int const iRank,  double const iEventsForSignal, double const iEventsForQCD){
	cutNames.push_back(iName);
	if( (iRank < 0) || 2 < (iRank)){ cerr << "ERROR: Cut named \"" << iName << "\" is trying to be registered with rank " << iRank << " but rank can only be 0, 1, or 2." << endl; exit(1); }
	cutRanks[iName] = iRank;
	passedEventsForSignal[iName] = iEventsForSignal;
	passedEventsForQCD[iName] = iEventsForQCD;

	if(iRank==1){
		pair<float,float> thresholds = ExtractCutThresholds(iName);
		minThresholds[iName] = (thresholds.first);
		maxThresholds[iName] = (thresholds.second);
	}else{
		minThresholds[iName] = 0;
		maxThresholds[iName] = 0;
	}

	UpdateCutNamesMap();
}

void CutFlow::RegisterCutFromLast(string const iName, int const iRank, double const iFactorForSignal, double const iFactorForQCD){
	double lastCountForSignal = GetLastCountForSignal();
	double lastCountForQCD = GetLastCountForQCD();
	RegisterCut(iName, iRank, iFactorForSignal*GetLastCountForSignal(), iFactorForQCD*GetLastCountForQCD());
}

void CutFlow::SetCutCounts(string const iName, double const iEventsForSignal, double const iEventsForQCD){
	if(cutNamesMap.find(iName) == cutNamesMap.end()){ cerr << "ERROR: Trying to set cut counts for \"" << iName << "\" but this cut is not registered in CutFlow." << endl; exit(1); }
	passedEventsForSignal[iName] = iEventsForSignal;
	passedEventsForQCD[iName] = iEventsForQCD;
}

bool CutFlow::CheckComboAndStop(string const iName, float const iValue, pair<bool,bool> iTarget, bool iBypassQCD){
	bool result = false;

	// If the value relevant for this cut is within thresholds, set results for this cut to true
	if( minThresholds.find(iName)->second <= iValue && iValue <= maxThresholds.find(iName)->second ){ result = true; }

	// Bypass result check for specific cases
	if(iTarget.second && (!qcdComboLocked) && iBypassQCD){ result = true; }

	thisCombosResultsForSignal[iName] = (iTarget.first && (!signalComboLocked) && result);
	thisCombosResultsForQCD[iName] = (iTarget.second && (!qcdComboLocked) && result);

	if(iTarget.first && (!result)){ signalComboLocked = true; }
	if(iTarget.second && (!result)){ qcdComboLocked = true; }

	if(signalComboLocked && qcdComboLocked){
		signalComboLocked = false;
		qcdComboLocked = false;

		return true;
	}

	return false;
}

bool CutFlow::CheckComboDiscretely(string const iName, float const iValue){
	return ((minThresholds.find(iName)->second <= iValue) && (iValue <= maxThresholds.find(iName)->second));
}

void CutFlow::ComboIsGood(string const iName){
	thisCombosResultsForSignal[iName] = true;
	thisCombosResultsForQCD[iName] = true;
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
		if(GetCutRank(cutName) != 1){ 
			//ComboIsGood(cutName);
			//continue;
		} // Worry only about rank 1 cuts

		if(thisCombosResultsForSignal.find(cutName)->second){
			passedCombosForSignal[cutName]++; 
			if((heaviestComboForSignal < 0) && (c == cutNames.size()-1)){ heaviestComboForSignal = iComboNumber; }
		}
		if(thisCombosResultsForQCD.find(cutName)->second){
			passedCombosForQCD[cutName]++;
			if((heaviestComboForQCD < 0) && (c == cutNames.size()-1)){ heaviestComboForQCD = iComboNumber; }
		}

		thisCombosResultsForSignal.find(cutName)->second = false;
		thisCombosResultsForQCD.find(cutName)->second = false;

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

	signalComboLocked = false;
	qcdComboLocked = false;

}

// At the end of the event, loop over both combo counters (forSignal and forQCD) and check independently which combos have passed which cuts
void CutFlow::EndOfEvent(){

	// Loop over all the cuts
	for(unsigned int c=0; c<cutNames.size(); c++){
		string cutName = cutNames.at(c);
		if(GetCutRank(cutName) != 1){ continue; } // Worry only about other-than-rank 1 cuts

		// If at least one combo for signal has passed this cut, increase the event count in the "forSignal" cut map FOR THAT CUT only
		if(passedCombosForSignal.find(cutName)->second > 0){ passedEventsForSignal[cutName]++; }	

		// Wait for the last registered cut to determine the outcome of the event
		if(c == cutNames.size()-1){ eventForSignalPassed = (passedCombosForSignal.find(cutName)->second > 0); }

		// If at least one combo for QCD has passed this cut, increase the event count in the "forQCD" cut map FOR THAT CUT only
		if(passedCombosForQCD.find(cutName)->second > 0){ passedEventsForQCD[cutName]++; }	

		// Wait for the last registered cut to determine the outcome of the event
		if(c == cutNames.size()-1){ eventForQCDPassed = (passedCombosForQCD.find(cutName)->second > 0); }

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


vector<string> const		CutFlow::GetCutNames() const { return cutNames; }
map<string, int> const		CutFlow::GetCutRanks() const { return cutRanks; }

int const CutFlow::GetCutRank(string const iCut) const { 
	if(cutRanks.find(iCut) == cutRanks.end()){ cerr << "ERROR: Trying to get rank for cut named \"" << iCut << "\" but this cut is not registered in CutFlow." << endl; exit(1); }
	return (cutRanks.find(iCut)->second);
}

int const CutFlow::GetCutPosition(string const iCut) const { 
	if(cutNamesMap.find(iCut) == cutNamesMap.end()){ return -1; }
	return (cutNamesMap.find(iCut)->second);
}

map<string, float> const	CutFlow::GetMinThresholds() const { return minThresholds; }
map<string, float> const	CutFlow::GetMaxThresholds() const { return maxThresholds; }
map<string, float> const	CutFlow::GetPassedEventsForSignal() const { return passedEventsForSignal; }
map<string, float> const	CutFlow::GetPassedEventsForQCD() const { return passedEventsForQCD; }
string const				CutFlow::GetCutsToApply() const { return cutsToApply; }


float const CutFlow::GetPassedEventsForSignal(string const iCut) const {

	float result = 0;
	if(passedEventsForSignal.find(iCut) != passedEventsForSignal.end()){						result = passedEventsForSignal.find(iCut)->second; }
	else{ result = 0; }
	//else{ cerr << "ERROR: Could not find cut named \"" << iCut << "\" in cuts." << endl; exit(1); }
	return result;
}

float const CutFlow::GetPassedEventsForQCD(string const iCut) const {
	float result = 0;
	if(passedEventsForQCD.find(iCut) != passedEventsForQCD.end()){							result = passedEventsForQCD.find(iCut)->second; }
	else{ result = 0; }
	//else{ cerr << "ERROR: Could not find cut named \"" << iCut << "\" in cuts." << endl; exit(1); }
	return result;
}


float const CutFlow::GetRelEffForSignal(string const iCut) const {
	float result = 0;
	float numerator = 0;
	float denominator = 0;
	//if(passedEventsForSignal.find(iCut) == passedEventsForSignal.end()){ cerr << "ERROR: Cut named \"" << iCut << "\" not found in cutflow map." << endl; exit(1); }
	if(passedEventsForSignal.find(iCut) == passedEventsForSignal.end()){ return 0; }
	int cutPosition = cutNamesMap.find(iCut)->second;
	if(cutPosition==0){ result = 1; }
	else{
		numerator	= GetPassedEventsForSignal(iCut);
		denominator	= GetPassedEventsForSignal(cutNames.at(cutPosition-1));
		result = numerator/denominator;
	}

	if(fabs(denominator) < 1e-10){ result = 0; }
	return result;
}

float const CutFlow::GetCumEffForSignal(string const iCut) const {
	float result = 0;
	float numerator = 0;
	float denominator = 0;
	//if(passedEventsForSignal.find(iCut) == passedEventsForSignal.end()){ cerr << "ERROR: Cut named \"" << iCut << "\" not found in cutflow map." << endl; exit(1); }
	if(passedEventsForSignal.find(iCut) == passedEventsForSignal.end()){ return 0; }
	int cutPosition = cutNamesMap.find(iCut)->second;
	numerator	= GetPassedEventsForSignal(iCut);
	denominator	= GetPassedEventsForSignal(cutNames.front());
	result = numerator/denominator;

	if(fabs(denominator) < 1e-10){ result = 0; }
	return result;
}

float const CutFlow::GetRelEffForQCD(string const iCut) const {
	float result = 0;
	float numerator = 0;
	float denominator = 0;
	//if(passedEventsForQCD.find(iCut) == passedEventsForQCD.end()){ cerr << "ERROR: Cut named \"" << iCut << "\" not found in cutflow map." << endl; exit(1); }
	if(passedEventsForQCD.find(iCut) == passedEventsForQCD.end()){ return 0; }
	int cutPosition = cutNamesMap.find(iCut)->second;
	if(cutPosition==0){ result = 1; }
	else{
		numerator	= GetPassedEventsForQCD(iCut);
		denominator	= GetPassedEventsForQCD(cutNames.at(cutPosition-1));
		result = numerator/denominator;
	}

	if(fabs(denominator) < 1e-10){ result = 0; }
	return result;
}

float const CutFlow::GetCumEffForQCD(string const iCut) const {
	float result = 0;
	float numerator = 0;
	float denominator = 0;
	//if(passedEventsForQCD.find(iCut) == passedEventsForQCD.end()){ cerr << "ERROR: Cut named \"" << iCut << "\" not found in cutflow map." << endl; exit(1); }
	if(passedEventsForQCD.find(iCut) == passedEventsForQCD.end()){ return 0; }
	int cutPosition = cutNamesMap.find(iCut)->second;
	numerator	= GetPassedEventsForQCD(iCut);
	denominator	= GetPassedEventsForQCD(cutNames.front());
	result = numerator/denominator;

	if(fabs(denominator) < 1e-10){ result = 0; }
	return result;
}




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

string const CutFlow::GetLastCut() const{
	string result = "";
	if(cutNames.size() != 0){ result = cutNames.back(); }
	return result;
}

double const CutFlow::GetLastCountForSignal() const { return  GetPassedEventsForSignal(GetLastCut()); }
double const CutFlow::GetLastCountForQCD() const { return  GetPassedEventsForQCD(GetLastCut()); }

void CutFlow::Add(CutFlow const & iCutFlow, float const iFactor){
	// Check the current cuts	
	if(cutNames.size()==0){
		// If there are none, add them from the input CutFlow
		cutNames = iCutFlow.GetCutNames();
		for(unsigned int n = 0; n < cutNames.size(); n++){
			passedEventsForSignal[cutNames.at(n)] = GetPassedEventsForSignal(cutNames.at(n)) * iFactor;
			passedEventsForQCD[cutNames.at(n)] = GetPassedEventsForQCD(cutNames.at(n)) * iFactor;
		}
	}else{
		// Else, first check that we have the same sizes
		if(size() != iCutFlow.size()){ cerr << "ERROR: Current CutFlow has size " << size() << " while input CutFlow has size " << iCutFlow.size() << "." << endl; exit(1); }
		// Then check that all cuts are the same
		for(unsigned int n = 0; n < cutNames.size(); n++){
			if(cutNames.at(n).compare(iCutFlow.GetCutNames().at(n))!=0){
				cerr << "ERROR: Inconsistency in cut names of current and input CutFlows:" << endl; 
				cerr << "\tCurrent\t\tInput" << endl;
				cerr << "\t-------\t\t-----" << endl;
				for(unsigned int c = 0; c < cutNames.size(); c++){
					cerr << "\t" << cutNames.at(c) << "\t" << iCutFlow.GetCutNames().at(c) << endl;
				}
				exit(1);
			}
		}

		// If all the checks passed, perform the addition
		for(unsigned int n = 0; n < cutNames.size(); n++){
			passedEventsForSignal[cutNames.at(n)] += (iCutFlow.GetPassedEventsForSignal(cutNames.at(n))*iFactor);
			passedEventsForQCD[cutNames.at(n)] += (iCutFlow.GetPassedEventsForQCD(cutNames.at(n))*iFactor);
		}
	}
}

void CutFlow::UpdateCutNamesMap(){
	cutNamesMap.clear();
	for(unsigned int n = 0; n < cutNames.size(); n++){ cutNamesMap[cutNames.at(n)] = n; }
}

void CutFlow::PrintTable(){
	for(unsigned int n = 0; n < cutNames.size(); n++){
		cout << "\t" << cutNames.at(n) << "\t\t" << setprecision(10) << GetPassedEventsForSignal(cutNames.at(n)) << "\t\t" << GetPassedEventsForQCD(cutNames.at(n)) << endl;
	}	
}

void CutFlow::BuildNormalizedCutFlow(CutFlow const * iCutFlow){

		Reset();

		cutsToApply = iCutFlow->GetCutsToApply();

		vector<string> iCutNames = iCutFlow->GetCutNames();
		double scaleFactorForSignal = 1.0;
		double scaleFactorForQCD = 1.0;

		for(unsigned int n = 0; n < iCutNames.size(); n++){
			string iCutName = iCutNames.at(n);
			if(iCutFlow->GetCutRank(iCutName) != 2){ continue; }
			scaleFactorForSignal *= iCutFlow->GetRelEffForSignal(iCutName);
			scaleFactorForQCD *= iCutFlow->GetRelEffForQCD(iCutName);
		}

		for(unsigned int n = 0; n < iCutNames.size(); n++){
			string iCutName = iCutNames.at(n);
			if(iCutFlow->GetCutRank(iCutName) == 2){ continue; }

			RegisterCut( iCutName, iCutFlow->GetCutRank(iCutName),
						scaleFactorForSignal*iCutFlow->GetPassedEventsForSignal(iCutName),
						scaleFactorForQCD*iCutFlow->GetPassedEventsForQCD(iCutName));

			UpdateCutNamesMap();
		
		}


}

void CutFlow::ApplyRosls(double const iRosls){

	bool chargeProductApplied = (GetCutPosition("TT_ChargeProduct") >= 0);
	bool osRequested = false;
	if(chargeProductApplied){ osRequested = (GetMaxThresholds().find("TT_ChargeProduct")->second == -1.0); }

	for(unsigned int c=0; c<cutNames.size(); c++){
		string cutName = cutNames.at(c);

		if(!chargeProductApplied){  // Need both OS and LS: Scale by 1+Ros/ls
			SetCutCounts(cutName, (1+iRosls)*GetPassedEventsForSignal(cutName), (1+iRosls)*GetPassedEventsForQCD(cutName));
		}else if(osRequested){ // Need only OS: Scale by 1+Ros/ls before ChargeProduct cut and only by Ros/ls after
			if(GetCutPosition(cutName) < GetCutPosition("TT_ChargeProduct")){ 
				SetCutCounts(cutName, (iRosls)*GetPassedEventsForSignal(cutName), (1+iRosls)*GetPassedEventsForQCD(cutName));
			}else{
				SetCutCounts(cutName, (iRosls)*GetPassedEventsForSignal(cutName), (iRosls)*GetPassedEventsForQCD(cutName));
			}
		}
	}
}


ClassImp(CutFlow)
