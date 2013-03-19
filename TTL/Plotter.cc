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
TTLPlotter::~TTLPlotter(){
	if(mva != NULL){ delete mva; mva = NULL; }
}

// Constructor
TTLPlotter::TTLPlotter(map<string,string>const & iParams):Plotter(iParams){
	mva = NULL;
	ifstream mvaWeights(params.find("MVAweights")->second.c_str());
	if (mvaWeights.good()) {
        mva = new TTL_TMVAEvaluator(iParams);
        mva->BookMVA();
    }
	mvaWeights.close();
	comboSelector = new TTL_ComboSelector(iParams);
	comboSelector->BookMVA();

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

	if(iIsMC){
		if(IsFlagThere("topPtSF")){		iTopPtWeight	= event->Ev_topPtWeight;	}
		if(IsFlagThere("topPtSFup")){	iTopPtWeight	= event->Ev_topPtWeightUp;	}
		if(IsFlagThere("topPtSFdown")){	iTopPtWeight	= event->Ev_topPtWeightDown;}
		if(IsFlagThere("leptonSF")){ iLeptonWeight	= event->TTL_LeptonEventWeight->at(event->GetBestCombo());	}
		if(IsFlagThere("PUcorr")){ 
			//OLD: iPuWeight = iPUcorrector->GetWeight(event->Ev_numInteractionsBX0); 
			iPuWeight = event->Ev_puWeight;
		}
		if(IsFlagThere("trigger")){ 
			iTau1TriggerWeight = iTrigger->GetWeightFromFunc(event->TTL_Tau1Pt->at(event->GetBestCombo()));
			iTau2TriggerWeight = iTrigger->GetWeightFromFunc(event->TTL_Tau2Pt->at(event->GetBestCombo()));
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

