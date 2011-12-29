

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

	// Physics
	hContainer->Fill("Events", 0, weightFull);
	hContainer->Fill("MET_M", event->MET->at(iCombo), weightFull);
	hContainer->Fill("Btags", event->nBtagsHiEffTrkCnt->at(iCombo), weightFull);

	/*
	FillHisto(hContainer, "", ->at(iCombo), weightFull);
	FillHisto(hContainer, "", ->at(iCombo), weightFull);
	FillHisto(hContainer, "", ->at(iCombo), weightFull);
	FillHisto(hContainer, "", ->at(iCombo), weightFull);
	FillHisto(hContainer, "", ->at(iCombo), weightFull);
	FillHisto(hContainer, "", ->at(iCombo), weightFull);
	FillHisto(hContainer, "", ->at(iCombo), weightFull);
	FillHisto(hContainer, "", ->at(iCombo), weightFull);
	FillHisto(hContainer, "", ->at(iCombo), weightFull);
	FillHisto(hContainer, "", ->at(iCombo), weightFull); //*/



	/*

	if(hContainer->find("NumPV_afRW") != hContainer->end()){
		(*(hContainer->find("NumPV_afRW"))).second->GetHisto()->Fill(NumPV->at(iCombo), puCorrector->GetWeight(numInteractionsBX0));
	}


	// Filling of histos
	if(hContainer->find("InvariantMass_LSM") != hContainer->end()){
		(*(hContainer->find("InvariantMass_LSM"))).second->GetHisto()->Fill(TauTauVisPlusMetMass->at(iCombo), eventWeight);
	}
	if(hContainer->find("InvariantMass_LSM_forTTbar") != hContainer->end()){
		(*(hContainer->find("InvariantMass_LSM_forTTbar"))).second->GetHisto()->Fill(TauTauVisPlusMetMass->at(iCombo), eventWeight);
	}
	if(hContainer->find("InvariantMass_LSM_forNote1") != hContainer->end()){
		(*(hContainer->find("InvariantMass_LSM_forNote1"))).second->GetHisto()->Fill(TauTauVisPlusMetMass->at(iCombo), eventWeight);
	}
	if(hContainer->find("InvariantMass_LSM_forNote2") != hContainer->end()){
		(*(hContainer->find("InvariantMass_LSM_forNote2"))).second->GetHisto()->Fill(TauTauVisPlusMetMass->at(iCombo), eventWeight);
	}

	if(hContainer->find("VisibleMass_LS") != hContainer->end()){
		(*(hContainer->find("VisibleMass_LS"))).second->GetHisto()->Fill(TauTauVisibleMass->at(iCombo), eventWeight);
	}

	if(hContainer->find("VisibleMass_LS_forNote1") != hContainer->end()){
		(*(hContainer->find("VisibleMass_LS_forNote1"))).second->GetHisto()->Fill(TauTauVisibleMass->at(iCombo), eventWeight);
	}
	if(hContainer->find("VisibleMass_LS_forNote2") != hContainer->end()){
		(*(hContainer->find("VisibleMass_LS_forNote2"))).second->GetHisto()->Fill(TauTauVisibleMass->at(iCombo), eventWeight);
	}


	if(hContainer->find("MET_M_forNote") != hContainer->end()){
		(*(hContainer->find("MET_M_forNote"))).second->GetHisto()->Fill(mEt->at(iCombo), eventWeight);
	}

	if(FoundHisto("VSumPt_LS")){ 
		float cosdphi	= TauTauCosDPhi->at(iCombo);
		float sindphi	= sin(acos(cosdphi));
		float sumptx	= Tau1Pt->at(iCombo) + (Tau2Pt->at(iCombo))*cosdphi;
		float sumpty	= 					 (Tau2Pt->at(iCombo))*sindphi;
		float sumPt		= sqrt(pow(sumptx,2) + pow(sumpty,2));
		GetHisto("VSumPt_LS")->Fill(sumPt, eventWeight);
	}


	if(hContainer->find("TransverseMass_LM") != hContainer->end()){
		(*(hContainer->find("TransverseMass_LM"))).second->GetHisto()->Fill(Tau1MetMt->at(iCombo), eventWeight);
	}
	if(hContainer->find("TransverseMass_LM_forNote") != hContainer->end()){
		(*(hContainer->find("TransverseMass_LM_forNote"))).second->GetHisto()->Fill(Tau1MetMt->at(iCombo), eventWeight);
	}

	if(hContainer->find("TransverseMass_legTrigger_LM") != hContainer->end()){
		(*(hContainer->find("TransverseMass_legTrigger_LM"))).second->GetHisto()->Fill(Tau1MetMt->at(iCombo), tau1Weight);
	}
	if(hContainer->find("TransverseMass_legTrigger_log_LM") != hContainer->end()){
		(*(hContainer->find("TransverseMass_legTrigger_log_LM"))).second->GetHisto()->Fill(Tau1MetMt->at(iCombo), tau1Weight);
	}

	if(hContainer->find("TransverseMass_SM") != hContainer->end()){
		(*(hContainer->find("TransverseMass_SM"))).second->GetHisto()->Fill(Tau2MetMt->at(iCombo), eventWeight);
	}
	if(hContainer->find("TransverseMass_SM_forNote") != hContainer->end()){
		(*(hContainer->find("TransverseMass_SM_forNote"))).second->GetHisto()->Fill(Tau2MetMt->at(iCombo), eventWeight);
	}

	if(hContainer->find("NumPV") != hContainer->end()){
		(*(hContainer->find("NumPV"))).second->GetHisto()->Fill(NumPV->at(iCombo), eventWeight);
	}
	
	if(hContainer->find("HPSIsolation_LS") != hContainer->end()){
		if(Tau1hpsPFTauDiscriminationByTightIsolation->at(iCombo) ){ (*(hContainer->find("HPSIsolation_LS"))).second->GetHisto()->Fill(4.0, eventWeight); }
		if(Tau1hpsPFTauDiscriminationByMediumIsolation->at(iCombo)){ (*(hContainer->find("HPSIsolation_LS"))).second->GetHisto()->Fill(3.0, eventWeight); }
		if(Tau1hpsPFTauDiscriminationByLooseIsolation->at(iCombo) ){ (*(hContainer->find("HPSIsolation_LS"))).second->GetHisto()->Fill(2.0, eventWeight); }
		if(Tau1hpsPFTauDiscriminationByVLooseIsolation->at(iCombo)){ (*(hContainer->find("HPSIsolation_LS"))).second->GetHisto()->Fill(1.0, eventWeight); }
		else{														(*(hContainer->find("HPSIsolation_LS"))).second->GetHisto()->Fill(0.0, eventWeight); }

		if(Tau2hpsPFTauDiscriminationByTightIsolation->at(iCombo) ){ (*(hContainer->find("HPSIsolation_LS"))).second->GetHisto()->Fill(4.0, eventWeight); }
		if(Tau2hpsPFTauDiscriminationByMediumIsolation->at(iCombo)){ (*(hContainer->find("HPSIsolation_LS"))).second->GetHisto()->Fill(3.0, eventWeight); }
		if(Tau2hpsPFTauDiscriminationByLooseIsolation->at(iCombo) ){ (*(hContainer->find("HPSIsolation_LS"))).second->GetHisto()->Fill(2.0, eventWeight); }
		if(Tau2hpsPFTauDiscriminationByVLooseIsolation->at(iCombo)){ (*(hContainer->find("HPSIsolation_LS"))).second->GetHisto()->Fill(1.0, eventWeight); }
		else{														(*(hContainer->find("HPSIsolation_LS"))).second->GetHisto()->Fill(0.0, eventWeight); }
	}

	if(hContainer->find("HPSIsolation_L") != hContainer->end()){
		if(Tau1hpsPFTauDiscriminationByTightIsolation->at(iCombo) ){ (*(hContainer->find("HPSIsolation_L"))).second->GetHisto()->Fill(4.0, eventWeight); }
		if(Tau1hpsPFTauDiscriminationByMediumIsolation->at(iCombo)){ (*(hContainer->find("HPSIsolation_L"))).second->GetHisto()->Fill(3.0, eventWeight); }
		if(Tau1hpsPFTauDiscriminationByLooseIsolation->at(iCombo) ){ (*(hContainer->find("HPSIsolation_L"))).second->GetHisto()->Fill(2.0, eventWeight); }
		if(Tau1hpsPFTauDiscriminationByVLooseIsolation->at(iCombo)){ (*(hContainer->find("HPSIsolation_L"))).second->GetHisto()->Fill(1.0, eventWeight); }
		else{														(*(hContainer->find("HPSIsolation_L"))).second->GetHisto()->Fill(0.0, eventWeight); }
	}

	if(hContainer->find("HPSIsolation_S") != hContainer->end()){
		if(Tau2hpsPFTauDiscriminationByTightIsolation->at(iCombo) ){ (*(hContainer->find("HPSIsolation_S"))).second->GetHisto()->Fill(4.0, eventWeight); }
		if(Tau2hpsPFTauDiscriminationByMediumIsolation->at(iCombo)){ (*(hContainer->find("HPSIsolation_S"))).second->GetHisto()->Fill(3.0, eventWeight); }
		if(Tau2hpsPFTauDiscriminationByLooseIsolation->at(iCombo) ){ (*(hContainer->find("HPSIsolation_S"))).second->GetHisto()->Fill(2.0, eventWeight); }
		if(Tau2hpsPFTauDiscriminationByVLooseIsolation->at(iCombo)){ (*(hContainer->find("HPSIsolation_S"))).second->GetHisto()->Fill(1.0, eventWeight); }
		else{														(*(hContainer->find("HPSIsolation_S"))).second->GetHisto()->Fill(0.0, eventWeight); }
	}

	if(hContainer->find("HPSDiscAgainstElectron_LS") != hContainer->end()){
		if(Tau1hpsPFTauDiscriminationAgainstTightElectron->at(iCombo) ){ (*(hContainer->find("HPSDiscAgainstElectron_LS"))).second->GetHisto()->Fill(3.0, eventWeight); }
		if(Tau1hpsPFTauDiscriminationAgainstMediumElectron->at(iCombo)){ (*(hContainer->find("HPSDiscAgainstElectron_LS"))).second->GetHisto()->Fill(2.0, eventWeight); }
		if(Tau1hpsPFTauDiscriminationAgainstLooseElectron->at(iCombo) ){ (*(hContainer->find("HPSDiscAgainstElectron_LS"))).second->GetHisto()->Fill(1.0, eventWeight); }
		else{														(*(hContainer->find("HPSDiscAgainstElectron_LS"))).second->GetHisto()->Fill(0.0, eventWeight); }

		if(Tau2hpsPFTauDiscriminationAgainstTightElectron->at(iCombo) ){ (*(hContainer->find("HPSDiscAgainstElectron_LS"))).second->GetHisto()->Fill(3.0, eventWeight); }
		if(Tau2hpsPFTauDiscriminationAgainstMediumElectron->at(iCombo)){ (*(hContainer->find("HPSDiscAgainstElectron_LS"))).second->GetHisto()->Fill(2.0, eventWeight); }
		if(Tau2hpsPFTauDiscriminationAgainstLooseElectron->at(iCombo) ){ (*(hContainer->find("HPSDiscAgainstElectron_LS"))).second->GetHisto()->Fill(1.0, eventWeight); }
		else{														(*(hContainer->find("HPSDiscAgainstElectron_LS"))).second->GetHisto()->Fill(0.0, eventWeight); }
	}

	if(hContainer->find("HPSDiscAgainstElectron_L") != hContainer->end()){
		if(Tau1hpsPFTauDiscriminationAgainstTightElectron->at(iCombo) ){ (*(hContainer->find("HPSDiscAgainstElectron_L"))).second->GetHisto()->Fill(3.0, eventWeight); }
		if(Tau1hpsPFTauDiscriminationAgainstMediumElectron->at(iCombo)){ (*(hContainer->find("HPSDiscAgainstElectron_L"))).second->GetHisto()->Fill(2.0, eventWeight); }
		if(Tau1hpsPFTauDiscriminationAgainstLooseElectron->at(iCombo) ){ (*(hContainer->find("HPSDiscAgainstElectron_L"))).second->GetHisto()->Fill(1.0, eventWeight); }
		else{														(*(hContainer->find("HPSDiscAgainstElectron_L"))).second->GetHisto()->Fill(0.0, eventWeight); }
	}

	if(hContainer->find("HPSDiscAgainstElectron_s") != hContainer->end()){
		if(Tau2hpsPFTauDiscriminationAgainstTightElectron->at(iCombo) ){ (*(hContainer->find("HPSDiscAgainstElectron_s"))).second->GetHisto()->Fill(3.0, eventWeight); }
		if(Tau2hpsPFTauDiscriminationAgainstMediumElectron->at(iCombo)){ (*(hContainer->find("HPSDiscAgainstElectron_s"))).second->GetHisto()->Fill(2.0, eventWeight); }
		if(Tau2hpsPFTauDiscriminationAgainstLooseElectron->at(iCombo) ){ (*(hContainer->find("HPSDiscAgainstElectron_s"))).second->GetHisto()->Fill(1.0, eventWeight); }
		else{														(*(hContainer->find("HPSDiscAgainstElectron_s"))).second->GetHisto()->Fill(0.0, eventWeight); }
	}

	if(hContainer->find("HPSDiscAgainstMuon_LS") != hContainer->end()){
		if(Tau1hpsPFTauDiscriminationAgainstTightMuon->at(iCombo) ){ (*(hContainer->find("HPSDiscAgainstMuon_LS"))).second->GetHisto()->Fill(2.0, eventWeight); }
		if(Tau1hpsPFTauDiscriminationAgainstLooseMuon->at(iCombo) ){ (*(hContainer->find("HPSDiscAgainstMuon_LS"))).second->GetHisto()->Fill(1.0, eventWeight); }
		else{														(*(hContainer->find("HPSDiscAgainstMuon_LS"))).second->GetHisto()->Fill(0.0, eventWeight); }

		if(Tau2hpsPFTauDiscriminationAgainstTightMuon->at(iCombo) ){ (*(hContainer->find("HPSDiscAgainstMuon_LS"))).second->GetHisto()->Fill(2.0, eventWeight); }
		if(Tau2hpsPFTauDiscriminationAgainstLooseMuon->at(iCombo) ){ (*(hContainer->find("HPSDiscAgainstMuon_LS"))).second->GetHisto()->Fill(1.0, eventWeight); }
		else{														(*(hContainer->find("HPSDiscAgainstMuon_LS"))).second->GetHisto()->Fill(0.0, eventWeight); }
	}

	if(hContainer->find("HPSDiscAgainstMuon_L") != hContainer->end()){
		if(Tau1hpsPFTauDiscriminationAgainstTightMuon->at(iCombo) ){ (*(hContainer->find("HPSDiscAgainstMuon_L"))).second->GetHisto()->Fill(2.0, eventWeight); }
		if(Tau1hpsPFTauDiscriminationAgainstLooseMuon->at(iCombo) ){ (*(hContainer->find("HPSDiscAgainstMuon_L"))).second->GetHisto()->Fill(1.0, eventWeight); }
		else{														(*(hContainer->find("HPSDiscAgainstMuon_L"))).second->GetHisto()->Fill(0.0, eventWeight); }
	}

	if(hContainer->find("HPSDiscAgainstMuon_S") != hContainer->end()){
		if(Tau2hpsPFTauDiscriminationAgainstTightMuon->at(iCombo) ){ (*(hContainer->find("HPSDiscAgainstMuon_S"))).second->GetHisto()->Fill(2.0, eventWeight); }
		if(Tau2hpsPFTauDiscriminationAgainstLooseMuon->at(iCombo) ){ (*(hContainer->find("HPSDiscAgainstMuon_S"))).second->GetHisto()->Fill(1.0, eventWeight); }
		else{														(*(hContainer->find("HPSDiscAgainstMuon_S"))).second->GetHisto()->Fill(0.0, eventWeight); }
	}

	/*
	if(hContainer->find("DecayMode_LS") != hContainer->end()){
		(*(hContainer->find("DecayMode_LS"))).second->GetHisto()->Fill(Tau1DecayMode->at(iCombo), eventWeight );
		(*(hContainer->find("DecayMode_LS"))).second->GetHisto()->Fill(Tau2DecayMode->at(iCombo), eventWeight );
	}

	if(hContainer->find("DecayMode_L") != hContainer->end()){
		(*(hContainer->find("DecayMode_L"))).second->GetHisto()->Fill(Tau1DecayMode->at(iCombo), eventWeight );
	}

	if(hContainer->find("DecayMode_S") != hContainer->end()){
		(*(hContainer->find("DecayMode_S"))).second->GetHisto()->Fill(Tau2DecayMode->at(iCombo), eventWeight );
	}

	if(hContainer->find("DecayModeFinding_LS") != hContainer->end()){
		(*(hContainer->find("DecayModeFinding_LS"))).second->GetHisto()->Fill(Tau1hpsPFTauDiscriminationByDecayModeFinding->at(iCombo), eventWeight );
		(*(hContainer->find("DecayModeFinding_LS"))).second->GetHisto()->Fill(Tau2hpsPFTauDiscriminationByDecayModeFinding->at(iCombo), eventWeight );
	}

	if(hContainer->find("DecayModeFinding_L") != hContainer->end()){
		(*(hContainer->find("DecayModeFinding_L"))).second->GetHisto()->Fill(Tau1hpsPFTauDiscriminationByDecayModeFinding->at(iCombo), eventWeight );
	}

	if(hContainer->find("DecayModeFinding_S") != hContainer->end()){
		(*(hContainer->find("DecayModeFinding_S"))).second->GetHisto()->Fill(Tau2hpsPFTauDiscriminationByDecayModeFinding->at(iCombo), eventWeight );
	}
	//*/

