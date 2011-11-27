
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

		CutFlow cutFlow;

		string shortName;
		string niceName;
		string labelForLegend;
		string type;
		int color;

		float crossSection;
		float branchingRatio;
		float otherScaleFactor;

		double NOEinDS;
		double NOEinPATuple;
		double NOEinNtuple;
		double NOEanalyzed;

		string ntuplePath;

		bool normalizedToLumi;
		double lumiNorm;
		bool analyzed;
		bool valid;

		void NormalizeTo(double);

	public :
		// Default constructor
		Topology();
		Topology(string, Config*);
		virtual ~Topology();

		int GetNOEinDS();
		int GetNOEinPATuple();
		int GetNOEinNtuple();
		int GetNOEanalyzed();

		void SetShortName(string);
		void SetNiceName(string);
		void SetLabelForLegend(string);
		void SetColor(int);
		void SetNOEanalyzed(double);
		void SetNOEinNtuple(double);

		void NormalizeToLumi(double);
		void NormalizeToOne();
		void ScaleBy(double);
		void SetAnalyzed();
		bool Analyzed();

		void SetHistosForSignal(vector<HistoWrapper*>*);
		void SetHistosForQCD(vector<HistoWrapper*>*);
		void SetCutFlow(CutFlow*);
		CutFlow* GetCutFlow();

		int		GetColor();
		string	GetShortName();
		string	GetNiceName();
		string	GetLabelForLegend();
		string	GetNtuplePath();
		string	GetType();
		bool	IsMC();

		vector<HistoWrapper*>* GetHistosForSignal();
		vector<HistoWrapper*>* GetHistosForQCD();

		HistoWrapper* GetAvailableHistoWrapper();
		HistoWrapper* GetHistoForSignal(int);
		HistoWrapper* GetHistoForQCD(int);

		int GetNumberOfPlots();

		void SetMarkerStyle(int);
		void SetFillColor(int);
		void SetFillStyle(int);
		void SetLineColor(int);
		void SetLineWidth(int);

		Topology* Clone();
		
		ClassDef(Topology, 1);
};

#endif

