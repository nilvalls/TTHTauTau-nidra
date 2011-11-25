//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun  7 03:28:02 2011 by ROOT version 5.27/06b
// from TTree HMTTree/TauTauTree
// found on file: ditau_nTuple.root
//////////////////////////////////////////////////////////

#ifndef Plotter_h
#define Plotter_h

#include <TROOT.h>
#include <TSystem.h>
#include <TChain.h>
#include <TStyle.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <THStack.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TPaveText.h>
#include <TGraphAsymmErrors.h>
#include <TPaletteAxis.h>
#include <math.h>
#include <map>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <utility>
#include <stdlib.h>
#include "HistoWrapper.h"
#include "Topology.h"
#include "TopoPack.h"


using namespace std;

class Plotter {

	public:
		Plotter();
		virtual ~Plotter();

		TopoPack* GetTopologies(string);
		virtual void MakePlots(TopoPack*);

	private:
					

};

#endif










