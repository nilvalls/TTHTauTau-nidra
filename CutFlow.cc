
#define CutFlow_cxx
#include "CutFlow.h"

using namespace std;

CutFlow::Cut::Cut(const string n, const int r, const float mn, const float mx, const double sig, const double qcd):
    name(n), rank(r), min(mn), max(mx),
    passedSignalEvents(sig), passedQCDEvents(qcd),
    currentSignalResult(false), currentQCDResult(false)
{
}


// Default constructor
CutFlow::CutFlow(){}

CutFlow::CutFlow(string iCuts){
	cutsToApply = iCuts;
}

CutFlow::CutFlow(CutFlow const & iCutFlow){
    cuts = iCutFlow.GetCuts();
    name2idx.clear();
    int idx = 0;
    for (const auto& c: cuts)
        name2idx[c.name] = idx++;

	cutsToApply	= iCutFlow.GetCutsToApply();

	eventForSignalPassed	= false;
	eventForQCDPassed		= false;
	comboIsForSignal		= false;
	comboIsForQCD			= false;

	bestComboForSignal	= -1;
	bestComboForQCD		= -1;
}


// Default destructor
CutFlow::~CutFlow(){}

void CutFlow::Reset(){
	eventForSignalPassed = false;
	eventForQCDPassed    = false;
	comboIsForSignal     = false;
	comboIsForQCD        = false;

	bestComboForSignal = -1;
	bestComboForQCD    = -1;

    cuts.clear();
    name2idx.clear();
}

void CutFlow::Zero() {
    for (auto& c: cuts) {
        c.passedSignalEvents = 0;
        c.passedSignalCombos = 0;
        c.passedQCDEvents = 0;
        c.passedQCDCombos = 0;
    }

    eventForSignalPassed = false;
    eventForQCDPassed    = false;
    comboIsForSignal     = false;
    comboIsForQCD        = false;

    bestComboForSignal = -1;
    bestComboForQCD    = -1;
}

int const CutFlow::size() const { return cuts.size(); }

void CutFlow::InvertSignalAndQCD(){
        // map<string, float>	temp = passedEventsForSignal;
        // passedEventsForSignal	= passedEventsForQCD;
        // passedEventsForQCD		= temp;
        throw "not implemented";
}

void CutFlow::RegisterCut(string const iName, int const iRank,  double const iEventsForSignal, double const iEventsForQCD){
	if( (iRank < 0) || 2 < (iRank)){ cerr << "ERROR: Cut named \"" << iName << "\" is trying to be registered with rank " << iRank << " but rank can only be 0, 1, or 2." << endl; exit(1); }
    float mint = 0;
    float maxt = 0;
	if(iRank==1){
		pair<float,float> thresholds = ExtractCutThresholds(iName);
		mint = (thresholds.first);
		maxt = (thresholds.second);
	}
    Cut new_cut(iName, iRank, mint, maxt, iEventsForSignal, iEventsForQCD);
    cuts.push_back(new_cut);
    name2idx[iName] = cuts.size() - 1;
}

void CutFlow::RegisterCutFromLast(string const iName, int const iRank, double const iFactorForSignal, double const iFactorForQCD){
	RegisterCut(iName, iRank, iFactorForSignal*GetLastCountForSignal(), iFactorForQCD*GetLastCountForQCD());
}

void CutFlow::SetCutCounts(string const iName, double const iEventsForSignal, double const iEventsForQCD){
    cuts[name2idx[iName]].passedSignalEvents = iEventsForSignal;
    cuts[name2idx[iName]].passedQCDEvents = iEventsForQCD;
}

bool CutFlow::CheckComboAndStop(string const iName, float const iValue, pair<bool,bool> iTarget, bool iBypassQCD){
    CutFlow::Cut& cut = cuts[name2idx[iName]];

	bool result = false;

	// If the value relevant for this cut is within thresholds, set results for this cut to true
    if (cut.min <= iValue && iValue <= cut.max)
        result = true;

	// Bypass result check for specific cases
	if(iTarget.second && (!qcdComboLocked) && iBypassQCD){ result = true; }

	cut.currentSignalResult = (iTarget.first && (!signalComboLocked) && result);
	cut.currentQCDResult = (iTarget.second && (!qcdComboLocked) && result);

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
    CutFlow::Cut& cut = cuts[name2idx[iName]];
    return (cut.min <= iValue && iValue <= cut.max);
}

void CutFlow::ComboIsGood(string const iName){
    CutFlow::Cut& cut = cuts[name2idx[iName]];
    cut.currentSignalResult = true;
    cut.currentQCDResult = true;
}