/*
	if(hContainer->find("Pt_LS") != hContainer->end()){
		(*(hContainer->find("Pt_LS"))).second->GetHisto()->Fill(Tau1Pt->at(iCombo), eventWeight );
		(*(hContainer->find("Pt_LS"))).second->GetHisto()->Fill(Tau2Pt->at(iCombo), eventWeight );
	}
	if(hContainer->find("Pt_LS_forNote") != hContainer->end()){
		(*(hContainer->find("Pt_LS_forNote"))).second->GetHisto()->Fill(Tau1Pt->at(iCombo), eventWeight );
		(*(hContainer->find("Pt_LS_forNote"))).second->GetHisto()->Fill(Tau2Pt->at(iCombo), eventWeight );
	}

	if(hContainer->find("Pt_L") != hContainer->end()){
		(*(hContainer->find("Pt_L"))).second->GetHisto()->Fill(Tau1Pt->at(iCombo), eventWeight );
	}
	if(hContainer->find("Pt_legTrigger_LS") != hContainer->end()){
		(*(hContainer->find("Pt_legTrigger_LS"))).second->GetHisto()->Fill(Tau1Pt->at(iCombo), tau1Weight );
		(*(hContainer->find("Pt_legTrigger_LS"))).second->GetHisto()->Fill(Tau2Pt->at(iCombo), tau2Weight );
	}

	if(hContainer->find("Pt_noTrigger_LS") != hContainer->end()){
		(*(hContainer->find("Pt_noTrigger_LS"))).second->GetHisto()->Fill(Tau1Pt->at(iCombo), PUweight );
		(*(hContainer->find("Pt_noTrigger_LS"))).second->GetHisto()->Fill(Tau2Pt->at(iCombo), PUweight );
	}

	if(hContainer->find("Pt_S") != hContainer->end()){
		(*(hContainer->find("Pt_S"))).second->GetHisto()->Fill(Tau2Pt->at(iCombo), eventWeight );
	}

	if(hContainer->find("LTpT_LS") != hContainer->end()){
		(*(hContainer->find("LTpT_LS"))).second->GetHisto()->Fill(Tau1LTPt->at(iCombo), eventWeight );
		(*(hContainer->find("LTpT_LS"))).second->GetHisto()->Fill(Tau2LTPt->at(iCombo), eventWeight );
	}

	if(hContainer->find("LTpT_L") != hContainer->end()){
		(*(hContainer->find("LTpT_L"))).second->GetHisto()->Fill(Tau1LTPt->at(iCombo), eventWeight );
	}

	if(hContainer->find("LTpT_S") != hContainer->end()){
		(*(hContainer->find("LTpT_S"))).second->GetHisto()->Fill(Tau2LTPt->at(iCombo), eventWeight );
	}

	if(hContainer->find("NumProngs_LS") != hContainer->end()){
		(*(hContainer->find("NumProngs_LS"))).second->GetHisto()->Fill(Tau1NProngs->at(iCombo), eventWeight );
		(*(hContainer->find("NumProngs_LS"))).second->GetHisto()->Fill(Tau2NProngs->at(iCombo), eventWeight );
	}

	if(hContainer->find("NumProngs_L") != hContainer->end()){
		(*(hContainer->find("NumProngs_L"))).second->GetHisto()->Fill(Tau1NProngs->at(iCombo), eventWeight );
	}
	
	if(hContainer->find("NumProngs_S") != hContainer->end()){
		(*(hContainer->find("NumProngs_S"))).second->GetHisto()->Fill(Tau2NProngs->at(iCombo), eventWeight );
	}

	if(hContainer->find("CosDeltaPhi_LM") != hContainer->end()){
		(*(hContainer->find("CosDeltaPhi_LM"))).second->GetHisto()->Fill(Tau1MetCosDphi->at(iCombo), eventWeight );
	}

	if(hContainer->find("CosDeltaPhi_SM") != hContainer->end()){
		(*(hContainer->find("CosDeltaPhi_SM"))).second->GetHisto()->Fill(Tau2MetCosDphi->at(iCombo), eventWeight );
	}

	if(hContainer->find("DeltaPhi_LM") != hContainer->end()){
		(*(hContainer->find("DeltaPhi_LM"))).second->GetHisto()->Fill(acos(Tau1MetCosDphi->at(iCombo)), eventWeight );
	}

	if(hContainer->find("DeltaPhi_SM") != hContainer->end()){
		(*(hContainer->find("DeltaPhi_SM"))).second->GetHisto()->Fill(acos(Tau2MetCosDphi->at(iCombo)), eventWeight );
	}

	if(hContainer->find("SumETotherJets") != hContainer->end()){
		(*(hContainer->find("SumETotherJets"))).second->GetHisto()->Fill(jetSumEt->at(iCombo), eventWeight);
	}

	if(hContainer->find("SumETotherJetsPlusMET") != hContainer->end()){
		(*(hContainer->find("SumETotherJetsPlusMET"))).second->GetHisto()->Fill(jetMETSumEt->at(iCombo), eventWeight);
	}

	if(hContainer->find("NumOtherJets") != hContainer->end()){
		(*(hContainer->find("NumOtherJets"))).second->GetHisto()->Fill(nJets->at(iCombo), eventWeight);
	}

	if(hContainer->find("EmFraction_LS") != hContainer->end()){
		(*(hContainer->find("EmFraction_LS"))).second->GetHisto()->Fill(Tau1EmFraction->at(iCombo), eventWeight );
		(*(hContainer->find("EmFraction_LS"))).second->GetHisto()->Fill(Tau2EmFraction->at(iCombo), eventWeight );
	}

	if(hContainer->find("ChargeProduct_LS") != hContainer->end()){
		(*(hContainer->find("ChargeProduct_LS"))).second->GetHisto()->Fill((Tau1Charge->at(iCombo) * Tau2Charge->at(iCombo)), eventWeight );
	}

	if(hContainer->find("SumPtIsoGammas_LS") != hContainer->end()){
		(*(hContainer->find("SumPtIsoGammas_LS"))).second->GetHisto()->Fill(Tau1SumPtIsoGammas->at(iCombo), eventWeight );
		(*(hContainer->find("SumPtIsoGammas_LS"))).second->GetHisto()->Fill(Tau2SumPtIsoGammas->at(iCombo), eventWeight );
	}

	if(hContainer->find("SumPtIsoGammas_L") != hContainer->end()){
		(*(hContainer->find("SumPtIsoGammas_L"))).second->GetHisto()->Fill(Tau1SumPtIsoGammas->at(iCombo), eventWeight );
	}
	
	if(hContainer->find("SumPtIsoGammas_S") != hContainer->end()){
		(*(hContainer->find("SumPtIsoGammas_S"))).second->GetHisto()->Fill(Tau1SumPtIsoGammas->at(iCombo), eventWeight );
	}

	if(hContainer->find("SumPtIsoTracks_LS") != hContainer->end()){
		(*(hContainer->find("SumPtIsoTracks_LS"))).second->GetHisto()->Fill(Tau1SumPtIsoTracks->at(iCombo), eventWeight );
		(*(hContainer->find("SumPtIsoTracks_LS"))).second->GetHisto()->Fill(Tau2SumPtIsoTracks->at(iCombo), eventWeight );
	}

	if(hContainer->find("SumPtIsoTracks_L") != hContainer->end()){
		(*(hContainer->find("SumPtIsoTracks_L"))).second->GetHisto()->Fill(Tau1SumPtIsoTracks->at(iCombo), eventWeight );
	}

	if(hContainer->find("SumPtIsoTracks_s") != hContainer->end()){
		(*(hContainer->find("SumPtIsoTracks_s"))).second->GetHisto()->Fill(Tau2SumPtIsoTracks->at(iCombo), eventWeight );
	}

	if(hContainer->find("Eta_LS") != hContainer->end()){
		(*(hContainer->find("Eta_LS"))).second->GetHisto()->Fill(Tau1Eta->at(iCombo), eventWeight );
		(*(hContainer->find("Eta_LS"))).second->GetHisto()->Fill(Tau2Eta->at(iCombo), eventWeight );
	}
	
	if(hContainer->find("Eta_L") != hContainer->end()){
		(*(hContainer->find("Eta_L"))).second->GetHisto()->Fill(Tau1Eta->at(iCombo), eventWeight );
	}

	if(hContainer->find("Eta_S") != hContainer->end()){
		(*(hContainer->find("Eta_S"))).second->GetHisto()->Fill(Tau2Eta->at(iCombo), eventWeight );
	}

	if(hContainer->find("Phi_LS") != hContainer->end()){
		(*(hContainer->find("Phi_LS"))).second->GetHisto()->Fill(Tau1Phi->at(iCombo), eventWeight );
		(*(hContainer->find("Phi_LS"))).second->GetHisto()->Fill(Tau2Phi->at(iCombo), eventWeight );
	}

	if(hContainer->find("Phi_L") != hContainer->end()){
		(*(hContainer->find("Phi_L"))).second->GetHisto()->Fill(Tau1Phi->at(iCombo), eventWeight );
	}

	if(hContainer->find("Phi_S") != hContainer->end()){
		(*(hContainer->find("Phi_S"))).second->GetHisto()->Fill(Tau2Phi->at(iCombo), eventWeight );
	}

	if(hContainer->find("CosDeltaPhi_LS") != hContainer->end()){
		(*(hContainer->find("CosDeltaPhi_LS"))).second->GetHisto()->Fill(TauTauCosDPhi->at(iCombo), eventWeight);
	}
	if(hContainer->find("CosDeltaEta_LS") != hContainer->end()){
		(*(hContainer->find("CosDeltaEta_LS"))).second->GetHisto()->Fill(cos(fabs(Tau1Eta->at(iCombo)-Tau2Eta->at(iCombo))), eventWeight);
	}
	if(hContainer->find("DeltaPhi_LS") != hContainer->end()){
		(*(hContainer->find("DeltaPhi_LS"))).second->GetHisto()->Fill((acos(cos(Tau1Phi->at(iCombo)-Tau2Phi->at(iCombo)))), eventWeight);
	}

	if(hContainer->find("DeltaEta_LS") != hContainer->end()){
		(*(hContainer->find("DeltaEta_LS"))).second->GetHisto()->Fill(fabs(Tau1Eta->at(iCombo)-Tau2Eta->at(iCombo)), eventWeight);
	}

	if(hContainer->find("DeltaR_LS") != hContainer->end()){
		(*(hContainer->find("DeltaR_LS"))).second->GetHisto()->Fill(TauTauDeltaR->at(iCombo), eventWeight);
	}

	if(hContainer->find("LTNumHits_LS") != hContainer->end()){
		(*(hContainer->find("LTNumHits_LS"))).second->GetHisto()->Fill(Tau1LTValidHits->at(iCombo), eventWeight );
		(*(hContainer->find("LTNumHits_LS"))).second->GetHisto()->Fill(Tau2LTValidHits->at(iCombo), eventWeight );
	}

	if(hContainer->find("PZeta_LSM") != hContainer->end()){
		(*(hContainer->find("PZeta_LSM"))).second->GetHisto()->Fill(TauTauPZeta->at(iCombo), eventWeight );
	}

	if(hContainer->find("PZetaVis_LSM") != hContainer->end()){
		(*(hContainer->find("PZetaVis_LSM"))).second->GetHisto()->Fill(TauTauPZetaVis->at(iCombo), eventWeight );
	}

	if(hContainer->find("Zeta_LSM") != hContainer->end()){
		(*(hContainer->find("Zeta_LSM"))).second->GetHisto()->Fill((TauTauPZeta->at(iCombo)-0.875*TauTauPZetaVis->at(iCombo)), eventWeight );
	}

	if(hContainer->find("Btags") != hContainer->end()){
		(*(hContainer->find("Btags"))).second->GetHisto()->Fill(nBtagsHiEffTrkCnt->at(iCombo), eventWeight );
	}

	if(hContainer->find("PtVsPt_LS") != hContainer->end()){
		((TH2F*)((*(hContainer->find("PtVsPt_LS"))).second->GetHisto()))->Fill(Tau2Pt->at(iCombo), Tau1Pt->at(iCombo), eventWeight );
	}

	if(hContainer->find("PtVsEta_LS") != hContainer->end()){
		((TH2F*)((*(hContainer->find("PtVsEta_LS"))).second->GetHisto()))->Fill((Tau1Eta->at(iCombo)), Tau1Pt->at(iCombo), eventWeight );
		((TH2F*)((*(hContainer->find("PtVsEta_LS"))).second->GetHisto()))->Fill((Tau2Eta->at(iCombo)), Tau2Pt->at(iCombo), eventWeight );
	}
	if(hContainer->find("PtVsEta_L") != hContainer->end()){
		((TH2F*)((*(hContainer->find("PtVsEta_L"))).second->GetHisto()))->Fill((Tau1Eta->at(iCombo)), Tau1Pt->at(iCombo), eventWeight );
	}
	if(hContainer->find("PtVsEta_S") != hContainer->end()){
		((TH2F*)((*(hContainer->find("PtVsEta_S"))).second->GetHisto()))->Fill((Tau2Eta->at(iCombo)), Tau2Pt->at(iCombo), eventWeight );
	}


	if(hContainer->find("PhiVsEta_LS") != hContainer->end()){
		float phi = Tau1Phi->at(iCombo);
		int laps = floor(fabs(phi)/(2*TMath::Pi()));
		if(phi<0){ laps++; }
		phi+=(laps*2*TMath::Pi());
		((TH2F*)((*(hContainer->find("PhiVsEta_LS"))).second->GetHisto()))->Fill((Tau1Eta->at(iCombo)), phi, eventWeight );

		phi = Tau2Phi->at(iCombo);
		laps = floor(fabs(phi)/(2*TMath::Pi()));
		if(phi<0){ laps++; }
		phi+=(laps*2*TMath::Pi());

		((TH2F*)((*(hContainer->find("PhiVsEta_LS"))).second->GetHisto()))->Fill((Tau2Eta->at(iCombo)), phi, eventWeight );
	}

	if(hContainer->find("PhiVsEta_L") != hContainer->end()){
		float phi = Tau1Phi->at(iCombo);
		int laps = floor(fabs(phi)/(2*TMath::Pi()));
		if(phi<0){ laps++; }
		phi+=(laps*2*TMath::Pi());
		((TH2F*)((*(hContainer->find("PhiVsEta_L"))).second->GetHisto()))->Fill((Tau1Eta->at(iCombo)), phi, eventWeight );
	}

	if(hContainer->find("PhiVsEta_S") != hContainer->end()){
		float phi = Tau2Phi->at(iCombo);
		int laps = floor(fabs(phi)/(2*TMath::Pi()));
		if(phi<0){ laps++; }
		phi+=(laps*2*TMath::Pi());
		((TH2F*)((*(hContainer->find("PhiVsEta_S"))).second->GetHisto()))->Fill((Tau2Eta->at(iCombo)), phi, eventWeight );
	}

	if(hContainer->find("EtaVsEta_LS") != hContainer->end()){
		((TH2F*)((*(hContainer->find("EtaVsEta_LS"))).second->GetHisto()))->Fill(Tau2Eta->at(iCombo), Tau1Eta->at(iCombo), eventWeight );
	}

	if(hContainer->find("DeltaPhiVsDeltaEta_LS") != hContainer->end()){
		((TH2F*)((*(hContainer->find("DeltaPhiVsDeltaEta_LS"))).second->GetHisto()))->Fill(fabs(Tau1Eta->at(iCombo)-Tau2Eta->at(iCombo)), acos(cos(Tau1Phi->at(iCombo)-Tau2Phi->at(iCombo))), eventWeight );
	}
	
	if(hContainer->find("CosDeltaPhiVsCosDeltaEta_LS") != hContainer->end()){
		((TH2F*)((*(hContainer->find("CosDeltaPhiVsCosDeltaEta_LS"))).second->GetHisto()))->Fill(cos(Tau1Eta->at(iCombo)-Tau2Eta->at(iCombo)), cos(Tau1Phi->at(iCombo)-Tau2Phi->at(iCombo)), eventWeight );
	}

	if(hContainer->find("EtaVSNumPV_L") != hContainer->end()){
		((TH2F*)((*(hContainer->find("EtaVSNumPV_L"))).second->GetHisto()))->Fill(NumPV->at(iCombo),fabs(Tau1Eta->at(iCombo)), eventWeight );
	}
	if(hContainer->find("EtaVSNumPV_S") != hContainer->end()){
		((TH2F*)((*(hContainer->find("EtaVSNumPV_S"))).second->GetHisto()))->Fill(NumPV->at(iCombo),fabs(Tau2Eta->at(iCombo)), eventWeight );
	}
	if(hContainer->find("PtVSNumPV_L") != hContainer->end()){
		((TH2F*)((*(hContainer->find("PtVSNumPV_L"))).second->GetHisto()))->Fill(NumPV->at(iCombo),Tau1Pt->at(iCombo), eventWeight );
	}
	if(hContainer->find("PtVSNumPV_S") != hContainer->end()){
		((TH2F*)((*(hContainer->find("PtVSNumPV_S"))).second->GetHisto()))->Fill(NumPV->at(iCombo),Tau2Pt->at(iCombo), eventWeight );
	}
	if(hContainer->find("CosDeltaPhiVSNumPV_LS") != hContainer->end()){
		((TH2F*)((*(hContainer->find("CosDeltaPhiVSNumPV_LS"))).second->GetHisto()))->Fill(NumPV->at(iCombo),TauTauCosDPhi->at(iCombo), eventWeight );
	}




	// ===================== Tau-Electron matching plots ========================= //
	/*
	if(hContainer->find("MatchedElecPt_L") != hContainer->end()){
		(*(hContainer->find("MatchedElecPt_L"))).second->GetHisto()->Fill(Tau1MElecPt->at(iCombo), eventWeight );
	}
	if(hContainer->find("MatchedElecPt_S") != hContainer->end()){
		(*(hContainer->find("MatchedElecPt_S"))).second->GetHisto()->Fill(Tau2MElecPt->at(iCombo), eventWeight );
	}

	if(hContainer->find("MatchedElecPtDiff_L") != hContainer->end()){
		(*(hContainer->find("MatchedElecPtDiff_L"))).second->GetHisto()->Fill(Tau1MElecPt->at(iCombo)-Tau1Pt->at(iCombo), eventWeight );
	}
	if(hContainer->find("MatchedElecPtDiff_S") != hContainer->end()){
		(*(hContainer->find("MatchedElecPtDiff_S"))).second->GetHisto()->Fill(Tau2MElecPt->at(iCombo)-Tau2Pt->at(iCombo), eventWeight );
	}

	if(hContainer->find("MatchedElecDeltaR_L") != hContainer->end()){
		(*(hContainer->find("MatchedElecDeltaR_L"))).second->GetHisto()->Fill(Tau1MElecDeltaR->at(iCombo), eventWeight );
	}
	if(hContainer->find("MatchedElecDeltaR_S") != hContainer->end()){
		(*(hContainer->find("MatchedElecDeltaR_S"))).second->GetHisto()->Fill(Tau2MElecDeltaR->at(iCombo), eventWeight );
	}


	// Isolation
	if(hContainer->find("MatchedElecIsoTrkSumPt_L") != hContainer->end()){
		(*(hContainer->find("MatchedElecIsoTrkSumPt_L"))).second->GetHisto()->Fill(Tau1MElecTrkSumPt->at(iCombo), eventWeight );
	}
	if(hContainer->find("MatchedElecIsoTrkSumPt_S") != hContainer->end()){
		(*(hContainer->find("MatchedElecIsoTrkSumPt_S"))).second->GetHisto()->Fill(Tau2MElecTrkSumPt->at(iCombo), eventWeight );
	}
	if(hContainer->find("MatchedElecEcalIsoRecHitSumEt_L") != hContainer->end()){
		(*(hContainer->find("MatchedElecEcalIsoRecHitSumEt_L"))).second->GetHisto()->Fill(Tau1MElecEcalRecHitSumEt->at(iCombo), eventWeight );
	}
	if(hContainer->find("MatchedElecEcalIsoRecHitSumEt_S") != hContainer->end()){
		(*(hContainer->find("MatchedElecEcalIsoRecHitSumEt_S"))).second->GetHisto()->Fill(Tau2MElecEcalRecHitSumEt->at(iCombo), eventWeight );
	}

	// Isolation diff
	if(hContainer->find("MatchedElecIsoTrkSumPtDiff_L") != hContainer->end()){
		(*(hContainer->find("MatchedElecIsoTrkSumPtDiff_L"))).second->GetHisto()->Fill(Tau1SumPtIsoTracks->at(iCombo)-Tau1MElecTrkSumPt->at(iCombo), eventWeight );
	}
	if(hContainer->find("MatchedElecIsoTrkSumPtDiff_S") != hContainer->end()){
		(*(hContainer->find("MatchedElecIsoTrkSumPtDiff_S"))).second->GetHisto()->Fill(Tau2SumPtIsoTracks->at(iCombo)-Tau2MElecTrkSumPt->at(iCombo), eventWeight );
	}
	if(hContainer->find("MatchedElecEcalIsoRecHitSumEtDiff_L") != hContainer->end()){
		(*(hContainer->find("MatchedElecEcalIsoRecHitSumEtDiff_L"))).second->GetHisto()->Fill(Tau1SumPtIsoGammas->at(iCombo)-Tau1MElecEcalRecHitSumEt->at(iCombo), eventWeight );
	}
	if(hContainer->find("MatchedElecEcalIsoRecHitSumEtDiff_S") != hContainer->end()){
		(*(hContainer->find("MatchedElecEcalIsoRecHitSumEtDiff_S"))).second->GetHisto()->Fill(Tau2SumPtIsoGammas->at(iCombo)-Tau2MElecEcalRecHitSumEt->at(iCombo), eventWeight );
	}//*/

/*
	if(isMC && IsFlagThere("PUcorr")){ 
		if(hContainer->find("PUweightsPassingEvents") != hContainer->end()){
			(*(hContainer->find("PUweightsPassingEvents"))).second->GetHisto()->Fill(puCorrector->GetWeight(NumPV->at(iCombo)));
		}
	}

	//*/

