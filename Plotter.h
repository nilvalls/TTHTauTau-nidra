//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun  7 03:28:02 2011 by ROOT version 5.27/06b
// from TTree HMTTree/TauTauTree
// found on file: ditau_nTuple.root
//////////////////////////////////////////////////////////

#ifndef Plotter_h
#define Plotter_h

#include "TPaveText.h"

#include "TTL/Branches.h"
#include "TLL/Branches.h"
#include "Branches.h"
#include "Helper.h"
#include "ProPack.h"
#include "Process.h"
#include "Trigger.h"
#include "TLatex.h"

struct weightCounter{
	double topPtCorrection;
	double leptonCorrection;
	double lepton1Correction;
	double lepton2Correction;
	double puCorrection;
	double tauTrigger;
	double tau1Trigger;
	double tau2Trigger;
    double tauIdSys;
    double q2Sys;
    double jetCSV;
    double bf_sf;
	double total;
};

class Plotter {

	public:
		Plotter();
		Plotter(map<string,string> const &);
		~Plotter();

		void PrintEfficiencies(string const, string const);

	protected:
		virtual double	FillHistos(const std::string&, HContainer*, Branches*, bool const, Trigger const *, weightCounter *){};
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
		TLatex *			GetPlotTextLatex(const string);
		virtual void SaveCanvas(TCanvas const *, string const, string const) const;
		virtual void SaveCanvasLog(TCanvas*, string, string, bool, bool, bool, int iPad = 0);

};

#endif
