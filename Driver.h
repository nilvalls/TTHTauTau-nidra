#include <iomanip>
#include <iostream>
#include <fstream>

#include <map>

#include "CommonDefs.h"
#include "ColoredOutput.h"

#include "TError.h"
#include "TSystem.h"
#include "TStopwatch.h"

#include "style-CMSTDR.h"

#include "HistoWrapper.h"
#include "Topology.h"
#include "TopoPack.h"
#include "RootFileMaker.h"
#include "Analyzer.h"
#include "Cruncher.h"
#include "Stacker.h"

#include "configParser/config.h"


#ifndef Driver_h
#define Driver_h

using namespace std;


	string					inputArguments;
	TStopwatch*				stopwatch;
	map<string, string> 	params;

	TopoPack*				topologies;
	RootFileMaker			rootFileMaker;

	// ========== Function declarations ========== //

	void Initialize(int, char**);
	void ReadConfig(string);
	void Analyze();
	void CrunchNumbers();
	void PlotStacks();
	void PlotStamps();
	void Optimize();
	void Finalize();

	void SetParam(string, string);
	void SetParam(Config*, string);
	TopoPack* BuildTopoPack(Config*);
	string GetParam(string);
	void print(string,string);
	void ReMakeDir(string);
	void CheckAndRemove(string);
	void PrintURL(string);
	void PrintLocal(string);
	void print(string, string);
	void BackUpConfigFile(string, string);
	void NewSection(TStopwatch*);
	bool SkipTopology(string);
	bool IsArgumentThere(string);
	bool IsStringThere(string,string);
	/*
	bool DoThisAnalysis(string, string);
	bool doTopology(string, string); //*/





#endif
