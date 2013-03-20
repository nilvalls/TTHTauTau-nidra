float weightFull	= iLeptonWeight*iPuWeight*iTau1TriggerWeight*iTau2TriggerWeight*iTauIdSysWeight;
//float weightFull	= iLeptonWeight*iPuWeight*iTau1TriggerWeight*iTau2TriggerWeight;
float weightTrigger = iTau1TriggerWeight*iTau2TriggerWeight;
float weightTau1	= iPuWeight*iTau1TriggerWeight;
float weightTau2	= iPuWeight*iTau1TriggerWeight;
//cout << "orig: " << setprecision(4) << iLeptonWeight*iPuWeight*iTau1TriggerWeight*iTau2TriggerWeight << "; tauID: " << setprecision(4) << iTauIdSysWeight << endl;

// GenMatching =========================================================================================================================
//hContainer->Fill("MatchedTo_T1", event->Tau1MatchedTo(iCombo) , weightFull);
//hContainer->Fill("MatchedTo_T2", event->Tau2MatchedTo(iCombo) , weightFull);

// General =========================================================================================================================
hContainer->Fill("Events", 0, weightFull);
hContainer->Fill("MomentumRank", event->TTL_MomentumRank->at(iCombo), weightFull);
hContainer->Fill("MET", event->Ev_MET, weightFull);
hContainer->Fill("HT", event->TTL_HT->at(iCombo), weightFull);
if(mva!=NULL){ hContainer->Fill("MVA", mva->Evaluate(event, iCombo), weightFull); }
hContainer->Fill("ComboSelectorResponse", comboSelector->Evaluate(event, iCombo), weightFull);
hContainer->Fill("SelectedComboRank", iCombo, weightFull);

if(iPuWeight!=0){
	hContainer->Fill("NumberPV_noPURW", event->Ev_numPrimaryVertices, weightFull/iPuWeight);
	hContainer->Fill("NumberBXm1_noPURW", event->Ev_numInteractionsBXm1, weightFull/iPuWeight);
	hContainer->Fill("NumberBX0_noPURW", event->Ev_numInteractionsBX0, weightFull/iPuWeight);
	hContainer->Fill("NumberBXp1_noPURW", event->Ev_numInteractionsBXp1, weightFull/iPuWeight);
	hContainer->Fill("PUweights_noPURW", iPuWeight, weightFull/iPuWeight);
}else{
	//cout << "zero found in iPUweight, numBX: " << event->Ev_numInteractionsBX0 << endl;
}

if(IsFlagThere("PUcorr")){
	hContainer->Fill("NumberPV_afterPURW", event->Ev_numPrimaryVertices, weightFull);
	hContainer->Fill("NumberBXm1_afterPURW", event->Ev_numInteractionsBXm1, weightFull);
	hContainer->Fill("NumberBX0_afterPURW", event->Ev_numInteractionsBX0, weightFull);
	hContainer->Fill("NumberBXp1_afterPURW", event->Ev_numInteractionsBXp1, weightFull);
	hContainer->Fill("PUweights_afterPURW", iPuWeight, weightFull);
}

hContainer->Fill("ChargeProduct_TT", (event->TTL_Tau1Charge->at(iCombo) * event->TTL_Tau2Charge->at(iCombo)), weightFull);

