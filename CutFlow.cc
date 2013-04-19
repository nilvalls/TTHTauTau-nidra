#include <limits>

#include "boost/lexical_cast.hpp"

#include "Helper.h"
#include "CutFlow.h"

using namespace std;

CutFlow::Cut::Cut(const string n, CutFlow::Cut::val_f f, const int r, const float mn, const float mx, const double sig, const double qcd, bool bypass):
    name(n), GetVal(f), rank(r), min(mn), max(mx),
    passedSignalEvents(sig), passedQCDEvents(qcd),
    currentSignalResult(false), currentQCDResult(false),
    skip(bypass)
{
}

bool
CutFlow::Cut::Check(TTLBranches *b, const int idx, const bool bypass)
{
    float val = GetVal(b, idx);
    // if (rank == 1)
        // if (skip && bypass)
            // cout << "Skipping" << endl;
        // cout << name << "\t" << min << "\t" << val << "\t" << max << "\t";
    if ((rank != 1) || (skip && bypass) || (min <= val && val <= max)) {
        if (!currentSignalResult) {
            ++passedSignalEvents;
            currentSignalResult = true;
        }
        // if (rank == 1)
            // cout << "passed\n";
        return true;
    } else {
        // if (rank == 1)
            // cout << "failed\n";
        return false;
    }
}

// Default constructor
CutFlow::CutFlow(){}

CutFlow::CutFlow(string cuts)
{
    using boost::lexical_cast;

    cutsToApply = cuts;

    for (const auto& s: Helper::SplitString(cuts)) {
        auto first_colon = s.find(":");
        auto last_colon = s.rfind(":");

        string name = s.substr(0, first_colon);

        float max = numeric_limits<float>::infinity();
        float min = -numeric_limits<float>::infinity();
        try {
            max = lexical_cast<float>(s.substr(last_colon + 1));
        } catch (...) {}
        try {
            min = lexical_cast<float>(s.substr(first_colon + 1, last_colon - first_colon - 1));
        } catch (...) {}

        cuts_to_consider[name] = make_pair(min, max);
    }
}

CutFlow::CutFlow(CutFlow const & iCutFlow){
    std::cout << "COPY" << std::endl;
    cuts = iCutFlow.GetCuts();
    name2idx.clear();
    int idx = 0;
    for (const auto& c: cuts)
        name2idx[c.name] = idx++;

	cutsToApply	= iCutFlow.GetCutsToApply();
    cuts_to_consider = iCutFlow.GetCutsToConsider();

	eventForSignalPassed	= false;
	eventForQCDPassed		= false;
	comboIsForSignal		= false;
	comboIsForQCD			= false;

	bestComboForSignal	= -1;
	bestComboForQCD		= -1;
    std::cout << "COPY Done" << std::endl;
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

void CutFlow::RegisterCut(string const name, int const rank,  double const iEventsForSignal, double const iEventsForQCD){
    if (!(rank == 0 || 2 == rank)) {
        cerr << "ERROR: Cut named \"" << name << "\" is trying to be registered with rank " << rank << " but rank can only be 0 or 2." << endl;
        exit(1);
    }
    Cut new_cut(name, [](TTLBranches* b, const int idx) -> float { return 0.; },
            rank, 0, 0, iEventsForSignal, iEventsForQCD);
    cuts.push_back(new_cut);
    name2idx[name] = cuts.size() - 1;
}

void
CutFlow::RegisterCut(const string name, const int rank, CutFlow::Cut::val_f f, bool bypass, const double sig, const double qcd)
{
    auto res = cuts_to_consider.find(name);

    Cut new_cut(name, f, rank, res->second.first, res->second.second, sig, qcd, bypass);
    cuts.push_back(new_cut);
    name2idx[name] = cuts.size() - 1;
}

void CutFlow::RegisterCutFromLast(string const iName, int const iRank, double const iFactorForSignal, double const iFactorForQCD){
	RegisterCut(iName, iRank, iFactorForSignal*GetLastCountForSignal(), iFactorForQCD*GetLastCountForQCD());
}

void CutFlow::SetCutCounts(string const iName, double const iEventsForSignal, double const iEventsForQCD){
    cuts[name2idx[iName]].passedSignalEvents = iEventsForSignal;
    cuts[name2idx[iName]].passedQCDEvents = iEventsForQCD;
}

bool
CutFlow::CheckCuts(TTLBranches* b, const int idx, const bool bypass)
{
    for (auto& c: cuts)
        if (c.rank > 0 && !c.Check(b, idx, bypass))
            return false;
    return true;
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
        c.currentSignalResult = false;
        c.currentQCDResult = false;
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
    cuts_to_consider = iCutFlow->cuts_to_consider;

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
        RegisterCut(c.name, c.rank, c.GetVal, c.skip,
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
