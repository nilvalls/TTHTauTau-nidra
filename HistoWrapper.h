
#ifndef HistoWrapper_h
#define HistoWrapper_h

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

#include "configParser/config.h"

#include "TH1F.h"
#include "TH2F.h"

using namespace std;
//using namespace Common;


class HistoWrapper{
	private:
		TH1* histo;
		float xbins[100000];
		float visibleXmin;
		float visibleXmax;
		float visibleYmin;
		float visibleYmax;
		float visibleZmin;
		float visibleZmax;
		string xTitle;
		string yTitle;
		string zTitle;
		bool logx;
		bool logy;
		bool logz;
		bool showOverFlow;
		bool centerLabels;
		string TH1Type;
		bool hasVariableWidthBins;


	public :
		// Default constructor
		HistoWrapper();
		HistoWrapper(string, string, Config*);
		virtual ~HistoWrapper();

		TH1* GetHisto();
		void SetHisto(TH1*);
		HistoWrapper* Clone();

		ClassDef(HistoWrapper, 1);
};

#endif

