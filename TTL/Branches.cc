#include <fstream>

#include "ComboSelector.h"
#include "GenHelper.h"

#include "Branches.h"

using namespace std;

// Default constructor
TTLBranches::TTLBranches() : Branches(), comboSelector(0), conesize(.25), jetIndexCacheCombo(-1) {}

TTLBranches::TTLBranches(
      map<string,string> const & iParams,
      vector<string> const & iPath) : comboSelector(0), conesize(.25), jetIndexCacheCombo(-1) {
   SetUp(iParams, iPath);

   ifstream comboWeights(params.find("comboSelectorMVAweights")->second.c_str());
   if (comboWeights.good()) {
       comboSelector = new TTL_ComboSelector(iParams);
       comboSelector->BookMVA();
   }
   comboWeights.close();
}

// Default destructor
TTLBranches::~TTLBranches(){

	if(fChain != NULL){ fChain->ResetBranchAddresses(); }
	if(fChain != NULL){ delete (fChain->GetCurrentFile()); }
	delete fChain; fChain = NULL;

	Delete();
	Null();

    if (comboSelector)
        delete comboSelector;
}

void TTLBranches::Null(){
	#include "Branches_null.h"
}

void TTLBranches::Delete(){
	#include "Branches_delete.h"
}

void TTLBranches::Clear(){
	#include "Branches_clear.h"
}

void TTLBranches::SetBranchAddresses(){
	#include "Branches_setBranchAddress.h"
}

void
TTLBranches::GetEntry(double i)
{
    fChain->GetEntry(i);
    jetIndexCacheCombo = -1;
}


unsigned int TTLBranches::GetTau1IsolationIndex(const unsigned int iCombo) const {
	if(TTL_Tau1HPSbyTightCombinedIsolationDeltaBetaCorr->at(iCombo)){	return 4; }
	if(TTL_Tau1HPSbyMediumCombinedIsolationDeltaBetaCorr->at(iCombo)){	return 3; }
	if(TTL_Tau1HPSbyLooseCombinedIsolationDeltaBetaCorr->at(iCombo)){	return 2; }
	if(TTL_Tau1HPSbyVLooseCombinedIsolationDeltaBetaCorr->at(iCombo)){	return 1; }
	return 0;
}

unsigned int TTLBranches::GetTau2IsolationIndex(const unsigned int iCombo) const {
	if(TTL_Tau2HPSbyTightCombinedIsolationDeltaBetaCorr->at(iCombo)){	return 4; }
	if(TTL_Tau2HPSbyMediumCombinedIsolationDeltaBetaCorr->at(iCombo)){	return 3; }
	if(TTL_Tau2HPSbyLooseCombinedIsolationDeltaBetaCorr->at(iCombo)){	return 2; }
	if(TTL_Tau2HPSbyVLooseCombinedIsolationDeltaBetaCorr->at(iCombo)){	return 1; }
	return 0;
}

unsigned int TTLBranches::GetTau1AntiElectronIndex(const unsigned int iCombo) const {
	if(TTL_Tau1HPSagainstElectronTight->at(iCombo)){	return 3; }
	if(TTL_Tau1HPSagainstElectronMedium->at(iCombo)){	return 2; }
	if(TTL_Tau1HPSagainstElectronLoose->at(iCombo)){	return 1; }
	return 0;
}

unsigned int TTLBranches::GetTau2AntiElectronIndex(const unsigned int iCombo) const {
	if(TTL_Tau2HPSagainstElectronTight->at(iCombo)){	return 3; }
	if(TTL_Tau2HPSagainstElectronMedium->at(iCombo)){	return 2; }
	if(TTL_Tau2HPSagainstElectronLoose->at(iCombo)){	return 1; }
	return 0;
}

