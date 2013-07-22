
float weightFull	= iLepton1Weight*iLepton2Weight*iPuWeight*iTauIdSysWeight*iQ2SysWeight*iTopPtWeight;

// GenMatching =========================================================================================================================
//hContainer->Fill("MatchedTo_T", event->TauMatchedTo(iCombo) , weightFull);

// General =========================================================================================================================
hContainer->Fill("Events", 0, weightFull);
hContainer->Fill("MomentumRank", (*event->TLL_MomentumRank)[iCombo], weightFull);
hContainer->Fill("MET", event->Ev_MET, weightFull);
hContainer->Fill("HT", (*event->TLL_HT)[iCombo], weightFull);
if (auto mva = MVABase::gMVA["CFMlpANN"])
    hContainer->Fill("FinalCFMlpANN", mva->Evaluate(event, iCombo), weightFull);
if (auto mva = MVABase::gMVA["BDTG"])
    hContainer->Fill("FinalBDTG", mva->Evaluate(event, iCombo), weightFull);
if (auto mva = MVABase::gComboMVA["BDT"])
    hContainer->Fill("ComboBDT", mva->Evaluate(event, iCombo), weightFull);
hContainer->Fill("SelectedComboRank", iCombo, weightFull);

if(iPuWeight!=0){
	hContainer->Fill("NumberPV_noPURW", event->V_NumVertices, weightFull/iPuWeight);
	hContainer->Fill("NumberBXm1_noPURW", event->V_NumInteractionsBXm1, weightFull/iPuWeight);
	hContainer->Fill("NumberBX0_noPURW", event->V_NumInteractionsBX0, weightFull/iPuWeight);
	hContainer->Fill("NumberBXp1_noPURW", event->V_NumInteractionsBXp1, weightFull/iPuWeight);
	hContainer->Fill("PUweights_noPURW", iPuWeight, weightFull/iPuWeight);
}else{
	//cout << "zero found in iPUweight, numBX: " << event->V_numInteractionsBX0 << endl;
}

if(IsFlagThere("PUcorr")){
    hContainer->Fill("NumberPV_afterPURW", event->V_NumVertices, weightFull);
    hContainer->Fill("NumberBXm1_afterPURW", event->V_NumInteractionsBXm1, weightFull);
    hContainer->Fill("NumberBX0_afterPURW", event->V_NumInteractionsBX0, weightFull);
    hContainer->Fill("NumberBXp1_afterPURW", event->V_NumInteractionsBXp1, weightFull);
    hContainer->Fill("PUweights_afterPURW", iPuWeight, weightFull);
   
    for( vector<float>::const_iterator vertexIt = event->V_Zcoord->begin(); vertexIt != event->V_Zcoord->end(); ++vertexIt ) {
        hContainer->Fill("VertexZcoord_afterPURW", *vertexIt,weightFull);
    }
}


