#include <algorithm>
#include <set>

#include "Driver.h"
#include "Helper.h"

#include "boost/filesystem/operations.hpp"

#define Driver_cxx
using namespace std;

// Perform some initialization tasks
void Initialize() {
	// Keep track of how long things take
	//TDatime clock;
	stopwatch = TStopwatch();
	stopwatch.Start();
	NewSection(stopwatch);
	Print(CYAN,">>>>>>>> Initializing Nidra");

	proPack = NULL;

	// Clear paramater set
	params.clear();

	// Set up nice plot style
	setTDRStyle();

	// Supress ROOT warnings
	gErrorIgnoreLevel = kError;

}

// Read in config file and set up parameters
void ReadConfig(string iPath){
	NewSection(stopwatch);
	Print(CYAN,">>>>>>>> Reading configuration file from "+iPath);
	// Instatiate configuration parser and take the first argument as the config file
	Config theConfig(iPath);

    SetParam(theConfig, "MVAdir");
	SetParam(theConfig, "maxEvents");
	SetParam(theConfig, "luminosity");
	SetParam(theConfig, "plotText");
    SetParam(theConfig, "efficiencyFormat");
	SetParam(theConfig, "channel");
	SetParam(theConfig, "toDo");
	SetParam(theConfig, "analyze");
	SetParam(theConfig, "plot");
	SetParam(theConfig, "flags");
	SetParam(theConfig, "countMasses");
	SetParam(theConfig, "webDir");
	SetParam(theConfig, "bigDir");
	SetParam(theConfig, "format");
	SetParam(theConfig, "ntuplesDir");
	SetParam(theConfig, "treeName");
	SetParam(theConfig, "histoCfg");
	SetParam(theConfig, "histoList");
	SetParam(theConfig, "cutsToApply");
	SetParam(theConfig, "osls");
	SetParam(theConfig, "QCDcolor");
	SetParam(theConfig, "xLegend");
	SetParam(theConfig, "yLegend");
	SetParam(theConfig, "dxLegend");
	SetParam(theConfig, "dyLegend");
	SetParam(theConfig, "showBackgroundError");
	SetParam(theConfig, "stackSignals");
	SetParam(theConfig, "doRatioPlot");
	SetParam(theConfig, "MVAmethod");
	SetParam(theConfig, "comboSelectorMVAmethod");
	SetParam(theConfig, "MVAbackground");
	SetParam(theConfig, "MVAsignal");
	SetParam(theConfig, "signalToOptimize");
	SetParam(theConfig, "backgroundToOptimize");
	SetParam(theConfig, "eTauFakeSys");
	SetParam(theConfig, "jetTauFakeSys");
	SetParam(theConfig, "tauIdEffSys");
	SetParam(theConfig, "comboSelectorProcess");
	SetParam(theConfig, "selectComboBy");

	// Print out some info about the output dirs, etc
	cout << "\n\t"; PrintURL(GetParam("webDir"));
	cout << "\t"; PrintLocal(GetParam("bigDir"));
	cout << "\n\tLoading ntuples from " << GetParam("ntuplesDir") << "\n" << endl;
	cout << "\n\tUsing the following flags: " << GREEN << GetParam("flags") << NOCOLOR << "\n" << endl;

	// Set some additional internal parameters
	SetParam("process_file",string(GetParam("bigDir")+"nidra_ditau.root"));

    if (params.find("MVAdir") == params.end())
        params["MVAdir"] = params["bigDir"] + "/tmva";
    params["MVAweights"] = params["MVAdir"] + "/TMVAClassification_" + params["MVAmethod"] + ".weights.xml";
    params["MVAoutput"] = params["MVAdir"] + "/tmva.root";
    params["MVAinput"] = params["MVAdir"] + "/sample.root";

	SetParam("comboSelector_dir",string(GetParam("bigDir")+"/comboSelector"));
	SetParam("comboSelectorMVAweights",string(GetParam("comboSelector_dir") + "/TMVAClassification_" + GetParam("comboSelectorMVAmethod") + ".weights.xml"));
	SetParam("comboSelector_file",string(GetParam("bigDir")+"/tmva.root"));
	SetParam("comboSelector_sample",string(GetParam("bigDir")+"/comboSelector_trainingSample.root"));
	SetParam("goodEvents_file",string(GetParam("bigDir")+"goodEvents.root"));
	SetParam("stacks_output",string(GetParam("webDir")+"stacks/"));
	SetParam("stamps_output",string(GetParam("webDir")+"stamps/"));
	SetParam("efficiency_output",string(GetParam("webDir")+"efficiency/"));
	SetParam("optimization_output",string(GetParam("webDir")+"optimization/")); 
	SetParam("config_output",string(GetParam("webDir")+"config/"));
	SetParam("propack_name","HtoTauTau");
	SetParam("rawHisto_file",string(GetParam("bigDir")+"nidra_rawHistos.root"));

}

