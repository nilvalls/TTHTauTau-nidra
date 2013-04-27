/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			11 Jun 2011
    Description:	Plot stacking class.
    Notes:

*/


#define TTLPlotter_cxx
#include "Plotter.h"

using namespace std;

#define AT __LINE__

// Default destructor
TTLPlotter::~TTLPlotter() {}

// Constructor
TTLPlotter::TTLPlotter(map<string,string>const & iParams):Plotter(iParams){
    mva = TTL_TMVAEvaluator::gMVA;
	MakePlots(proPack);
	SaveFile();
}

// Fill the histograms with the event passed
void TTLPlotter::FillHistos(HContainer* iHContainer, Branches* iEvent, bool const iIsMC, Trigger const * iTrigger, weightCounter* iWeightCounter){
	HContainer* hContainer = iHContainer;
	TTLBranches* event = (TTLBranches*)iEvent;
	int iCombo = event->GetBestCombo();

	float iTopPtWeight			= 1.0;
	float iLeptonWeight			= 1.0;
	float iPuWeight				= 1.0;
	float iTau1TriggerWeight	= 1.0;
	float iTau2TriggerWeight	= 1.0;
    float iTauIdSysWeight       = 1.0;
    float iQ2SysWeight          = 1.0;
    float iJetCSVweight         = 1.0;

	if(iIsMC){
		if(IsFlagThere("topPtSF")){		iTopPtWeight	= event->Ev_topPtWeight;	}
		if(IsFlagThere("topPtSFUp")){	iTopPtWeight	= event->Ev_topPtWeightUp;	}
		if(IsFlagThere("topPtSFDown")){	iTopPtWeight	= event->Ev_topPtWeightDown;}
		if(IsFlagThere("leptonSF")){ iLeptonWeight	= event->TTL_LeptonEventWeight->at(iCombo);	}
		if(IsFlagThere("PUcorr")){ iPuWeight = event->Ev_puWeight; }
		if(IsFlagThere("PUcorrUp")){ iPuWeight = event->Ev_puWeightUp; }
		if(IsFlagThere("PUcorrDown")){ iPuWeight = event->Ev_puWeightDown; }
        if(IsFlagThere("qSquaredUp")){ iQ2SysWeight = event->Ev_q2WeightUp; }
		if(IsFlagThere("qSquaredDown")){ iQ2SysWeight = event->Ev_q2WeightDown; }
		if(IsFlagThere("JetCSVWeight")){ iJetCSVweight = event->TTL_TotalJetWeight->at(iCombo); }
		
        if(IsFlagThere("trigger")){ 
			iTau1TriggerWeight = iTrigger->GetWeightFromFunc(event->TTL_Tau1Pt->at(event->GetBestCombo()));
			iTau2TriggerWeight = iTrigger->GetWeightFromFunc(event->TTL_Tau2Pt->at(event->GetBestCombo()));
		}
        int matchIndex = -1;
        double wt = 1.0;
        if(IsFlagThere("eTauFakeUp")){
            matchIndex = 4; //electron
            wt = atof((params["eTauFakeSys"]).c_str());
        }
        if(IsFlagThere("eTauFakeDown")){
            matchIndex = 4; //electron
            wt = 1 - (atof((params["eTauFakeSys"]).c_str()) - 1);
        }
        if(IsFlagThere("jetTauFakeUp")){
            matchIndex = 1; //quark/gluon/jet
            wt = atof((params["jetTauFakeSys"]).c_str());
        }
        if(IsFlagThere("jetTauFakeDown")){
            matchIndex = 1; //quark/gluon/jet
            wt = 1 - (atof((params["jetTauFakeSys"]).c_str()) - 1);
        }
        if(IsFlagThere("tauIdEffUp")){
            matchIndex = 2; //tau
            wt = atof((params["tauIdEffSys"]).c_str());
        }
        if(IsFlagThere("tauIdEffDown")){
            matchIndex = 2; //tau
            wt = 1 - (atof((params["tauIdEffSys"]).c_str()) - 1);
        }
        //cout << "wt = " << wt << endl;
        if( ( event->GetTau1MatchIndex(iCombo) == matchIndex ) || ( event->GetTau2MatchIndex(iCombo) == matchIndex ) )
            iTauIdSysWeight = wt;
        if( ( event->GetTau1MatchIndex(iCombo) == matchIndex ) && ( event->GetTau2MatchIndex(iCombo) == matchIndex ) )
            iTauIdSysWeight = wt*wt;//*/
	}//*/
    //cout << "iTauIdSysWeight = " << iTauIdSysWeight << endl;
	iWeightCounter->topPtCorrection		+= iTopPtWeight;
	iWeightCounter->leptonCorrection	+= iLeptonWeight;
	iWeightCounter->puCorrection		+= iPuWeight;
	iWeightCounter->tau1Trigger			+= iTau1TriggerWeight*iPuWeight;
	iWeightCounter->tau2Trigger			+= iTau2TriggerWeight*iTau1TriggerWeight*iPuWeight;
	iWeightCounter->tauIdSys    		+= iTauIdSysWeight;
	iWeightCounter->q2Sys        		+= iQ2SysWeight;
	iWeightCounter->jetCSV      		+= iJetCSVweight;
	iWeightCounter->total++;
	

	#include "FillHistos.h"
}

