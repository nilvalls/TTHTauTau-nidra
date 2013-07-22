/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			11 Jun 2011
    Description:	Plot stacking class.
    Notes:

*/

#include "MVABase.h"

#include "Plotter.h"

using namespace std;

// Default destructor
TLLPlotter::~TLLPlotter() {}

// Constructor
TLLPlotter::TLLPlotter(map<string,string>const & iParams):Plotter(iParams){
	MakePlots(proPack);
	SaveFile();
}

// Fill the histograms with the event passed
double TLLPlotter::FillHistos(const std::string& name, HContainer* iHContainer, Branches* iEvent, bool const iIsMC, Trigger const * iTrigger, weightCounter* iWeightCounter){
	HContainer* hContainer = iHContainer;
	TLLBranches* event = (TLLBranches*)iEvent;
	int iCombo = event->GetBestCombo();

	float iTopPtWeight			= 1.0;
	float iLepton1Weight		= 1.0;
	float iLepton2Weight		= 1.0;
	float iPuWeight				= 1.0;
	float iTauTriggerWeight		= 1.0;
    float iTauIdSysWeight       = 1.0;
    float iQ2SysWeight          = 1.0;
    float iJetCSVweight         = 1.0;
	float bf_weight = 1.0; // to correct branching fraction in inclusive MC


	if(iIsMC){
		if (IsFlagThere("brSF") and name.find("TTH_") != std::string::npos) {
			unsigned int matches = 0;
			for (const auto& id: *dynamic_cast<TLLBranches*>(iEvent)->GT_ParentId)
				matches += (abs(id) == 25);
			bf_weight = (matches == 2) ? 0.0632 / 0.0722 : (1 - 0.0632) / (1 - 0.0722);
		}

		if(IsFlagThere("topPtSF")){		iTopPtWeight	= event->Ev_topPtWeight;	}
		if(IsFlagThere("topPtSFUp")){	iTopPtWeight	= event->Ev_topPtWeightUp;	}
		if(IsFlagThere("topPtSFDown")){	iTopPtWeight	= event->Ev_topPtWeightDown;}
		if(IsFlagThere("leptonSF")){
			iLepton1Weight	= event->TLL_Lepton1EventWeight->at(iCombo);
			iLepton2Weight	= event->TLL_Lepton2EventWeight->at(iCombo);
		}
		if(IsFlagThere("PUcorr")){ iPuWeight = event->Ev_puWeight; }
		if(IsFlagThere("PUcorrUp")){ iPuWeight = event->Ev_puWeightUp; }
		if(IsFlagThere("PUcorrDown")){ iPuWeight = event->Ev_puWeightDown; }
		if(IsFlagThere("PUcorr2012A")){ iPuWeight = event->Ev_puWeight2012A; }
		if(IsFlagThere("PUcorr2012B")){ iPuWeight = event->Ev_puWeight2012B; }
		if(IsFlagThere("PUcorr2012C")){ iPuWeight = event->Ev_puWeight2012C; }
		if(IsFlagThere("PUcorr2012D")){ iPuWeight = event->Ev_puWeight2012D; }
		if(IsFlagThere("PUcorr2012AB")){ iPuWeight = event->Ev_puWeight2012AB; }
		if(IsFlagThere("PUcorr2012BC")){ iPuWeight = event->Ev_puWeight2012BC; }
		if(IsFlagThere("PUcorr2012CD")){ iPuWeight = event->Ev_puWeight2012CD; }
		if(IsFlagThere("PUcorr2012ABC")){ iPuWeight = event->Ev_puWeight2012ABC; }
        if(IsFlagThere("qSquaredUp")){ iQ2SysWeight = event->Ev_q2WeightUp; }
		if(IsFlagThere("qSquaredDown")){ iQ2SysWeight = event->Ev_q2WeightDown; }
		
/*        if(IsFlagThere("CSVeventWeight")){ iJetCSVweight = event->TTL_CSVeventWeight->at(iCombo); }
		if(IsFlagThere("CSVeventWeightHFdown")){ iJetCSVweight = event->TTL_CSVeventWeightHFdown->at(iCombo); }
		if(IsFlagThere("CSVeventWeightHFup")){ iJetCSVweight = event->TTL_CSVeventWeightHFup->at(iCombo); }
		if(IsFlagThere("CSVeventWeightLFdown")){ iJetCSVweight = event->TTL_CSVeventWeightLFdown->at(iCombo); }
		if(IsFlagThere("CSVeventWeightLFup")){ iJetCSVweight = event->TTL_CSVeventWeightLFup->at(iCombo); }
		if(IsFlagThere("CSVeventWeightHFStats1down")){ iJetCSVweight = event->TTL_CSVeventWeightHFStats1down->at(iCombo); }
		if(IsFlagThere("CSVeventWeightHFStats1up")){ iJetCSVweight = event->TTL_CSVeventWeightHFStats1up->at(iCombo); }
		if(IsFlagThere("CSVeventWeightLFStats1down")){ iJetCSVweight = event->TTL_CSVeventWeightLFStats1down->at(iCombo); }
		if(IsFlagThere("CSVeventWeightLFStats1up")){ iJetCSVweight = event->TTL_CSVeventWeightLFStats1up->at(iCombo); }
		if(IsFlagThere("CSVeventWeightHFStats2down")){ iJetCSVweight = event->TTL_CSVeventWeightHFStats2down->at(iCombo); }
		if(IsFlagThere("CSVeventWeightHFStats2up")){ iJetCSVweight = event->TTL_CSVeventWeightHFStats2up->at(iCombo); }
		if(IsFlagThere("CSVeventWeightLFStats2down")){ iJetCSVweight = event->TTL_CSVeventWeightLFStats2down->at(iCombo); }
		if(IsFlagThere("CSVeventWeightLFStats2up")){ iJetCSVweight = event->TTL_CSVeventWeightLFStats2up->at(iCombo); }
		//*/
		
        if(IsFlagThere("trigger")){ 
			iTauTriggerWeight = iTrigger->GetWeightFromFunc(event->TLL_TauPt->at(event->GetBestCombo()));
		}
        unsigned int matchIndex = 666666;
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
//        if( event->GetTauMatchIndex(iCombo) == matchIndex ) 
//            iTauIdSysWeight = wt;

	}//*/
    //cout << "iTauIdSysWeight = " << iTauIdSysWeight << endl;
	iWeightCounter->topPtCorrection		+= iTopPtWeight;
	iWeightCounter->lepton1Correction	+= iLepton1Weight;
	iWeightCounter->lepton2Correction	+= iLepton2Weight;
	iWeightCounter->puCorrection		+= iPuWeight;
	iWeightCounter->tauIdSys    		+= iTauIdSysWeight;
	iWeightCounter->q2Sys        		+= iQ2SysWeight;
	iWeightCounter->jetCSV      		+= iJetCSVweight;
	iWeightCounter->total++;

	#include "FillHistos.h"

	return weightFull;
}

