/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			11 Jun 2011
    Description:	Plot stacking class.
    Notes:

*/


#define DILPlotter_cxx
#include "Plotter.h"

using namespace std;

#define AT __LINE__

// Default destructor
DILPlotter::~DILPlotter(){
}

// Constructor
DILPlotter::DILPlotter(map<string,string>const & iParams):Plotter(iParams){
	MakePlots(proPack);
	SaveFile();
}

// Fill the histograms with the event passed
void DILPlotter::FillHistos(HContainer* iHContainer, Branches* iEvent, bool const iIsMC, Trigger const * iTrigger, weightCounter* iWeightCounter){
	HContainer* hContainer = iHContainer;
	DILBranches* event = (DILBranches*)iEvent;
	int iCombo = event->bestCombo;

	float iPuWeight = 1.0;
	float iTau1TriggerWeight = 1.0;
	float iTau2TriggerWeight = 1.0;

	if(iIsMC){
		if(IsFlagThere("PUcorr")){ 
			//OLD: iPuWeight = iPUcorrector->GetWeight(event->Ev_numInteractionsBX0); 
			iPuWeight = event->Ev_puWeight;
		}
	}//*/

	iWeightCounter->puCorrection	+= iPuWeight;
	iWeightCounter->total++;
	

	#include "FillHistos.h"
}

