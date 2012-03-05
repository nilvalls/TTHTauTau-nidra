
float weightFull	= iPuWeight*iTau1TriggerWeight*iTau2TriggerWeight;
float weightTrigger = iTau1TriggerWeight*iTau2TriggerWeight;
float weightTau1	= iPuWeight*iTau1TriggerWeight;
float weightTau2	= iPuWeight*iTau1TriggerWeight;


/*
// Non-physics
FillHisto(hContainer, "NumInteractionsBX0_b4RW", event->numInteractionsBX0, weightTrigger);
FillHisto(hContainer, "NumInteractionsBX0_afRW", event->numInteractionsBX0, weightFull);

FillHisto(hContainer, "NumPV_bfRW", event->NumPV->at(iCombo), weightTrigger);
FillHisto(hContainer, "NumPV_afRW", event->NumPV->at(iCombo), weightFull); //*/
/*

   if(hContainer->find("NumPV_afRW") != hContainer->end()){
   (*(hContainer->find("NumPV_afRW"))).second->GetHisto()->Fill(NumPV->at(iCombo), puCorrector->GetWeight(numInteractionsBX0));
   }//*/


// Physics =========================================================================================================================
hContainer->Fill("Events", 0, weightFull);
hContainer->Fill("MET_M", event->MET->at(iCombo), weightFull);
hContainer->Fill("Btags", event->nBtagsHiEffTrkCnt->at(iCombo), weightFull);
hContainer->Fill("InvariantMass_LSM", event->TauTauVisPlusMetMass->at(iCombo), weightFull);
hContainer->Fill("SVFitMass_LSM", event->NSVFitMass->at(iCombo), weightFull);
hContainer->Fill("SVFitStatus_LSM", event->NSVFitStatus->at(iCombo), weightFull);
hContainer->Fill("SVFitMET_LSM", event->NSVFitMET->at(iCombo), weightFull);
hContainer->Fill("SVFitSystemPt_LSM", event->NSVFitSystemPt->at(iCombo), weightFull);
hContainer->Fill("SVFitSystemMag_LSM", event->NSVFitSystemMag->at(iCombo), weightFull);
hContainer->Fill("SVFitSystemPhi_LSM", fabs(event->NSVFitSystemPhi->at(iCombo)), weightFull);
hContainer->Fill("SVFitSystemEta_LSM", fabs(event->NSVFitSystemEta->at(iCombo)), weightFull);

hContainer->Fill("InvariantMass_LSM_forTTbar", event->TauTauVisPlusMetMass->at(iCombo), weightFull);
hContainer->Fill("InvariantMass_LSM_forNote1", event->TauTauVisPlusMetMass->at(iCombo), weightFull);
hContainer->Fill("InvariantMass_LSM_forNote2", event->TauTauVisPlusMetMass->at(iCombo), weightFull);
hContainer->Fill("VisibleMass_LS", event->TauTauVisibleMass->at(iCombo), weightFull);
hContainer->Fill("VisibleMass_LS_forNote1", event->TauTauVisibleMass->at(iCombo), weightFull);
hContainer->Fill("VisibleMass_LS_forNote2", event->TauTauVisibleMass->at(iCombo), weightFull);
hContainer->Fill("MET_M_forNote", event->MET->at(iCombo), weightFull);
hContainer->Fill("TransverseMass_LM", event->Tau1MetMt->at(iCombo), weightFull);
hContainer->Fill("TransverseMass_LM_forNote", event->Tau1MetMt->at(iCombo), weightFull);
hContainer->Fill("TransverseMass_legTrigger_LM", event->Tau1MetMt->at(iCombo), weightFull);
hContainer->Fill("TransverseMass_legTrigger_log_LM", event->Tau1MetMt->at(iCombo), weightFull);
hContainer->Fill("TransverseMass_SM", event->Tau2MetMt->at(iCombo), weightFull);
hContainer->Fill("TransverseMass_SM_forNote", event->Tau2MetMt->at(iCombo), weightFull);
hContainer->Fill("NumPV", event->NumPV->at(iCombo), weightFull);
hContainer->Fill("DecayMode_LS", event->Tau1DecayMode->at(iCombo), weightFull);
hContainer->Fill("DecayMode_LS", event->Tau2DecayMode->at(iCombo), weightFull);
hContainer->Fill("DecayMode_L", event->Tau1DecayMode->at(iCombo), weightFull);
hContainer->Fill("DecayMode_S", event->Tau2DecayMode->at(iCombo), weightFull);
hContainer->Fill("DecayModeFinding_LS", event->Tau1hpsPFTauDiscriminationByDecayModeFinding->at(iCombo), weightFull);
hContainer->Fill("DecayModeFinding_LS", event->Tau2hpsPFTauDiscriminationByDecayModeFinding->at(iCombo), weightFull);
hContainer->Fill("DecayModeFinding_L", event->Tau1hpsPFTauDiscriminationByDecayModeFinding->at(iCombo), weightFull);
hContainer->Fill("DecayModeFinding_S", event->Tau2hpsPFTauDiscriminationByDecayModeFinding->at(iCombo), weightFull);
hContainer->Fill("Pt_LS", event->Tau1Pt->at(iCombo), weightFull);
hContainer->Fill("Pt_LS", event->Tau2Pt->at(iCombo), weightFull);
hContainer->Fill("Pt_LS_forNote", event->Tau1Pt->at(iCombo), weightFull);
hContainer->Fill("Pt_LS_forNote", event->Tau2Pt->at(iCombo), weightFull);
hContainer->Fill("Pt_L", event->Tau1Pt->at(iCombo), weightFull);
hContainer->Fill("Pt_legTrigger_LS", event->Tau1Pt->at(iCombo), weightFull);
hContainer->Fill("Pt_legTrigger_LS", event->Tau2Pt->at(iCombo), weightFull);
hContainer->Fill("Pt_noTrigger_LS", event->Tau1Pt->at(iCombo), weightFull);
hContainer->Fill("Pt_noTrigger_LS", event->Tau2Pt->at(iCombo), weightFull);
hContainer->Fill("Pt_S", event->Tau2Pt->at(iCombo), weightFull);
hContainer->Fill("LTpT_LS", event->Tau1LTPt->at(iCombo), weightFull);
hContainer->Fill("LTpT_LS", event->Tau2LTPt->at(iCombo), weightFull);
hContainer->Fill("LTpT_L", event->Tau1LTPt->at(iCombo), weightFull);
hContainer->Fill("LTpT_S", event->Tau2LTPt->at(iCombo), weightFull);
hContainer->Fill("NumProngs_LS", event->Tau1NProngs->at(iCombo), weightFull);
hContainer->Fill("NumProngs_LS", event->Tau2NProngs->at(iCombo), weightFull);
hContainer->Fill("NumProngs_L", event->Tau1NProngs->at(iCombo), weightFull);
hContainer->Fill("NumProngs_S", event->Tau2NProngs->at(iCombo), weightFull);
hContainer->Fill("CosDeltaPhi_LM", event->Tau1MetCosDphi->at(iCombo), weightFull);
hContainer->Fill("CosDeltaPhi_SM", event->Tau2MetCosDphi->at(iCombo), weightFull);
hContainer->Fill("DeltaPhi_LM", acos(event->Tau1MetCosDphi->at(iCombo)), weightFull);
hContainer->Fill("DeltaPhi_SM", acos(event->Tau2MetCosDphi->at(iCombo)), weightFull);
hContainer->Fill("SumETotherJets", event->jetSumEt->at(iCombo), weightFull);
hContainer->Fill("SumETotherJetsPlusMET", event->jetMETSumEt->at(iCombo), weightFull);
hContainer->Fill("NumOtherJets", event->nJets->at(iCombo), weightFull);
hContainer->Fill("EmFraction_LS", event->Tau1EmFraction->at(iCombo), weightFull);
hContainer->Fill("EmFraction_LS", event->Tau2EmFraction->at(iCombo), weightFull);
hContainer->Fill("ChargeProduct_LS", (event->Tau1Charge->at(iCombo) * event->Tau2Charge->at(iCombo)), weightFull);

