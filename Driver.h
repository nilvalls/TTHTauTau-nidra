#include <iomanip>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <utility>

#include <map>

#include "ColoredOutput.h"

#include "TError.h"
#include "TSystem.h"
#include "TStopwatch.h"
#include "TDatime.h"


#include "style-CMSTDR.h"

#include "TTree.h"
#include "TFile.h"
#include "HWrapper.h"
#include "HContainer.h"
#include "CutFlow.h"
#include "DitauBranches.h"
#include "Process.h"
#include "PContainer.h"
#include "ProPack.h"

#include "Analyzer.h"
#include "Cruncher.h"
#include "RootFileMaker.h"
#include "Plotter.h"
#include "Stacker.h"
//#include "Optimizer.h"

#include "configParser/config.h"


#ifndef Driver_h
#define Driver_h

using namespace std;


	string								inputArguments;
	TStopwatch							stopwatch;
	map<string, string> 				params;

	ProPack*		proPack;
	RootFileMaker	rootFileMaker;

	// ========== Function declarations ========== //

	void			Initialize(int, char**);
	void			ReadConfig(string);
	void			Analyze();
	void			DistributeProcesses();
	void			CrunchNumbers();
	void			PreparePlots();
	void			PlotStacks();
	void			PlotStamps();
	void			Optimize();
	void			Finalize();

	// ========================================== //

	void			SetParam(string, string);
	void			SetParam(Config const &, string);
	string	GetParam(string);

	void			DeleteDir(string);
	void			ReMakeDir(string);
	bool const		IsArgumentThere(string);
	bool const		IsStringThere(string, string);

	void			BuildProPack(ProPack&, Config const &);
	void			Print(string, string);
	void			CheckAndRemove(string);
	void			PrintURL(string);
	void			PrintLocal(string);
	void			Print(string, string);
	void			BackUpConfigFile(string, string);
	void			NewSection(TStopwatch&);
	bool			AnalyzeProcess(string const);
	bool			PlotProcess(string const);
	//*/

#endif
