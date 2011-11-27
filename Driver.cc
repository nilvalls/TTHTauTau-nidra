
#include "Driver.h"

#define Driver_cxx
using namespace std;

// Perform some initialization tasks
void Initialize(int argc, char **argv){

	inputArguments = "";
	for(unsigned a = 0; a < argc; a++){ inputArguments += (string(argv[a]) + " "); }

	// Clear paramater set
	params.clear();

	// Init root file maker
	rootFileMaker = RootFileMaker();

	// Set up nice plot style
	gROOT->Reset();

	//gROOT->SetStyle("Plain");
	setTDRStyle();

	// Supress ROOT warnings
	gErrorIgnoreLevel = kError;

	// Keep track of how long things take
	TDatime clock;
	stopwatch = new TStopwatch();

	print(CYAN, ">>> Starting analysis...");
	stopwatch->Start();

}

// Read in config file and set up parameters
void ReadConfig(string iPath){

	// Instatiate configuration parser and take the first argument as the config file
	Config theConfig(iPath);

	SetParam(&theConfig, "maxEvents");
	SetParam(&theConfig, "luminosity");
	SetParam(&theConfig, "puList");
	SetParam(&theConfig, "toDo");
	SetParam(&theConfig, "enabledTopologies");
	SetParam(&theConfig, "flags");
	SetParam(&theConfig, "countMasses");
	SetParam(&theConfig, "webDir"); ReMakeDir(GetParam("webDir"));
	SetParam(&theConfig, "bigDir"); if(IsArgumentThere("-a")){ ReMakeDir(GetParam("bigDir")); }
	SetParam(&theConfig, "ntuplesDir");
	SetParam(&theConfig, "histoCfg");
	SetParam(&theConfig, "cutsToApply");
	SetParam(&theConfig, "osls");
	SetParam(&theConfig, "QCDcolor");
	SetParam(&theConfig, "xLegend");
	SetParam(&theConfig, "yLegend");
	SetParam(&theConfig, "dxLegend");
	SetParam(&theConfig, "dyLegend");

	// Copy original config file to output dir
	BackUpConfigFile(iPath, GetParam("webDir")); 

	// Print out some info about the output dirs, etc
	cout << "\n\t"; PrintURL(GetParam("webDir"));
	cout << "\t"; PrintLocal(GetParam("bigDir"));
	cout << "\n\tLoading ntuples from " << GetParam("ntuplesDir") << "\n" << endl;
	cout << "\n\tUsing the following flags: " << GREEN << GetParam("flags") << NOCOLOR << "\n" << endl;

	// Set some additional internal parameters
	SetParam("topology_file",string(GetParam("bigDir")+"topologies.root"));
	SetParam("stacks_output",string(GetParam("webDir")+"stacks/")); ReMakeDir(GetParam("stacks_output"));

	// Build the topopack from the info in the config file
	topologies = BuildTopoPack(&theConfig);

}

void Analyze(){

	// Set up analyzer with global paramaters
	Analyzer* analyzer = new Analyzer(new map<string,string>(params));	

	// Pass topopack to analyzer to analyze
	analyzer->AnalyzeAll(topologies);

	// Save analyzed topopack to a root file
	rootFileMaker.MakeFile(topologies, GetParam("topology_file"));
}

void CrunchNumbers(){
	Cruncher cruncher = Cruncher(&params);
//	cruncher.PrintCutEfficiencies();
}

void PlotStacks(){
	// Read root file with topologies and make stacks
	Stacker stacker = Stacker(&params);
}

void PlotStamps(){
	// Read root file with topologies and make stamps
	//Stamper stamper = Stamper(new map<string,string>(params));
}

void Optimize(){
	// Read root file with topologies and make optimization plots
	//Optimizer optimizer = Optimizer(new map<string,string>(params));
}

void Finalize(){
	// Print output dirs
	NewSection(stopwatch);
	cout << "\n" << endl;
	PrintURL(GetParam("webDir"));
	PrintLocal(GetParam("bigDir"));
	cout << "\n" << endl;
}



void SetParam(string iParam, string iValue){
	params[iParam] = iValue;
}

void SetParam(Config *theConfig, string iParam){
	params[iParam] = theConfig->pString(iParam);
}

string GetParam(string iParam){
	return (params[iParam]);
}

void print(string color, string iString){
	cout << color << iString << NOCOLOR << endl;
}


