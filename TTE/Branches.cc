#define TTEBranches_cxx
#include "Branches.h"

using namespace std;

#define AT __LINE__

// Default constructor
TTEBranches::TTEBranches() : Branches(){}

TTEBranches::TTEBranches(map<string,string> const & iParams, string const iPath){ SetUp(iParams, iPath); }

// Default destructor
TTEBranches::~TTEBranches(){

	if(fChain != NULL){ fChain->ResetBranchAddresses(); }
	if(fChain != NULL){ delete (fChain->GetCurrentFile()); }
	delete fChain; fChain = NULL;

	Delete();
	Null();

}

void TTEBranches::Null(){
	#include "Branches_null.h"
}

void TTEBranches::Delete(){
	#include "Branches_delete.h"
}

void TTEBranches::Clear(){
	#include "Branches_clear.h"
}

void TTEBranches::SetBranchAddresses(){
	#include "Branches_setBranchAddress.h"
}


unsigned int TTEBranches::GetTau1IsolationIndex(const unsigned int iCombo) const {
	if(TTE_Tau1HPSbyTightCombinedIsolationDeltaBetaCorr->at(iCombo)){	return 4; }
	if(TTE_Tau1HPSbyMediumCombinedIsolationDeltaBetaCorr->at(iCombo)){	return 3; }
	if(TTE_Tau1HPSbyLooseCombinedIsolationDeltaBetaCorr->at(iCombo)){	return 2; }
	if(TTE_Tau1HPSbyVLooseCombinedIsolationDeltaBetaCorr->at(iCombo)){	return 1; }
	return 0;
}

unsigned int TTEBranches::GetTau2IsolationIndex(const unsigned int iCombo) const {
	if(TTE_Tau2HPSbyTightCombinedIsolationDeltaBetaCorr->at(iCombo)){	return 4; }
	if(TTE_Tau2HPSbyMediumCombinedIsolationDeltaBetaCorr->at(iCombo)){	return 3; }
	if(TTE_Tau2HPSbyLooseCombinedIsolationDeltaBetaCorr->at(iCombo)){	return 2; }
	if(TTE_Tau2HPSbyVLooseCombinedIsolationDeltaBetaCorr->at(iCombo)){	return 1; }
	return 0;
}

unsigned int TTEBranches::GetTau1AntiElectronIndex(const unsigned int iCombo) const {
	if(TTE_Tau1HPSagainstElectronTight->at(iCombo)){	return 3; }
	if(TTE_Tau1HPSagainstElectronMedium->at(iCombo)){	return 2; }
	if(TTE_Tau1HPSagainstElectronLoose->at(iCombo)){	return 1; }
	return 0;
}

unsigned int TTEBranches::GetTau2AntiElectronIndex(const unsigned int iCombo) const {
	if(TTE_Tau2HPSagainstElectronTight->at(iCombo)){	return 3; }
	if(TTE_Tau2HPSagainstElectronMedium->at(iCombo)){	return 2; }
	if(TTE_Tau2HPSagainstElectronLoose->at(iCombo)){	return 1; }
	return 0;
}

unsigned int TTEBranches::GetTau1AntiMuonIndex(const unsigned int iCombo) const {
	if(TTE_Tau1HPSagainstMuonTight->at(iCombo)){	return 3; }
	if(TTE_Tau1HPSagainstMuonMedium->at(iCombo)){	return 2; }
	if(TTE_Tau1HPSagainstMuonLoose->at(iCombo)){	return 1; }
	return 0;
}

unsigned int TTEBranches::GetTau2AntiMuonIndex(const unsigned int iCombo) const {
	if(TTE_Tau2HPSagainstMuonTight->at(iCombo)){	return 3; }
	if(TTE_Tau2HPSagainstMuonMedium->at(iCombo)){	return 2; }
	if(TTE_Tau2HPSagainstMuonLoose->at(iCombo)){	return 1; }
	return 0;
}