// Taus ============================================================================================================================
hContainer->Fill("NumTaus", event->TLL_NumTaus, weightFull);
hContainer->Fill("Pt_T", (*event->TLL_TauPt)[iCombo], weightFull);
hContainer->Fill("Eta_T", (*event->TLL_TauEta)[iCombo], weightFull);
hContainer->Fill("Phi_T", (*event->TLL_TauPhi)[iCombo], weightFull);
hContainer->Fill("DecayMode_T", (*event->TLL_TauDecayMode)[iCombo], weightFull);
hContainer->Fill("LTPt_T", (*event->TLL_TauLTPt)[iCombo], weightFull);
hContainer->Fill("NProngs_T", (*event->TLL_TauNProngs)[iCombo], weightFull);
hContainer->Fill("IsolationIndex_T", event->GetTauIsolationIndex(iCombo), weightFull);
hContainer->Fill("IsolationIndexMVA_T", event->GetTauIsolationIndexMVA(iCombo), weightFull);
hContainer->Fill("IsolationIndexMVA2_T", event->GetTauIsolationIndexMVA2(iCombo), weightFull);
hContainer->Fill("IsolationIndex3Hits_T", event->GetTauIsolationIndex3Hits(iCombo), weightFull);
hContainer->Fill("CombIsoDBcorrRaw_T", (*event->TLL_TauHPSbyCombinedIsolationDeltaBetaCorrRaw)[iCombo], weightFull);
hContainer->Fill("CombIsoDBcorrRaw3Hits_T", (*event->TLL_TauHPSbyCombinedIsolationDeltaBetaCorrRaw3Hits)[iCombo], weightFull);
hContainer->Fill("IsolationMVAraw_T", (*event->TLL_TauHPSbyIsolationMVAraw)[iCombo], weightFull);
hContainer->Fill("IsolationMVA2raw_T", (*event->TLL_TauHPSbyIsolationMVA2raw)[iCombo], weightFull);
hContainer->Fill("AntiElectronIndex_T", event->GetTauAntiElectronIndex(iCombo), weightFull);
hContainer->Fill("AntiElectronIndexMVA2_T", event->GetTauAntiElectronIndexMVA2(iCombo), weightFull);
hContainer->Fill("AntiElectronIndexMVA3_T", event->GetTauAntiElectronIndexMVA3(iCombo), weightFull);
hContainer->Fill("AgainstElectronMVA_T", (*event->TLL_TauHPSagainstElectronMVA)[iCombo], weightFull);
hContainer->Fill("AgainstElectronMVA2raw_T", (*event->TLL_TauHPSagainstElectronMVA2raw)[iCombo], weightFull);
hContainer->Fill("AgainstElectronMVA3raw_T", (*event->TLL_TauHPSagainstElectronMVA3raw)[iCombo], weightFull);
hContainer->Fill("AgainstElectronMVA2category_T", (*event->TLL_TauHPSagainstElectronMVA2category)[iCombo], weightFull);
hContainer->Fill("AgainstElectronMVA3category_T", (*event->TLL_TauHPSagainstElectronMVA3category)[iCombo], weightFull);
hContainer->Fill("AgainstElectronDeadECAL_T", (*event->TLL_TauHPSagainstElectronDeadECAL)[iCombo], weightFull);
hContainer->Fill("AntiMuonIndex_T", event->GetTauAntiMuonIndex(iCombo), weightFull);
hContainer->Fill("AntiMuonIndex2_T", event->GetTauAntiMuonIndex2(iCombo), weightFull);
hContainer->Fill("Match_T", event->GetTauMatchIndex(iCombo), weightFull);

// Lepton1 ============================================================================================================================
hContainer->Fill("Pt_L1", (*event->TLL_Lepton1Pt)[iCombo], weightFull);
hContainer->Fill("Eta_L1", (*event->TLL_Lepton1Eta)[iCombo], weightFull);
hContainer->Fill("Phi_L1", (*event->TLL_Lepton1Phi)[iCombo], weightFull);
hContainer->Fill("NumTightMuons", (*event->TLL_NumTightMuons)[iCombo], weightFull);
hContainer->Fill("NumLooseMuons", (*event->TLL_NumLooseMuons)[iCombo], weightFull);
hContainer->Fill("NumExLooseMuons", (*event->TLL_NumExLooseMuons)[iCombo], weightFull);
hContainer->Fill("NumTightElectrons", (*event->TLL_NumTightElectrons)[iCombo], weightFull);
hContainer->Fill("NumLooseElectrons", (*event->TLL_NumLooseElectrons)[iCombo], weightFull);
hContainer->Fill("NumExLooseElectrons", (*event->TLL_NumExLooseElectrons)[iCombo], weightFull);
hContainer->Fill("NumTightLeptons",		(*event->TLL_NumTightMuons)[iCombo]	+	(*event->TLL_NumTightElectrons)[iCombo]	, weightFull);
hContainer->Fill("NumLooseLeptons",		(*event->TLL_NumLooseMuons)[iCombo]	+	(*event->TLL_NumLooseElectrons)[iCombo]	, weightFull);
hContainer->Fill("NumExLooseLeptons",	(*event->TLL_NumExLooseMuons)[iCombo]	+	(*event->TLL_NumExLooseElectrons)[iCombo]	, weightFull);
hContainer->Fill("DeltaR_L1T", DeltaR((*event->TLL_Lepton1Eta)[iCombo], (*event->TLL_Lepton1Phi)[iCombo], (*event->TLL_TauEta)[iCombo], (*event->TLL_TauPhi)[iCombo]), weightFull);

