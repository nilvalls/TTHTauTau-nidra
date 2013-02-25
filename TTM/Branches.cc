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


unsigned int TTMBranches::GetTau1IsolationIndex(const unsigned int iCombo) const {
	if(TTM_Tau1HPSbyTightCombinedIsolationDeltaBetaCorr->at(iCombo)){	return 4; }
	if(TTM_Tau1HPSbyMediumCombinedIsolationDeltaBetaCorr->at(iCombo)){	return 3; }
	if(TTM_Tau1HPSbyLooseCombinedIsolationDeltaBetaCorr->at(iCombo)){	return 2; }
	if(TTM_Tau1HPSbyVLooseCombinedIsolationDeltaBetaCorr->at(iCombo)){	return 1; }
	return 0;
}

unsigned int TTMBranches::GetTau2IsolationIndex(const unsigned int iCombo) const {
	if(TTM_Tau2HPSbyTightCombinedIsolationDeltaBetaCorr->at(iCombo)){	return 4; }
	if(TTM_Tau2HPSbyMediumCombinedIsolationDeltaBetaCorr->at(iCombo)){	return 3; }
	if(TTM_Tau2HPSbyLooseCombinedIsolationDeltaBetaCorr->at(iCombo)){	return 2; }
	if(TTM_Tau2HPSbyVLooseCombinedIsolationDeltaBetaCorr->at(iCombo)){	return 1; }
	return 0;
}

unsigned int TTMBranches::GetTau1AntiElectronIndex(const unsigned int iCombo) const {
	if(TTM_Tau1HPSagainstElectronTight->at(iCombo)){	return 3; }
	if(TTM_Tau1HPSagainstElectronMedium->at(iCombo)){	return 2; }
	if(TTM_Tau1HPSagainstElectronLoose->at(iCombo)){	return 1; }
	return 0;
}

unsigned int TTMBranches::GetTau2AntiElectronIndex(const unsigned int iCombo) const {
	if(TTM_Tau2HPSagainstElectronTight->at(iCombo)){	return 3; }
	if(TTM_Tau2HPSagainstElectronMedium->at(iCombo)){	return 2; }
	if(TTM_Tau2HPSagainstElectronLoose->at(iCombo)){	return 1; }
	return 0;
}

unsigned int TTMBranches::GetTau1AntiMuonIndex(const unsigned int iCombo) const {
	if(TTM_Tau1HPSagainstMuonTight->at(iCombo)){	return 3; }
	if(TTM_Tau1HPSagainstMuonMedium->at(iCombo)){	return 2; }
	if(TTM_Tau1HPSagainstMuonLoose->at(iCombo)){	return 1; }
	return 0;
}

unsigned int TTMBranches::GetTau2AntiMuonIndex(const unsigned int iCombo) const {
	if(TTM_Tau2HPSagainstMuonTight->at(iCombo)){	return 3; }
	if(TTM_Tau2HPSagainstMuonMedium->at(iCombo)){	return 2; }
	if(TTM_Tau2HPSagainstMuonLoose->at(iCombo)){	return 1; }
	return 0;
}
