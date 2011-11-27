
//void Analyzer::FillHistos(map<string, HistoWrapper*>* iHistos, int iCombo, double iPuWeight, double iTau1TriggerWeight, double iTau2TriggerWeight){



	if(iHistos->find("NumPV_b4RW") != iHistos->end()){
		(*(iHistos->find("NumPV_b4RW"))).second->GetHisto()->Fill(NumPV->at(iCombo));
	}

	if(iHistos->find("MET_M") != iHistos->end()){
		(*(iHistos->find("MET_M"))).second->GetHisto()->Fill(MET->at(iCombo), iPuWeight*iTau1TriggerWeight*iTau2TriggerWeight);
	}


	if(iHistos->find("Btags") != iHistos->end()){
		(*(iHistos->find("Btags"))).second->GetHisto()->Fill(nBtagsHiEffTrkCnt->at(iCombo), iPuWeight*iTau1TriggerWeight*iTau2TriggerWeight);
	}

	/*

	if(iHistos->find("NumPV_afRW") != iHistos->end()){
		(*(iHistos->find("NumPV_afRW"))).second->GetHisto()->Fill(NumPV->at(iCombo), puCorrector->GetWeight(numInteractionsBX0));
	}

	if(iHistos->find("NumInteractionsBX0_b4RW") != iHistos->end()){
		(*(iHistos->find("NumInteractionsBX0_b4RW"))).second->GetHisto()->Fill(numInteractionsBX0);
	}

	if(iHistos->find("NumInteractionsBX0_afRW") != iHistos->end()){
		(*(iHistos->find("NumInteractionsBX0_afRW"))).second->GetHisto()->Fill(numInteractionsBX0, puCorrector->GetWeight(numInteractionsBX0));
	}

	// Filling of histos
	if(iHistos->find("InvariantMass_LSM") != iHistos->end()){
		(*(iHistos->find("InvariantMass_LSM"))).second->GetHisto()->Fill(TauTauVisPlusMetMass->at(iCombo), eventWeight);
	}
	if(iHistos->find("InvariantMass_LSM_forTTbar") != iHistos->end()){
		(*(iHistos->find("InvariantMass_LSM_forTTbar"))).second->GetHisto()->Fill(TauTauVisPlusMetMass->at(iCombo), eventWeight);
	}
	if(iHistos->find("InvariantMass_LSM_forNote1") != iHistos->end()){
		(*(iHistos->find("InvariantMass_LSM_forNote1"))).second->GetHisto()->Fill(TauTauVisPlusMetMass->at(iCombo), eventWeight);
	}
	if(iHistos->find("InvariantMass_LSM_forNote2") != iHistos->end()){
		(*(iHistos->find("InvariantMass_LSM_forNote2"))).second->GetHisto()->Fill(TauTauVisPlusMetMass->at(iCombo), eventWeight);
	}

	if(iHistos->find("VisibleMass_LS") != iHistos->end()){
		(*(iHistos->find("VisibleMass_LS"))).second->GetHisto()->Fill(TauTauVisibleMass->at(iCombo), eventWeight);
	}

	if(iHistos->find("VisibleMass_LS_forNote1") != iHistos->end()){
		(*(iHistos->find("VisibleMass_LS_forNote1"))).second->GetHisto()->Fill(TauTauVisibleMass->at(iCombo), eventWeight);
	}
	if(iHistos->find("VisibleMass_LS_forNote2") != iHistos->end()){
		(*(iHistos->find("VisibleMass_LS_forNote2"))).second->GetHisto()->Fill(TauTauVisibleMass->at(iCombo), eventWeight);
	}


	if(iHistos->find("MET_M_forNote") != iHistos->end()){
		(*(iHistos->find("MET_M_forNote"))).second->GetHisto()->Fill(mEt->at(iCombo), eventWeight);
	}

	if(FoundHisto("VSumPt_LS")){ 
		float cosdphi	= TauTauCosDPhi->at(iCombo);
		float sindphi	= sin(acos(cosdphi));
		float sumptx	= Tau1Pt->at(iCombo) + (Tau2Pt->at(iCombo))*cosdphi;
		float sumpty	= 					 (Tau2Pt->at(iCombo))*sindphi;
		float sumPt		= sqrt(pow(sumptx,2) + pow(sumpty,2));
		GetHisto("VSumPt_LS")->Fill(sumPt, eventWeight);
	}


	if(iHistos->find("TransverseMass_LM") != iHistos->end()){
		(*(iHistos->find("TransverseMass_LM"))).second->GetHisto()->Fill(Tau1MetMt->at(iCombo), eventWeight);
	}
	if(iHistos->find("TransverseMass_LM_forNote") != iHistos->end()){
		(*(iHistos->find("TransverseMass_LM_forNote"))).second->GetHisto()->Fill(Tau1MetMt->at(iCombo), eventWeight);
	}

	if(iHistos->find("TransverseMass_legTrigger_LM") != iHistos->end()){
		(*(iHistos->find("TransverseMass_legTrigger_LM"))).second->GetHisto()->Fill(Tau1MetMt->at(iCombo), tau1Weight);
	}
	if(iHistos->find("TransverseMass_legTrigger_log_LM") != iHistos->end()){
		(*(iHistos->find("TransverseMass_legTrigger_log_LM"))).second->GetHisto()->Fill(Tau1MetMt->at(iCombo), tau1Weight);
	}

	if(iHistos->find("TransverseMass_SM") != iHistos->end()){
		(*(iHistos->find("TransverseMass_SM"))).second->GetHisto()->Fill(Tau2MetMt->at(iCombo), eventWeight);
	}
	if(iHistos->find("TransverseMass_SM_forNote") != iHistos->end()){
		(*(iHistos->find("TransverseMass_SM_forNote"))).second->GetHisto()->Fill(Tau2MetMt->at(iCombo), eventWeight);
	}

	if(iHistos->find("NumPV") != iHistos->end()){
		(*(iHistos->find("NumPV"))).second->GetHisto()->Fill(NumPV->at(iCombo), eventWeight);
	}
	
	if(iHistos->find("HPSIsolation_LS") != iHistos->end()){
		if(Tau1hpsPFTauDiscriminationByTightIsolation->at(iCombo) ){ (*(iHistos->find("HPSIsolation_LS"))).second->GetHisto()->Fill(4.0, eventWeight); }
		if(Tau1hpsPFTauDiscriminationByMediumIsolation->at(iCombo)){ (*(iHistos->find("HPSIsolation_LS"))).second->GetHisto()->Fill(3.0, eventWeight); }
		if(Tau1hpsPFTauDiscriminationByLooseIsolation->at(iCombo) ){ (*(iHistos->find("HPSIsolation_LS"))).second->GetHisto()->Fill(2.0, eventWeight); }
		if(Tau1hpsPFTauDiscriminationByVLooseIsolation->at(iCombo)){ (*(iHistos->find("HPSIsolation_LS"))).second->GetHisto()->Fill(1.0, eventWeight); }
		else{														(*(iHistos->find("HPSIsolation_LS"))).second->GetHisto()->Fill(0.0, eventWeight); }

		if(Tau2hpsPFTauDiscriminationByTightIsolation->at(iCombo) ){ (*(iHistos->find("HPSIsolation_LS"))).second->GetHisto()->Fill(4.0, eventWeight); }
		if(Tau2hpsPFTauDiscriminationByMediumIsolation->at(iCombo)){ (*(iHistos->find("HPSIsolation_LS"))).second->GetHisto()->Fill(3.0, eventWeight); }
		if(Tau2hpsPFTauDiscriminationByLooseIsolation->at(iCombo) ){ (*(iHistos->find("HPSIsolation_LS"))).second->GetHisto()->Fill(2.0, eventWeight); }
		if(Tau2hpsPFTauDiscriminationByVLooseIsolation->at(iCombo)){ (*(iHistos->find("HPSIsolation_LS"))).second->GetHisto()->Fill(1.0, eventWeight); }
		else{														(*(iHistos->find("HPSIsolation_LS"))).second->GetHisto()->Fill(0.0, eventWeight); }
	}

	if(iHistos->find("HPSIsolation_L") != iHistos->end()){
		if(Tau1hpsPFTauDiscriminationByTightIsolation->at(iCombo) ){ (*(iHistos->find("HPSIsolation_L"))).second->GetHisto()->Fill(4.0, eventWeight); }
		if(Tau1hpsPFTauDiscriminationByMediumIsolation->at(iCombo)){ (*(iHistos->find("HPSIsolation_L"))).second->GetHisto()->Fill(3.0, eventWeight); }
		if(Tau1hpsPFTauDiscriminationByLooseIsolation->at(iCombo) ){ (*(iHistos->find("HPSIsolation_L"))).second->GetHisto()->Fill(2.0, eventWeight); }
		if(Tau1hpsPFTauDiscriminationByVLooseIsolation->at(iCombo)){ (*(iHistos->find("HPSIsolation_L"))).second->GetHisto()->Fill(1.0, eventWeight); }
		else{														(*(iHistos->find("HPSIsolation_L"))).second->GetHisto()->Fill(0.0, eventWeight); }
	}

	if(iHistos->find("HPSIsolation_S") != iHistos->end()){
		if(Tau2hpsPFTauDiscriminationByTightIsolation->at(iCombo) ){ (*(iHistos->find("HPSIsolation_S"))).second->GetHisto()->Fill(4.0, eventWeight); }
		if(Tau2hpsPFTauDiscriminationByMediumIsolation->at(iCombo)){ (*(iHistos->find("HPSIsolation_S"))).second->GetHisto()->Fill(3.0, eventWeight); }
		if(Tau2hpsPFTauDiscriminationByLooseIsolation->at(iCombo) ){ (*(iHistos->find("HPSIsolation_S"))).second->GetHisto()->Fill(2.0, eventWeight); }
		if(Tau2hpsPFTauDiscriminationByVLooseIsolation->at(iCombo)){ (*(iHistos->find("HPSIsolation_S"))).second->GetHisto()->Fill(1.0, eventWeight); }
		else{														(*(iHistos->find("HPSIsolation_S"))).second->GetHisto()->Fill(0.0, eventWeight); }
	}

	if(iHistos->find("HPSDiscAgainstElectron_LS") != iHistos->end()){
		if(Tau1hpsPFTauDiscriminationAgainstTightElectron->at(iCombo) ){ (*(iHistos->find("HPSDiscAgainstElectron_LS"))).second->GetHisto()->Fill(3.0, eventWeight); }
		if(Tau1hpsPFTauDiscriminationAgainstMediumElectron->at(iCombo)){ (*(iHistos->find("HPSDiscAgainstElectron_LS"))).second->GetHisto()->Fill(2.0, eventWeight); }
		if(Tau1hpsPFTauDiscriminationAgainstLooseElectron->at(iCombo) ){ (*(iHistos->find("HPSDiscAgainstElectron_LS"))).second->GetHisto()->Fill(1.0, eventWeight); }
		else{														(*(iHistos->find("HPSDiscAgainstElectron_LS"))).second->GetHisto()->Fill(0.0, eventWeight); }

		if(Tau2hpsPFTauDiscriminationAgainstTightElectron->at(iCombo) ){ (*(iHistos->find("HPSDiscAgainstElectron_LS"))).second->GetHisto()->Fill(3.0, eventWeight); }
		if(Tau2hpsPFTauDiscriminationAgainstMediumElectron->at(iCombo)){ (*(iHistos->find("HPSDiscAgainstElectron_LS"))).second->GetHisto()->Fill(2.0, eventWeight); }
		if(Tau2hpsPFTauDiscriminationAgainstLooseElectron->at(iCombo) ){ (*(iHistos->find("HPSDiscAgainstElectron_LS"))).second->GetHisto()->Fill(1.0, eventWeight); }
		else{														(*(iHistos->find("HPSDiscAgainstElectron_LS"))).second->GetHisto()->Fill(0.0, eventWeight); }
	}

	if(iHistos->find("HPSDiscAgainstElectron_L") != iHistos->end()){
		if(Tau1hpsPFTauDiscriminationAgainstTightElectron->at(iCombo) ){ (*(iHistos->find("HPSDiscAgainstElectron_L"))).second->GetHisto()->Fill(3.0, eventWeight); }
		if(Tau1hpsPFTauDiscriminationAgainstMediumElectron->at(iCombo)){ (*(iHistos->find("HPSDiscAgainstElectron_L"))).second->GetHisto()->Fill(2.0, eventWeight); }
		if(Tau1hpsPFTauDiscriminationAgainstLooseElectron->at(iCombo) ){ (*(iHistos->find("HPSDiscAgainstElectron_L"))).second->GetHisto()->Fill(1.0, eventWeight); }
		else{														(*(iHistos->find("HPSDiscAgainstElectron_L"))).second->GetHisto()->Fill(0.0, eventWeight); }
	}

	if(iHistos->find("HPSDiscAgainstElectron_s") != iHistos->end()){
		if(Tau2hpsPFTauDiscriminationAgainstTightElectron->at(iCombo) ){ (*(iHistos->find("HPSDiscAgainstElectron_s"))).second->GetHisto()->Fill(3.0, eventWeight); }
		if(Tau2hpsPFTauDiscriminationAgainstMediumElectron->at(iCombo)){ (*(iHistos->find("HPSDiscAgainstElectron_s"))).second->GetHisto()->Fill(2.0, eventWeight); }
		if(Tau2hpsPFTauDiscriminationAgainstLooseElectron->at(iCombo) ){ (*(iHistos->find("HPSDiscAgainstElectron_s"))).second->GetHisto()->Fill(1.0, eventWeight); }
		else{														(*(iHistos->find("HPSDiscAgainstElectron_s"))).second->GetHisto()->Fill(0.0, eventWeight); }
	}

	if(iHistos->find("HPSDiscAgainstMuon_LS") != iHistos->end()){
		if(Tau1hpsPFTauDiscriminationAgainstTightMuon->at(iCombo) ){ (*(iHistos->find("HPSDiscAgainstMuon_LS"))).second->GetHisto()->Fill(2.0, eventWeight); }
		if(Tau1hpsPFTauDiscriminationAgainstLooseMuon->at(iCombo) ){ (*(iHistos->find("HPSDiscAgainstMuon_LS"))).second->GetHisto()->Fill(1.0, eventWeight); }
		else{														(*(iHistos->find("HPSDiscAgainstMuon_LS"))).second->GetHisto()->Fill(0.0, eventWeight); }

		if(Tau2hpsPFTauDiscriminationAgainstTightMuon->at(iCombo) ){ (*(iHistos->find("HPSDiscAgainstMuon_LS"))).second->GetHisto()->Fill(2.0, eventWeight); }
		if(Tau2hpsPFTauDiscriminationAgainstLooseMuon->at(iCombo) ){ (*(iHistos->find("HPSDiscAgainstMuon_LS"))).second->GetHisto()->Fill(1.0, eventWeight); }
		else{														(*(iHistos->find("HPSDiscAgainstMuon_LS"))).second->GetHisto()->Fill(0.0, eventWeight); }
	}

	if(iHistos->find("HPSDiscAgainstMuon_L") != iHistos->end()){
		if(Tau1hpsPFTauDiscriminationAgainstTightMuon->at(iCombo) ){ (*(iHistos->find("HPSDiscAgainstMuon_L"))).second->GetHisto()->Fill(2.0, eventWeight); }
		if(Tau1hpsPFTauDiscriminationAgainstLooseMuon->at(iCombo) ){ (*(iHistos->find("HPSDiscAgainstMuon_L"))).second->GetHisto()->Fill(1.0, eventWeight); }
		else{														(*(iHistos->find("HPSDiscAgainstMuon_L"))).second->GetHisto()->Fill(0.0, eventWeight); }
	}

	if(iHistos->find("HPSDiscAgainstMuon_S") != iHistos->end()){
		if(Tau2hpsPFTauDiscriminationAgainstTightMuon->at(iCombo) ){ (*(iHistos->find("HPSDiscAgainstMuon_S"))).second->GetHisto()->Fill(2.0, eventWeight); }
		if(Tau2hpsPFTauDiscriminationAgainstLooseMuon->at(iCombo) ){ (*(iHistos->find("HPSDiscAgainstMuon_S"))).second->GetHisto()->Fill(1.0, eventWeight); }
		else{														(*(iHistos->find("HPSDiscAgainstMuon_S"))).second->GetHisto()->Fill(0.0, eventWeight); }
	}

	/*
	if(iHistos->find("DecayMode_LS") != iHistos->end()){
		(*(iHistos->find("DecayMode_LS"))).second->GetHisto()->Fill(Tau1DecayMode->at(iCombo), eventWeight );
		(*(iHistos->find("DecayMode_LS"))).second->GetHisto()->Fill(Tau2DecayMode->at(iCombo), eventWeight );
	}

	if(iHistos->find("DecayMode_L") != iHistos->end()){
		(*(iHistos->find("DecayMode_L"))).second->GetHisto()->Fill(Tau1DecayMode->at(iCombo), eventWeight );
	}

	if(iHistos->find("DecayMode_S") != iHistos->end()){
		(*(iHistos->find("DecayMode_S"))).second->GetHisto()->Fill(Tau2DecayMode->at(iCombo), eventWeight );
	}

	if(iHistos->find("DecayModeFinding_LS") != iHistos->end()){
		(*(iHistos->find("DecayModeFinding_LS"))).second->GetHisto()->Fill(Tau1hpsPFTauDiscriminationByDecayModeFinding->at(iCombo), eventWeight );
		(*(iHistos->find("DecayModeFinding_LS"))).second->GetHisto()->Fill(Tau2hpsPFTauDiscriminationByDecayModeFinding->at(iCombo), eventWeight );
	}

	if(iHistos->find("DecayModeFinding_L") != iHistos->end()){
		(*(iHistos->find("DecayModeFinding_L"))).second->GetHisto()->Fill(Tau1hpsPFTauDiscriminationByDecayModeFinding->at(iCombo), eventWeight );
	}

	if(iHistos->find("DecayModeFinding_S") != iHistos->end()){
		(*(iHistos->find("DecayModeFinding_S"))).second->GetHisto()->Fill(Tau2hpsPFTauDiscriminationByDecayModeFinding->at(iCombo), eventWeight );
	}
	//*/