// Lepton2 ============================================================================================================================
hContainer->Fill("Pt_L2", (*event->TLL_Lepton2Pt)[iCombo], weightFull);
hContainer->Fill("Eta_L2", (*event->TLL_Lepton2Eta)[iCombo], weightFull);
hContainer->Fill("Phi_L2", (*event->TLL_Lepton2Phi)[iCombo], weightFull);
hContainer->Fill("NumTightMuons", (*event->TLL_NumTightMuons)[iCombo], weightFull);
hContainer->Fill("NumLooseMuons", (*event->TLL_NumLooseMuons)[iCombo], weightFull);
hContainer->Fill("NumExLooseMuons", (*event->TLL_NumExLooseMuons)[iCombo], weightFull);
hContainer->Fill("NumTightElectrons", (*event->TLL_NumTightElectrons)[iCombo], weightFull);
hContainer->Fill("NumLooseElectrons", (*event->TLL_NumLooseElectrons)[iCombo], weightFull);
hContainer->Fill("NumExLooseElectrons", (*event->TLL_NumExLooseElectrons)[iCombo], weightFull);
hContainer->Fill("NumTightLeptons",		(*event->TLL_NumTightMuons)[iCombo]	+	(*event->TLL_NumTightElectrons)[iCombo]	, weightFull);
hContainer->Fill("NumLooseLeptons",		(*event->TLL_NumLooseMuons)[iCombo]	+	(*event->TLL_NumLooseElectrons)[iCombo]	, weightFull);
hContainer->Fill("NumExLooseLeptons",	(*event->TLL_NumExLooseMuons)[iCombo]	+	(*event->TLL_NumExLooseElectrons)[iCombo]	, weightFull);
hContainer->Fill("DeltaR_L2T", DeltaR((*event->TLL_Lepton2Eta)[iCombo], (*event->TLL_Lepton2Phi)[iCombo], (*event->TLL_TauEta)[iCombo], (*event->TLL_TauPhi)[iCombo]), weightFull);

