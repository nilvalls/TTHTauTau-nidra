//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun  7 03:28:02 2011 by ROOT version 5.27/06b
// from TTree HMTTree/TauTauTree
// found on file: ditau_nTuple.root
//////////////////////////////////////////////////////////

#ifndef Analyzer_h
#define Analyzer_h

#include "TChain.h"

#include "configParser/config.h"
#include "Trigger.h"
#include "PUcorrector.h"
#include "HistoWrapper.h"
#include "CutFlow.h"
#include "Topology.h"
#include "TopoPack.h"

//#include "CommonDefs.h"


using namespace std;
//using namespace Common;

class Analyzer {
	private:
		map<string,string>	params;
		TChain*          	fChain;   //!pointer to the analyzed TTree or TChain
		Int_t           	fCurrent; //!current Tree number in a TChain
//		Trigger*			tauTrigger;
		PUcorrector*		puCorrector;
		Config*				histoConfig;

		vector<HistoWrapper*>	histos;
		vector<HistoWrapper*>	histosLS;
		CutFlow					cutFlow;
		CutFlow					cutFlowLS;


		#include "clarity/cuts.h"
		#include "clarity/branches.h"

	public:
		Analyzer(map<string,string>*);
		virtual ~Analyzer();

		void Analyze(Topology*);
		void AnalyzeAll(TopoPack*);
		void Reset();
		void Loop();

/*		virtual Int_t					Cut(Long64_t entry);
		virtual Int_t					GetEntry(Long64_t entry);
		virtual Long64_t				LoadTree(Long64_t entry);
		virtual void					Init();
		virtual void					Loop();
		virtual Bool_t					Notify();
		virtual TChain*					GetTChain(string, string);
		virtual void					Show(Long64_t entry = -1);
		virtual void					SetTrigger(string, string);
		virtual void					SetTrigger(string);
		virtual void					SetMETSF(string, string);
		virtual void					SetFlags(string);
		virtual void					SetSelectEvents(string);
		virtual bool					IsFlagThere(string);
		virtual void					LoadPuFile(string);
		virtual void					LoadTriggerConfig(string);;
		virtual float 					GetEffectiveLumi(string, string, float);
		virtual void					SetEffectiveLumi(float);
		virtual vector<HistoWrapper*>*	GetPlots(string, bool, bool);
		virtual vector<HistoWrapper*>*	GetOSPlots(string, bool, bool, long long, long long, float iOtherSF=1.0, float iAllMCscaleFactor=1.0);
		virtual vector<HistoWrapper*>*	GetQCDPlots(string, bool, bool, long long, long long, float iOtherSF=1.0, float iAllMCscaleFactor=1.0);
		virtual void					SetOS2LS(float iOS2LS=1.0);
		virtual void					BookHistos();
		virtual void					FillEvents(int);
		virtual void					FillHistos(int);
		virtual bool					PassesCuts(unsigned int);
		virtual pair<float,float>		ExtractCutThresholds(string);
		virtual vector<cutResult*>*		GetCutResults();
		virtual void					UpPairsForCut(string);
		virtual void					UpPairsForCut(string, double);
		virtual void					RegisterCut(string, bool iPrint=true);
		virtual void					SetCutThresholds(string);
		virtual pair<string,string>		GetThresholdStrings(string);
		virtual string					GetCutStringWithThresholds(string, bool iPadding=true);
		virtual bool					ApplyThisCut(string,string);
		virtual void					SetCutsToApply(string);
		virtual void					SetReportRate(int);
		virtual void					SetPassingEventsOutput(string);
		virtual void					SetTopology(string, float);
		virtual void					ResetCounters();
		virtual void 					MakeNewCutFlows();
		virtual bool					OutOfRange(float, float, float);
		virtual void					SpacePad(stringstream&, int);
		virtual void					AddCutToList(string, float, float);
		virtual void					MakeCutsPave();
		virtual void					MakeFlagsPave();
		virtual	vector<string>*			ParseString(const string&, char);
		virtual bool					FoundHisto(string);
		virtual TH1*					GetHisto(string);
		virtual bool 					FindStringInFile(string, string);
		virtual bool					ProcessThisEvent();
		virtual string					GetRunLSevent();
		virtual void					PrintEfficienciesHTML(string);
		virtual string					Replace(string, string, string);
		virtual bool					StringContains(string, string);
		virtual unsigned int			ParseCSV(const string&, char, float[]);
		virtual void					ProcessAll(TopoPack*);

//*/

};

#endif

