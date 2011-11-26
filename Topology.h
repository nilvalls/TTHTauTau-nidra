
#ifndef Topology_h
#define Topology_h

#include <TROOT.h>
#include <math.h>
#include <map>
#include <vector>
#include <sstream>
#include <iostream>
#include <utility>
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <vector>

#include "CutFlow.h"
#include "HistoWrapper.h"

#include "configParser/config.h"

using namespace std;
//using namespace Common;


class Topology {
	private:
		vector<HistoWrapper*> histosForSignal;
		vector<HistoWrapper*> histosForQCD;

		CutFlow cutFlowLS;

		string shortName;
		string niceName;
		string labelForLegend;
		string type;
		int color;

		float crossSection;
		float branchingRatio;
		float otherScaleFactor;

		double NOEinPATuple;
		double NOEinDS;

		string ntuplePath;

		bool normalized;
		bool analyzed;
		bool valid;

	public :
		// Default constructor
		Topology();
		Topology(string, Config*);
		virtual ~Topology();
		CutFlow cutFlow;

		void SetAnalyzed();
		bool Analyzed();

		void SetHistosForSignal(vector<HistoWrapper*>*);
		void SetHistosForQCD(vector<HistoWrapper*>*);
		void SetCutFlow(CutFlow*);
		void SetCutFlowLS(CutFlow*);

		string GetShortName();
		string GetNtuplePath();
		string GetType();

		vector<HistoWrapper*>* GetHistosForSignal();
		vector<HistoWrapper*>* GetHistosForQCD();

		Topology* Clone();
		
		ClassDef(Topology, 1);
};

#endif