// Taus ============================================================================================================================
hContainer->Fill("NumTaus", event->TTL_NumTaus, weightFull);
hContainer->Fill("VisibleMass_TT", event->TTL_DitauVisibleMass->at(iCombo), weightFull);
hContainer->Fill("DeltaR_TT", event->TTL_DitauDeltaR->at(iCombo), weightFull);
hContainer->Fill("Pt_T1", event->TTL_Tau1Pt->at(iCombo), weightFull);
hContainer->Fill("Pt_T2", event->TTL_Tau2Pt->at(iCombo), weightFull);
hContainer->Fill("Eta_T1", event->TTL_Tau1Eta->at(iCombo), weightFull);
hContainer->Fill("Eta_T2", event->TTL_Tau2Eta->at(iCombo), weightFull);
hContainer->Fill("Phi_T1", event->TTL_Tau1Phi->at(iCombo), weightFull);
hContainer->Fill("Phi_T2", event->TTL_Tau2Phi->at(iCombo), weightFull);
hContainer->Fill("DecayMode_T1", event->TTL_Tau1DecayMode->at(iCombo), weightFull);
hContainer->Fill("DecayMode_T2", event->TTL_Tau2DecayMode->at(iCombo), weightFull);
hContainer->Fill("LTPt_T1", event->TTL_Tau1LTPt->at(iCombo), weightFull);
hContainer->Fill("LTPt_T2", event->TTL_Tau2LTPt->at(iCombo), weightFull);
hContainer->Fill("NProngs_T1", event->TTL_Tau1NProngs->at(iCombo), weightFull);
hContainer->Fill("NProngs_T2", event->TTL_Tau2NProngs->at(iCombo), weightFull);
hContainer->Fill("IsolationIndex_T1", event->GetTau1IsolationIndex(iCombo), weightFull);
hContainer->Fill("IsolationIndex_T2", event->GetTau2IsolationIndex(iCombo), weightFull);
hContainer->Fill("AntiElectronIndex_T1", event->GetTau1AntiElectronIndex(iCombo), weightFull);
hContainer->Fill("AntiElectronIndex_T2", event->GetTau2AntiElectronIndex(iCombo), weightFull);
hContainer->Fill("AntiMuonIndex_T1", event->GetTau1AntiMuonIndex(iCombo), weightFull);
hContainer->Fill("AntiMuonIndex_T2", event->GetTau2AntiMuonIndex(iCombo), weightFull);
hContainer->Fill("Match_T1", event->GetTau1MatchIndex(iCombo), weightFull);
hContainer->Fill("Match_T2", event->GetTau2MatchIndex(iCombo), weightFull);

// Lepton ============================================================================================================================
hContainer->Fill("Pt_L", event->TTL_LeptonPt->at(iCombo), weightFull);
hContainer->Fill("Eta_L", event->TTL_LeptonEta->at(iCombo), weightFull);
hContainer->Fill("Phi_L", event->TTL_LeptonPhi->at(iCombo), weightFull);
hContainer->Fill("NumTightMuons", event->TTL_NumTightMuons->at(iCombo), weightFull);
hContainer->Fill("NumLooseMuons", event->TTL_NumLooseMuons->at(iCombo), weightFull);
hContainer->Fill("NumExLooseMuons", event->TTL_NumExLooseMuons->at(iCombo), weightFull);
hContainer->Fill("NumTightElectrons", event->TTL_NumTightElectrons->at(iCombo), weightFull);
hContainer->Fill("NumLooseElectrons", event->TTL_NumLooseElectrons->at(iCombo), weightFull);
hContainer->Fill("NumExLooseElectrons", event->TTL_NumExLooseElectrons->at(iCombo), weightFull);
hContainer->Fill("NumTightLeptons",		event->TTL_NumTightMuons->at(iCombo)	+	event->TTL_NumTightElectrons->at(iCombo)	, weightFull);
hContainer->Fill("NumLooseLeptons",		event->TTL_NumLooseMuons->at(iCombo)	+	event->TTL_NumLooseElectrons->at(iCombo)	, weightFull);
hContainer->Fill("NumExLooseLeptons",	event->TTL_NumExLooseMuons->at(iCombo)	+	event->TTL_NumExLooseElectrons->at(iCombo)	, weightFull);
hContainer->Fill("DeltaR_LT1", DeltaR(event->TTL_LeptonEta->at(iCombo), event->TTL_LeptonPhi->at(iCombo), event->TTL_Tau1Eta->at(iCombo), event->TTL_Tau1Phi->at(iCombo)), weightFull);
hContainer->Fill("DeltaR_LT2", DeltaR(event->TTL_LeptonEta->at(iCombo), event->TTL_LeptonPhi->at(iCombo), event->TTL_Tau2Eta->at(iCombo), event->TTL_Tau2Phi->at(iCombo)), weightFull);