unsigned int TTLBranches::GetTau1AntiMuonIndex(const unsigned int iCombo) const {
	if(TTL_Tau1HPSagainstMuonTight->at(iCombo)){	return 3; }
	if(TTL_Tau1HPSagainstMuonMedium->at(iCombo)){	return 2; }
	if(TTL_Tau1HPSagainstMuonLoose->at(iCombo)){	return 1; }
	return 0;
}

unsigned int TTLBranches::GetTau2AntiMuonIndex(const unsigned int iCombo) const {
	if(TTL_Tau2HPSagainstMuonTight->at(iCombo)){	return 3; }
	if(TTL_Tau2HPSagainstMuonMedium->at(iCombo)){	return 2; }
	if(TTL_Tau2HPSagainstMuonLoose->at(iCombo)){	return 1; }
	return 0;
}

unsigned int TTLBranches::GetTau1MatchIndex(const unsigned int iCombo) const {
	if(TTL_Tau1GenMatchId->at(iCombo) == -99){  return 0; } // no match
	if(abs(TTL_Tau1GenMatchId->at(iCombo)) == 15){	return 2; } // tau
	if(abs(TTL_Tau1GenMatchId->at(iCombo)) == 13){	return 3; } // muon
	if(abs(TTL_Tau1GenMatchId->at(iCombo)) == 11){	return 4; } // electron
	if(abs(TTL_Tau1GenMatchId->at(iCombo)) == 22){	return 5; } // photon
	if(abs(TTL_Tau1GenMatchId->at(iCombo)) == 23){	return 6; } // Z
	if(abs(TTL_Tau1GenMatchId->at(iCombo)) == 24){	return 7; } // W
	if(abs(TTL_Tau1GenMatchId->at(iCombo)) == 25){	return 8; } // Higgs
	return 1; // hadronic
}

unsigned int TTLBranches::GetTau2MatchIndex(const unsigned int iCombo) const {
	if(TTL_Tau2GenMatchId->at(iCombo) == -99){  return 0; } // no match
	if(abs(TTL_Tau2GenMatchId->at(iCombo)) == 15){	return 2; } // tau
	if(abs(TTL_Tau2GenMatchId->at(iCombo)) == 13){	return 3; } // muon
	if(abs(TTL_Tau2GenMatchId->at(iCombo)) == 11){	return 4; } // electron
	if(abs(TTL_Tau2GenMatchId->at(iCombo)) == 22){	return 5; } // photon
	if(abs(TTL_Tau2GenMatchId->at(iCombo)) == 23){	return 6; } // Z
	if(abs(TTL_Tau2GenMatchId->at(iCombo)) == 24){	return 7; } // W
	if(abs(TTL_Tau2GenMatchId->at(iCombo)) == 25){	return 8; } // Higgs
	return 1; // hadronic
}

float
TTLBranches::GetComboSelectorResponse(const unsigned int idx) const
{
    if (comboSelector)
        return comboSelector->Evaluate(this, idx);
    else
        throw "No combo selection MVA defined!"; // TODO add exception class
}

unsigned int
TTLBranches::GetJetIndex(const unsigned int idx, const unsigned int num)
{
    if (idx != jetIndexCacheCombo) {
        jetIndexCache.clear();
        for (unsigned int i = 0, c = 0; i < J_Pt->size(); i++) {
            if ((DeltaR(J_Eta->at(i), J_Phi->at(i), TTL_Tau1Eta->at(idx), TTL_Tau1Phi->at(idx)) > conesize) &&
                    (DeltaR(J_Eta->at(i), J_Phi->at(i), TTL_Tau2Eta->at(idx), TTL_Tau2Phi->at(idx)) > conesize) &&
                    (DeltaR(J_Eta->at(i), J_Phi->at(i), TTL_LeptonEta->at(idx), TTL_LeptonPhi->at(idx)) > conesize)) {
                jetIndexCache.push_back(i);
                ++c;
            }
        }
        jetIndexCacheCombo = idx;
    }
    return jetIndexCache[num];
}
