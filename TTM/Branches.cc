/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			11 Jun 2011
    Description:	Plot stacking class.
    Notes:

*/


#define TTMBranches_cxx
#include "Branches.h"

using namespace std;

#define AT __LINE__

// Default constructor
TTMBranches::TTMBranches() : Branches(){}

TTMBranches::TTMBranches(map<string,string> const & iParams, string const iPath){ SetUp(iParams, iPath); }

// Default destructor
TTMBranches::~TTMBranches(){

	if(fChain != NULL){ fChain->ResetBranchAddresses(); }
	if(fChain != NULL){ delete (fChain->GetCurrentFile()); }
	delete fChain; fChain = NULL;

	Delete();
	Null();

}

void TTMBranches::Null(){
	#include "Branches_null.h"
}

void TTMBranches::Delete(){
	#include "Branches_delete.h"
}

void TTMBranches::Clear(){
	#include "Branches_clear.h"
}

void TTMBranches::SetBranchAddresses(){
	#include "Branches_setBranchAddress.h"
}


unsigned int TTMBranches::GetTau1IsolationIndex(const unsigned int iCombo){
	if(TTM_Tau1HPSbyTightCombinedIsolationDeltaBetaCorr->at(iCombo)){	return 4; }
	if(TTM_Tau1HPSbyMediumCombinedIsolationDeltaBetaCorr->at(iCombo)){	return 3; }
	if(TTM_Tau1HPSbyLooseCombinedIsolationDeltaBetaCorr->at(iCombo)){	return 2; }
	if(TTM_Tau1HPSbyVLooseCombinedIsolationDeltaBetaCorr->at(iCombo)){	return 1; }
	return 0;
}

unsigned int TTMBranches::GetTau2IsolationIndex(const unsigned int iCombo){
	if(TTM_Tau2HPSbyTightCombinedIsolationDeltaBetaCorr->at(iCombo)){	return 4; }
	if(TTM_Tau2HPSbyMediumCombinedIsolationDeltaBetaCorr->at(iCombo)){	return 3; }
	if(TTM_Tau2HPSbyLooseCombinedIsolationDeltaBetaCorr->at(iCombo)){	return 2; }
	if(TTM_Tau2HPSbyVLooseCombinedIsolationDeltaBetaCorr->at(iCombo)){	return 1; }
	return 0;
}

unsigned int TTMBranches::GetTau1AntiElectronIndex(const unsigned int iCombo){
	if(TTM_Tau1HPSagainstElectronTight->at(iCombo)){	return 3; }
	if(TTM_Tau1HPSagainstElectronMedium->at(iCombo)){	return 2; }
	if(TTM_Tau1HPSagainstElectronLoose->at(iCombo)){	return 1; }
	return 0;
}

unsigned int TTMBranches::GetTau2AntiElectronIndex(const unsigned int iCombo){
	if(TTM_Tau2HPSagainstElectronTight->at(iCombo)){	return 3; }
	if(TTM_Tau2HPSagainstElectronMedium->at(iCombo)){	return 2; }
	if(TTM_Tau2HPSagainstElectronLoose->at(iCombo)){	return 1; }
	return 0;
}

unsigned int TTMBranches::GetTau1AntiMuonIndex(const unsigned int iCombo){
	if(TTM_Tau1HPSagainstMuonTight->at(iCombo)){	return 3; }
	if(TTM_Tau1HPSagainstMuonMedium->at(iCombo)){	return 2; }
	if(TTM_Tau1HPSagainstMuonLoose->at(iCombo)){	return 1; }
	return 0;
}

unsigned int TTMBranches::GetTau2AntiMuonIndex(const unsigned int iCombo){
	if(TTM_Tau2HPSagainstMuonTight->at(iCombo)){	return 3; }
	if(TTM_Tau2HPSagainstMuonMedium->at(iCombo)){	return 2; }
	if(TTM_Tau2HPSagainstMuonLoose->at(iCombo)){	return 1; }
	return 0;
}

unsigned int TTMBranches::Tau1MatchedTo(unsigned int iCombo){
	unsigned int result = 0;
	if(TTM_Tau1MatchesGenHadTauFromH1->at(iCombo)){ result = 1; }
	else if(TTM_Tau1MatchesGenHadTauFromH2->at(iCombo)){ result = 2; }
	else if(TTM_Tau1MatchesGenHadTauFromW1->at(iCombo)){ result = 3; }
	else if(TTM_Tau1MatchesGenHadTauFromW2->at(iCombo)){ result = 4; }
	else{ result = 5; }
	return result;
}

unsigned int TTMBranches::Tau2MatchedTo(unsigned int iCombo){
	unsigned int result = 0;
	if(TTM_Tau2MatchesGenHadTauFromH1->at(iCombo)){ result = 1; }
	else if(TTM_Tau2MatchesGenHadTauFromH2->at(iCombo)){ result = 2; }
	else if(TTM_Tau2MatchesGenHadTauFromW1->at(iCombo)){ result = 3; }
	else if(TTM_Tau2MatchesGenHadTauFromW2->at(iCombo)){ result = 4; }
	else{ result = 5; }
	return result;
}

bool TTMBranches::IsRealDitauCombo(unsigned int iCombo){
	return (((TTM_Tau1MatchesGenHadTauFromH1->at(iCombo)) && (TTM_Tau2MatchesGenHadTauFromH2->at(iCombo))) ||
			((TTM_Tau1MatchesGenHadTauFromH2->at(iCombo)) && (TTM_Tau2MatchesGenHadTauFromH1->at(iCombo))));
}

void TTMBranches::PrintDitauReality(unsigned int iCombo){
	cout << TTM_Tau1MatchesGenHadTauFromH1->at(iCombo) << " " << 
			TTM_Tau2MatchesGenHadTauFromH2->at(iCombo) << " | " << 
			TTM_Tau1MatchesGenHadTauFromH2->at(iCombo) << " " <<
			TTM_Tau2MatchesGenHadTauFromH1->at(iCombo) << endl;

}