void ReMakeDir(string iPath){
	TString sysCommand;

	if(iPath.substr(iPath.length()-1).compare("/")!=0){
		iPath = iPath.substr(0,iPath.rfind("/"));
	}

	sysCommand = "rm -rf " + iPath;
	if(gSystem->Exec(sysCommand) > 0){ cout << ">>> ERROR: problem deleting \"" << iPath << "\" -- Check permissions." << endl; exit(1); }
	sysCommand = "if [ ! -d " + iPath + " ]; then mkdir -p " + iPath + "; fi";
	if(gSystem->Exec(sysCommand) > 0){ cout << ">>> ERROR: problem creating dir \"" << iPath << "\" -- Check input path and permissions." << endl; exit(1); }
}


void BackUpConfigFile(string iConfigPath, string iOutputDir){
	TString sysCommand;
	string filename = iConfigPath.substr(iConfigPath.rfind("/")+1);
	filename = filename.substr(0,iConfigPath.find(".cfg"));
	sysCommand = "cp " + iConfigPath + " " + iOutputDir + "/config_" + filename + ".txt";
	if(gSystem->Exec(sysCommand) > 0){ cout << ">>> ERROR: problem copying config file " << iConfigPath << " to output dir " << iOutputDir << endl; exit(1); }
}

void CheckAndRemove(string iPath){
	TString sysCommand;
	sysCommand = "rm -rf " + iPath;
	if(gSystem->Exec(sysCommand) > 0){ cout << ">>> ERROR: problem deleting \"" << iPath << "\" -- Check permissions." << endl; exit(1); }
}


void PrintURL(string iPath){
	TString sysCommand;
	cout << "Web dir: " << ORANGE; cout.flush();
	sysCommand = "echo \"http://$USER.web.cern.ch/$USER/" + iPath.substr(iPath.find("www/")+4) +"\"";
	cout << NOCOLOR;
	gSystem->Exec(sysCommand);
}

void PrintLocal(string iPath){
	cout << "Big dir: ";
	print(ORANGE, iPath);
}

void NewSection(TStopwatch* iStopWatch){

	float realSecs = iStopWatch->RealTime();
	float cpuSecs = iStopWatch->CpuTime();
	iStopWatch->Continue();

	TDatime clock;

	cout << "\n" << BGRAY << "--- " << clock.AsString() << " ----- Elapsed: " << setw(7) << setfill(' ') << setprecision(3) << realSecs << "s ("
		<< setw(7) << setfill(' ')  << cpuSecs << " CPUs) "  << string(50, '-') << NOCOLOR << endl;
}

TopoPack* BuildTopoPack(Config *theConfig){
	TopoPack* result = new TopoPack(&params);

	// Loop over all the topologies in the config file
	vector<pair<string,Config*> > topoConfigs = theConfig->getGroupsVec();
	for(unsigned int t = 0; t < topoConfigs.size(); t++){
		string shortName = ((topoConfigs.at(t)).first).substr(string("topology_").length());
		Config* topoConfig = (topoConfigs.at(t)).second;

		// Pass subConfig to topology and let it build itself
		Topology* topology = new Topology(shortName, topoConfig);
		string type = topology->GetType();

		// Add topology to the topopack according to its type
			 if(type.compare("collisions")==0){	
			 										result->SetCollisions(topology);
			 										result->PrepareCollisions(!SkipTopology("Collisions"));
			 										result->PrepareQCD(!SkipTopology("QCD"));
		}else if(type.compare("mcBackground")==0){
													if(SkipTopology(shortName)){ continue; }
													result->AddMCbackground(topology);	
		}else if(type.compare("signal")==0){
													if(SkipTopology(shortName)){ continue; }
													result->AddSignal(topology);
		}else{ cerr << "ERROR: topology type \"" << type << "\" invalid" << endl; exit(1);	}
	}

	return result;
}

bool SkipTopology(string iThisTopo){
	string enabledTopologies = " " + GetParam("enabledTopologies") + " ";
	string thisTopo			 = " " + iThisTopo + " ";

	bool result = IsStringThere(thisTopo,enabledTopologies);

	// Print to screen enabled topology
	if(!result || ((iThisTopo.compare("QCD"))==0) ){ print(CYAN, "\tWill analyze \"" + iThisTopo + "\""); }

	return result;
}

bool IsArgumentThere(string iArgument){ 
return IsStringThere(iArgument,inputArguments); }

bool IsStringThere(string iNeedle, string iHaystack){
	string haystack = " " + iHaystack + " ";
	string needle = " " + iNeedle + " ";

	bool result = ((haystack.find(needle) < haystack.length()));

	return result;

}
