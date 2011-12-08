
#include "Driver.h"

#define Driver_cxx
using namespace std;

// Perform some initialization tasks
void Initialize(int argc, char **argv){

	proPack = NULL;
	inputArguments = "";
	for(unsigned a = 0; a < argc; a++){ inputArguments += (string(argv[a]) + " "); }

	// Clear paramater set
	params.clear();

	// Set up nice plot style
//	gROOT->Reset();

	//gROOT->SetStyle("Plain");
	setTDRStyle();

	// Supress ROOT warnings
	gErrorIgnoreLevel = kError;

	// Keep track of how long things take
	//TDatime clock;
	stopwatch = TStopwatch();

	Print(CYAN, ">>> Starting analysis...");
	stopwatch.Start();

}

// Read in config file and set up parameters
void ReadConfig(string iPath){

	// Instatiate configuration parser and take the first argument as the config file
	Config theConfig(iPath);

	SetParam(theConfig, "maxEvents");
	SetParam(theConfig, "luminosity");
	SetParam(theConfig, "puList");
	SetParam(theConfig, "toDo");
	SetParam(theConfig, "enabledTopologies");
	SetParam(theConfig, "flags");
	SetParam(theConfig, "countMasses");
	SetParam(theConfig, "webDir"); ReMakeDir(GetParam("webDir"));
	SetParam(theConfig, "bigDir"); if(IsArgumentThere("-a")){ ReMakeDir(GetParam("bigDir")); }
	SetParam(theConfig, "ntuplesDir");
	SetParam(theConfig, "treeName");
	SetParam(theConfig, "histoCfg");
	SetParam(theConfig, "cutsToApply");
	SetParam(theConfig, "osls");
	SetParam(theConfig, "QCDcolor");
	SetParam(theConfig, "xLegend");
	SetParam(theConfig, "yLegend");
	SetParam(theConfig, "dxLegend");
	SetParam(theConfig, "dyLegend");

	// Copy original config file to output dir
	BackUpConfigFile(iPath, GetParam("webDir")); 

	// Print out some info about the output dirs, etc
	cout << "\n\t"; PrintURL(GetParam("webDir"));
	cout << "\t"; PrintLocal(GetParam("bigDir"));
	cout << "\n\tLoading ntuples from " << GetParam("ntuplesDir") << "\n" << endl;
	cout << "\n\tUsing the following flags: " << GREEN << GetParam("flags") << NOCOLOR << "\n" << endl;

	// Set some additional internal parameters
	SetParam("process_file",string(GetParam("bigDir")+"nidra_ditau.root"));
	SetParam("goodEvents_file",string(GetParam("bigDir")+"goodEvents.root"));
	SetParam("stacks_output",string(GetParam("webDir")+"stacks/")); ReMakeDir(GetParam("stacks_output"));
	SetParam("optimization_output",string(GetParam("webDir")+"optimization/")); ReMakeDir(GetParam("optimization_output"));
	SetParam("propack_name","HtoTauTau");

	// Build the topopack from the info in the config file
	proPack = new ProPack(params);
	BuildProPack(*proPack, theConfig);

	// Init root file maker
	rootFileMaker = RootFileMaker(params);

}

void Analyze(){

	// Set up analyzer with global paramaters
	Analyzer analyzer(params);	

	// Pass topopack to analyzer to analyze
	analyzer.AnalyzeAll(*proPack);

	// Save analyzed ProPack to a root file
	rootFileMaker.MakeFile(proPack, GetParam("process_file"));
}

void CrunchNumbers(){
/*
	Cruncher cruncher = Cruncher(&params);
//	cruncher.PrintCutEfficiencies();
//*/
}

void PreparePlots(){
	// Book histos and fill them with good events
	Plotter plotter = Plotter(params);
}

void PlotStacks(){
	// Read root file with topologies and make stacks
	Stacker stacker = Stacker(params);
}

void PlotStamps(){
	// Read root file with topologies and make stamps
	//Stamper stamper = Stamper(new map<string,string>(params));
}

void Optimize(){
	// Read root file with topologies and make optimization plots
	//Optimizer optimizer = Optimizer(&params);
}