void Analyze(){
	NewSection(stopwatch);
	Print(CYAN,">>>>>>>> Analyzing events...");

	// Set up analyzer with global paramaters
	Analyzer* analyzer = NULL;
	
	string channel = GetParam("channel");
	if(channel == "TTL"){	analyzer = new TTLAnalyzer(params); }
	else{	assert(GetParam("channel") == "TTL");		}

	// Pass topopack to analyzer to analyze
	analyzer->AnalyzeAll(*proPack);

	// Save analyzed ProPack to a root file
	rootFileMaker.MakeFile(proPack, GetParam("process_file"));
	delete analyzer; analyzer = NULL;
	Print(GREEN," done!");
}

void DistributeProcesses(){
	NewSection(stopwatch);
	Print(CYAN,">>>>>>>> Distributing processes...");

	Long_t *id,*size,*flags,*mt; id=NULL; size=NULL;flags=NULL;mt=NULL;
	bool badFile = gSystem->GetPathInfo((params["process_file"]).c_str(),id,size,flags,mt);
	if(badFile){ cerr << "ERROR: trying to distribute processes but proPack file '" << (params["process_file"]) << "' does not exist." << endl; exit(1); }

	TFile* file = new TFile((params["process_file"]).c_str(), "UPDATE");
	file->cd();

	ProPack* tempProPack = (ProPack*)file->Get((params["propack_name"]).c_str());
		
	tempProPack->DistributeProcesses();
	tempProPack->Update(proPack);

	file->cd();
	tempProPack->Write((params["propack_name"]).c_str(), TObject::kOverwrite);

	file->Close();
	delete file;

	Print(GREEN," done!");
}

void PreparePlots(){
	NewSection(stopwatch);
	Print(CYAN,">>>>>>>> Filling histograms...");

	// Book histos and fill them with good events
	Plotter* plotter = NULL;
	
	string channel = GetParam("channel");
	if(channel == "TTL"){	plotter = new TTLPlotter(params); }
	else{	assert(GetParam("channel") == "TTL");		}

	delete plotter; plotter = NULL;
	Print(GREEN," done!");
}

void CrunchNumbers(){
	NewSection(stopwatch);
	Print(CYAN,">>>>>>>> Crunching numbers...");
	ReMakeDir(GetParam("efficiency_output"));

    string unsplit = GetParam("efficiencyFormat");
    if (unsplit == "")
        unsplit = "HTML"; // set default value

	Cruncher cruncher(params);

    string fmt;
    istringstream fmts(unsplit);
    while (fmts >> fmt) {
        cruncher.PrintEfficiencies(fmt, "erc");
        cruncher.PrintEfficiencies(fmt, "e");
        cruncher.PrintEfficiencies(fmt, "ercn");
        cruncher.PrintEfficiencies(fmt, "en");
        cruncher.PrintEfficiencies(fmt, "r");
        cruncher.PrintEfficiencies(fmt, "rc");
    }
	Print(GREEN," done!");
}

void CombineProcesses(){
	NewSection(stopwatch);
	Print(CYAN,">>>>>>>> Combining processes...");
	Combiner combiner(params);
	Print(GREEN," done!");
}

void PlotStacks(){
	NewSection(stopwatch);
	Print(CYAN,">>>>>>>> Stacking plots...");
	ReMakeDir(GetParam("stacks_output"));
	Stacker stacker(params);
	Print(GREEN," done!");
}

void PlotStamps(){
	NewSection(stopwatch);
	Print(CYAN,">>>>>>>> Stamping plots...");
	ReMakeDir(GetParam("stamps_output"));
	Stamper stamper (params);
	Print(GREEN," done!");
}

void Optimize(){
	NewSection(stopwatch);
	Print(CYAN,">>>>>>>> Making optimization plots...");
	ReMakeDir(GetParam("optimization_output"));
	Optimizer optimizer(params);
	Print(GREEN," done!");
}

void TrainComboSelectorSampler(){
	NewSection(stopwatch);
	Print(CYAN,">>>>>>>> Training combo selector...");

	// Set up analyzer with global paramaters
	Analyzer* analyzer = NULL;
	
	string channel = GetParam("channel");
	if(channel == "TTL"){	analyzer = new TTLAnalyzer(params); }
	else{	assert(GetParam("channel") == "TTL");		}

	// Pass topopack to analyzer to analyze
	analyzer->SampleComboSelectorSampler(*proPack->GetPContainer()->Get(GetParam("comboSelectorProcess")));
	analyzer->TrainComboSelectorSampler();

	// Save analyzed ProPack to a root file
	delete analyzer; analyzer = NULL;
	Print(GREEN," done!");


}

