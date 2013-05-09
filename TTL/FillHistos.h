float weightFull	= iLeptonWeight*iPuWeight*iTau1TriggerWeight*iTau2TriggerWeight*iTauIdSysWeight*iQ2SysWeight*iTopPtWeight;
float weightTrigger = iTau1TriggerWeight*iTau2TriggerWeight;
float weightTau1	= iPuWeight*iTau1TriggerWeight;
float weightTau2	= iPuWeight*iTau1TriggerWeight;

// GenMatching =========================================================================================================================
//hContainer->Fill("MatchedTo_T1", event->Tau1MatchedTo(iCombo) , weightFull);
//hContainer->Fill("MatchedTo_T2", event->Tau2MatchedTo(iCombo) , weightFull);

// General =========================================================================================================================
hContainer->Fill("Events", 0, weightFull);
hContainer->Fill("MomentumRank", (*event->TTL_MomentumRank)[iCombo], weightFull);
hContainer->Fill("MET", event->Ev_MET, weightFull);
hContainer->Fill("HT", (*event->TTL_HT)[iCombo], weightFull);
if (auto mva = TTL_TMVAEvaluator::gMVA["CFMlpANN"])
    hContainer->Fill("FinalCFMlpANN", mva->Evaluate(event, iCombo), weightFull);
if (auto mva = TTL_TMVAEvaluator::gMVA["BDTG"])
    hContainer->Fill("FinalBDTG", mva->Evaluate(event, iCombo), weightFull);
if (auto mva = TTL_TMVAEvaluator::gComboMVA["BDT"])
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
hContainer->Fill("ChargeProduct_TT", ((*event->TTL_Tau1Charge)[iCombo] * (*event->TTL_Tau2Charge)[iCombo]), weightFull);

