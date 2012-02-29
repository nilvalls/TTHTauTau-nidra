
#define Process_cxx
#include "Process.h"

using namespace std;



// Default constructor
Process::Process(){
	analyzed			= false;
	goodEventsForSignal.clear();
	goodEventsForQCD.clear();
	plot				= false;
}

Process::Process(Process const & iProcess){

	params							= iProcess.GetParams();
	goodEventsForSignal				= vector<pair<int, int> >(iProcess.GetGoodEventsForSignal());
	goodEventsForQCD				= vector<pair<int, int> >(iProcess.GetGoodEventsForQCD());

	hContainerForSignal				= HContainer(*iProcess.GetHContainerForSignal());
	hContainerForQCD				= HContainer(*iProcess.GetHContainerForQCD());
	cutFlow							= CutFlow(*iProcess.GetCutFlow());
	normalizedCutFlow				= CutFlow(*iProcess.GetNormalizedCutFlow());

	shortName						= iProcess.GetShortName();
	niceName						= iProcess.GetNiceName();
	labelForLegend					= iProcess.GetLabelForLegend();
	type							= iProcess.GetType();
	ntuplePath						= iProcess.GetNtuplePath();
	color							= iProcess.GetColor();

	crossSection					= iProcess.GetCrossSection();
	branchingRatio					= iProcess.GetBranchingRatio();
	otherScaleFactor				= iProcess.GetOtherScaleFactor();

	analyzed						= iProcess.Analyzed();
	NOEinDS							= iProcess.GetNOEinDS();
	NOEinPATuple					= iProcess.GetNOEinPATuple();
	NOEinNtuple						= iProcess.GetNOEinNtuple();
	NOEanalyzed						= iProcess.GetNOEanalyzed();
	NOEexpectedForSignal			= iProcess.GetNOEexpectedForSignal();
	NOEexpectedForQCD				= iProcess.GetNOEexpectedForQCD();
	plot							= iProcess.Plot();

	obtainedGoodEventsForSignal		= iProcess.ObtainedGoodEventsForSignal();
	obtainedGoodEventsForQCD		= iProcess.ObtainedGoodEventsForQCD();
	filledHistosForSignal			= iProcess.FilledHistosForSignal();
	filledHistosForQCD				= iProcess.FilledHistosForQCD();
	normalizedHistosForSignal		= iProcess.NormalizedHistosForSignal();
	normalizedHistosForQCD			= iProcess.NormalizedHistosForQCD();

}

Process::Process(string const iShortName, map<string,string> const & iParams, Config const & iConfig){

	params						= map<string,string>(iParams);
	goodEventsForSignal.clear();
	goodEventsForQCD.clear();

	// Id
	shortName					= iShortName;
	niceName					= iConfig.pString("niceName");
	labelForLegend				= iConfig.pString("labelForLegend");
	type						= iConfig.pString("type");
	ntuplePath					= iConfig.pString("ntuplePath");
	color						= iConfig.pInt("color");

	// Physics
	crossSection				= iConfig.pDouble("crossSection");
	branchingRatio				= iConfig.pDouble("branchingRatio");
	otherScaleFactor			= iConfig.pDouble("otherScaleFactor");

	// Logistics
	analyzed					= false;
	NOEinDS						= iConfig.pInt("NOEinDS");
	NOEinPATuple				= iConfig.pInt("NOEinPATuple");
	NOEinNtuple					= 0;
	NOEanalyzed					= 0;
	NOEexpectedForSignal		= 0;
	NOEexpectedForQCD			= 0;
	plot						= PlotProcess(shortName);

	obtainedGoodEventsForSignal	= false;
	obtainedGoodEventsForQCD	= false;
	filledHistosForSignal		= false;
	filledHistosForQCD			= false;
	normalizedHistosForSignal	= false;
	normalizedHistosForQCD		= false;


}


// Default destructor
Process::~Process(){}


