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
		Trigger*			tauTrigger;
		PUcorrector*		puCorrector;
		Config*				histoConfig;

		map<string, HistoWrapper*>	histosForSignal;
		map<string, HistoWrapper*>	histosForQCD;
		CutFlow						cutFlow;


		#include "clarity/cuts.h"
		#include "clarity/branches.h"

	public:
		Analyzer(map<string,string>*);
		virtual ~Analyzer();

		void					Analyze(Topology*);
		void					Analyze(vector<Topology*>*);
		void					AnalyzeAll(TopoPack*);
		void					Reset();
		void					Loop();
		void					Init(string);
		Long64_t				LoadTree(Long64_t entry);
		TChain*					GetTChain(string);
		pair<bool,bool>			ComboPassesCuts(unsigned int);
		void					SetCutsToApply(string);
		bool					ApplyThisCut(string);
		bool					IsFlagThere(string);
		void					FillHistosForSignal(int);
		void					FillHistosForQCD(int);
		void					FillHistos(map<string,HistoWrapper*>*, int);
		vector<HistoWrapper*>*	MakeHistoWrapperVector(map<string, HistoWrapper*>*);
		void					BookHistos(map<string, HistoWrapper*>*);

/*		virtual Int_t					Cut(Long64_t entry);
		virtual Int_t					GetEntry(Long64_t entry);
		virtual Bool_t					Notify();
		virtual void					Show(Long64_t entry = -1);
		virtual void					SetTrigger(string, string);
		virtual void					SetTrigger(string);
		virtual void					SetMETSF(string, string);
		virtual void					SetFlags(string);
		virtual void					SetSelectEvents(string);
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
		virtual pair<float,float>		ExtractCutThresholds(string);
		virtual vector<cutResult*>*		GetCutResults();
		virtual void					UpPairsForCut(string);
		virtual void					UpPairsForCut(string, double);
		virtual void					RegisterCut(string, bool iPrint=true);
		virtual void					SetCutThresholds(string);
		virtual pair<string,string>		GetThresholdStrings(string);
		virtual string					GetCutStringWithThresholds(string, bool iPadding=true);
		virtual void					SetReportRate(int);
		virtual void					SetPassingEventsOutput(string);
		virtual void					SetTopology(string, float);
		virtual void					ResetCounters();
		virtual void 					MakeNewCutFlows();
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