// Taus ============================================================================================================================
hContainer->Fill("NumTaus", event->TTL_NumTaus, weightFull);
hContainer->Fill("VisibleMass_TT", (*event->TTL_DitauVisibleMass)[iCombo], weightFull);
hContainer->Fill("DeltaR_TT", (*event->TTL_DitauDeltaR)[iCombo], weightFull);
hContainer->Fill("Pt_T1", (*event->TTL_Tau1Pt)[iCombo], weightFull);
hContainer->Fill("Pt_T2", (*event->TTL_Tau2Pt)[iCombo], weightFull);
hContainer->Fill("Eta_T1", (*event->TTL_Tau1Eta)[iCombo], weightFull);
hContainer->Fill("Eta_T2", (*event->TTL_Tau2Eta)[iCombo], weightFull);
hContainer->Fill("Phi_T1", (*event->TTL_Tau1Phi)[iCombo], weightFull);
hContainer->Fill("Phi_T2", (*event->TTL_Tau2Phi)[iCombo], weightFull);
hContainer->Fill("DecayMode_T1", (*event->TTL_Tau1DecayMode)[iCombo], weightFull);
hContainer->Fill("DecayMode_T2", (*event->TTL_Tau2DecayMode)[iCombo], weightFull);
hContainer->Fill("LTPt_T1", (*event->TTL_Tau1LTPt)[iCombo], weightFull);
hContainer->Fill("LTPt_T2", (*event->TTL_Tau2LTPt)[iCombo], weightFull);
hContainer->Fill("NProngs_T1", (*event->TTL_Tau1NProngs)[iCombo], weightFull);
hContainer->Fill("NProngs_T2", (*event->TTL_Tau2NProngs)[iCombo], weightFull);
hContainer->Fill("IsolationIndex_T1", event->GetTau1IsolationIndex(iCombo), weightFull);
hContainer->Fill("IsolationIndex_T2", event->GetTau2IsolationIndex(iCombo), weightFull);
hContainer->Fill("IsolationIndexMVA_T1", event->GetTau1IsolationIndexMVA(iCombo), weightFull);
hContainer->Fill("IsolationIndexMVA_T2", event->GetTau2IsolationIndexMVA(iCombo), weightFull);
hContainer->Fill("IsolationIndexMVA2_T1", event->GetTau1IsolationIndexMVA2(iCombo), weightFull);
hContainer->Fill("IsolationIndexMVA2_T2", event->GetTau2IsolationIndexMVA2(iCombo), weightFull);
hContainer->Fill("IsolationIndex3Hits_T1", event->GetTau1IsolationIndex3Hits(iCombo), weightFull);
hContainer->Fill("IsolationIndex3Hits_T2", event->GetTau2IsolationIndex3Hits(iCombo), weightFull);
hContainer->Fill("CombIsoDBcorrRaw_T1", (*event->TTL_Tau1HPSbyCombinedIsolationDeltaBetaCorrRaw)[iCombo], weightFull);
hContainer->Fill("CombIsoDBcorrRaw_T2", (*event->TTL_Tau2HPSbyCombinedIsolationDeltaBetaCorrRaw)[iCombo], weightFull);
hContainer->Fill("CombIsoDBcorrRaw3Hits_T1", (*event->TTL_Tau1HPSbyCombinedIsolationDeltaBetaCorrRaw3Hits)[iCombo], weightFull);
hContainer->Fill("CombIsoDBcorrRaw3Hits_T2", (*event->TTL_Tau2HPSbyCombinedIsolationDeltaBetaCorrRaw3Hits)[iCombo], weightFull);
hContainer->Fill("IsolationMVAraw_T1", (*event->TTL_Tau1HPSbyIsolationMVAraw)[iCombo], weightFull);
hContainer->Fill("IsolationMVAraw_T2", (*event->TTL_Tau2HPSbyIsolationMVAraw)[iCombo], weightFull);
hContainer->Fill("IsolationMVA2raw_T1", (*event->TTL_Tau1HPSbyIsolationMVA2raw)[iCombo], weightFull);
hContainer->Fill("IsolationMVA2raw_T2", (*event->TTL_Tau2HPSbyIsolationMVA2raw)[iCombo], weightFull);
hContainer->Fill("AntiElectronIndex_T1", event->GetTau1AntiElectronIndex(iCombo), weightFull);
hContainer->Fill("AntiElectronIndex_T2", event->GetTau2AntiElectronIndex(iCombo), weightFull);
hContainer->Fill("AntiElectronIndexMVA2_T1", event->GetTau1AntiElectronIndexMVA2(iCombo), weightFull);
hContainer->Fill("AntiElectronIndexMVA2_T2", event->GetTau2AntiElectronIndexMVA2(iCombo), weightFull);
hContainer->Fill("AntiElectronIndexMVA3_T1", event->GetTau1AntiElectronIndexMVA3(iCombo), weightFull);
hContainer->Fill("AntiElectronIndexMVA3_T2", event->GetTau2AntiElectronIndexMVA3(iCombo), weightFull);
hContainer->Fill("AgainstElectronMVA_T1", (*event->TTL_Tau1HPSagainstElectronMVA)[iCombo], weightFull);
hContainer->Fill("AgainstElectronMVA_T2", (*event->TTL_Tau2HPSagainstElectronMVA)[iCombo], weightFull);
hContainer->Fill("AgainstElectronMVA2raw_T1", (*event->TTL_Tau1HPSagainstElectronMVA2raw)[iCombo], weightFull);
hContainer->Fill("AgainstElectronMVA2raw_T2", (*event->TTL_Tau2HPSagainstElectronMVA2raw)[iCombo], weightFull);
hContainer->Fill("AgainstElectronMVA3raw_T1", (*event->TTL_Tau1HPSagainstElectronMVA3raw)[iCombo], weightFull);
hContainer->Fill("AgainstElectronMVA3raw_T2", (*event->TTL_Tau2HPSagainstElectronMVA3raw)[iCombo], weightFull);
hContainer->Fill("AgainstElectronMVA2category_T1", (*event->TTL_Tau1HPSagainstElectronMVA2category)[iCombo], weightFull);
hContainer->Fill("AgainstElectronMVA2category_T2", (*event->TTL_Tau2HPSagainstElectronMVA2category)[iCombo], weightFull);
hContainer->Fill("AgainstElectronMVA3category_T1", (*event->TTL_Tau1HPSagainstElectronMVA3category)[iCombo], weightFull);
hContainer->Fill("AgainstElectronMVA3category_T2", (*event->TTL_Tau2HPSagainstElectronMVA3category)[iCombo], weightFull);
hContainer->Fill("AgainstElectronDeadECAL_T1", (*event->TTL_Tau1HPSagainstElectronDeadECAL)[iCombo], weightFull);
hContainer->Fill("AgainstElectronDeadECAL_T2", (*event->TTL_Tau2HPSagainstElectronDeadECAL)[iCombo], weightFull);
hContainer->Fill("AntiMuonIndex_T1", event->GetTau1AntiMuonIndex(iCombo), weightFull);
hContainer->Fill("AntiMuonIndex_T2", event->GetTau2AntiMuonIndex(iCombo), weightFull);
hContainer->Fill("AntiMuonIndex2_T1", event->GetTau1AntiMuonIndex2(iCombo), weightFull);
hContainer->Fill("AntiMuonIndex2_T2", event->GetTau2AntiMuonIndex2(iCombo), weightFull);
hContainer->Fill("Match_T1", event->GetTau1MatchIndex(iCombo), weightFull);
hContainer->Fill("Match_T2", event->GetTau2MatchIndex(iCombo), weightFull);

