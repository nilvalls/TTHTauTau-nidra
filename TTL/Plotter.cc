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
    if (mva)
        delete mva;
    if (comboSelector)
        delete comboSelector;
}

// Constructor
TTLPlotter::TTLPlotter(map<string,string>const & iParams):Plotter(iParams){
    params = iParams;
    ifstream mvaWeights(params.find("MVAweights")->second.c_str());
    if (mvaWeights.good()) {
        mva = new TTL_TMVAEvaluator(iParams);
        mva->BookMVA();
    } else {
        mva = 0;
    }
    mvaWeights.close();

    ifstream comboWeights(params.find("comboSelectorMVAweights")->second.c_str());
    if (comboWeights.good()) {
        comboSelector = new TTL_ComboSelector(iParams);
        comboSelector->BookMVA();
    } else {
        comboSelector = 0;
    }
    comboWeights.close();

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
        int matchIndex = -1;
        double wt = 1.0;
        if(IsFlagThere("eTauFakeUp")){
            matchIndex = 4;
            wt = atof((params["eTauFakeSys"]).c_str());
        }
        if(IsFlagThere("eTauFakeDown")){
            matchIndex = 4;
            wt = 1 - (atof((params["eTauFakeSys"]).c_str()) - 1);
        }
        if(IsFlagThere("jetTauFakeUp")){
            matchIndex = 1;
            //cout << atof((params["jetTauFakeSys"]).c_str()) << " " << (params["jetTauFakeSys"]).c_str() << " " << params["jetTauFakeSys"] << endl;
            wt = atof((params["jetTauFakeSys"]).c_str());
        }
        if(IsFlagThere("jetTauFakeDown")){
            matchIndex = 1;
            wt = 1 - (atof((params["jetTauFakeSys"]).c_str()) - 1);
        }
        if(IsFlagThere("tauIdEffUp")){
            matchIndex = 1;
            wt = atof((params["tauIdEffSys"]).c_str());
        }
        if(IsFlagThere("tauIdEffDown")){
            matchIndex = 1;
            wt = 1 - (atof((params["tauIdEffSys"]).c_str()) - 1);
        }   
        //cout << "wt: " << setprecision(4) << wt << endl;
        if( ( event->GetTau1MatchIndex(iCombo) == matchIndex ) || ( event->GetTau2MatchIndex(iCombo) == matchIndex ) )
            iTauIdSysWeight = wt;
        if( ( event->GetTau1MatchIndex(iCombo) == matchIndex ) && ( event->GetTau2MatchIndex(iCombo) == matchIndex ) )
            iTauIdSysWeight = sqrt(wt*wt + wt*wt);
	}//*/

	iWeightCounter->topPtCorrection		+= iTopPtWeight;
	iWeightCounter->leptonCorrection	+= iLeptonWeight;
	iWeightCounter->puCorrection		+= iPuWeight;
	iWeightCounter->tau1Trigger			+= iTau1TriggerWeight*iPuWeight;
	iWeightCounter->tau2Trigger			+= iTau2TriggerWeight*iTau1TriggerWeight*iPuWeight;
	iWeightCounter->tauIdSys    		+= iTauIdSysWeight;
	iWeightCounter->total++;
	

	#include "FillHistos.h"
}