/*
	if(iHistos->find("Pt_LS") != iHistos->end()){
		(*(iHistos->find("Pt_LS"))).second->GetHisto()->Fill(Tau1Pt->at(iCombo), eventWeight );
		(*(iHistos->find("Pt_LS"))).second->GetHisto()->Fill(Tau2Pt->at(iCombo), eventWeight );
	}
	if(iHistos->find("Pt_LS_forNote") != iHistos->end()){
		(*(iHistos->find("Pt_LS_forNote"))).second->GetHisto()->Fill(Tau1Pt->at(iCombo), eventWeight );
		(*(iHistos->find("Pt_LS_forNote"))).second->GetHisto()->Fill(Tau2Pt->at(iCombo), eventWeight );
	}

	if(iHistos->find("Pt_L") != iHistos->end()){
		(*(iHistos->find("Pt_L"))).second->GetHisto()->Fill(Tau1Pt->at(iCombo), eventWeight );
	}
	if(iHistos->find("Pt_legTrigger_LS") != iHistos->end()){
		(*(iHistos->find("Pt_legTrigger_LS"))).second->GetHisto()->Fill(Tau1Pt->at(iCombo), tau1Weight );
		(*(iHistos->find("Pt_legTrigger_LS"))).second->GetHisto()->Fill(Tau2Pt->at(iCombo), tau2Weight );
	}

	if(iHistos->find("Pt_noTrigger_LS") != iHistos->end()){
		(*(iHistos->find("Pt_noTrigger_LS"))).second->GetHisto()->Fill(Tau1Pt->at(iCombo), PUweight );
		(*(iHistos->find("Pt_noTrigger_LS"))).second->GetHisto()->Fill(Tau2Pt->at(iCombo), PUweight );
	}

	if(iHistos->find("Pt_S") != iHistos->end()){
		(*(iHistos->find("Pt_S"))).second->GetHisto()->Fill(Tau2Pt->at(iCombo), eventWeight );
	}

	if(iHistos->find("LTpT_LS") != iHistos->end()){
		(*(iHistos->find("LTpT_LS"))).second->GetHisto()->Fill(Tau1LTPt->at(iCombo), eventWeight );
		(*(iHistos->find("LTpT_LS"))).second->GetHisto()->Fill(Tau2LTPt->at(iCombo), eventWeight );
	}

	if(iHistos->find("LTpT_L") != iHistos->end()){
		(*(iHistos->find("LTpT_L"))).second->GetHisto()->Fill(Tau1LTPt->at(iCombo), eventWeight );
	}

	if(iHistos->find("LTpT_S") != iHistos->end()){
		(*(iHistos->find("LTpT_S"))).second->GetHisto()->Fill(Tau2LTPt->at(iCombo), eventWeight );
	}

	if(iHistos->find("NumProngs_LS") != iHistos->end()){
		(*(iHistos->find("NumProngs_LS"))).second->GetHisto()->Fill(Tau1NProngs->at(iCombo), eventWeight );
		(*(iHistos->find("NumProngs_LS"))).second->GetHisto()->Fill(Tau2NProngs->at(iCombo), eventWeight );
	}

	if(iHistos->find("NumProngs_L") != iHistos->end()){
		(*(iHistos->find("NumProngs_L"))).second->GetHisto()->Fill(Tau1NProngs->at(iCombo), eventWeight );
	}
	
	if(iHistos->find("NumProngs_S") != iHistos->end()){
		(*(iHistos->find("NumProngs_S"))).second->GetHisto()->Fill(Tau2NProngs->at(iCombo), eventWeight );
	}

	if(iHistos->find("CosDeltaPhi_LM") != iHistos->end()){
		(*(iHistos->find("CosDeltaPhi_LM"))).second->GetHisto()->Fill(Tau1MetCosDphi->at(iCombo), eventWeight );
	}

	if(iHistos->find("CosDeltaPhi_SM") != iHistos->end()){
		(*(iHistos->find("CosDeltaPhi_SM"))).second->GetHisto()->Fill(Tau2MetCosDphi->at(iCombo), eventWeight );
	}

	if(iHistos->find("DeltaPhi_LM") != iHistos->end()){
		(*(iHistos->find("DeltaPhi_LM"))).second->GetHisto()->Fill(acos(Tau1MetCosDphi->at(iCombo)), eventWeight );
	}

	if(iHistos->find("DeltaPhi_SM") != iHistos->end()){
		(*(iHistos->find("DeltaPhi_SM"))).second->GetHisto()->Fill(acos(Tau2MetCosDphi->at(iCombo)), eventWeight );
	}

	if(iHistos->find("SumETotherJets") != iHistos->end()){
		(*(iHistos->find("SumETotherJets"))).second->GetHisto()->Fill(jetSumEt->at(iCombo), eventWeight);
	}

	if(iHistos->find("SumETotherJetsPlusMET") != iHistos->end()){
		(*(iHistos->find("SumETotherJetsPlusMET"))).second->GetHisto()->Fill(jetMETSumEt->at(iCombo), eventWeight);
	}

	if(iHistos->find("NumOtherJets") != iHistos->end()){
		(*(iHistos->find("NumOtherJets"))).second->GetHisto()->Fill(nJets->at(iCombo), eventWeight);
	}

	if(iHistos->find("EmFraction_LS") != iHistos->end()){
		(*(iHistos->find("EmFraction_LS"))).second->GetHisto()->Fill(Tau1EmFraction->at(iCombo), eventWeight );
		(*(iHistos->find("EmFraction_LS"))).second->GetHisto()->Fill(Tau2EmFraction->at(iCombo), eventWeight );
	}

	if(iHistos->find("ChargeProduct_LS") != iHistos->end()){
		(*(iHistos->find("ChargeProduct_LS"))).second->GetHisto()->Fill((Tau1Charge->at(iCombo) * Tau2Charge->at(iCombo)), eventWeight );
	}

	if(iHistos->find("SumPtIsoGammas_LS") != iHistos->end()){
		(*(iHistos->find("SumPtIsoGammas_LS"))).second->GetHisto()->Fill(Tau1SumPtIsoGammas->at(iCombo), eventWeight );
		(*(iHistos->find("SumPtIsoGammas_LS"))).second->GetHisto()->Fill(Tau2SumPtIsoGammas->at(iCombo), eventWeight );
	}

	if(iHistos->find("SumPtIsoGammas_L") != iHistos->end()){
		(*(iHistos->find("SumPtIsoGammas_L"))).second->GetHisto()->Fill(Tau1SumPtIsoGammas->at(iCombo), eventWeight );
	}
	
	if(iHistos->find("SumPtIsoGammas_S") != iHistos->end()){
		(*(iHistos->find("SumPtIsoGammas_S"))).second->GetHisto()->Fill(Tau1SumPtIsoGammas->at(iCombo), eventWeight );
	}

	if(iHistos->find("SumPtIsoTracks_LS") != iHistos->end()){
		(*(iHistos->find("SumPtIsoTracks_LS"))).second->GetHisto()->Fill(Tau1SumPtIsoTracks->at(iCombo), eventWeight );
		(*(iHistos->find("SumPtIsoTracks_LS"))).second->GetHisto()->Fill(Tau2SumPtIsoTracks->at(iCombo), eventWeight );
	}

	if(iHistos->find("SumPtIsoTracks_L") != iHistos->end()){
		(*(iHistos->find("SumPtIsoTracks_L"))).second->GetHisto()->Fill(Tau1SumPtIsoTracks->at(iCombo), eventWeight );
	}

	if(iHistos->find("SumPtIsoTracks_s") != iHistos->end()){
		(*(iHistos->find("SumPtIsoTracks_s"))).second->GetHisto()->Fill(Tau2SumPtIsoTracks->at(iCombo), eventWeight );
	}

	if(iHistos->find("Eta_LS") != iHistos->end()){
		(*(iHistos->find("Eta_LS"))).second->GetHisto()->Fill(Tau1Eta->at(iCombo), eventWeight );
		(*(iHistos->find("Eta_LS"))).second->GetHisto()->Fill(Tau2Eta->at(iCombo), eventWeight );
	}
	
	if(iHistos->find("Eta_L") != iHistos->end()){
		(*(iHistos->find("Eta_L"))).second->GetHisto()->Fill(Tau1Eta->at(iCombo), eventWeight );
	}

	if(iHistos->find("Eta_S") != iHistos->end()){
		(*(iHistos->find("Eta_S"))).second->GetHisto()->Fill(Tau2Eta->at(iCombo), eventWeight );
	}

	if(iHistos->find("Phi_LS") != iHistos->end()){
		(*(iHistos->find("Phi_LS"))).second->GetHisto()->Fill(Tau1Phi->at(iCombo), eventWeight );
		(*(iHistos->find("Phi_LS"))).second->GetHisto()->Fill(Tau2Phi->at(iCombo), eventWeight );
	}

	if(iHistos->find("Phi_L") != iHistos->end()){
		(*(iHistos->find("Phi_L"))).second->GetHisto()->Fill(Tau1Phi->at(iCombo), eventWeight );
	}

	if(iHistos->find("Phi_S") != iHistos->end()){
		(*(iHistos->find("Phi_S"))).second->GetHisto()->Fill(Tau2Phi->at(iCombo), eventWeight );
	}

	if(iHistos->find("CosDeltaPhi_LS") != iHistos->end()){
		(*(iHistos->find("CosDeltaPhi_LS"))).second->GetHisto()->Fill(TauTauCosDPhi->at(iCombo), eventWeight);
	}
	if(iHistos->find("CosDeltaEta_LS") != iHistos->end()){
		(*(iHistos->find("CosDeltaEta_LS"))).second->GetHisto()->Fill(cos(fabs(Tau1Eta->at(iCombo)-Tau2Eta->at(iCombo))), eventWeight);
	}
	if(iHistos->find("DeltaPhi_LS") != iHistos->end()){
		(*(iHistos->find("DeltaPhi_LS"))).second->GetHisto()->Fill((acos(cos(Tau1Phi->at(iCombo)-Tau2Phi->at(iCombo)))), eventWeight);
	}

	if(iHistos->find("DeltaEta_LS") != iHistos->end()){
		(*(iHistos->find("DeltaEta_LS"))).second->GetHisto()->Fill(fabs(Tau1Eta->at(iCombo)-Tau2Eta->at(iCombo)), eventWeight);
	}

	if(iHistos->find("DeltaR_LS") != iHistos->end()){
		(*(iHistos->find("DeltaR_LS"))).second->GetHisto()->Fill(TauTauDeltaR->at(iCombo), eventWeight);
	}

	if(iHistos->find("LTNumHits_LS") != iHistos->end()){
		(*(iHistos->find("LTNumHits_LS"))).second->GetHisto()->Fill(Tau1LTValidHits->at(iCombo), eventWeight );
		(*(iHistos->find("LTNumHits_LS"))).second->GetHisto()->Fill(Tau2LTValidHits->at(iCombo), eventWeight );
	}

	if(iHistos->find("PZeta_LSM") != iHistos->end()){
		(*(iHistos->find("PZeta_LSM"))).second->GetHisto()->Fill(TauTauPZeta->at(iCombo), eventWeight );
	}

	if(iHistos->find("PZetaVis_LSM") != iHistos->end()){
		(*(iHistos->find("PZetaVis_LSM"))).second->GetHisto()->Fill(TauTauPZetaVis->at(iCombo), eventWeight );
	}

	if(iHistos->find("Zeta_LSM") != iHistos->end()){
		(*(iHistos->find("Zeta_LSM"))).second->GetHisto()->Fill((TauTauPZeta->at(iCombo)-0.875*TauTauPZetaVis->at(iCombo)), eventWeight );
	}

	if(iHistos->find("Btags") != iHistos->end()){
		(*(iHistos->find("Btags"))).second->GetHisto()->Fill(nBtagsHiEffTrkCnt->at(iCombo), eventWeight );
	}

	if(iHistos->find("PtVsPt_LS") != iHistos->end()){
		((TH2F*)((*(iHistos->find("PtVsPt_LS"))).second->GetHisto()))->Fill(Tau2Pt->at(iCombo), Tau1Pt->at(iCombo), eventWeight );
	}

	if(iHistos->find("PtVsEta_LS") != iHistos->end()){
		((TH2F*)((*(iHistos->find("PtVsEta_LS"))).second->GetHisto()))->Fill((Tau1Eta->at(iCombo)), Tau1Pt->at(iCombo), eventWeight );
		((TH2F*)((*(iHistos->find("PtVsEta_LS"))).second->GetHisto()))->Fill((Tau2Eta->at(iCombo)), Tau2Pt->at(iCombo), eventWeight );
	}
	if(iHistos->find("PtVsEta_L") != iHistos->end()){
		((TH2F*)((*(iHistos->find("PtVsEta_L"))).second->GetHisto()))->Fill((Tau1Eta->at(iCombo)), Tau1Pt->at(iCombo), eventWeight );
	}
	if(iHistos->find("PtVsEta_S") != iHistos->end()){
		((TH2F*)((*(iHistos->find("PtVsEta_S"))).second->GetHisto()))->Fill((Tau2Eta->at(iCombo)), Tau2Pt->at(iCombo), eventWeight );
	}


	if(iHistos->find("PhiVsEta_LS") != iHistos->end()){
		float phi = Tau1Phi->at(iCombo);
		int laps = floor(fabs(phi)/(2*TMath::Pi()));
		if(phi<0){ laps++; }
		phi+=(laps*2*TMath::Pi());
		((TH2F*)((*(iHistos->find("PhiVsEta_LS"))).second->GetHisto()))->Fill((Tau1Eta->at(iCombo)), phi, eventWeight );

		phi = Tau2Phi->at(iCombo);
		laps = floor(fabs(phi)/(2*TMath::Pi()));
		if(phi<0){ laps++; }
		phi+=(laps*2*TMath::Pi());

		((TH2F*)((*(iHistos->find("PhiVsEta_LS"))).second->GetHisto()))->Fill((Tau2Eta->at(iCombo)), phi, eventWeight );
	}

	if(iHistos->find("PhiVsEta_L") != iHistos->end()){
		float phi = Tau1Phi->at(iCombo);
		int laps = floor(fabs(phi)/(2*TMath::Pi()));
		if(phi<0){ laps++; }
		phi+=(laps*2*TMath::Pi());
		((TH2F*)((*(iHistos->find("PhiVsEta_L"))).second->GetHisto()))->Fill((Tau1Eta->at(iCombo)), phi, eventWeight );
	}

	if(iHistos->find("PhiVsEta_S") != iHistos->end()){
		float phi = Tau2Phi->at(iCombo);
		int laps = floor(fabs(phi)/(2*TMath::Pi()));
		if(phi<0){ laps++; }
		phi+=(laps*2*TMath::Pi());
		((TH2F*)((*(iHistos->find("PhiVsEta_S"))).second->GetHisto()))->Fill((Tau2Eta->at(iCombo)), phi, eventWeight );
	}

	if(iHistos->find("EtaVsEta_LS") != iHistos->end()){
		((TH2F*)((*(iHistos->find("EtaVsEta_LS"))).second->GetHisto()))->Fill(Tau2Eta->at(iCombo), Tau1Eta->at(iCombo), eventWeight );
	}

	if(iHistos->find("DeltaPhiVsDeltaEta_LS") != iHistos->end()){
		((TH2F*)((*(iHistos->find("DeltaPhiVsDeltaEta_LS"))).second->GetHisto()))->Fill(fabs(Tau1Eta->at(iCombo)-Tau2Eta->at(iCombo)), acos(cos(Tau1Phi->at(iCombo)-Tau2Phi->at(iCombo))), eventWeight );
	}
	
	if(iHistos->find("CosDeltaPhiVsCosDeltaEta_LS") != iHistos->end()){
		((TH2F*)((*(iHistos->find("CosDeltaPhiVsCosDeltaEta_LS"))).second->GetHisto()))->Fill(cos(Tau1Eta->at(iCombo)-Tau2Eta->at(iCombo)), cos(Tau1Phi->at(iCombo)-Tau2Phi->at(iCombo)), eventWeight );
	}

	if(iHistos->find("EtaVSNumPV_L") != iHistos->end()){
		((TH2F*)((*(iHistos->find("EtaVSNumPV_L"))).second->GetHisto()))->Fill(NumPV->at(iCombo),fabs(Tau1Eta->at(iCombo)), eventWeight );
	}
	if(iHistos->find("EtaVSNumPV_S") != iHistos->end()){
		((TH2F*)((*(iHistos->find("EtaVSNumPV_S"))).second->GetHisto()))->Fill(NumPV->at(iCombo),fabs(Tau2Eta->at(iCombo)), eventWeight );
	}
	if(iHistos->find("PtVSNumPV_L") != iHistos->end()){
		((TH2F*)((*(iHistos->find("PtVSNumPV_L"))).second->GetHisto()))->Fill(NumPV->at(iCombo),Tau1Pt->at(iCombo), eventWeight );
	}
	if(iHistos->find("PtVSNumPV_S") != iHistos->end()){
		((TH2F*)((*(iHistos->find("PtVSNumPV_S"))).second->GetHisto()))->Fill(NumPV->at(iCombo),Tau2Pt->at(iCombo), eventWeight );
	}
	if(iHistos->find("CosDeltaPhiVSNumPV_LS") != iHistos->end()){
		((TH2F*)((*(iHistos->find("CosDeltaPhiVSNumPV_LS"))).second->GetHisto()))->Fill(NumPV->at(iCombo),TauTauCosDPhi->at(iCombo), eventWeight );
	}




	// ===================== Tau-Electron matching plots ========================= //
	/*
	if(iHistos->find("MatchedElecPt_L") != iHistos->end()){
		(*(iHistos->find("MatchedElecPt_L"))).second->GetHisto()->Fill(Tau1MElecPt->at(iCombo), eventWeight );
	}
	if(iHistos->find("MatchedElecPt_S") != iHistos->end()){
		(*(iHistos->find("MatchedElecPt_S"))).second->GetHisto()->Fill(Tau2MElecPt->at(iCombo), eventWeight );
	}

	if(iHistos->find("MatchedElecPtDiff_L") != iHistos->end()){
		(*(iHistos->find("MatchedElecPtDiff_L"))).second->GetHisto()->Fill(Tau1MElecPt->at(iCombo)-Tau1Pt->at(iCombo), eventWeight );
	}
	if(iHistos->find("MatchedElecPtDiff_S") != iHistos->end()){
		(*(iHistos->find("MatchedElecPtDiff_S"))).second->GetHisto()->Fill(Tau2MElecPt->at(iCombo)-Tau2Pt->at(iCombo), eventWeight );
	}

	if(iHistos->find("MatchedElecDeltaR_L") != iHistos->end()){
		(*(iHistos->find("MatchedElecDeltaR_L"))).second->GetHisto()->Fill(Tau1MElecDeltaR->at(iCombo), eventWeight );
	}
	if(iHistos->find("MatchedElecDeltaR_S") != iHistos->end()){
		(*(iHistos->find("MatchedElecDeltaR_S"))).second->GetHisto()->Fill(Tau2MElecDeltaR->at(iCombo), eventWeight );
	}


	// Isolation
	if(iHistos->find("MatchedElecIsoTrkSumPt_L") != iHistos->end()){
		(*(iHistos->find("MatchedElecIsoTrkSumPt_L"))).second->GetHisto()->Fill(Tau1MElecTrkSumPt->at(iCombo), eventWeight );
	}
	if(iHistos->find("MatchedElecIsoTrkSumPt_S") != iHistos->end()){
		(*(iHistos->find("MatchedElecIsoTrkSumPt_S"))).second->GetHisto()->Fill(Tau2MElecTrkSumPt->at(iCombo), eventWeight );
	}
	if(iHistos->find("MatchedElecEcalIsoRecHitSumEt_L") != iHistos->end()){
		(*(iHistos->find("MatchedElecEcalIsoRecHitSumEt_L"))).second->GetHisto()->Fill(Tau1MElecEcalRecHitSumEt->at(iCombo), eventWeight );
	}
	if(iHistos->find("MatchedElecEcalIsoRecHitSumEt_S") != iHistos->end()){
		(*(iHistos->find("MatchedElecEcalIsoRecHitSumEt_S"))).second->GetHisto()->Fill(Tau2MElecEcalRecHitSumEt->at(iCombo), eventWeight );
	}

	// Isolation diff
	if(iHistos->find("MatchedElecIsoTrkSumPtDiff_L") != iHistos->end()){
		(*(iHistos->find("MatchedElecIsoTrkSumPtDiff_L"))).second->GetHisto()->Fill(Tau1SumPtIsoTracks->at(iCombo)-Tau1MElecTrkSumPt->at(iCombo), eventWeight );
	}
	if(iHistos->find("MatchedElecIsoTrkSumPtDiff_S") != iHistos->end()){
		(*(iHistos->find("MatchedElecIsoTrkSumPtDiff_S"))).second->GetHisto()->Fill(Tau2SumPtIsoTracks->at(iCombo)-Tau2MElecTrkSumPt->at(iCombo), eventWeight );
	}
	if(iHistos->find("MatchedElecEcalIsoRecHitSumEtDiff_L") != iHistos->end()){
		(*(iHistos->find("MatchedElecEcalIsoRecHitSumEtDiff_L"))).second->GetHisto()->Fill(Tau1SumPtIsoGammas->at(iCombo)-Tau1MElecEcalRecHitSumEt->at(iCombo), eventWeight );
	}
	if(iHistos->find("MatchedElecEcalIsoRecHitSumEtDiff_S") != iHistos->end()){
		(*(iHistos->find("MatchedElecEcalIsoRecHitSumEtDiff_S"))).second->GetHisto()->Fill(Tau2SumPtIsoGammas->at(iCombo)-Tau2MElecEcalRecHitSumEt->at(iCombo), eventWeight );
	}//*/

/*
	if(isMC && IsFlagThere("PUcorr")){ 
		if(iHistos->find("PUweightsPassingEvents") != iHistos->end()){
			(*(iHistos->find("PUweightsPassingEvents"))).second->GetHisto()->Fill(puCorrector->GetWeight(NumPV->at(iCombo)));
		}
	}

	//*/