// Lepton ============================================================================================================================
hContainer->Fill("Pt_L", (*event->TTL_LeptonPt)[iCombo], weightFull);
hContainer->Fill("Eta_L", (*event->TTL_LeptonEta)[iCombo], weightFull);
hContainer->Fill("Phi_L", (*event->TTL_LeptonPhi)[iCombo], weightFull);
hContainer->Fill("NumTightMuons", (*event->TTL_NumTightMuons)[iCombo], weightFull);
hContainer->Fill("NumLooseMuons", (*event->TTL_NumLooseMuons)[iCombo], weightFull);
hContainer->Fill("NumExLooseMuons", (*event->TTL_NumExLooseMuons)[iCombo], weightFull);
hContainer->Fill("NumTightElectrons", (*event->TTL_NumTightElectrons)[iCombo], weightFull);
hContainer->Fill("NumLooseElectrons", (*event->TTL_NumLooseElectrons)[iCombo], weightFull);
hContainer->Fill("NumExLooseElectrons", (*event->TTL_NumExLooseElectrons)[iCombo], weightFull);
hContainer->Fill("NumTightLeptons",		(*event->TTL_NumTightMuons)[iCombo]	+	(*event->TTL_NumTightElectrons)[iCombo]	, weightFull);
hContainer->Fill("NumLooseLeptons",		(*event->TTL_NumLooseMuons)[iCombo]	+	(*event->TTL_NumLooseElectrons)[iCombo]	, weightFull);
hContainer->Fill("NumExLooseLeptons",	(*event->TTL_NumExLooseMuons)[iCombo]	+	(*event->TTL_NumExLooseElectrons)[iCombo]	, weightFull);
hContainer->Fill("DeltaR_LT1", DeltaR((*event->TTL_LeptonEta)[iCombo], (*event->TTL_LeptonPhi)[iCombo], (*event->TTL_Tau1Eta)[iCombo], (*event->TTL_Tau1Phi)[iCombo]), weightFull);
hContainer->Fill("DeltaR_LT2", DeltaR((*event->TTL_LeptonEta)[iCombo], (*event->TTL_LeptonPhi)[iCombo], (*event->TTL_Tau2Eta)[iCombo], (*event->TTL_Tau2Phi)[iCombo]), weightFull);

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