/*
// Jets ============================================================================================================================
// tau/jet matching con size
try {
    unsigned int ljet = event->GetJetIndex(iCombo, 0);
    hContainer->Fill("LeadingJet_Pt", event->J_Pt->at(ljet), weightFull);
    hContainer->Fill("LeadingJet_Eta", event->J_Eta->at(ljet), weightFull);
    hContainer->Fill("DeltaR_LJ1", DeltaR((*event->TTL_LeptonEta)[iCombo], (*event->TTL_LeptonPhi)[iCombo], event->J_Eta->at(ljet), event->J_Phi->at(ljet)), weightFull);
    hContainer->Fill("DeltaR_T1J1", DeltaR((*event->TTL_Tau1Eta)[iCombo], (*event->TTL_Tau1Phi)[iCombo], event->J_Eta->at(ljet), event->J_Phi->at(ljet)), weightFull);
    hContainer->Fill("DeltaR_T2J1", DeltaR((*event->TTL_Tau2Eta)[iCombo], (*event->TTL_Tau2Phi)[iCombo], event->J_Eta->at(ljet), event->J_Phi->at(ljet)), weightFull);

    unsigned int sljet = event->GetJetIndex(iCombo, 1);
    hContainer->Fill("SubLeadingJet_Pt", event->J_Pt->at(sljet), weightFull);
    hContainer->Fill("SubLeadingJet_Eta", event->J_Eta->at(sljet), weightFull);
    hContainer->Fill("DeltaR_LJ2", DeltaR((*event->TTL_LeptonEta)[iCombo], (*event->TTL_LeptonPhi)[iCombo], event->J_Eta->at(sljet), event->J_Phi->at(sljet)), weightFull);
    hContainer->Fill("DeltaR_T1J2", DeltaR((*event->TTL_Tau1Eta)[iCombo], (*event->TTL_Tau1Phi)[iCombo], event->J_Eta->at(sljet), event->J_Phi->at(sljet)), weightFull);
    hContainer->Fill("DeltaR_T2J2", DeltaR((*event->TTL_Tau2Eta)[iCombo], (*event->TTL_Tau2Phi)[iCombo], event->J_Eta->at(sljet), event->J_Phi->at(sljet)), weightFull);

    unsigned int ssljet = event->GetJetIndex(iCombo, 2);
    hContainer->Fill("SubSubLeadingJet_Pt", event->J_Pt->at(ssljet), weightFull);
    hContainer->Fill("SubSubLeadingJet_Eta", event->J_Eta->at(ssljet), weightFull);

    unsigned int sssljet = event->GetJetIndex(iCombo, 3);
    hContainer->Fill("SubSubLeadingJet_Pt", event->J_Pt->at(sssljet), weightFull);
    hContainer->Fill("SubSubLeadingJet_Eta", event->J_Eta->at(sssljet), weightFull);
} catch (...) {}

float conesize = .25;
for (unsigned int i = 0, c = 0; c < 2 and i < event->J_Pt->size(); i++) {
    if ((DeltaR((*event->J_Eta)[i], (*event->J_Phi)[i], (*event->TTL_Tau1Eta)[iCombo], (*event->TTL_Tau1Phi)[iCombo]) > conesize) &&
            (DeltaR((*event->J_Eta)[i], (*event->J_Phi)[i], (*event->TTL_Tau2Eta)[iCombo], (*event->TTL_Tau2Phi)[iCombo]) > conesize) &&
            (DeltaR((*event->J_Eta)[i], (*event->J_Phi)[i], (*event->TTL_LeptonEta)[iCombo], (*event->TTL_LeptonPhi)[iCombo]) > conesize)) {
        if ((*event->J_combSecVtxMediumBTag)[i]) {
           hContainer->Fill("BTagJet_Pt", (*event->J_Pt)[i], weightFull);
           hContainer->Fill("BTagJet_Eta", (*event->J_Eta)[i], weightFull);
        } else {
           hContainer->Fill("NonBTagJet_Pt", (*event->J_Pt)[i], weightFull);
           hContainer->Fill("NonBTagJet_Eta", (*event->J_Eta)[i], weightFull);
        }

        ++c;
    }
}

hContainer->Fill("NumCSVLbtags", (*event->TTL_NumCSVLbtagJets)[iCombo], weightFull);
hContainer->Fill("NumCSVMbtags", (*event->TTL_NumCSVMbtagJets)[iCombo], weightFull);
hContainer->Fill("NumCSVTbtags", (*event->TTL_NumCSVTbtagJets)[iCombo], weightFull);
hContainer->Fill("NumCSVLnonBtags", (*event->TTL_NumNonCSVLbtagJets)[iCombo], weightFull);
hContainer->Fill("NumCSVMnonBtags", (*event->TTL_NumNonCSVMbtagJets)[iCombo], weightFull);
hContainer->Fill("NumCSVTnonBtags", (*event->TTL_NumNonCSVTbtagJets)[iCombo], weightFull);
hContainer->Fill("NumCSVnonHTauJets", ((*event->TTL_NumNonCSVMbtagJets)[iCombo] + (*event->TTL_NumCSVMbtagJets)[iCombo]), weightFull);
hContainer->Fill("NumCleanCSVLbtags", (*event->TTL_NumCleanCSVLbtagJets)[iCombo], weightFull);
hContainer->Fill("NumCleanCSVMbtags", (*event->TTL_NumCleanCSVMbtagJets)[iCombo], weightFull);
hContainer->Fill("NumCleanCSVTbtags", (*event->TTL_NumCleanCSVTbtagJets)[iCombo], weightFull);
hContainer->Fill("NumCleanCSVLnonBtags", (*event->TTL_NumCleanNonCSVLbtagJets)[iCombo], weightFull);
hContainer->Fill("NumCleanCSVMnonBtags", (*event->TTL_NumCleanNonCSVMbtagJets)[iCombo], weightFull);
hContainer->Fill("NumCleanCSVTnonBtags", (*event->TTL_NumCleanNonCSVTbtagJets)[iCombo], weightFull);
hContainer->Fill("NumCleanCSVnonHTauJets", ((*event->TTL_NumCleanNonCSVMbtagJets)[iCombo] + (*event->TTL_NumCleanCSVMbtagJets)[iCombo]), weightFull);
hContainer->Fill("NumInclusiveJets", ((*event->TTL_NumCleanNonCSVMbtagJets)[iCombo] + (*event->TTL_NumCleanCSVMbtagJets)[iCombo]) + 2, weightFull);

//*/
