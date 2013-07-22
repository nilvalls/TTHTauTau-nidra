#include "TFile.h"

#include "GenHelper.h"
#include "Branches.h"

using namespace std;

// Default constructor
TLLBranches::TLLBranches() : Branches(), conesize(.25), jetIndexCacheCombo(-1) {
    Null();
}

TLLBranches::TLLBranches(const std::string& tree_name, const vector<string>& paths) :
        Branches(tree_name, paths), conesize(.25), jetIndexCacheCombo(-1)
{
	Null();
	SetBranchAddresses();
}

TLLBranches::~TLLBranches()
{
    Delete();
    Null();
}

void TLLBranches::Null(){
	#include "Branches_null.h"
}

void TLLBranches::Delete(){
	#include "Branches_delete.h"
}

void TLLBranches::Clear(){
	#include "Branches_clear.h"
}

void TLLBranches::SetBranchAddresses(){
	#include "Branches_setBranchAddress.h"
}

void
TLLBranches::GetEntry(double i)
{
    fChain->GetEntry(i);
    jetIndexCacheCombo = -1;
}

bool
TLLBranches::IsGoodGenMatch(const int& idx) const {
    return (abs((*TLL_TauGenMatchId)[idx]) == 15 &&
            abs((*TLL_TauGenMatchMother0Id)[idx]) == 25);
}

unsigned int TLLBranches::GetTauIsolationIndex(const unsigned int iCombo) const {
	if((*TLL_TauHPSbyTightCombinedIsolationDeltaBetaCorr)[iCombo]){	return 4; }
	if((*TLL_TauHPSbyMediumCombinedIsolationDeltaBetaCorr)[iCombo]){	return 3; }
	if((*TLL_TauHPSbyLooseCombinedIsolationDeltaBetaCorr)[iCombo]){	return 2; }
	if((*TLL_TauHPSbyVLooseCombinedIsolationDeltaBetaCorr)[iCombo]){	return 1; }
	return 0;
}

unsigned int TLLBranches::GetTauIsolationIndex3Hits(const unsigned int iCombo) const {
	if((*TLL_TauHPSbyTightCombinedIsolationDeltaBetaCorr3Hits)[iCombo]){	return 3; }
	if((*TLL_TauHPSbyMediumCombinedIsolationDeltaBetaCorr3Hits)[iCombo]){	return 2; }
	if((*TLL_TauHPSbyLooseCombinedIsolationDeltaBetaCorr3Hits)[iCombo]){	return 1; }
	return 0;
}

unsigned int TLLBranches::GetTauIsolationIndexMVA(const unsigned int iCombo) const {
	if((*TLL_TauHPSbyTightIsolationMVA)[iCombo]){	return 3; }
	if((*TLL_TauHPSbyMediumIsolationMVA)[iCombo]){	return 2; }
	if((*TLL_TauHPSbyLooseIsolationMVA)[iCombo]){	return 1; }
	return 0;
}

unsigned int TLLBranches::GetTauIsolationIndexMVA2(const unsigned int iCombo) const {
	if((*TLL_TauHPSbyTightIsolationMVA2)[iCombo]){	return 3; }
	if((*TLL_TauHPSbyMediumIsolationMVA2)[iCombo]){	return 2; }
	if((*TLL_TauHPSbyLooseIsolationMVA2)[iCombo]){	return 1; }
	return 0;
}

unsigned int TLLBranches::GetTauAntiElectronIndex(const unsigned int iCombo) const {
	if((*TLL_TauHPSagainstElectronTight)[iCombo]){	return 3; }
	if((*TLL_TauHPSagainstElectronMedium)[iCombo]){	return 2; }
	if((*TLL_TauHPSagainstElectronLoose)[iCombo]){	return 1; }
	return 0;
}

unsigned int TLLBranches::GetTauAntiElectronIndexMVA2(const unsigned int iCombo) const {
	if((*TLL_TauHPSagainstElectronTightMVA2)[iCombo]){	return 4; }
	if((*TLL_TauHPSagainstElectronMediumMVA2)[iCombo]){	return 3; }
	if((*TLL_TauHPSagainstElectronLooseMVA2)[iCombo]){	return 2; }
	if((*TLL_TauHPSagainstElectronVLooseMVA2)[iCombo]){	return 1; }
	return 0;
}

unsigned int TLLBranches::GetTauAntiElectronIndexMVA3(const unsigned int iCombo) const {
	if((*TLL_TauHPSagainstElectronVTightMVA3)[iCombo]){	return 4; }
	if((*TLL_TauHPSagainstElectronTightMVA3)[iCombo]){	return 3; }
	if((*TLL_TauHPSagainstElectronMediumMVA3)[iCombo]){	return 2; }
	if((*TLL_TauHPSagainstElectronLooseMVA3)[iCombo]){	return 1; }
	return 0;
}

unsigned int TLLBranches::GetTauAntiMuonIndex(const unsigned int iCombo) const {
	if((*TLL_TauHPSagainstMuonTight)[iCombo]){	return 3; }
	if((*TLL_TauHPSagainstMuonMedium)[iCombo]){	return 2; }
	if((*TLL_TauHPSagainstMuonLoose)[iCombo]){	return 1; }
	return 0;
}

unsigned int TLLBranches::GetTauAntiMuonIndex2(const unsigned int iCombo) const {
	if((*TLL_TauHPSagainstMuonTight2)[iCombo]){	return 3; }
	if((*TLL_TauHPSagainstMuonMedium2)[iCombo]){	return 2; }
	if((*TLL_TauHPSagainstMuonLoose2)[iCombo]){	return 1; }
	return 0;
}

unsigned int TLLBranches::GetTauMatchIndex(const unsigned int iCombo) const {
	if((*TLL_TauGenMatchId)[iCombo] == -99){  return 0; } // no match
	if(abs((*TLL_TauGenMatchId)[iCombo]) == 15){	return 2; } // tau
	if(abs((*TLL_TauGenMatchId)[iCombo]) == 13){	return 3; } // muon
	if(abs((*TLL_TauGenMatchId)[iCombo]) == 11){	return 4; } // electron
	if(abs((*TLL_TauGenMatchId)[iCombo]) == 22){	return 5; } // photon
	if(abs((*TLL_TauGenMatchId)[iCombo]) == 23){	return 6; } // Z
	if(abs((*TLL_TauGenMatchId)[iCombo]) == 24){	return 7; } // W
	if(abs((*TLL_TauGenMatchId)[iCombo]) == 25){	return 8; } // Higgs
	return 1; // hadronic
}

unsigned int
TLLBranches::GetJetIndex(const int idx, const unsigned int num)
{
    if (idx != jetIndexCacheCombo) {
        jetIndexCache.clear();
        for (unsigned int i = 0; i < J_Pt->size(); i++) {
            if ((DeltaR((*J_Eta)[i], (*J_Phi)[i], (*TLL_TauEta)[idx], (*TLL_TauPhi)[idx]) > conesize) &&
                    (DeltaR((*J_Eta)[i], (*J_Phi)[i], (*TLL_Lepton1Eta)[idx], (*TLL_Lepton1Phi)[idx]) > conesize) &&
                    (DeltaR((*J_Eta)[i], (*J_Phi)[i], (*TLL_Lepton2Eta)[idx], (*TLL_Lepton2Phi)[idx]) > conesize)) {
                jetIndexCache.push_back(i);
            }
        }
        jetIndexCacheCombo = idx;
    }
    return jetIndexCache.at(num);
}

unsigned int TLLBranches::GetNumCombos(){ return TLL_TauPt->size(); }