/*
hContainer->Fill("CosDeltaPhi_LM", (*event->Tau1MetCosDphi)[iCombo], weightFull);
hContainer->Fill("CosDeltaPhi_SM", (*event->Tau2MetCosDphi)[iCombo], weightFull);
hContainer->Fill("DeltaPhi_LM", acos((*event->Tau1MetCosDphi)[iCombo]), weightFull);
hContainer->Fill("DeltaPhi_SM", acos((*event->Tau2MetCosDphi)[iCombo]), weightFull);
hContainer->Fill("SumETotherJets", (*event->jetSumEt)[iCombo], weightFull);
hContainer->Fill("SumETotherJetsPlusMET", (*event->jetMETSumEt)[iCombo], weightFull);
hContainer->Fill("NumOtherJets", (*event->nJets)[iCombo], weightFull);
hContainer->Fill("EmFraction_LS", (*event->Tau1EmFraction)[iCombo], weightFull);
hContainer->Fill("EmFraction_LS", (*event->Tau2EmFraction)[iCombo], weightFull);

hContainer->Fill("AbsDeltaEta_LS", fabs(((*event->Tau1Eta)[iCombo])-((*event->Tau2Eta)[iCombo])), weightFull);
hContainer->Fill("CosDeltaPhi_LS", (*event->TauTauCosDPhi)[iCombo], weightFull);
hContainer->Fill("CosDeltaEta_LS", cos(fabs((*event->Tau1Eta)[iCombo]-(*event->Tau2Eta)[iCombo])), weightFull);
hContainer->Fill("DeltaPhi_LS", acos(cos((*event->Tau1Phi)[iCombo]-(*event->Tau2Phi)[iCombo])), weightFull);
hContainer->Fill("DeltaEta_LS", fabs((*event->Tau1Eta)[iCombo]-(*event->Tau2Eta)[iCombo]), weightFull);
hContainer->Fill("DeltaR_LS", (*event->TauTauDeltaR)[iCombo], weightFull);
hContainer->Fill("LTNumHits_LS", (*event->Tau1LTValidHits)[iCombo], weightFull);
hContainer->Fill("LTNumHits_LS", (*event->Tau2LTValidHits)[iCombo], weightFull);
hContainer->Fill("PZeta_LSM", (*event->TauTauPZeta)[iCombo], weightFull);
hContainer->Fill("PZetaVis_LSM", (*event->TauTauPZetaVis)[iCombo], weightFull);
hContainer->Fill("Zeta_LSM", ((*event->TauTauPZeta)[iCombo]-0.875*(*event->TauTauPZetaVis)[iCombo]), weightFull);

//hContainer->Fill("PUweightsPassingEvents", event->puCorrector->GetWeight(NumPV->at(iCombo), weightFull);


int DDMI = -1; 
if((*event->Tau1DecayMode)[iCombo]<0 || (*event->Tau2DecayMode)[iCombo]<0){ DDMI = -1; }
else if((*event->Tau1DecayMode)[iCombo]==0 && (*event->Tau2DecayMode)[iCombo]==0){ DDMI = 0; }
else if( 
		((*event->Tau1DecayMode)[iCombo]==0 && (*event->Tau2DecayMode)[iCombo] == 1) ||
		((*event->Tau1DecayMode)[iCombo]==0 && (*event->Tau2DecayMode)[iCombo] == 2) ||
		((*event->Tau1DecayMode)[iCombo]==0 && (*event->Tau2DecayMode)[iCombo] == 3) ||
		((*event->Tau1DecayMode)[iCombo]==0 && (*event->Tau2DecayMode)[iCombo] == 4) ||
		((*event->Tau1DecayMode)[iCombo]==1 && (*event->Tau2DecayMode)[iCombo] == 0) ||
		((*event->Tau1DecayMode)[iCombo]==2 && (*event->Tau2DecayMode)[iCombo] == 0) ||
		((*event->Tau1DecayMode)[iCombo]==3 && (*event->Tau2DecayMode)[iCombo] == 0) ||
		((*event->Tau1DecayMode)[iCombo]==4 && (*event->Tau2DecayMode)[iCombo] == 0) ){ DDMI = 1; }
else if( 
		((*event->Tau1DecayMode)[iCombo]==0 && (*event->Tau2DecayMode)[iCombo]>=10) ||
		((*event->Tau1DecayMode)[iCombo]>=10 && (*event->Tau2DecayMode)[iCombo]==0) ){ DDMI = 2; }
else{ DDMI = 3; }
hContainer->Fill("DDMI", DDMI, weightFull);

int DTMI = -1; 
if(((*event->Tau1NProngs)[iCombo]<1) || ((*event->Tau2NProngs)[iCombo]<1)){ DTMI = -1; }
else if((*event->Tau1NProngs)[iCombo]==1 && (*event->Tau2NProngs)[iCombo]==1){ DTMI = 0; }
else if(((*event->Tau1NProngs)[iCombo]==1 && (*event->Tau2NProngs)[iCombo]==3) || ((*event->Tau2NProngs)[iCombo]==1 && (*event->Tau1NProngs)[iCombo]==3)){ DTMI = 1; }
else if((*event->Tau1NProngs)[iCombo]==3 && (*event->Tau2NProngs)[iCombo]==3){ DTMI = 2; }
else{ DTMI = 3; }
hContainer->Fill("DTMI", DTMI, weightFull);

// Vertex-track stuff
hContainer->Fill("LTdxy_L", ((*event->Tau1LTIpVtdxy)[iCombo]), weightFull);
hContainer->Fill("LTdxy_S", ((*event->Tau2LTIpVtdxy)[iCombo]), weightFull);
hContainer->Fill("LTdz_L", ((*event->Tau1LTIpVtdz)[iCombo]), weightFull);
hContainer->Fill("LTdz_S", ((*event->Tau2LTIpVtdz)[iCombo]), weightFull);
hContainer->Fill("DeltaLTdz_LS", ((*event->Tau1LTIpVtdz)[iCombo]-(*event->Tau2LTIpVtdz)[iCombo]), weightFull);


hContainer->Fill("SigLTdz_L", ((*event->Tau1LTIpVtdz)[iCombo])/(*event->Tau1LTIpVtdzError)[iCombo], weightFull);
hContainer->Fill("SigLTdz_S", ((*event->Tau2LTIpVtdz)[iCombo])/(*event->Tau2LTIpVtdzError)[iCombo], weightFull);

hContainer->Fill("SigLTdxy_L", ((*event->Tau1LTIpVtdxy)[iCombo])/(*event->Tau1LTIpVtdxyError)[iCombo], weightFull);
hContainer->Fill("SigLTdxy_S", ((*event->Tau2LTIpVtdxy)[iCombo])/(*event->Tau2LTIpVtdxyError)[iCombo], weightFull);

double a1 = (*event->Tau1LTIpVtdxy)[iCombo];
double b1 = (*event->Tau1LTIpVtdz)[iCombo];
double da1 = (*event->Tau1LTIpVtdxyError)[iCombo];
double db1 = (*event->Tau1LTIpVtdzError)[iCombo];
double error1 = sqrt((pow(a1*da1,2)+pow(b1*db1,2))/(pow(a1,2)+pow(b1,2)));
double a2 = (*event->Tau2LTIpVtdxy)[iCombo];
double b2 = (*event->Tau2LTIpVtdz)[iCombo];
double da2 = (*event->Tau2LTIpVtdxyError)[iCombo];
double db2 = (*event->Tau2LTIpVtdzError)[iCombo];
double error2 = sqrt((pow(a2*da2,2)+pow(b2*db2,2))/(pow(a2,2)+pow(b2,2)));


double deltaLTvxy = sqrt(
	pow( (*event->Tau1LTvx)[iCombo] - (*event->Tau2LTvx)[iCombo], 2) +
	pow( (*event->Tau1LTvy)[iCombo] - (*event->Tau2LTvy)[iCombo], 2)
);

double deltaLTvxyz = sqrt(
	pow( (*event->Tau1LTvx)[iCombo] - (*event->Tau2LTvx)[iCombo], 2) +
	pow( (*event->Tau1LTvy)[iCombo] - (*event->Tau2LTvy)[iCombo], 2) +
	pow( (*event->Tau1LTvz)[iCombo] - (*event->Tau2LTvz)[iCombo], 2)
);

hContainer->Fill("AbsDeltaLTvxy_LS", deltaLTvxy, weightFull);
hContainer->Fill("AbsDeltaLTvxyz_LS", deltaLTvxyz, weightFull);




//*/




