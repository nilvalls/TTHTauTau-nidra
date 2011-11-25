
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
#include "TH1F.h"
#include "TH2F.h"

using namespace std;
//using namespace Common;


class HistoWrapper : public TH1 {
	private:
		int a;	
		TH1* test;
		TH1F* histo1F;
		TH2F* histo2F;
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
		virtual ~HistoWrapper();

		int GetNum();
		
		ClassDef(HistoWrapper, 1);
};

#endif

