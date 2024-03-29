#include <iomanip>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <utility>
#include <assert.h>

#include <map>


#include "TError.h"
#include "TSystem.h"
#include "TStopwatch.h"
#include "TDatime.h"

#include "style-CMSTDR.h"
#include "configParser/config.h"
#include "ColoredOutput.h"

#include "TTree.h"
#include "TFile.h"
#include "Process.h"
#include "ProPack.h"

#include "Cruncher.h"
#include "Combiner.h"
#include "RootFileMaker.h"
#include "Plotter.h"
#include "Stacker.h"
#include "Stamper.h"
#include "Optimizer.h"

#include "TTL/Plotter.h"
#include "TLL/Plotter.h"

#ifndef Driver_h
#define Driver_h

using namespace std;


	TStopwatch							stopwatch;
	map<string, string> 				params;

	ProPack*		proPack;
	RootFileMaker	rootFileMaker;

	// ========== Function declarations ========== //

	void			Initialize(int, char**);
    const Config	ReadConfig(string);
	void			TrainComboSelectorSampler();
	void			Analyze();
	void			DistributeProcesses();
	void			CrunchNumbers();
	void			PreparePlots();
	void			MakeTreeForCorrelations();
	void			PlotStacks();
	void			PlotStacksWithShapeSystematics();
	void			PlotStamps();
	void			Optimize();
	void			Finalize();

	// ========================================== //

	void			SetParam(string, string);
	void			SetParam(Config const &, string);
	string			GetParam(string);

	void			DeleteDir(string);
	void			ReMakeDir(string);
	bool const		IsStringThere(string, string);

	void			BuildProPack(ProPack&, Config const &);
	void			Print(string, string);
	void			CheckAndRemove(string);
	void			PrintURL(string);
	void			PrintLocal(string);
	void			Print(string, string);
	void			BackUpConfigFile(string, string);
	void			NewSection(TStopwatch&);

#endif
