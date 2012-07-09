/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			11 Jun 2011
    Description:	Plot stacking class.
    Notes:

*/

#include "TTPlotter.h"

#define TTPlotter_cxx
using namespace std;

#define AT __LINE__

// Default destructor
TTPlotter::~TTPlotter(){
	file->cd();
	proPack->Write((params["propack_name"]).c_str(), TObject::kOverwrite);
	RawHistoSaver rawHistoSaver(params, *proPack);
}

// Constructor
TTPlotter::TTPlotter(map<string,string>const & iParams):Plotter(iParams){
	MakePlots(proPack);
}

// Fill the histograms with the event passed
void TTPlotter::FillHistos(HContainer* iHContainer, DitauBranches* iEvent, bool const iIsMC, Trigger const * iTrigger, PUcorrector const * iPUcorrector, weightCounter* iWeightCounter){
	HContainer* hContainer = iHContainer;
	DitauBranches* event = iEvent;
	int iCombo = event->bestCombo;

	float iPuWeight = 1.0;
	float iTau1TriggerWeight = 1.0;
	float iTau2TriggerWeight = 1.0;

/*	MUST REACTIVATE
	if(iIsMC){
		if(IsFlagThere("PUcorr")){ iPuWeight = iPUcorrector->GetWeight(event->numInteractionsBX0); }
		if(IsFlagThere("trigger")){ 
			iTau1TriggerWeight = iTrigger->GetWeightFromFunc(event->Tau1Pt->at(event->bestCombo));
			iTau2TriggerWeight = iTrigger->GetWeightFromFunc(event->Tau2Pt->at(event->bestCombo));
		}
	}//*/

	iWeightCounter->puCorrection	+= iPuWeight;
	iWeightCounter->tau1Trigger		+= iTau1TriggerWeight*iPuWeight;
	iWeightCounter->tau2Trigger		+= iTau2TriggerWeight*iTau1TriggerWeight*iPuWeight;
	iWeightCounter->total++;
	

	#include "clarity/fillHistos.h"
}

