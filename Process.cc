
#define Process_cxx

#include "Helper.h"

#include "Process.h"

using namespace std;



// Default constructor
Process::Process(){
	analyzed			= false;
	goodEventsForSignal.clear();
	plot				= false;
}

Process::Process(Process const & iProcess){

	params							= iProcess.GetParams();
	goodEventsForSignal				= iProcess.GetGoodEventsForSignal();

	hContainerForSignal				= HContainer(*iProcess.GetHContainerForSignal());
	cutFlow							= CutFlow(*iProcess.GetCutFlow());
	normalizedCutFlow				= CutFlow(*iProcess.GetNormalizedCutFlow());

	shortName						= iProcess.GetShortName();
	niceName						= iProcess.GetNiceName();
	labelForLegend					= iProcess.GetLabelForLegend();
	type							= iProcess.GetType();
	checkReality					= iProcess.CheckReality();
	ntuplePaths						= iProcess.GetNtuplePaths();
	color							= iProcess.GetColor();

	crossSection					= iProcess.GetCrossSection();
	branchingRatio					= iProcess.GetBranchingRatio();
	otherScaleFactor				= iProcess.GetOtherScaleFactor();
    relSysUncertainty               = iProcess.GetRelSysUncertainty();

	analyzed						= iProcess.Analyzed();
	NOEinDS							= iProcess.GetNOEinDS();
	NoEreadByNUTter					= iProcess.GetNoEreadByNUTter();
	NOEinNtuple						= iProcess.GetNOEinNtuple();
	NOEanalyzed						= iProcess.GetNOEanalyzed();
	NOEexpectedForSignal			= iProcess.GetNOEexpectedForSignal();
	plot							= iProcess.Plot();

	obtainedGoodEventsForSignal		= iProcess.ObtainedGoodEventsForSignal();
	filledHistosForSignal			= iProcess.FilledHistosForSignal();
	normalizedHistosForSignal		= iProcess.NormalizedHistosForSignal();

}

Process::Process(string const iShortName, map<string,string> const & iParams, Config const & iConfig){

	params						= map<string,string>(iParams);
	goodEventsForSignal.clear();

	// Id
	shortName					= iShortName;
	niceName					= iConfig.pString("niceName");
	labelForLegend				= iConfig.pString("labelForLegend");
	type						= iConfig.pString("type");
	checkReality				= iConfig.pBool("checkReality");

	if((params.find("format")->second).compare("jeff")==0){
		string wildcard		= "*process*";
		string jeffspath	= (params.find("ntuplesDir")->second);
		string jeffspath1	= jeffspath.substr(0, jeffspath.find(wildcard));
		string jeffspath2	= jeffspath.substr(jeffspath.find(wildcard) + wildcard.length());
		string process		= iConfig.pString("ntuplePath");
		if(process.substr(process.length()-1).compare("/")==0){ process = process.substr(0,process.length()-1); }
		//ntuplePath					= jeffspath1 + process + jeffspath2+"/res/";
      for (const auto& p: Helper::SplitString(process)) {
         ntuplePaths.push_back(jeffspath1 + p + jeffspath2);
      }
	}else{
		string process		= iConfig.pString("ntuplePath");
      for (const auto& p: Helper::SplitString(process)) {
         ntuplePaths.push_back((params.find("ntuplesDir")->second) + p + "res");
      }
	}

	color						= iConfig.pInt("color");

	// Physics
	crossSection				= iConfig.pDouble("crossSection");
	branchingRatio				= iConfig.pDouble("branchingRatio");
	otherScaleFactor			= iConfig.pDouble("otherScaleFactor");
    
    relSysUncertainty           = iConfig.pDouble("relativeSysUncertainty");

	// Logistics
	analyzed					= false;
	NOEinDS						= iConfig.pInt("NOEinDS");
	NoEreadByNUTter				= iConfig.pInt("NoEreadByNUTter");
	NOEinNtuple					= 0;
	NOEanalyzed					= 0;
	NOEexpectedForSignal		= 0;
	plot						= PlotProcess(shortName);

	obtainedGoodEventsForSignal	= false;
	filledHistosForSignal		= false;
	normalizedHistosForSignal	= false;
}


// Default destructor
Process::~Process(){}

// Update process
void Process::Update(Process const * iProcess){
	params							= iProcess->GetParams();

	niceName						= iProcess->GetNiceName();
	labelForLegend					= iProcess->GetLabelForLegend();
	type							= iProcess->GetType();
	checkReality					= iProcess->CheckReality();
	color							= iProcess->GetColor();

	crossSection					= iProcess->GetCrossSection();
	branchingRatio					= iProcess->GetBranchingRatio();
	otherScaleFactor				= iProcess->GetOtherScaleFactor();
    relSysUncertainty               = iProcess->GetRelSysUncertainty();

	plot							= iProcess->Plot();
	SetPlot(params);

	normalizedHistosForSignal		= false;

	// Update cutflow
	cutFlow.SetCutCounts("Read from DS", iProcess->GetNOEinDS());
	cutFlow.SetCutCounts("skimming + PAT", iProcess->GetNoEreadByNUTter());
	
}


map<string, string> const Process::GetParams() const { return params; }
void Process::SetHContainerForSignal(HContainer const & iHContainer){ hContainerForSignal = HContainer(iHContainer); }
vector<Process::Event> const Process::GetGoodEventsForSignal() const { return goodEventsForSignal; }
void Process::SetCutFlow(CutFlow const & iCutFlow){ cutFlow	= CutFlow(iCutFlow); }
void Process::SetNormalizedCutFlow(CutFlow const & iCutFlow){ normalizedCutFlow	= CutFlow(iCutFlow); }
void Process::SetNOEanalyzed(double const iEvents){ NOEanalyzed = iEvents; }
void Process::SetNOEinNtuple(double const iEvents){ NOEinNtuple = iEvents; }
void Process::SetRelSysUncertainty(double const iError){ relSysUncertainty = iError; }
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
void Process::SetNtuplePaths(vector<string> const iPath){ ntuplePaths = iPath; }