/*hContainer->Fill("SumPtIsoGammas_LS", event->Tau1SumPtIsoGammas->at(iCombo), weightFull);
hContainer->Fill("SumPtIsoGammas_LS", event->Tau2SumPtIsoGammas->at(iCombo), weightFull);
hContainer->Fill("SumPtIsoGammas_L", event->Tau1SumPtIsoGammas->at(iCombo), weightFull);
hContainer->Fill("SumPtIsoGammas_S", event->Tau1SumPtIsoGammas->at(iCombo), weightFull);
hContainer->Fill("SumPtIsoTracks_LS", event->Tau1SumPtIsoTracks->at(iCombo), weightFull);
hContainer->Fill("SumPtIsoTracks_LS", event->Tau2SumPtIsoTracks->at(iCombo), weightFull);
hContainer->Fill("SumPtIsoTracks_L", event->Tau1SumPtIsoTracks->at(iCombo), weightFull);
hContainer->Fill("SumPtIsoTracks_S", event->Tau2SumPtIsoTracks->at(iCombo), weightFull);//*/


hContainer->Fill("Eta_LS", event->Tau1Eta->at(iCombo), weightFull);
hContainer->Fill("Eta_LS", event->Tau2Eta->at(iCombo), weightFull);
hContainer->Fill("Eta_L", event->Tau1Eta->at(iCombo), weightFull);
hContainer->Fill("Eta_S", event->Tau2Eta->at(iCombo), weightFull);
hContainer->Fill("AbsDeltaEta_LS", fabs((event->Tau1Eta->at(iCombo))-(event->Tau2Eta->at(iCombo))), weightFull);
hContainer->Fill("Phi_LS", event->Tau1Phi->at(iCombo), weightFull);
hContainer->Fill("Phi_LS", event->Tau2Phi->at(iCombo), weightFull);
hContainer->Fill("Phi_L", event->Tau1Phi->at(iCombo), weightFull);
hContainer->Fill("Phi_S", event->Tau2Phi->at(iCombo), weightFull);
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


hContainer->Fill("DeltaOmegaBoostAndBoostedSVFitTau1_LSM",				fabs(event->DeltaOmegaBoostAndBoostedSVFitTau1->at(iCombo)), weightFull);
hContainer->Fill("DeltaOmegaBoostAndBoostedSVFitTau2_LSM",				fabs(event->DeltaOmegaBoostAndBoostedSVFitTau2->at(iCombo)), weightFull);
hContainer->Fill("DeltaOmegaBoostedSVFitTau1AndBoostedSVFitTau2_LSM",	fabs(event->DeltaOmegaBoostedSVFitTau1AndBoostedSVFitTau2->at(iCombo)), weightFull);

hContainer->Fill("DeltaPhiBoostAndBoostedSVFitTau1_LSM",			fabs(event->DeltaPhiBoostAndBoostedSVFitTau1->at(iCombo)), weightFull);
hContainer->Fill("DeltaPhiBoostAndBoostedSVFitTau2_LSM",			fabs(event->DeltaPhiBoostAndBoostedSVFitTau2->at(iCombo)), weightFull);
hContainer->Fill("DeltaPhiBoostedSVFitTau1AndBoostedSVFitTau2_LSM",	fabs(event->DeltaPhiBoostedSVFitTau1AndBoostedSVFitTau2->at(iCombo)), weightFull);