map<string, string> const Process::GetParams() const { return params; }
void Process::SetHContainerForSignal(HContainer const & iHContainer){ hContainerForSignal = HContainer(iHContainer); }
void Process::SetHContainerForQCD(HContainer const & iHContainer){ hContainerForQCD = HContainer(iHContainer); }
vector<pair<int, int> > const Process::GetGoodEventsForSignal() const { return goodEventsForSignal; }
vector<pair<int, int> > const Process::GetGoodEventsForQCD() const {	return goodEventsForQCD; }
void Process::SetCutFlow(CutFlow const & iCutFlow){ cutFlow	= CutFlow(iCutFlow); }
void Process::SetNormalizedCutFlow(CutFlow const & iCutFlow){ normalizedCutFlow	= CutFlow(iCutFlow); }
void Process::SetNOEanalyzed(double const iEvents){ NOEanalyzed = iEvents; }
void Process::SetNOEinNtuple(double const iEvents){ NOEinNtuple = iEvents; }
void Process::SetColor(int const iColor){ color = iColor; }
CutFlow* Process::GetCutFlow() { return &cutFlow; }
CutFlow const * Process::GetCutFlow() const { return &cutFlow; }
CutFlow* Process::GetNormalizedCutFlow() { return &normalizedCutFlow; }
CutFlow const * Process::GetNormalizedCutFlow() const { return &normalizedCutFlow; }
string const Process::GetShortName() const {	return shortName;		}
string const Process::GetNiceName() const {			return niceName;		}
string const Process::GetLabelForLegend() const {	return labelForLegend;	}
string const Process::GetType() const {				return type;			}
bool const Process::IsMC() const { return ((type.compare("mcBackground")==0) || (type.compare("signal")==0)); }
bool const Process::Plot() const { return plot; }

void Process::SetPlot(map<string,string> const & iParams){
	bool result;
	if(iParams.find("plot")->second.compare("All")==0){
		result = true;
	}else{
		string enabledProcesses = " " + iParams.find("plot")->second + " ";
		cout << enabledProcesses << endl;
		string thisProcess			 = " " + shortName + " ";
		result = IsStringThere(thisProcess,enabledProcesses);
	}
	plot = result;
	cout << "Plot? " << plot << endl;
}

bool const Process::IsCollisions() const { return ((type.compare("collisions")==0)); }
bool const Process::IsQCD() const { return ((type.compare("qcd")==0)); }
bool const Process::IsMCbackground() const { return ((type.compare("mcBackground")==0)); }
bool const Process::IsSignal() const { return ((type.compare("signal")==0)); }
string const Process::GetNtuplePath() const { return ntuplePath; }
int const Process::GetColor() const { return color; }
int const Process::GetNOEinDS() const {			return NOEinDS;		}
int const Process::GetNOEinPATuple() const {	return NOEinPATuple;}
int const Process::GetNOEinNtuple() const {		return NOEinNtuple; }
int const Process::GetNOEanalyzed() const {		return NOEanalyzed; }

double const Process::GetCrossSection() const{ return crossSection;}
double const Process::GetBranchingRatio() const{ return branchingRatio;}
double const Process::GetOtherScaleFactor() const{ return otherScaleFactor;}
double const Process::GetNOEexpectedForSignal() const{ return NOEexpectedForSignal;}
double const Process::GetNOEexpectedForQCD() const{ return NOEexpectedForQCD;}
bool const Process::ObtainedGoodEventsForSignal() const{ return obtainedGoodEventsForSignal;}
bool const Process::ObtainedGoodEventsForQCD() const{ return obtainedGoodEventsForQCD;}
bool const Process::FilledHistosForSignal() const{ return filledHistosForSignal;}
bool const Process::FilledHistosForQCD() const{ return filledHistosForQCD;}
bool const Process::NormalizedHistosForSignal() const{ return normalizedHistosForSignal;}
bool const Process::NormalizedHistosForQCD() const{ return normalizedHistosForQCD;}


