/*
    Author:			Nil Valls <nil.valls@cern.ch>, Matthias Wolf <matthias.wolf@cern.ch>
    Date:			11 Jun 2011
    Description:	TMVA evaluating class
    Notes:

*/

#include "Helper.h"
#include "MVABase.h"

using namespace std;

TLL::MVABase::MVABase(const std::string& dir, const std::vector<std::string>& vars, const int rnk) :
    ::MVABase(dir, vars, rnk)
{
}

void
TLL::MVABase::SetupVariables(TMVA::Factory* f)
{
    SetupVariablesT(f);
}

void
TLL::MVABase::SetupVariables(TMVA::Reader* r)
{
    SetupVariablesT(r);
}

void
TLL::MVABase::SetupVariables(TTree* t)
{
    SetupVariablesT(t);
}

void
TLL::MVABase::SetupCorrelationsVariables(TTree* t)
{
	TLL::MVABase::SetupVariablesT(t);

	// Needed for correlation plots
    AddVariable(t, "MVAoutput", 'F', MVAoutput);
    AddVariable(t, "Xsec", 'F', Xsec);
	AddVariable(t, "nGen", 'I', nGen);
	AddVariable(t, "weight", 'F', weight);
	AddVariable(t, "topPtWgt", 'F', topPtWgt);
	AddVariable(t, "lep1TotalSF", 'F', lep1TotalSF);
	AddVariable(t, "lep2TotalSF", 'F', lep2TotalSF);
	AddVariable(t, "triggerSF", 'F', triggerSF);
	AddVariable(t, "csvWgtlf", 'F', csvWgtlf);
	AddVariable(t, "csvWgthf", 'F', csvWgthf);
}

template<typename T> void
TLL::MVABase::SetupVariablesT(T* obj)
{
    AddVariableConditionally(obj, "CSR", 'F', csr);
    AddVariableConditionally(obj, "HT", 'F', HT);
    AddVariableConditionally(obj, "TauPt", 'F', TauPt);
    AddVariableConditionally(obj, "TauEta", 'F', TauEta);
    AddVariableConditionally(obj, "TauDecayMode", 'I', TauDecayMode);
    AddVariableConditionally(obj, "TauIsolationIndex", 'I', TauIsolationIndex);
    AddVariableConditionally(obj, "TauIsolationIndexMVA2", 'I', TauIsolationIndexMVA2);
    AddVariableConditionally(obj, "TauIsolationMVA2Raw", 'F', TauIsolationMVA2Raw);
    AddVariableConditionally(obj, "DeltaRTauLepton1", 'F', DeltaRTauLepton1);
    AddVariableConditionally(obj, "DeltaRTauLepton2", 'F', DeltaRTauLepton2);
    AddVariableConditionally(obj, "DeltaRLepton1Lepton2", 'F', DeltaRLepton1Lepton2);
    AddVariableConditionally(obj, "DeltaRTauLeadingJet", 'F', DeltaRTauLeadingJet);
    AddVariableConditionally(obj, "DeltaRTauSubleadingJet", 'F', DeltaRTauSubleadingJet);
    AddVariableConditionally(obj, "DeltaRLepton1LeadingJet", 'F', DeltaRLepton1LeadingJet);
    AddVariableConditionally(obj, "DeltaRLepton1SubleadingJet", 'F', DeltaRLepton1SubleadingJet);
    AddVariableConditionally(obj, "DeltaRLepton2LeadingJet", 'F', DeltaRLepton2LeadingJet);
    AddVariableConditionally(obj, "DeltaRLepton2SubleadingJet", 'F', DeltaRLepton2SubleadingJet);
    AddVariableConditionally(obj, "LeadingJetSubleadingJetMass", 'F', LeadingJetSubleadingJetMass);
    AddVariableConditionally(obj, "TauLTPt", 'F', TauLTPt);
    AddVariableConditionally(obj, "TauNProngs", 'I', TauNProngs);
    AddVariableConditionally(obj, "LeadingJetPt", 'F', LeadingJetPt);
    AddVariableConditionally(obj, "SubLeadingJetPt", 'F', SubLeadingJetPt);
}

void
TLL::MVABase::FillCorrelationsVariables(Branches *branches, const int combo, const Process* iProcess, ::MVABase* iMVA)
{
	FillVariables(branches, combo);

	TLLBranches* event = (TLLBranches*)branches;

	Xsec			= iProcess->GetCrossSection() * iProcess->GetBranchingRatio();
	nGen			= iProcess->GetNOEinDS();
	weight			= event->Ev_puWeight;
	topPtWgt		= event->Ev_topPtWeight;
	lep1TotalSF		= event->TLL_Lepton1EventWeight->at(combo);
	lep2TotalSF		= event->TLL_Lepton2EventWeight->at(combo);
	triggerSF		= 1;
	csvWgtlf		= event->TTL_CSVeventWeight->at(combo);
	csvWgthf		= 1;
	MVAoutput		= iMVA->Evaluate(event, combo);
}

