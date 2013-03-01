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
#include <TFile.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "TCanvas.h"
#include "Helper.h"
#include "CutFlow.h"
#include "Branches.h"
#include "TTM/Branches.h"
#include "TTE/Branches.h"
#include "TTL/Branches.h"
#include "Process.h"
#include "ProPack.h"
#include "Analyzer.h"
#include "TPaveText.h"
#include "Trigger.h"
#include "TLegend.h"
#include "TStyle.h"
#include "RawHistoSaver.h"

using namespace std;

struct weightCounter{
	double leptonCorrection;
	double puCorrection;
	double tau1Trigger;
	double tau2Trigger;
	double total;
};

class Plotter {

	public:
		Plotter();
		Plotter(map<string,string> const &);
		~Plotter();

		void PrintEfficiencies(string const, string const);

	protected:
		virtual void	FillHistos(HContainer*, Branches*, bool const, Trigger const *, weightCounter *);
		Trigger*		ditauTrigger;
		void			SaveFile();
		virtual void	MakePlots(ProPack*);
		virtual void	MakePlots(Process*);
		virtual void	MakePlots(vector<Process>*);
		void			BookHistos(HContainer*);
		bool const		IsFlagThere(string const) const;
		void			LoopOverHistoCfgFile(const string, HContainer*);
		float const		ThetaToEta(const float) const;		

	private: 

	protected:
		TFile* file;
		ProPack* proPack;
		map<string,string>	params;
		HWrapper const  	GetBackgroundSum(ProPack const *, string const) const;
	/*	double const		GetMaximum(ProPack const *, string const, bool const) const;
		double const		GetMaximum(ProPack const *, string const) const;
		double const		GetMaximumWithError(ProPack const *, string const) const;//*/
		double const		GetMaxIntegral(ProPack const *, string const) const;
		TPaveText *			GetPlotText(const string);
		virtual void SaveCanvas(TCanvas const *, string const, string const) const;
		virtual void SaveCanvasLog(TCanvas*, string, string, bool, bool, bool);

};

#endif










