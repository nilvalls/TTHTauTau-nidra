/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			11 Jun 2011
    Description:	Plot stacking class.
    Notes:

*/


#define TTMPlotter_cxx
#include "Plotter.h"

using namespace std;

#define AT __LINE__

// Default destructor
TTMPlotter::~TTMPlotter(){
	if(mva != NULL){ delete mva; mva = NULL; }
}

// Constructor
TTMPlotter::TTMPlotter(map<string,string>const & iParams):Plotter(iParams){
	//mva = new TTM_TMVAEvaluator(iParams);
	MakePlots(proPack);
	SaveFile();
}

// Fill the histograms with the event passed
void TTMPlotter::FillHistos(HContainer* iHContainer, Branches* iEvent, bool const iIsMC, Trigger const * iTrigger, weightCounter* iWeightCounter){
	HContainer* hContainer = iHContainer;
	TTMBranches* event = (TTMBranches*)iEvent;
	int iCombo = event->bestCombo;

	float iTopPtWeight			= 1.0;
	float iLeptonWeight			= 1.0;
	float iPuWeight				= 1.0;
	float iTau1TriggerWeight	= 1.0;
	float iTau2TriggerWeight	= 1.0;

	if(iIsMC){
		//if(IsFlagThere("topPtSF")){		iTopPtWeight	= event->Ev_topPtWeight;	}
		//if(IsFlagThere("topPtSFup")){	iTopPtWeight	= event->Ev_topPtWeightUp;	}
		//if(IsFlagThere("topPtSFdown")){	iTopPtWeight	= event->Ev_topPtWeightDown;}
		if(IsFlagThere("leptonSF")){ iLeptonWeight	= event->TTM_LeptonEventWeight->at(event->bestCombo);	}
		if(IsFlagThere("PUcorr")){ 
			//OLD: iPuWeight = iPUcorrector->GetWeight(event->Ev_numInteractionsBX0); 
			iPuWeight = event->Ev_puWeight;
		}
		if(IsFlagThere("trigger")){ 
			iTau1TriggerWeight = iTrigger->GetWeightFromFunc(event->TTM_Tau1Pt->at(event->bestCombo));
			iTau2TriggerWeight = iTrigger->GetWeightFromFunc(event->TTM_Tau2Pt->at(event->bestCombo));
		}
	}//*/

	iWeightCounter->topPtCorrection		+= iTopPtWeight;
	iWeightCounter->leptonCorrection	+= iLeptonWeight;
	iWeightCounter->puCorrection		+= iPuWeight;
	iWeightCounter->tau1Trigger			+= iTau1TriggerWeight*iPuWeight;
	iWeightCounter->tau2Trigger			+= iTau2TriggerWeight*iTau1TriggerWeight*iPuWeight;
	iWeightCounter->total++;
	

	#include "FillHistos.h"
}