void
TLL::MVABase::FillVariables(Branches *branches, const int combo)
{
    TLLBranches *event = dynamic_cast<TLLBranches*>(branches);

    if (rank > 0 && MVABase::gComboMVA["BDT"]) {
        csr = MVABase::gComboMVA["BDT"]->Evaluate(event, combo);
    } else {
        csr = 0.;
    }

    HT = (*event->TLL_HT)[combo];
    TauPt = (*event->TLL_TauPt)[combo];
    TauEta = abs((*event->TLL_TauEta)[combo]);
    TauDecayMode = (*event->TLL_TauDecayMode)[combo];
    TauIsolationIndex = event->GetTauIsolationIndex(combo);
    TauIsolationIndexMVA2 = event->GetTauIsolationIndexMVA2(combo);
    TauIsolationMVA2Raw = (*event->TLL_TauHPSbyIsolationMVA2raw)[combo];
    TauLTPt = (*event->TLL_TauLTPt)[combo];
    TauNProngs = (*event->TLL_TauNProngs)[combo];

    // Leading and subleading jets are not always present!
    LeadingJetPt = 0.;
    SubLeadingJetPt = 0.;
    try {
        LeadingJetPt = event->J_Pt->at(event->GetJetIndex(combo, 0));
        SubLeadingJetPt = event->J_Pt->at(event->GetJetIndex(combo, 1));
    } catch (...) {
        // std::cerr << combo << "\t" << event->J_Pt->size() << endl;
    }

    float tauEta	= (*event->TLL_TauEta)[combo];
    float tauPhi	= (*event->TLL_TauPhi)[combo];
    float lep1Eta	= (*event->TLL_Lepton1Eta)[combo];
    float lep1Phi	= (*event->TLL_Lepton1Phi)[combo];
    float lep2Eta	= (*event->TLL_Lepton2Eta)[combo];
    float lep2Phi	= (*event->TLL_Lepton2Phi)[combo];

    DeltaRTauLepton1 = DeltaR(tauEta, tauPhi, lep1Eta, lep1Phi);
    DeltaRTauLepton2 = DeltaR(tauEta, tauPhi, lep2Eta, lep2Phi);
    DeltaRLepton1Lepton2 = DeltaR(lep1Eta, lep1Phi, lep2Eta, lep2Phi);

    DeltaRTauLeadingJet			= -99;
    DeltaRTauSubleadingJet		= -99;
    DeltaRLepton1LeadingJet		= -99;
    DeltaRLepton1SubleadingJet	= -99;
    DeltaRLepton2LeadingJet		= -99;
    DeltaRLepton2SubleadingJet	= -99;
    LeadingJetSubleadingJetMass	= -99;

    bool foundLeadingJet = false;
    for(unsigned int j = 0; j < event->J_Pt->size(); j++){
        float pt	= (*event->J_Pt)[j];
        float eta	= (*event->J_Eta)[j];
        float phi	= (*event->J_Phi)[j];
        TLorentzVector leadingJet(0,0,0,0); TLorentzVector subleadingJet(0,0,0,0);
        if(DeltaR(eta, phi, tauEta, tauPhi) < 0.25 || DeltaR(eta, phi, lep2Eta, lep1Phi) < 0.25 || DeltaR(eta, phi, lep2Eta, lep2Phi) < 0.25){ continue; }
        if(!foundLeadingJet){ // Fill leading jet
            DeltaRTauLeadingJet			= DeltaR(eta, phi, tauEta, tauPhi);
            DeltaRLepton1LeadingJet		= DeltaR(eta, phi, lep1Eta, lep1Phi);
            DeltaRLepton2LeadingJet		= DeltaR(eta, phi, lep2Eta, lep2Phi);
            leadingJet.SetPtEtaPhiM(pt, eta, phi, 0);
            foundLeadingJet = true;
        }else{ // Fill subleading jet
            DeltaRTauSubleadingJet			= DeltaR(eta, phi, tauEta, tauPhi);
            DeltaRLepton1SubleadingJet		= DeltaR(eta, phi, lep1Eta, lep1Phi);
            DeltaRLepton2SubleadingJet		= DeltaR(eta, phi, lep2Eta, lep2Phi);
            subleadingJet.SetPtEtaPhiM(pt, eta, phi, 0);
            LeadingJetSubleadingJetMass = (leadingJet + subleadingJet).M();
            break;
        }
    }
}

Branches*
TLL::MVABase::GetBranches(const Process *proc)
{
    return new TLLBranches(proc->GetParams().find("treeName")->second, proc->GetNtuplePaths());
}
