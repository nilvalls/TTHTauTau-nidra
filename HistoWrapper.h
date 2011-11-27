
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
		float xMinVis;
		float xMaxVis;
		float yMinVis;
		float yMaxVis;
		float zMinVis;
		float zMaxVis;
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
		HistoWrapper* Clone();
		virtual ~HistoWrapper();

		TH1*	GetHisto();
		string	GetName();
		float 	GetXminVis();
		float 	GetXmaxVis();
		float 	GetYminVis();
		float 	GetYmaxVis();
		string	GetXtitle();
		string	GetYtitle();
		string	GetZtitle();
		bool	GetLogX();
		bool	GetLogY();
		bool	GetLogZ();

		void	Draw(string);

		void	SetHisto(TH1*);
		void	Add(TH1*, double iFactor=1.0);
		void	Add(HistoWrapper*, double iFactor=1.0);
		void	NormalizeTo(double);
		void	ScaleBy(double);
		void	Positivize();

		void	SetLineWidth(int,int iColor=0);
		void	SetFillStyle(int,int iColor=0);

		ClassDef(HistoWrapper, 1);
};

#endif

