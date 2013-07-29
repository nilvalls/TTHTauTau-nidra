#include <algorithm>
#include <set>

#include "Driver.h"
#include "Helper.h"

#include "TTL/MVABase.h"
#include "TLL/MVABase.h"

#include "boost/filesystem/operations.hpp"

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
const Config ReadConfig(string iPath){
	NewSection(stopwatch);
	Print(CYAN,">>>>>>>> Reading configuration file from "+iPath);
	// Instatiate configuration parser and take the first argument as the config file
	Config theConfig(iPath);

    SetParam(theConfig, "analysisTag");
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
	SetParam(theConfig, "xLegend");
	SetParam(theConfig, "x1Legend");
	SetParam(theConfig, "x2Legend");
	SetParam(theConfig, "yLegend");
	SetParam(theConfig, "dxLegend");
	SetParam(theConfig, "dyLegend");
    SetParam(theConfig, "colLegend");
    SetParam(theConfig, "signalScale");
	SetParam(theConfig, "showBackgroundError");
	SetParam(theConfig, "stackSignals");
	SetParam(theConfig, "doRatioPlot");

	SetParam(theConfig, "comboSelectorProcess");
	SetParam(theConfig, "selectComboBy");

	SetParam(theConfig, "signalToOptimize");
	SetParam(theConfig, "backgroundToOptimize");
	SetParam(theConfig, "eTauFakeSys");
	SetParam(theConfig, "jetTauFakeSys");
	SetParam(theConfig, "tauIdEffSys");
	SetParam(theConfig, "saveStackedHistos");
	SetParam(theConfig, "systematicsFile");
	
	SetParam(theConfig, "MVAvariables");

	// Print out some info about the output dirs, etc
	cout << "\n\t"; PrintURL(GetParam("webDir"));
	cout << "\t"; PrintLocal(GetParam("bigDir"));
	cout << "\n\tLoading ntuples from " << GetParam("ntuplesDir") << "\n" << endl;
	cout << "\n\tUsing the following flags: " << GREEN << GetParam("flags") << NOCOLOR << "\n" << endl;

	// Set some additional internal parameters
	SetParam("process_file",string(GetParam("bigDir")+"nidra_ditau.root"));

	SetParam("goodEvents_file",string(GetParam("bigDir")+"goodEvents.root"));
	SetParam("stacks_output",string(GetParam("webDir")+"stacks/"));
	SetParam("stamps_output",string(GetParam("webDir")+"stamps/"));
	SetParam("efficiency_output",string(GetParam("webDir")+"efficiency/"));
	SetParam("optimization_output",string(GetParam("webDir")+"optimization/")); 
	SetParam("config_output",string(GetParam("webDir")+"config/"));
	SetParam("propack_name","HtoTauTau");
	SetParam("rawHisto_file",string(GetParam("bigDir")+"nidra_rawHistos.root"));
	SetParam("stackedHisto_file",string(GetParam("bigDir")+"nidra_stackedHistos.root"));

    return theConfig;
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
    if (not tempProPack) {
        // FIXME
        cout << "SOMETHING WENT HORRIBLY WRONG!" << endl;
    }
		
	tempProPack->DistributeProcesses();
	tempProPack->Update(proPack);

	file->cd();
	tempProPack->Write((params["propack_name"]).c_str(), TObject::kOverwrite);

	file->Close();
	delete file;

	Print(GREEN," done!");
}

void MakeTreeForCorrelations(){
	NewSection(stopwatch);
	Print(CYAN,">>>>>>>> Making trees for correlation studies...");

	// Open up file with proPack
	Long_t *id,*size,*flags,*mt; id=NULL; size=NULL;flags=NULL;mt=NULL;
	bool badFile = gSystem->GetPathInfo(GetParam("process_file").c_str(),id,size,flags,mt);
	if(badFile){ cerr << "ERROR: trying to fill plots but proPack file does not exist. Please run the event analysis first" << endl; exit(1); }
	TFile* file = new TFile(GetParam("process_file").c_str(), "READ");
	file->cd();
	proPack = (ProPack*)file->Get(GetParam("propack_name").c_str());

	// Set up fake MVA to make trees for correlation plots
	string dir = GetParam("webDir") + "/summaryTrees/";
	ReMakeDir(dir);
    vector<string> vars = Helper::SplitString(GetParam("MVAvariables"));
    MVABase *fakeMVA = NULL;

	string channel = GetParam("channel");
	if(channel == "TTL"){		fakeMVA = new TTL::MVABase(dir, vars, 0); }
	else if(channel == "TLL"){	fakeMVA = new TLL::MVABase(dir, vars, 0); }
	else{	assert(GetParam("channel") == "TTL or TLL");		}

	// Set up MVA evaluator to get event score
	MVABase *mvaEvaluator = NULL;
		 if(MVABase::gMVA.find("CFMlpANN")	!= MVABase::gMVA.end()){ mvaEvaluator = MVABase::gMVA["CFMlpANN"];	}
	else if(MVABase::gMVA.find("BDTG")		!= MVABase::gMVA.end()){ mvaEvaluator = MVABase::gMVA["BDTG"];		}

	// Loop over all processes and create a file/tree for each
	for (const auto &p: (proPack->GetPContainer()->GetProcesses())){	fakeMVA->CreateCorrelationsTree(p->GetShortName(), proPack, mvaEvaluator); }

	delete fakeMVA, file;

	/****/

	Print(GREEN," done!");
}

void PreparePlots(){
	NewSection(stopwatch);
	Print(CYAN,">>>>>>>> Filling histograms...");

	// Book histos and fill them with good events
	Plotter* plotter = NULL;
	
	string channel = GetParam("channel");
	if(channel == "TTL"){	plotter = new TTLPlotter(params); }
	else if(channel == "TLL"){	plotter = new TLLPlotter(params); }
	else{	assert(GetParam("channel") == "TTL or TLL");		}

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
	Stacker stacker(params, false);
	Print(GREEN," done!");
}

void PlotStacksWithShapeSystematics(){
	NewSection(stopwatch);
	Print(CYAN,">>>>>>>> Stacking plots with shape systematics...");
	ReMakeDir(GetParam("stacks_output"));
	Stacker stacker(params, true);
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