// This function is intended to save time if we have already one good combo for signal and one for QCD. Since the best combos come first, no need to check the rest. This will tell the analyzer it's time to move on.
bool CutFlow::HaveGoodCombos(){
	return ((bestComboForSignal >= 0) && (bestComboForQCD >= 0));
}


void CutFlow::EndOfCombo(pair<bool, bool> iCombosTarget, int const iComboNumber){

	// At the end of the cutflow for this very combo, determine its target, and fill the signal/QCD combo counters accordingly
    // bool comboIsForSignal	= iCombosTarget.first;
    // bool comboIsForQCD		= iCombosTarget.second;

	// Provided that the each target has not yet been satisfied by any combo, assume the first combo to do so is good
	// Then assume that the first combo that satisfies the target is the best. If there are registered cuts, they will change this if needed
	//cout << "end of combo: target: " << comboIsForSignal << " " << comboIsForQCD << " best combo: " << bestComboForSignal << " " << bestComboForQCD << endl;
/*	if(comboIsForSignal	&& (bestComboForSignal < 0)){ eventForSignalPassed	= true;	bestComboForSignal  = iComboNumber; }
	if(comboIsForQCD	&& (bestComboForQCD < 0)){	  eventForQCDPassed		= true;	bestComboForQCD  	= iComboNumber; }//*/

	// Loop over all the cuts this combo has gone through
	//cout << "cuts ======" << endl;
    for (auto& c: cuts) {
		//cout << cutNames.at(c) << " " << thisCombosResultsForSignal.find(cutName)->second << " " << thisCombosResultsForQCD.find(cutName)->second << endl;
		if (c.currentSignalResult) {
            c.passedSignalCombos++;

            if (c.name == cuts.back().name) {
                if (bestComboForSignal < 0)
                    bestComboForSignal = iComboNumber;
                eventForSignalPassed = true; // TODO can this ever be reached? Changed from before!
            }
		}
		if (c.currentQCDResult) {
			c.passedQCDCombos++;

            if (c.name == cuts.back().name) {
                if (bestComboForQCD < 0)
                    bestComboForQCD = iComboNumber;
                eventForQCDPassed = true; // TODO can this ever be reached? Changed from before!
            }
		}

        c.currentSignalResult = false;
        c.currentQCDResult = false;
	}
}

// Reset counters relevant to the start of the event
void CutFlow::StartOfEvent(){

	bestComboForSignal	= -1;
	bestComboForQCD		= -1;

	eventForSignalPassed	= false;	
	eventForQCDPassed		= false;	

    for (auto& c: cuts) {
        c.passedSignalCombos = 0;
        c.passedQCDCombos = 0;
    }

	signalComboLocked = false;
	qcdComboLocked = false;
}

// At the end of the event, loop over both combo counters (forSignal and forQCD) and check independently which combos have passed which cuts
void CutFlow::EndOfEvent(){
    // Loop over all the cuts
    for (auto& c: cuts) {
        if (c.rank != 1)
            continue; // Worry only about other-than-rank 1 cuts

        // If at least one combo for signal has passed this cut, increase the event count in the "forSignal" cut map FOR THAT CUT only
        if (c.passedSignalCombos > 0)
            c.passedSignalEvents++;

        // Wait for the last registered cut to determine the outcome of the event
        if (c.name == cuts.back().name)
            eventForSignalPassed = (c.passedSignalCombos > 0);

        // If at least one combo for QCD has passed this cut, increase the event count in the "forQCD" cut map FOR THAT CUT only
        if (c.passedQCDCombos > 0)
            c.passedQCDEvents++;

        // Wait for the last registered cut to determine the outcome of the event
        if (c.name == cuts.back().name)
            eventForQCDPassed = (c.passedQCDCombos > 0);

        // Reset combo counter
        c.passedSignalCombos = 0;
        c.passedQCDCombos = 0;
    }
}

bool CutFlow::EventForSignalPassed(){ 
	if(eventForSignalPassed && (bestComboForSignal==-1)){ cerr << "ERROR: about to return true EventForSignalPassed() but bestCombo is -1" << endl; exit(1); }
	return eventForSignalPassed;
}

bool CutFlow::EventForQCDPassed(){
	if(eventForQCDPassed && (bestComboForQCD==-1)){ cerr << "ERROR: about to return true EventForQCDPassed() but bestCombo is -1" << endl; exit(1); }
	return eventForQCDPassed;
}

int CutFlow::GetBestComboForSignal(){
	if(!eventForSignalPassed){ cerr << "ERROR: trying to obtain highest combo in event for signal, but no event for signal has passed all the cuts" << endl; exit(1); }
	return bestComboForSignal;
}

int CutFlow::GetBestComboForQCD(){
	if(!eventForQCDPassed){ cerr << "ERROR: trying to obtain highest combo in event for QCD, but no event for QCD has passed all the cuts" << endl; exit(1); }
	return bestComboForQCD;
}