// Jets ============================================================================================================================
// tau/jet matching con size
float conesize = 0.25;
int jetCounter = 0;
for( unsigned int iJet = 0; iJet < event->J_Pt->size(); iJet++ ) {
    if( (DeltaR( event->J_Eta->at(iJet),
            event->J_Phi->at(iJet),
            event->TTL_Tau1Eta->at(iCombo),
            event->TTL_Tau1Phi->at(iCombo)) > conesize) &&
        (DeltaR( event->J_Eta->at(iJet),
            event->J_Phi->at(iJet),
            event->TTL_Tau2Eta->at(iCombo),
            event->TTL_Tau2Phi->at(iCombo)) > conesize) &&
        (DeltaR( event->J_Eta->at(iJet),
            event->J_Phi->at(iJet),
            event->TTL_LeptonEta->at(iCombo),
            event->TTL_LeptonPhi->at(iCombo)) > conesize)
    ) {
		if (jetCounter == 0) {
			hContainer->Fill("LeadingJet_Pt", event->J_Pt->at(iJet), weightFull);
			hContainer->Fill("LeadingJet_Eta", event->J_Eta->at(iJet), weightFull);

			hContainer->Fill("DeltaR_LJ1", DeltaR(event->TTL_LeptonEta->at(iCombo), event->TTL_LeptonPhi->at(iCombo), event->J_Eta->at(iJet), event->J_Phi->at(iJet)), weightFull);
			hContainer->Fill("DeltaR_T1J1", DeltaR(event->TTL_Tau1Eta->at(iCombo), event->TTL_Tau1Phi->at(iCombo), event->J_Eta->at(iJet), event->J_Phi->at(iJet)), weightFull);
			hContainer->Fill("DeltaR_T2J1", DeltaR(event->TTL_Tau2Eta->at(iCombo), event->TTL_Tau2Phi->at(iCombo), event->J_Eta->at(iJet), event->J_Phi->at(iJet)), weightFull);
		} else if (jetCounter==1) {
			hContainer->Fill("SubLeadingJet_Pt", event->J_Pt->at(iJet), weightFull);
			hContainer->Fill("SubLeadingJet_Eta", event->J_Eta->at(iJet), weightFull);

			hContainer->Fill("DeltaR_LJ2", DeltaR(event->TTL_LeptonEta->at(iCombo), event->TTL_LeptonPhi->at(iCombo), event->J_Eta->at(iJet), event->J_Phi->at(iJet)), weightFull);
			hContainer->Fill("DeltaR_T1J2", DeltaR(event->TTL_Tau1Eta->at(iCombo), event->TTL_Tau1Phi->at(iCombo), event->J_Eta->at(iJet), event->J_Phi->at(iJet)), weightFull);
			hContainer->Fill("DeltaR_T2J2", DeltaR(event->TTL_Tau2Eta->at(iCombo), event->TTL_Tau2Phi->at(iCombo), event->J_Eta->at(iJet), event->J_Phi->at(iJet)), weightFull);
		} else if (jetCounter == 2) {
			hContainer->Fill("SubSubLeadingJet_Pt", event->J_Pt->at(iJet), weightFull);
			hContainer->Fill("SubSubLeadingJet_Eta", event->J_Eta->at(iJet), weightFull);
		} else if (jetCounter == 3) {
			hContainer->Fill("SubSubSubLeadingJet_Pt", event->J_Pt->at(iJet), weightFull);
			hContainer->Fill("SubSubSubLeadingJet_Eta", event->J_Eta->at(iJet), weightFull);
		}

        if (event->J_combSecVtxMediumBTag->at(iJet)) {
           hContainer->Fill("BTagJet_Pt", event->J_Pt->at(iJet), weightFull);
           hContainer->Fill("BTagJet_Eta", event->J_Eta->at(iJet), weightFull);
        } else {
           hContainer->Fill("NonBTagJet_Pt", event->J_Pt->at(iJet), weightFull);
           hContainer->Fill("NonBTagJet_Eta", event->J_Eta->at(iJet), weightFull);
        }

        jetCounter++;
        // if(jetCounter > 3){ break; }
    }
}

hContainer->Fill("NumCSVLbtags", event->TTL_NumCSVLbtagJets->at(iCombo), weightFull);
hContainer->Fill("NumCSVMbtags", event->TTL_NumCSVMbtagJets->at(iCombo), weightFull);
hContainer->Fill("NumCSVTbtags", event->TTL_NumCSVTbtagJets->at(iCombo), weightFull);
hContainer->Fill("NumCSVLnonBtags", event->TTL_NumNonCSVLbtagJets->at(iCombo), weightFull);
hContainer->Fill("NumCSVMnonBtags", event->TTL_NumNonCSVMbtagJets->at(iCombo), weightFull);
hContainer->Fill("NumCSVTnonBtags", event->TTL_NumNonCSVTbtagJets->at(iCombo), weightFull);
hContainer->Fill("NumCSVnonHTauJets", (event->TTL_NumNonCSVMbtagJets->at(iCombo) + event->TTL_NumCSVMbtagJets->at(iCombo)), weightFull);
hContainer->Fill("NumCleanCSVLbtags", event->TTL_NumCleanCSVLbtagJets->at(iCombo), weightFull);
hContainer->Fill("NumCleanCSVMbtags", event->TTL_NumCleanCSVMbtagJets->at(iCombo), weightFull);
hContainer->Fill("NumCleanCSVTbtags", event->TTL_NumCleanCSVTbtagJets->at(iCombo), weightFull);
hContainer->Fill("NumCleanCSVLnonBtags", event->TTL_NumCleanNonCSVLbtagJets->at(iCombo), weightFull);
hContainer->Fill("NumCleanCSVMnonBtags", event->TTL_NumCleanNonCSVMbtagJets->at(iCombo), weightFull);
hContainer->Fill("NumCleanCSVTnonBtags", event->TTL_NumCleanNonCSVTbtagJets->at(iCombo), weightFull);
hContainer->Fill("NumCleanCSVnonHTauJets", (event->TTL_NumCleanNonCSVMbtagJets->at(iCombo) + event->TTL_NumCleanCSVMbtagJets->at(iCombo)), weightFull);

