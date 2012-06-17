
float weightFull	= iPuWeight*iTau1TriggerWeight*iTau2TriggerWeight;
float weightTrigger = iTau1TriggerWeight*iTau2TriggerWeight;
float weightTau1	= iPuWeight*iTau1TriggerWeight;
float weightTau2	= iPuWeight*iTau1TriggerWeight;


// General =========================================================================================================================
hContainer->Fill("Events", 0, weightFull);
hContainer->Fill("MomentumRank", event->TTM_MomentumRank->at(iCombo), weightFull);
hContainer->Fill("MET", event->Ev_MET, weightFull);
//hContainer->Fill("NumPV", event->NumPV->at(iCombo), weightFull);
hContainer->Fill("ChargeProduct_TT", (event->TTM_Tau1Charge->at(iCombo) * event->TTM_Tau2Charge->at(iCombo)), weightFull);

// Taus ============================================================================================================================
hContainer->Fill("VisibleMass_TT", event->TTM_DitauVisibleMass->at(iCombo), weightFull);
hContainer->Fill("Pt_T1", event->TTM_Tau1Pt->at(iCombo), weightFull);
hContainer->Fill("Pt_T2", event->TTM_Tau2Pt->at(iCombo), weightFull);
hContainer->Fill("Eta_T1", event->TTM_Tau1Eta->at(iCombo), weightFull);
hContainer->Fill("Eta_T2", event->TTM_Tau2Eta->at(iCombo), weightFull);
hContainer->Fill("Phi_T1", event->TTM_Tau1Phi->at(iCombo), weightFull);
hContainer->Fill("Phi_T2", event->TTM_Tau2Phi->at(iCombo), weightFull);
hContainer->Fill("DecayMode_T1", event->TTM_Tau1DecayMode->at(iCombo), weightFull);
hContainer->Fill("DecayMode_T2", event->TTM_Tau2DecayMode->at(iCombo), weightFull);
hContainer->Fill("LTPt_T1", event->TTM_Tau1LTPt->at(iCombo), weightFull);
hContainer->Fill("LTPt_T2", event->TTM_Tau2LTPt->at(iCombo), weightFull);
hContainer->Fill("NProngs_T1", event->TTM_Tau1NProngs->at(iCombo), weightFull);
hContainer->Fill("NProngs_T2", event->TTM_Tau2NProngs->at(iCombo), weightFull);

// Muon ============================================================================================================================
hContainer->Fill("Pt_M", event->TTM_MuonPt->at(iCombo), weightFull);
hContainer->Fill("Eta_M", event->TTM_MuonEta->at(iCombo), weightFull);
hContainer->Fill("Phi_M", event->TTM_MuonPhi->at(iCombo), weightFull);

// Jets ============================================================================================================================
hContainer->Fill("NumCSVLbTags", event->TTM_Tau2LTPt->at(iCombo), weightFull);
hContainer->Fill("NumCSVLbtags", event->TTM_NumCSVLbtags->at(iCombo), weightFull);
hContainer->Fill("NumCSVMbtags", event->TTM_NumCSVMbtags->at(iCombo), weightFull);
hContainer->Fill("NumCSVTbtags", event->TTM_NumCSVTbtags->at(iCombo), weightFull);
hContainer->Fill("NumCSVLextraJets", event->TTM_NumCSVLextraJets->at(iCombo), weightFull);
hContainer->Fill("NumCSVMextraJets", event->TTM_NumCSVMextraJets->at(iCombo), weightFull);
hContainer->Fill("NumCSVTextraJets", event->TTM_NumCSVTextraJets->at(iCombo), weightFull);

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




