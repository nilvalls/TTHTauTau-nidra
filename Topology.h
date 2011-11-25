
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

using namespace std;
//using namespace Common;


class Topology {
	private:
		vector<HistoWrapper*> histos;
		vector<HistoWrapper*> histosLS;

		CutFlow cutFlowLS;

		string shortName;
		string niceName;
		string labelForLegend;
		int color;

		float crossSection;
		float branchingRatio;
		float otherScaleFactor;

		double NOEinPATuple;
		double NOEinDS;

		bool normalized;
		bool analyzed;

	public :
		// Default constructor
		Topology();
		virtual ~Topology();
		CutFlow cutFlow;

		void SetAnalyzed();
		bool Analyzed();

		void SetHistos(vector<HistoWrapper*>*);
		void SetHistosLS(vector<HistoWrapper*>*);
		void SetCutFlow(CutFlow*);
		void SetCutFlowLS(CutFlow*);

		int GetOne();
		int GetTwo();
		
		ClassDef(Topology, 1);
};

#endif