void Finalize(){
	// Print output dirs
	NewSection(stopwatch);
	cout << "\n" << endl;
	PrintURL(GetParam("webDir"));
	PrintLocal(GetParam("bigDir"));
	cout << "\n" << endl;

	if(proPack != NULL){ delete proPack; proPack = NULL; }
}


// ======================================================================== //

void SetParam(string iParam, string iValue){
	params.insert(make_pair(iParam, iValue));
}

void SetParam(Config const & iConfig, string iParam){
	SetParam(iParam, iConfig.pString(iParam));
}

string GetParam(string iParam){
	return (params[iParam]);
}

void Print(string color, string iString){
	cout << color << iString << NOCOLOR << endl;
}

void ReMakeDir(string iPath){
	TString sysCommand;

	string path = iPath;

	if(path.substr(path.length()-1).compare("/")!=0){
		path = path.substr(0,path.rfind("/"));
	}

	sysCommand = "rm -rf " + path;
	if(gSystem->Exec(sysCommand) > 0){ cout << ">>> ERROR: problem deleting \"" << path << "\" -- Check permissions." << endl; exit(1); }
	sysCommand = "if [ ! -d " + path + " ]; then mkdir -p " + path + "; fi";
	if(gSystem->Exec(sysCommand) > 0){ cout << ">>> ERROR: problem creating dir \"" << path << "\" -- Check input path and permissions." << endl; exit(1); }
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
	Print(ORANGE, iPath);
}

void NewSection(TStopwatch & iStopWatch){

	const float realSecs = iStopWatch.RealTime();
	const float cpuSecs = iStopWatch.CpuTime();
	iStopWatch.Continue();

	TDatime clock;

	cout << "\n" << BGRAY << "--- " << clock.AsString() << " ----- Elapsed: " << setw(7) << setfill(' ') << setprecision(3) << realSecs << "s ("
		<< setw(7) << setfill(' ')  << cpuSecs << " CPUs) "  << string(50, '-') << NOCOLOR << endl;
}


void BuildProPack(ProPack& iProPack, Config const & theConfig){

	// Loop over all the topologies in the config file
	vector<pair<string,Config*> > topoConfigs = theConfig.getGroupsVec();
	for(unsigned int t = 0; t < topoConfigs.size(); t++){
		string shortName = ((topoConfigs.at(t)).first).substr(string("process_").length()+1);
		Config* topoConfig = (topoConfigs.at(t)).second;

		// Pass subConfig to process and let it build itself
		Process process(shortName, params, *topoConfig);
		string type = process.GetType();

		// Add process to the topopack according to its type
			 if(type.compare("collisions")==0){	
			 										iProPack.SetCollisions(process);
			 										iProPack.PrepareCollisions(!SkipProcess("Collisions"));
			 										iProPack.PrepareQCD(!SkipProcess("QCD"));
		}else if(type.compare("mcBackground")==0){
													if(SkipProcess(shortName)){ continue; }
													iProPack.AddMCbackground(process);	
		}else if(type.compare("signal")==0){
													if(SkipProcess(shortName)){ continue; }
													iProPack.AddSignal(process);
		}else{ cerr << "ERROR: process type \"" << type << "\" invalid" << endl; exit(1);	}


	}

	// In-function cleanup
	topoConfigs.clear();

}


bool SkipProcess(string iThisTopo){
	string enabledTopologies = " " + GetParam("enabledTopologies") + " ";
	string thisTopo			 = " " + iThisTopo + " ";

	bool result = IsStringThere(thisTopo,enabledTopologies);

	// Print to screen enabled process
	if(!result || ((iThisTopo.compare("QCD"))==0) ){ Print(CYAN, "\tWill analyze \"" + iThisTopo + "\""); }

	return result;
}

bool const IsArgumentThere(string iArgument){ return IsStringThere(iArgument,inputArguments); }

bool const IsStringThere(string iNeedle, string iHaystack){
	string haystack = " " + iHaystack + " ";
	string needle = " " + iNeedle + " ";

	bool const result = ((haystack.find(needle) < haystack.length()));

	return result;

}