/*
#ifdef Analyzer_cxx

void Analyzer::SpacePad(stringstream& iSS, int iNum){
	for (int i = 0; i < iNum; i++){ iSS << " "; }
}

void Analyzer::Init(){
	// The Init() function is called when the selector needs to initialize
	// a new tree or chain. Typically here the branch addresses and branch
	// pointers of the tree will be set.
	// It is normally not necessary to make changes to the generated
	// code, but the routine can be extended by the user if needed.
	// Init() will be called many times when running on PROOF
	// (once per file to be processed).



	#include "clarity/zeroBranches.h"

	// Set branch addresses and branch pointers
	if (!fChain) return;
	//fChain->Add(tree);
	fCurrent = -1; 
	fChain->SetMakeClass(1);

	#include "clarity/setBranchAddresses.h"

	Notify();
}

void Analyzer::BookHistos(){

	HistoWrapper* prepWrapper;
	histoCollection = new map<string, HistoWrapper*>();
	histoCollection->clear();

	map<string, Config*> histo = histoConfig->getGroups();
	string histoPrefix;

	// First get all TH1F
	histoPrefix = "th1f_";
	for (map<string, Config*>::iterator i = histo.begin(); i != histo.end(); ++i) {
		string groupName = i->first;
		Config* group = i->second;
		if (groupName.substr(0, histoPrefix.length()) == histoPrefix) {

			string th1Name		= groupName.substr(histoPrefix.length());
			string title		= group->pString("title");
			int numBins			= group->pInt("numBins");
			string xbinsString	= group->pString("xbins");
			double xMin			= group->pDouble("xMin");
			double xMax			= group->pDouble("xMax");
			double xMinVis		= group->pDouble("xMinVis");
			double xMaxVis		= group->pDouble("xMaxVis");

			double yMinVis		= group->pDouble("yMinVis");
			double yMaxVis		= group->pDouble("yMaxVis");

			string xLabel		= group->pString("xLabel");
			string yLabel		= group->pString("yLabel");
			bool logx			= group->pBool("logx");
			bool logy			= group->pBool("logy");
			bool centerLabels	= group->pBool("centerLabels");
			bool showOF			= group->pBool("showOF");

			if(xbinsString.length() > 0){
				float *xbins = 0;
				xbins = new float [10000];
				int dim = ParseCSV(xbinsString,',',xbins);
				prepWrapper = new HistoWrapper((TH1F*)(new TH1F(th1Name.c_str(), title.c_str(), dim, xbins)));
				prepWrapper->SetRangeUser(xbins[0], xbins[dim], yMinVis, yMaxVis);
				prepWrapper->SetHasVariableWidthBins(true);
			}else{
				prepWrapper = new HistoWrapper((TH1F*)(new TH1F(th1Name.c_str(), title.c_str(), numBins, xMin, xMax)));
				prepWrapper->SetRangeUser(xMinVis, xMaxVis, yMinVis, yMaxVis);
			}
			prepWrapper->SetXlabel(xLabel);
			prepWrapper->SetYlabel(yLabel);
			prepWrapper->SetLog(logx,logy);
			prepWrapper->SetShowOF(showOF);
			prepWrapper->SetCenterLabels(centerLabels);
			prepWrapper->SetOutputFilename(th1Name);
			histoCollection->insert(pair<string,HistoWrapper*>(th1Name,prepWrapper));
		}
	}

	// Then get all TH2F
	histoPrefix = "th2f_";
	for (map<string, Config*>::iterator i = histo.begin(); i != histo.end(); ++i) {
		string groupName = i->first;
		Config* group = i->second;
		if (groupName.substr(0, histoPrefix.length()) == histoPrefix) {

			string th1Name		= groupName.substr(histoPrefix.length());
			string title		= group->pString("title");
			int numBinsX		= group->pInt("numBinsX");
			int numBinsY		= group->pInt("numBinsY");
			double xMin			= group->pDouble("xMin");
			double xMax			= group->pDouble("xMax");
			double yMin			= group->pDouble("yMin");
			double yMax			= group->pDouble("yMax");
			double xMinVis		= group->pDouble("xMinVis");
			double xMaxVis		= group->pDouble("xMaxVis");
			double yMinVis		= group->pDouble("yMinVis");
			double yMaxVis		= group->pDouble("yMaxVis");
			string xLabel		= group->pString("xLabel");
			string yLabel		= group->pString("yLabel");
			string zLabel		= group->pString("zLabel");
			bool logx			= group->pBool("logx");
			bool logy			= group->pBool("logy");
			bool logz			= group->pBool("logz");
			bool centerLabels	= group->pBool("centerLabels");


			//prepWrapper = new HistoWrapper(new TH2F(th1Name.c_str(), title.c_str(), numBinsX, xMin, xMax, numBinsY, yMin, yMax));
			prepWrapper->SetRangeUser(xMinVis,xMaxVis,yMinVis,yMaxVis);
			prepWrapper->SetXlabel(xLabel);
			prepWrapper->SetYlabel(yLabel);
			prepWrapper->SetZlabel(zLabel);
			prepWrapper->SetLog(logx,logy,logz);
			prepWrapper->SetCenterLabels(centerLabels);
			prepWrapper->SetOutputFilename(th1Name);
			histoCollection->insert(pair<string,HistoWrapper*>(th1Name,prepWrapper));
		}
	}

}

Bool_t Analyzer::Notify(){
	// The Notify() function is called when a new file is opened. This
	// can be either for a new TTree in a TChain or when when a new TTree
	// is started when using PROOF. It is normally not necessary to make changes
	// to the generated code, but the routine can be extended by the
	// user if needed. The return value is currently not used.

	return kTRUE;
}

void Analyzer::Show(Long64_t entry){
	// Print contents of entry.
	// If entry is not specified, print current entry
	if (!fChain) return;
	fChain->Show(entry);
}


Int_t Analyzer::Cut(Long64_t entry){
	// This function may be called from Loop.
	// returns  1 if entry is accepted.
	// returns -1 otherwise.
	return 1;
}


#endif
//*/