/*
hContainer->Fill("CosDeltaPhi_LM", event->Tau1MetCosDphi->at(iCombo), weightFull);
hContainer->Fill("CosDeltaPhi_SM", event->Tau2MetCosDphi->at(iCombo), weightFull);
hContainer->Fill("DeltaPhi_LM", acos(event->Tau1MetCosDphi->at(iCombo)), weightFull);
hContainer->Fill("DeltaPhi_SM", acos(event->Tau2MetCosDphi->at(iCombo)), weightFull);
hContainer->Fill("SumETotherJets", event->jetSumEt->at(iCombo), weightFull);
hContainer->Fill("SumETotherJetsPlusMET", event->jetMETSumEt->at(iCombo), weightFull);
hContainer->Fill("NumOtherJets", event->nJets->at(iCombo), weightFull);
hContainer->Fill("EmFraction_LS", event->Tau1EmFraction->at(iCombo), weightFull);
hContainer->Fill("EmFraction_LS", event->Tau2EmFraction->at(iCombo), weightFull);

hContainer->Fill("AbsDeltaEta_LS", fabs((event->Tau1Eta->at(iCombo))-(event->Tau2Eta->at(iCombo))), weightFull);
hContainer->Fill("CosDeltaPhi_LS", event->TauTauCosDPhi->at(iCombo), weightFull);
hContainer->Fill("CosDeltaEta_LS", cos(fabs(event->Tau1Eta->at(iCombo)-event->Tau2Eta->at(iCombo))), weightFull);
hContainer->Fill("DeltaPhi_LS", acos(cos(event->Tau1Phi->at(iCombo)-event->Tau2Phi->at(iCombo))), weightFull);
hContainer->Fill("DeltaEta_LS", fabs(event->Tau1Eta->at(iCombo)-event->Tau2Eta->at(iCombo)), weightFull);
hContainer->Fill("DeltaR_LS", event->TauTauDeltaR->at(iCombo), weightFull);
hContainer->Fill("LTNumHits_LS", event->Tau1LTValidHits->at(iCombo), weightFull);
hContainer->Fill("LTNumHits_LS", event->Tau2LTValidHits->at(iCombo), weightFull);
hContainer->Fill("PZeta_LSM", event->TauTauPZeta->at(iCombo), weightFull);
hContainer->Fill("PZetaVis_LSM", event->TauTauPZetaVis->at(iCombo), weightFull);
hContainer->Fill("Zeta_LSM", (event->TauTauPZeta->at(iCombo)-0.875*event->TauTauPZetaVis->at(iCombo)), weightFull);

//hContainer->Fill("PUweightsPassingEvents", event->puCorrector->GetWeight(NumPV->at(iCombo), weightFull);


int DDMI = -1; 
if(event->Tau1DecayMode->at(iCombo)<0 || event->Tau2DecayMode->at(iCombo)<0){ DDMI = -1; }
else if(event->Tau1DecayMode->at(iCombo)==0 && event->Tau2DecayMode->at(iCombo)==0){ DDMI = 0; }
else if( 
		(event->Tau1DecayMode->at(iCombo)==0 && event->Tau2DecayMode->at(iCombo) == 1) ||
		(event->Tau1DecayMode->at(iCombo)==0 && event->Tau2DecayMode->at(iCombo) == 2) ||
		(event->Tau1DecayMode->at(iCombo)==0 && event->Tau2DecayMode->at(iCombo) == 3) ||
		(event->Tau1DecayMode->at(iCombo)==0 && event->Tau2DecayMode->at(iCombo) == 4) ||
		(event->Tau1DecayMode->at(iCombo)==1 && event->Tau2DecayMode->at(iCombo) == 0) ||
		(event->Tau1DecayMode->at(iCombo)==2 && event->Tau2DecayMode->at(iCombo) == 0) ||
		(event->Tau1DecayMode->at(iCombo)==3 && event->Tau2DecayMode->at(iCombo) == 0) ||
		(event->Tau1DecayMode->at(iCombo)==4 && event->Tau2DecayMode->at(iCombo) == 0) ){ DDMI = 1; }
else if( 
		(event->Tau1DecayMode->at(iCombo)==0 && event->Tau2DecayMode->at(iCombo)>=10) ||
		(event->Tau1DecayMode->at(iCombo)>=10 && event->Tau2DecayMode->at(iCombo)==0) ){ DDMI = 2; }
else{ DDMI = 3; }
hContainer->Fill("DDMI", DDMI, weightFull);

int DTMI = -1; 
if((event->Tau1NProngs->at(iCombo)<1) || (event->Tau2NProngs->at(iCombo)<1)){ DTMI = -1; }
else if(event->Tau1NProngs->at(iCombo)==1 && event->Tau2NProngs->at(iCombo)==1){ DTMI = 0; }
else if((event->Tau1NProngs->at(iCombo)==1 && event->Tau2NProngs->at(iCombo)==3) || (event->Tau2NProngs->at(iCombo)==1 && event->Tau1NProngs->at(iCombo)==3)){ DTMI = 1; }
else if(event->Tau1NProngs->at(iCombo)==3 && event->Tau2NProngs->at(iCombo)==3){ DTMI = 2; }
else{ DTMI = 3; }
hContainer->Fill("DTMI", DTMI, weightFull);

// Vertex-track stuff
hContainer->Fill("LTdxy_L", (event->Tau1LTIpVtdxy->at(iCombo)), weightFull);
hContainer->Fill("LTdxy_S", (event->Tau2LTIpVtdxy->at(iCombo)), weightFull);
hContainer->Fill("LTdz_L", (event->Tau1LTIpVtdz->at(iCombo)), weightFull);
hContainer->Fill("LTdz_S", (event->Tau2LTIpVtdz->at(iCombo)), weightFull);
hContainer->Fill("DeltaLTdz_LS", (event->Tau1LTIpVtdz->at(iCombo)-event->Tau2LTIpVtdz->at(iCombo)), weightFull);


hContainer->Fill("SigLTdz_L", (event->Tau1LTIpVtdz->at(iCombo))/event->Tau1LTIpVtdzError->at(iCombo), weightFull);
hContainer->Fill("SigLTdz_S", (event->Tau2LTIpVtdz->at(iCombo))/event->Tau2LTIpVtdzError->at(iCombo), weightFull);

hContainer->Fill("SigLTdxy_L", (event->Tau1LTIpVtdxy->at(iCombo))/event->Tau1LTIpVtdxyError->at(iCombo), weightFull);
hContainer->Fill("SigLTdxy_S", (event->Tau2LTIpVtdxy->at(iCombo))/event->Tau2LTIpVtdxyError->at(iCombo), weightFull);

double a1 = event->Tau1LTIpVtdxy->at(iCombo);
double b1 = event->Tau1LTIpVtdz->at(iCombo);
double da1 = event->Tau1LTIpVtdxyError->at(iCombo);
double db1 = event->Tau1LTIpVtdzError->at(iCombo);
double error1 = sqrt((pow(a1*da1,2)+pow(b1*db1,2))/(pow(a1,2)+pow(b1,2)));
double a2 = event->Tau2LTIpVtdxy->at(iCombo);
double b2 = event->Tau2LTIpVtdz->at(iCombo);
double da2 = event->Tau2LTIpVtdxyError->at(iCombo);
double db2 = event->Tau2LTIpVtdzError->at(iCombo);
double error2 = sqrt((pow(a2*da2,2)+pow(b2*db2,2))/(pow(a2,2)+pow(b2,2)));


double deltaLTvxy = sqrt(
	pow( event->Tau1LTvx->at(iCombo) - event->Tau2LTvx->at(iCombo), 2) +
	pow( event->Tau1LTvy->at(iCombo) - event->Tau2LTvy->at(iCombo), 2)
);

double deltaLTvxyz = sqrt(
	pow( event->Tau1LTvx->at(iCombo) - event->Tau2LTvx->at(iCombo), 2) +
	pow( event->Tau1LTvy->at(iCombo) - event->Tau2LTvy->at(iCombo), 2) +
	pow( event->Tau1LTvz->at(iCombo) - event->Tau2LTvz->at(iCombo), 2)
);

hContainer->Fill("AbsDeltaLTvxy_LS", deltaLTvxy, weightFull);
hContainer->Fill("AbsDeltaLTvxyz_LS", deltaLTvxyz, weightFull);




//*/




