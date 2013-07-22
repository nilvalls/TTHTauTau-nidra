#include "../MVABase.h"

#include "GenHelper.h"
#include "Branches.h"

void
TLLBranches::RegisterCuts(CutFlow& c)
{
    // if(ApplyThisCut("RunNumber"    )){ CutOn_RunNumber     =  true; c.RegisterCut("RunNumber", 1);     }
    // if(ApplyThisCut("LumiSection"    )){ CutOn_LumiSection    =  true; c.RegisterCut("LumiSection", 1);    }
    // if(ApplyThisCut("EventNumber"    )){ CutOn_EventNumber    =  true; c.RegisterCut("EventNumber", 1);    }
    // if(ApplyThisCut("GenMatching"    )){ CutOn_GenMatching    =  true; c.RegisterCut("GenMatching", 1);    }
    // if(ApplyThisCut("NumHadronicGenTaus"  )){ CutOn_NumHadronicGenTaus  =  true; c.RegisterCut("NumHadronicGenTaus", 1);   }
    //   if(selectedEvents.size() > 0){   c.RegisterCut("Run:LS:Event", 1);  }
    // if(ApplyThisCut("InvariantMass"   )){ CutOn_InvariantMass    =  true; c.RegisterCut("InvariantMass", 1);    }
    // if(ApplyThisCut("VisibleMass"    )){ CutOn_VisibleMass    =  true; c.RegisterCut("VisibleMass", 1);    }

    // if(ApplyThisCut("G_NumGenHadTausFromH"  )){ CutOn_G_NumGenHadTausFromH  =  true; c.RegisterCut("G_NumGenHadTausFromH", 1);  }

    c.RegisterCut("T_MatchAbsId", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return abs((*e->TLL_TauGenMatchId)[idx]); }, true);
    c.RegisterCut("T_ParentAbsId", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return abs((*e->TLL_TauGenMatchMother0Id)[idx]); }, true);

    c.RegisterCut("J_NumCSVL", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_NumCSVLbtagJets)[idx]; });
    c.RegisterCut("J_NumCSVM", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_NumCSVMbtagJets)[idx]; });
    c.RegisterCut("J_NumCSVT", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_NumCSVTbtagJets)[idx]; });
    c.RegisterCut("J_NumNonCSVL", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_NumNonCSVLbtagJets)[idx]; });
    c.RegisterCut("J_NumNonCSVM", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_NumNonCSVMbtagJets)[idx]; });
    c.RegisterCut("J_NumNonCSVT", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_NumNonCSVTbtagJets)[idx]; });
    c.RegisterCut("J_NumInclusive", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_NumCSVMbtagJets)[idx] + (*e->TLL_NumNonCSVMbtagJets)[idx]; });
    c.RegisterCut("J_NumCleanCSVL", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_NumCleanCSVLbtagJets)[idx]; });
    c.RegisterCut("J_NumCleanCSVM", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_NumCleanCSVMbtagJets)[idx]; });
    c.RegisterCut("J_NumCleanCSVT", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_NumCleanCSVTbtagJets)[idx]; });
    c.RegisterCut("J_NumCleanNonCSVL", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_NumCleanNonCSVLbtagJets)[idx]; });
    c.RegisterCut("J_NumCleanNonCSVM", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_NumCleanNonCSVMbtagJets)[idx]; });
    c.RegisterCut("J_NumCleanNonCSVT", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_NumCleanNonCSVTbtagJets)[idx]; });
    c.RegisterCut("J_NumCleanInclusive", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_NumCleanCSVMbtagJets)[idx] + (*e->TLL_NumCleanNonCSVMbtagJets)[idx]; });
    c.RegisterCut("NumTightLeptons", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_NumTightMuons)[idx] + (*e->TLL_NumTightElectrons)[idx]; });
    c.RegisterCut("NumTightMuons", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_NumTightMuons)[idx]; });
    c.RegisterCut("NumTightElectrons", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_NumTightElectrons)[idx]; });
    c.RegisterCut("NumLooseLeptons", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_NumLooseMuons)[idx] + (*e->TLL_NumLooseElectrons)[idx]; });
    c.RegisterCut("NumLooseMuons", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_NumLooseMuons)[idx]; });
    c.RegisterCut("NumLooseElectrons", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_NumLooseElectrons)[idx]; });
    c.RegisterCut("NumExLooseLeptons", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_NumExLooseMuons)[idx] + (*e->TLL_NumExLooseElectrons)[idx]; });
    c.RegisterCut("NumExLooseMuons", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_NumExLooseMuons)[idx]; });
    c.RegisterCut("NumExLooseElectrons", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_NumExLooseElectrons)[idx]; });

    c.RegisterCut("L1_pT", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_Lepton1Pt)[idx]; });
    c.RegisterCut("L1_Eta", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_Lepton1Eta)[idx]; });
    c.RegisterCut("L1_IsLoose", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_Lepton1IsLoose)[idx]; });
    c.RegisterCut("L1_IsTight", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_Lepton1IsTight)[idx]; });
    c.RegisterCut("L1_RelIso", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_Lepton1RelIso)[idx]; });

    c.RegisterCut("L2_pT", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_Lepton2Pt)[idx]; });
    c.RegisterCut("L2_Eta", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_Lepton2Eta)[idx]; });
    c.RegisterCut("L2_IsLoose", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_Lepton2IsLoose)[idx]; });
    c.RegisterCut("L2_IsTight", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_Lepton2IsTight)[idx]; });
    c.RegisterCut("L2_RelIso", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_Lepton2RelIso)[idx]; });

    c.RegisterCut("T_pT", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_TauPt)[idx]; });
    c.RegisterCut("T_Eta", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_TauEta)[idx]; });
    c.RegisterCut("T_InCracks", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_TauIsInTheCracks)[idx]; });


    c.RegisterCut("LL_DeltaR", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return DeltaR((*e->TLL_Lepton1Eta)[idx], (*e->TLL_Lepton1Phi)[idx],
                (*e->TLL_Lepton2Eta)[idx], (*e->TLL_Lepton2Phi)[idx]); });
    c.RegisterCut("TL1_DeltaR", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return DeltaR((*e->TLL_TauEta)[idx], (*e->TLL_TauPhi)[idx],
                (*e->TLL_Lepton1Eta)[idx], (*e->TLL_Lepton1Phi)[idx]); });
    c.RegisterCut("TL2_DeltaR", 2, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return DeltaR((*e->TLL_TauEta)[idx], (*e->TLL_TauPhi)[idx],
                (*e->TLL_Lepton2Eta)[idx], (*e->TLL_Lepton2Phi)[idx]); });

    c.RegisterCut("T_DecayModeFinding", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_TauHPSdecayModeFinding)[idx]; });
    c.RegisterCut("T_LTvalid", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_TauLTvalid)[idx]; });
    c.RegisterCut("T_LTpT", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_TauLTPt)[idx]; });
    c.RegisterCut("T_NumProngs", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_TauNProngs)[idx]; });

    c.RegisterCut("T_AntiElectronMVA", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_TauHPSagainstElectronMVA)[idx]; });
    c.RegisterCut("T_AntiElectronIndex", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return e->GetTauAntiElectronIndex(idx); });
    c.RegisterCut("T_AntiMuonIndex", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return e->GetTauAntiMuonIndex(idx); });

    c.RegisterCut("T_IsolationIndex", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return e->GetTauIsolationIndex(idx); });
    c.RegisterCut("T_IsolationIndex3Hits", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return e->GetTauIsolationIndex3Hits(idx); });
    c.RegisterCut("T_IsolationIndexMVA", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return e->GetTauIsolationIndexMVA(idx); });
    c.RegisterCut("T_IsolationIndexMVA2", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return e->GetTauIsolationIndexMVA2(idx); });
    c.RegisterCut("T_IsolationMVA2Raw", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return (*e->TLL_TauHPSbyIsolationMVA2raw)[idx]; });

    c.RegisterCut("MET", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return e->Ev_MET; });
    c.RegisterCut("MVA", 1, [](Branches *b, const int& idx) -> float {
            TLLBranches* e = dynamic_cast<TLLBranches*>(b);
            return MVABase::gMVA["CFMlpANN"] ? MVABase::gMVA["CFMlpANN"]->Evaluate(e, idx) : 0.; });
}
