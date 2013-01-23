/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			11 Jun 2011
    Description:	Plot stacking class.
    Notes:

*/

#include "TMVAEvaluator.h"

#define TMVAEvaluator_cxx
using namespace std;

#define AT __LINE__

// Default constructor
TMVAEvaluator::TMVAEvaluator(){
	event = NULL;
	tmvaReader = NULL;
}

// Default destructor
TMVAEvaluator::~TMVAEvaluator(){
	delete event; event = NULL;
	delete tmvaReader; tmvaReader = NULL;
}

TMVAEvaluator::TMVAEvaluator(map<string,string>const & iParams){
	params = iParams;
	event = NULL;

	tmvaReader = new TMVA::Reader( "!Color:!Silent" );

	tmvaReader->AddVariable("NSVFitSystemEta", &NSVFitSystemEta);
	tmvaReader->AddVariable("NSVFitSystemPt", &NSVFitSystemPt);
	tmvaReader->AddVariable("NSVFitMass", &NSVFitMass);
//	tmvaReader->AddVariable("NSVFitMassUncert", &NSVFitMassUncert);
	tmvaReader->AddVariable("NSVFitMET", &NSVFitMET);
	tmvaReader->AddVariable("DeltaR_recoTau1_SVFitTau1", &DeltaR_recoTau1_SVFitTau1);
	tmvaReader->AddVariable("BoostedSVFitTau1Pt", &BoostedSVFitTau1Pt);

	tmvaReader->BookMVA(TString(params.find("MVAmethod")->second + " method") , TString(params.find("MVAweights")->second));

}

float TMVAEvaluator::Evaluate(Branches const * iEvent, int iCombo){

	if (iCombo < 0){ cerr << "ERROR: 'iCombo' is " << iCombo << "." << endl; exit(1); }

	unsigned int combo = iCombo;

	NSVFitSystemEta				= iEvent->NSVFitSystemEta->at(combo);
	NSVFitSystemPt				= iEvent->NSVFitSystemPt->at(combo);
	NSVFitMass					= iEvent->NSVFitMass->at(combo);
//	NSVFitMassUncert			= iEvent->NSVFitMassUncert->at(combo);
	NSVFitMET					= iEvent->NSVFitMET->at(combo);
	DeltaR_recoTau1_SVFitTau1	= iEvent->DeltaR_recoTau1_SVFitTau1->at(combo);
	BoostedSVFitTau1Pt			= iEvent->BoostedSVFitTau1Pt->at(combo);

	return tmvaReader->EvaluateMVA(TString(params.find("MVAmethod")->second + " method"));
}