void Process::SetShortName(string const iVal){ shortName = iVal; }
void Process::SetNiceName(string const iVal){ niceName = iVal; }
void Process::SetLabelForLegend(string const iVal){ labelForLegend = iVal; }
void Process::SetAnalyzed(){ analyzed = true; }
bool const Process::Analyzed() const { return analyzed; }
HContainer* Process::GetHContainerForSignal(){ return &hContainerForSignal; }
HContainer* Process::GetHContainerForQCD(){ return &hContainerForQCD; }
HContainer const * Process::GetHContainerForSignal() const { return &hContainerForSignal; }
HContainer const * Process::GetHContainerForQCD() const { return &hContainerForQCD; }

HWrapper const * Process::GetHistoForSignal(string const iName) const { return (hContainerForSignal.Get(iName)); }
HWrapper const * Process::GetHistoForQCD(string const iName) const { return (hContainerForQCD.Get(iName)); }

bool const Process::IsStringThere(string iNeedle, string iHaystack) const {
	string haystack = iHaystack;
	string needle = iNeedle;
	bool const result = ((haystack.find(needle) < haystack.length()));
	return result;
}


int const Process::GetNumberOfPlots() const {
	return hContainerForSignal.size();
}

HWrapper const * Process::GetAvailableHWrapper() const {
	if(hContainerForSignal.size()==0){ cerr << "ERROR: trying to obtain a sample HWrapper from process but there are none" << endl; }
	return &((hContainerForSignal.begin()))->second;
}

HWrapper const * Process::GetAvailableHWrapper(string const iName) const {
	if(hContainerForSignal.size()==0){ cerr << "ERROR: trying to obtain a sample HWrapper from process but there are none" << endl; }
	return ((hContainerForSignal.Get(iName)));
}

// Massive set histogram properties
void Process::SetMarkerStyle(int const iVal){ hContainerForSignal.SetMarkerStyle(iVal); }
void Process::SetFillStyle(int const iVal){ hContainerForSignal.SetFillStyle(iVal); }
void Process::SetFillColor(int const iVal){ hContainerForSignal.SetFillColor(iVal); }
void Process::SetLineColor(int const iVal){ hContainerForSignal.SetLineColor(iVal); }
void Process::SetLineWidth(int const iVal){ hContainerForSignal.SetLineWidth(iVal,color); }
void Process::SetGoodEventsForSignal(vector<pair<int,int> > const iVector){ goodEventsForSignal = iVector; }
void Process::SetGoodEventsForQCD(vector<pair<int,int> > const iVector){ goodEventsForQCD = iVector; }


void Process::NormalizeToLumi(double const iIntLumi){
	if((!IsCollisions()) && (!normalizedHistosForSignal) && (!normalizedHistosForQCD)){
		double NOElumiEvents		= iIntLumi*crossSection*branchingRatio;
		double NOErawEvents			= GetNOEinDS()*(GetNOEanalyzed()/(double)GetNOEinNtuple());	
		double lumiNormalization	= NOElumiEvents/NOErawEvents;
		ScaleBy(lumiNormalization);
		GetCutFlow()->RegisterCutFromLast("Lumi norm", 2, lumiNormalization, lumiNormalization);
	}
	normalizedHistosForSignal	= true;
	normalizedHistosForQCD		= true;
}

void Process::NormalizeToOne(){
	NormalizeTo(1);
	normalizedHistosForSignal	= true;
	normalizedHistosForQCD		= true;
}

void Process::NormalizeTo(double const iNormalization){
	hContainerForSignal.NormalizeTo(iNormalization);
	hContainerForQCD.NormalizeTo(iNormalization);
}

void Process::ScaleBy(double const iScale){
	hContainerForSignal.ScaleBy(iScale);
	hContainerForQCD.ScaleBy(iScale);
}

void Process::BuildNormalizedCutFlow(){ normalizedCutFlow.BuildNormalizedCutFlow(&cutFlow); }

bool Process::PlotProcess(string const iThisProcess){
	bool result;
	if(params["plot"].compare("All")==0){
		result = true;
	}else{
		string enabledProcesses = " " + params["plot"] + " ";
		string thisProcess			 = " " + iThisProcess + " ";
		result = IsStringThere(thisProcess,enabledProcesses);
	}
	return result;
}

ClassImp(Process)