void Process::SetPlot(map<string,string> const & iParams){
	bool result;
	if(iParams.find("plot")->second.compare("All")==0){
		result = true;
	}else{
		string enabledProcesses = " " + iParams.find("plot")->second + " ";
		string thisProcess			 = " " + shortName + " ";
		result = IsStringThere(thisProcess,enabledProcesses);
	}
	plot = result;
}

bool const Process::IsCollisions() const { return ((type.compare("collisions")==0)); }
bool const Process::IsMCbackground() const { return ((type.compare("mcBackground")==0)); }
bool const Process::IsSignal() const { return ((type.compare("signal")==0)); }
bool const Process::CheckReality() const { return checkReality; }
vector<string> const Process::GetNtuplePaths() const { return ntuplePaths; }
int const Process::GetColor() const { return color; }
int const Process::GetNOEinDS() const {			return NOEinDS;		}
int const Process::GetNoEreadByNUTter() const {	return NoEreadByNUTter;}
int const Process::GetNOEinNtuple() const {		return NOEinNtuple; }
int const Process::GetNOEanalyzed() const {		return NOEanalyzed; }

double const Process::GetCrossSection() const{ return crossSection;}
double const Process::GetBranchingRatio() const{ return branchingRatio;}
double const Process::GetOtherScaleFactor() const{ return otherScaleFactor;}
double const Process::GetNOEexpectedForSignal() const{ return NOEexpectedForSignal;}
double const Process::GetRelSysUncertainty() const{ return relSysUncertainty;}
bool const Process::ObtainedGoodEventsForSignal() const{ return obtainedGoodEventsForSignal;}
bool const Process::FilledHistosForSignal() const{ return filledHistosForSignal;}
bool const Process::NormalizedHistosForSignal() const{ return normalizedHistosForSignal;}


void Process::SetShortName(string const iVal){ 
	shortName = iVal;
}
void Process::SetNiceName(string const iVal){ niceName = iVal; }
void Process::SetLabelForLegend(string const iVal){ labelForLegend = iVal; }
void Process::SetAnalyzed(){ analyzed = true; }
bool const Process::Analyzed() const { return analyzed; }
HContainer* Process::GetHContainerForSignal(){ 
return &hContainerForSignal; }
HContainer const * Process::GetHContainerForSignal() const { return &hContainerForSignal; }

HWrapper const * Process::GetHistoForSignal(string const iName) const { return (hContainerForSignal.Get(iName)); }

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
void Process::SetGoodEventsForSignal(const vector<Process::Event>& iVector){ goodEventsForSignal = iVector; }


void
Process::NormalizeToLumi(double const iIntLumi)
{
	if ((!IsCollisions()) && (!normalizedHistosForSignal)) {
		double NOElumi				= iIntLumi*crossSection*branchingRatio;
		double NOEraw				= GetNOEinDS()*(GetNOEanalyzed()/(double)GetNOEinNtuple());	
		double lumiNormalization	= NOElumi/NOEraw;
		lumiNormalization 			*= GetOtherScaleFactor();
		cout << setprecision(7) << "\n" << shortName << " normalization: \n" 
			<< "\t---------------------------------------\n"
			<< "\tintLumi...." << iIntLumi << "\n" 
			<< "\tcrossSec..." << crossSection << "\n" 
			<< "\tBR............" << branchingRatio << "\n" 
			<< "\tNOEinDS......." << GetNOEinDS() << "\n" 
			<< "\tNOEanalyzed..." << GetNOEanalyzed() << "\n" 
			<< "\tNOEinNtuple..." << GetNOEinNtuple() << "\n" 
			<< "\t---------------------------------------\n"
			<< "\tNOElumi......." << NOElumi << "\n" 
			<< "\tNOEraw........" << NOEraw << "\n" 
			<< "\tOtherSF......." << GetOtherScaleFactor() << "\n" 
			<< "\t---------------------------------------\n"
			<< "\tSF............" << lumiNormalization << "\n" 
			<< "\trelSysSuncertainty....." << relSysUncertainty*100 << "%" << "\n" << endl; //*/

		ScaleBy(lumiNormalization);
		GetCutFlow()->RegisterCutFromLast("Lumi norm", 2, lumiNormalization);

        hContainerForSignal.AddRelErrorInQuadrature(relSysUncertainty);
	}
	normalizedHistosForSignal	= true;
}

void Process::NormalizeToOne(){
	NormalizeTo(1);
	normalizedHistosForSignal	= true;
}

void Process::NormalizeTo(double const iNormalization){
	hContainerForSignal.NormalizeTo(iNormalization);
}

void Process::ScaleBy(double const iScale){
	hContainerForSignal.ScaleBy(iScale);
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

void Process::Add(Process* iProcess){
    for (const auto& p: iProcess->GetNtuplePaths())
        ntuplePaths.push_back(p);
	iProcess->GetHContainerForSignal();
	hContainerForSignal.Add(*(iProcess->GetHContainerForSignal()));
	cutFlow.Add(*(iProcess->GetCutFlow()));
	normalizedCutFlow.Add(*(iProcess->GetNormalizedCutFlow()));
}

ClassImp(Process)
ClassImp(Process::Event)
