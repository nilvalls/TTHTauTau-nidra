/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			11 Jun 2011
    Description:	TMVA evaluating class
    Notes:

*/

#include "TMVAEvaluator.h"

#define TTE_TMVAEvaluator_cxx
using namespace std;

#define AT __LINE__

// Default destructor
TTE_TMVAEvaluator::~TTE_TMVAEvaluator(){
	delete tmvaReader; tmvaReader = NULL;
}

// Constructor
TTE_TMVAEvaluator::TTE_TMVAEvaluator(map<string,string>const & iParams){
	params = iParams;

	tmvaReader = new TMVA::Reader( "!Color:!Silent" );

	// Tell tmva what variables to consider
	tmvaReader->AddVariable("Tau1Pt", &Tau1Pt);
	tmvaReader->AddVariable("Tau2Pt", &Tau2Pt);
	tmvaReader->AddVariable("Tau1AbsEta", &Tau1AbsEta);
	tmvaReader->AddVariable("Tau2AbsEta", &Tau2AbsEta);

	// Book TMVA
	tmvaReader->BookMVA(TString(params.find("MVAmethod")->second + " method") , TString(params.find("MVAweights")->second));
}


// Evaluate each event
float TTE_TMVAEvaluator::Evaluate(TTEBranches const * iEvent, int iCombo){

	if (iCombo < 0){ cerr << "ERROR: 'iCombo' is " << iCombo << "." << endl; exit(1); }

	Tau1Pt		= iEvent->TTE_Tau1Pt->at(iCombo);
	Tau2Pt		= iEvent->TTE_Tau1Pt->at(iCombo);
	Tau1AbsEta	= fabs(iEvent->TTE_Tau1Eta->at(iCombo));
	Tau2AbsEta	= fabs(iEvent->TTE_Tau1Eta->at(iCombo));

	return tmvaReader->EvaluateMVA(TString(params.find("MVAmethod")->second + " method"));
}