int const CutFlow::GetCutRank(string const iCut) const { 
    return cuts[name2idx.find(iCut)->second].rank;
}

int const CutFlow::GetCutPosition(string const iCut) const { 
    return name2idx.find(iCut)->second;
}

string const				CutFlow::GetCutsToApply() const { return cutsToApply; }


float const CutFlow::GetPassedEventsForSignal(string const iCut) const {
    return cuts[name2idx.find(iCut)->second].passedSignalEvents;
}

float const CutFlow::GetPassedEventsForQCD(string const iCut) const {
    return cuts[name2idx.find(iCut)->second].passedQCDEvents;
}

float const CutFlow::GetRelEffForSignal(string const iCut) const {
    const int idx = name2idx.find(iCut)->second;
    if (idx < 0)
        return 0.;
    else if (not cuts[idx - 1].passedSignalEvents)
        return 1e10;
    return cuts[idx].passedSignalEvents / cuts[idx - 1].passedSignalEvents;
}

float const CutFlow::GetCumEffForSignal(string const iCut) const {
    const int idx = name2idx.find(iCut)->second;
    return cuts[idx].passedSignalEvents / cuts.front().passedSignalEvents;
}

float const CutFlow::GetRelEffForQCD(string const iCut) const {
    const int idx = name2idx.find(iCut)->second;
    return cuts[idx].passedQCDEvents / cuts[idx - 1].passedQCDEvents;
}

float const CutFlow::GetCumEffForQCD(string const iCut) const {
    const int idx = name2idx.find(iCut)->second;
    return cuts[idx].passedQCDEvents / cuts.front().passedQCDEvents;
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
    return cuts.back().name;
}

double const CutFlow::GetLastCountForSignal() const { return  GetPassedEventsForSignal(GetLastCut()); }
double const CutFlow::GetLastCountForQCD() const { return  GetPassedEventsForQCD(GetLastCut()); }

void CutFlow::Add(CutFlow const & iCutFlow, float const iFactor){
    // Check the current cuts	
    if (cuts.size() == 0) {
        // If there are none, add them from the input CutFlow
        cuts = iCutFlow.GetCuts();
        for (auto& c: cuts) {
            c.passedSignalEvents *= iFactor;
            c.passedQCDEvents *= iFactor;
        }
    } else {
        // Else, first check that we have the same sizes
        if (size() != iCutFlow.size()) {
            cerr << "ERROR: Current CutFlow has size " << size() << " while input CutFlow has size " << iCutFlow.size() << "." << endl;
            exit(1);
        }
        // Then check that all cuts are the same
        vector<CutFlow::Cut> other_cuts = iCutFlow.GetCuts();
        for (unsigned int i = 0; i < cuts.size(); ++i) {
            if (cuts[i].name != other_cuts[i].name) {
                cerr << "ERROR: Inconsistency in cut names of current and input CutFlows:" << endl; 
                cerr << "\tCurrent\t\tInput" << endl;
                cerr << "\t-------\t\t-----" << endl;
                for (unsigned int j = 0; j < cuts.size(); ++j) {
                    cerr << "\t" << cuts[j].name << "\t" << other_cuts[j].name << endl;
                }
                exit(1);
            } else {
                cuts[i].passedSignalEvents += other_cuts[i].passedSignalEvents * iFactor;
                cuts[i].passedQCDEvents += other_cuts[i].passedQCDEvents * iFactor;
            }
        }
    }
}

void CutFlow::BuildNormalizedCutFlow(CutFlow const * iCutFlow){
    Reset();

    cutsToApply = iCutFlow->GetCutsToApply();

    vector<Cut> other_cuts = iCutFlow->GetCuts();
    double scaleFactorForSignal = 1.0;
    double scaleFactorForQCD = 1.0;

    for (auto& c: other_cuts) {
        if (c.rank != 2)
            continue;
        scaleFactorForSignal *= iCutFlow->GetRelEffForSignal(c.name);
        scaleFactorForQCD *= iCutFlow->GetRelEffForQCD(c.name);
    }

    for (auto& c: other_cuts) {
        if (c.rank == 2)
            continue;
        RegisterCut(c.name, c.rank,
                scaleFactorForSignal * c.passedSignalEvents,
                scaleFactorForQCD * c.passedQCDEvents);
    }
}

void CutFlow::ApplyRosls(double const iRosls){
    bool chargeProductApplied = name2idx.find("TT_ChargeProduct") != name2idx.end();
    bool osRequested = false;
    if (chargeProductApplied)
        osRequested = (cuts[name2idx["TT_ChargeProduct"]].max == -1.0);

    for (auto& c: cuts) {
        string cutName = c.name;
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
ClassImp(CutFlow::Cut)