void MakeTMVATrainingSample(){
	NewSection(stopwatch);
	Print(CYAN,">>>>>>>> Making TMVA training sample...");

	// Setup TMVAsampler and produce training sample
	TMVASampler* tmvaSampler = NULL;
	
	string channel = GetParam("channel");
	if(channel == "TTL"){	tmvaSampler = new TTL_TMVASampler(params); }
	else{	assert(GetParam("channel") == "TTL");		}

	tmvaSampler->MakeTrainingSample();
	delete tmvaSampler; tmvaSampler = NULL;

	Print(GREEN," done!");
}

void Finalize(){
	NewSection(stopwatch);
	Print(CYAN,">>>>>>>> Finalizing...");
	// Print output dirs
	cout << "\t"; PrintURL(GetParam("webDir"));
	cout << "\t"; PrintLocal(GetParam("bigDir"));
	if(proPack != NULL){ delete proPack; proPack = NULL; }
	NewSection(stopwatch);
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

void DeleteDir(string iPath){
	TString sysCommand;

	string path = iPath;

	if(path.substr(path.length()-1).compare("/")!=0){
		path = path.substr(0,path.rfind("/"));
	}

	sysCommand = "rm -rf " + path;
	if(gSystem->Exec(sysCommand) > 0){ cout << ">>> ERROR: problem deleting \"" << path << "\" -- Check permissions." << endl; exit(1); }
}

void ReMakeDir(string iPath){
	TString sysCommand;

	string path = iPath;

	if(path.substr(path.length()-1).compare("/")!=0){
		path = path.substr(0,path.rfind("/"));
	}

   // sysCommand = "rm -rf " + path;
   // if(gSystem->Exec(sysCommand) > 0){ cout << ">>> ERROR: problem deleting \"" << path << "\" -- Check permissions." << endl; exit(1); }
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


void BuildProPack(string iPath){

	Config theConfig(iPath);

	// Build the topopack from the info in the config file
	proPack = new ProPack(params);

	// Loop over all the topologies in the config file
    // Cloned for to avoid double free()
	vector<pair<string,Config*> > topoConfigs(theConfig.getGroupsVec());

    // Try to find option for (additional) topologies
    std::string topofile = theConfig.pString("topologyFile");
    Config *topocfg = NULL; // need to keep dependent stuff in memory until end of function
    if (topofile != "") {
        using namespace boost::filesystem;

        // If additional topologies are not defined locally, look in nidra's
        // directory
        path lpath(topofile);
        if (not exists(lpath) or is_directory(lpath)) {
            path epath = system_complete(lpath);
            topofile = epath.string();
        }

        // Read additional topologies, and copy them into the vector to be
        // looped over
        topocfg = new Config(topofile);
        std::vector< pair<string,Config*> > new_topos = topocfg->getGroupsVec();
        topoConfigs.insert(topoConfigs.end(), new_topos.begin(), new_topos.end());
    }

    string analyze_param = GetParam("analyze");
    cout << analyze_param << endl;
    bool analyze_all = analyze_param == "All";
    vector<string> to_analyze = Helper::SplitString(analyze_param);

	for(unsigned int t = 0; t < topoConfigs.size(); t++){
		string shortName = ((topoConfigs.at(t)).first).substr(string("process_").length()+1);
		Config* topoConfig = (topoConfigs.at(t)).second;

		// Pass subConfig to process and let it build itself
		Process process(shortName, params, *topoConfig);

		// Put process in ProPack's PContainer if we want it analyzed
        auto pos = find(to_analyze.begin(), to_analyze.end(), shortName);
        if (analyze_all or pos != to_analyze.end()) {
            proPack->GetPContainer()->Add(process);
            if (not analyze_all)
                to_analyze.erase(pos);
        }
    }

    if (not analyze_all and to_analyze.size() > 0) {
        cerr << "Illdefined processes:";
        for (const auto& p: to_analyze)
            cerr << " " << p;
        cerr << endl;
        abort();
    }

	// Init root file maker
	rootFileMaker = RootFileMaker(params);

    // Clean-up time
    if (topocfg != NULL)
        delete topocfg;
}

bool const IsStringThere(string iNeedle, string iHaystack){
	string haystack = iHaystack;
	string needle = iNeedle;
	bool const result = ((haystack.find(needle) < haystack.length()));
	return result;
}


