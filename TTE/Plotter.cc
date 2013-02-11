/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			11 Jun 2011
    Description:	Plot stacking class.
    Notes:

*/


#define TTEPlotter_cxx
#include "Plotter.h"

using namespace std;

#define AT __LINE__

// Default destructor
TTEPlotter::~TTEPlotter(){
}

// Constructor
TTEPlotter::TTEPlotter(map<string,string>const & iParams):Plotter(iParams){
	MakePlots(proPack);
	SaveFile();
}

// Fill the histograms with the event passed
void TTEPlotter::FillHistos(HContainer* iHContainer, Branches* iEvent, bool const iIsMC, Trigger const * iTrigger, weightCounter* iWeightCounter){
	HContainer* hContainer = iHContainer;
	TTEBranches* event = (TTEBranches*)iEvent;
	int iCombo = event->bestCombo;

	float iLeptonWeight			= 1.0;
	float iPuWeight				= 1.0;
	float iTau1TriggerWeight	= 1.0;
	float iTau2TriggerWeight	= 1.0;

	if(iIsMC){
		if(IsFlagThere("leptonSF")){ iLeptonWeight	= event->TTE_LeptonEventWeight->at(event->bestCombo);	}
		if(IsFlagThere("PUcorr")){ 
			//OLD: iPuWeight = iPUcorrector->GetWeight(event->Ev_numInteractionsBX0); 
			iPuWeight = event->Ev_puWeight;
		}
		if(IsFlagThere("trigger")){ 
			iTau1TriggerWeight = iTrigger->GetWeightFromFunc(event->TTE_Tau1Pt->at(event->bestCombo));
			iTau2TriggerWeight = iTrigger->GetWeightFromFunc(event->TTE_Tau2Pt->at(event->bestCombo));
		}
	}//*/

	iWeightCounter->leptonCorrection	+= iLeptonWeight;
	iWeightCounter->puCorrection		+= iPuWeight;
	iWeightCounter->tau1Trigger			+= iTau1TriggerWeight*iPuWeight;
	iWeightCounter->tau2Trigger			+= iTau2TriggerWeight*iTau1TriggerWeight*iPuWeight;
	iWeightCounter->total++;
	

	#include "FillHistos.h"
}

