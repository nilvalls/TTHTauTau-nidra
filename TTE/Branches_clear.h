	Ev_runNumber = 0;
	Ev_eventNumber = 0;
	Ev_lumiBlock = 0;
	Ev_numInteractionsBXm1 = 0;
	Ev_numInteractionsBX0 = 0;
	Ev_numInteractionsBXp1 = 0;
	Ev_numPrimaryVertices = 0;
	Ev_puWeight = 0;
	Ev_MET = 0;
	Ev_METphi = 0;
	GT_NumGenTaus = 0;
	GT_MomentumRank->clear();
	GT_Pt->clear();
	GT_Eta->clear();
	GT_Phi->clear();
	GT_VisPt->clear();
	GT_VisEta->clear();
	GT_VisPhi->clear();
	GT_ToElectron->clear();
	GT_ToMuon->clear();
	GT_ToHadrons->clear();
	GT_ParentId->clear();
	GT_ParentP->clear();
	GT_ParentPt->clear();
	GT_ParentEta->clear();
	GT_ParentPhi->clear();
	GJ_NumGenJets = 0;
	GJ_MomentumRank->clear();
	GJ_Pt->clear();
	GJ_Eta->clear();
	GJ_Phi->clear();
	GJ_IsBjet->clear();
	T_NumTaus = 0;
	T_MomentumRank->clear();
	T_Pt->clear();
	T_Eta->clear();
	T_Phi->clear();
	T_NProngs->clear();
	T_NSignalGammas->clear();
	T_NSignalNeutrals->clear();
	T_DecayMode->clear();
	T_EmFraction->clear();
	T_IsInTheCracks->clear();
	T_HPSagainstElectronLoose->clear();
	T_HPSagainstElectronMVA->clear();
	T_HPSagainstElectronMedium->clear();
	T_HPSagainstElectronTight->clear();
	T_HPSagainstMuonLoose->clear();
	T_HPSagainstMuonMedium->clear();
	T_HPSagainstMuonTight->clear();
	T_HPSbyLooseCombinedIsolationDeltaBetaCorr->clear();
	T_HPSbyMediumCombinedIsolationDeltaBetaCorr->clear();
	T_HPSbyTightCombinedIsolationDeltaBetaCorr->clear();
	T_HPSbyVLooseCombinedIsolationDeltaBetaCorr->clear();
	T_HPSdecayModeFinding->clear();
	T_LTPt->clear();
	T_Charge->clear();
	T_LTvalid->clear();
	T_LTIpVtdxy->clear();
	T_LTIpVtdz->clear();
	T_LTIpVtdxyError->clear();
	T_LTIpVtdzError->clear();
	T_LTvx->clear();
	T_LTvy->clear();
	T_LTvz->clear();
	T_LTValidHits->clear();
	T_LTNormChiSqrd->clear();
	T_TauGenMatchDaughter0Id->clear();
	T_TauGenMatchDaughter1Id->clear();
	T_TauGenMatchId->clear();
	T_TauGenMatchMother0Id->clear();
	T_TauGenMatchMother1Id->clear();
	T_TauGenMatchGrandmother00Id->clear();
	T_TauGenMatchGrandmother01Id->clear();
	T_TauGenMatchGrandmother10Id->clear();
	T_TauGenMatchGrandmother11Id->clear();
	T_TauGenMatchDaughter0Status->clear();
	T_TauGenMatchDaughter1Status->clear();
	T_TauGenMatchStatus->clear();
	T_TauGenMatchMother0Status->clear();
	T_TauGenMatchMother1Status->clear();
	T_TauGenMatchGrandmother00Status->clear();
	T_TauGenMatchGrandmother01Status->clear();
	T_TauGenMatchGrandmother10Status->clear();
	T_TauGenMatchGrandmother11Status->clear();
	E_NumElectrons = 0;
	E_MomentumRank->clear();
	E_Pt->clear();
	E_Eta->clear();
	E_Phi->clear();
	E_IsTightElectron->clear();
	E_IsLooseElectron->clear();
	E_ElectronGenMatchDaughter0Id->clear();
	E_ElectronGenMatchDaughter1Id->clear();
	E_ElectronGenMatchId->clear();
	E_ElectronGenMatchMother0Id->clear();
	E_ElectronGenMatchMother1Id->clear();
	E_ElectronGenMatchGrandmother00Id->clear();
	E_ElectronGenMatchGrandmother01Id->clear();
	E_ElectronGenMatchGrandmother10Id->clear();
	E_ElectronGenMatchGrandmother11Id->clear();
	E_ElectronGenMatchDaughter0Status->clear();
	E_ElectronGenMatchDaughter1Status->clear();
	E_ElectronGenMatchStatus->clear();
	E_ElectronGenMatchMother0Status->clear();
	E_ElectronGenMatchMother1Status->clear();
	E_ElectronGenMatchGrandmother00Status->clear();
	E_ElectronGenMatchGrandmother01Status->clear();
	E_ElectronGenMatchGrandmother10Status->clear();
	E_ElectronGenMatchGrandmother11Status->clear();
	M_NumMuons = 0;
	M_MomentumRank->clear();
	M_Pt->clear();
	M_Eta->clear();
	M_Phi->clear();
	M_RelIso->clear();
	M_IsTightMuon->clear();
	M_IsLooseMuon->clear();
	M_MuonGenMatchDaughter0Id->clear();
	M_MuonGenMatchDaughter1Id->clear();
	M_MuonGenMatchId->clear();
	M_MuonGenMatchMother0Id->clear();
	M_MuonGenMatchMother1Id->clear();
	M_MuonGenMatchGrandmother00Id->clear();
	M_MuonGenMatchGrandmother01Id->clear();
	M_MuonGenMatchGrandmother10Id->clear();
	M_MuonGenMatchGrandmother11Id->clear();
	M_MuonGenMatchDaughter0Status->clear();
	M_MuonGenMatchDaughter1Status->clear();
	M_MuonGenMatchStatus->clear();
	M_MuonGenMatchMother0Status->clear();
	M_MuonGenMatchMother1Status->clear();
	M_MuonGenMatchGrandmother00Status->clear();
	M_MuonGenMatchGrandmother01Status->clear();
	M_MuonGenMatchGrandmother10Status->clear();
	M_MuonGenMatchGrandmother11Status->clear();
	J_NumJets = 0;
	J_MomentumRank->clear();
	J_Pt->clear();
	J_Eta->clear();
	J_Phi->clear();
	J_combSecVtxBTag->clear();
	J_combSecVtxLooseBTag->clear();
	J_combSecVtxMediumBTag->clear();
	J_combSecVtxTightBTag->clear();
	TTE_NumTaus = 0;
	TTE_NumElectrons = 0;
	TTE_NumCombos = 0;
	TTE_MomentumRank->clear();
	TTE_Tau1MomentumRank->clear();
	TTE_Tau1Pt->clear();
	TTE_Tau1Eta->clear();
	TTE_Tau1Phi->clear();
	TTE_Tau1NProngs->clear();
	TTE_Tau1NSignalGammas->clear();
	TTE_Tau1NSignalNeutrals->clear();
	TTE_Tau1DecayMode->clear();
	TTE_Tau1EmFraction->clear();
	TTE_Tau1IsInTheCracks->clear();
	TTE_Tau1HPSagainstElectronLoose->clear();
	TTE_Tau1HPSagainstElectronMVA->clear();
	TTE_Tau1HPSagainstElectronMedium->clear();
	TTE_Tau1HPSagainstElectronTight->clear();
	TTE_Tau1HPSagainstMuonLoose->clear();
	TTE_Tau1HPSagainstMuonMedium->clear();
	TTE_Tau1HPSagainstMuonTight->clear();
	TTE_Tau1HPSbyLooseCombinedIsolationDeltaBetaCorr->clear();
	TTE_Tau1HPSbyMediumCombinedIsolationDeltaBetaCorr->clear();
	TTE_Tau1HPSbyTightCombinedIsolationDeltaBetaCorr->clear();
	TTE_Tau1HPSbyVLooseCombinedIsolationDeltaBetaCorr->clear();
	TTE_Tau1HPSdecayModeFinding->clear();
	TTE_Tau1LTPt->clear();
	TTE_Tau1Charge->clear();
	TTE_Tau1LTvalid->clear();
	TTE_Tau1LTIpVtdxy->clear();
	TTE_Tau1LTIpVtdz->clear();
	TTE_Tau1LTIpVtdxyError->clear();
	TTE_Tau1LTIpVtdzError->clear();
	TTE_Tau1LTvx->clear();
	TTE_Tau1LTvy->clear();
	TTE_Tau1LTvz->clear();
	TTE_Tau1LTValidHits->clear();
	TTE_Tau1LTNormChiSqrd->clear();
	TTE_Tau1GenMatchDaughter0Id->clear();
	TTE_Tau1GenMatchDaughter1Id->clear();
	TTE_Tau1GenMatchId->clear();
	TTE_Tau1GenMatchMother0Id->clear();
	TTE_Tau1GenMatchMother1Id->clear();
	TTE_Tau1GenMatchGrandmother00Id->clear();
	TTE_Tau1GenMatchGrandmother01Id->clear();
	TTE_Tau1GenMatchGrandmother10Id->clear();
	TTE_Tau1GenMatchGrandmother11Id->clear();
	TTE_Tau1GenMatchDaughter0Status->clear();
	TTE_Tau1GenMatchDaughter1Status->clear();
	TTE_Tau1GenMatchStatus->clear();
	TTE_Tau1GenMatchMother0Status->clear();
	TTE_Tau1GenMatchMother1Status->clear();
	TTE_Tau1GenMatchGrandmother00Status->clear();
	TTE_Tau1GenMatchGrandmother01Status->clear();
	TTE_Tau1GenMatchGrandmother10Status->clear();
	TTE_Tau1GenMatchGrandmother11Status->clear();
	TTE_Tau2MomentumRank->clear();
	TTE_Tau2Pt->clear();
	TTE_Tau2Eta->clear();
	TTE_Tau2Phi->clear();
	TTE_Tau2NProngs->clear();
	TTE_Tau2NSignalGammas->clear();
	TTE_Tau2NSignalNeutrals->clear();
	TTE_Tau2DecayMode->clear();
	TTE_Tau2EmFraction->clear();
	TTE_Tau2IsInTheCracks->clear();
	TTE_Tau2HPSagainstElectronLoose->clear();
	TTE_Tau2HPSagainstElectronMVA->clear();
	TTE_Tau2HPSagainstElectronMedium->clear();
	TTE_Tau2HPSagainstElectronTight->clear();
	TTE_Tau2HPSagainstMuonLoose->clear();
	TTE_Tau2HPSagainstMuonMedium->clear();
	TTE_Tau2HPSagainstMuonTight->clear();
	TTE_Tau2HPSbyLooseCombinedIsolationDeltaBetaCorr->clear();
	TTE_Tau2HPSbyMediumCombinedIsolationDeltaBetaCorr->clear();
	TTE_Tau2HPSbyTightCombinedIsolationDeltaBetaCorr->clear();
	TTE_Tau2HPSbyVLooseCombinedIsolationDeltaBetaCorr->clear();
	TTE_Tau2HPSdecayModeFinding->clear();
	TTE_Tau2LTPt->clear();
	TTE_Tau2Charge->clear();
	TTE_Tau2LTvalid->clear();
	TTE_Tau2LTIpVtdxy->clear();
	TTE_Tau2LTIpVtdz->clear();
	TTE_Tau2LTIpVtdxyError->clear();
	TTE_Tau2LTIpVtdzError->clear();
	TTE_Tau2LTvx->clear();
	TTE_Tau2LTvy->clear();
	TTE_Tau2LTvz->clear();
	TTE_Tau2LTValidHits->clear();
	TTE_Tau2LTNormChiSqrd->clear();
	TTE_Tau2GenMatchDaughter0Id->clear();
	TTE_Tau2GenMatchDaughter1Id->clear();
	TTE_Tau2GenMatchId->clear();
	TTE_Tau2GenMatchMother0Id->clear();
	TTE_Tau2GenMatchMother1Id->clear();
	TTE_Tau2GenMatchGrandmother00Id->clear();
	TTE_Tau2GenMatchGrandmother01Id->clear();
	TTE_Tau2GenMatchGrandmother10Id->clear();
	TTE_Tau2GenMatchGrandmother11Id->clear();
	TTE_Tau2GenMatchDaughter0Status->clear();
	TTE_Tau2GenMatchDaughter1Status->clear();
	TTE_Tau2GenMatchStatus->clear();
	TTE_Tau2GenMatchMother0Status->clear();
	TTE_Tau2GenMatchMother1Status->clear();
	TTE_Tau2GenMatchGrandmother00Status->clear();
	TTE_Tau2GenMatchGrandmother01Status->clear();
	TTE_Tau2GenMatchGrandmother10Status->clear();
	TTE_Tau2GenMatchGrandmother11Status->clear();
	TTE_ElectronMomentumRank->clear();
	TTE_ElectronPt->clear();
	TTE_ElectronEta->clear();
	TTE_ElectronPhi->clear();
	TTE_ElectronRelIso->clear();
	TTE_ElectronIsLooseElectron->clear();
	TTE_ElectronIsTightElectron->clear();
	TTE_NumOtherLooseMuons = 0;
	TTE_NumOtherExLooseMuons = 0;
	TTE_NumOtherTightMuons = 0;
	TTE_NumOtherLooseElectrons->clear();
	TTE_NumOtherExLooseElectrons->clear();
	TTE_NumOtherTightElectrons->clear();
	TTE_LeptonEventWeight->clear();
	TTE_ElectronGenMatchDaughter0Id->clear();
	TTE_ElectronGenMatchDaughter1Id->clear();
	TTE_ElectronGenMatchId->clear();
	TTE_ElectronGenMatchMother0Id->clear();
	TTE_ElectronGenMatchMother1Id->clear();
	TTE_ElectronGenMatchGrandmother00Id->clear();
	TTE_ElectronGenMatchGrandmother01Id->clear();
	TTE_ElectronGenMatchGrandmother10Id->clear();
	TTE_ElectronGenMatchGrandmother11Id->clear();
	TTE_ElectronGenMatchDaughter0Status->clear();
	TTE_ElectronGenMatchDaughter1Status->clear();
	TTE_ElectronGenMatchStatus->clear();
	TTE_ElectronGenMatchMother0Status->clear();
	TTE_ElectronGenMatchMother1Status->clear();
	TTE_ElectronGenMatchGrandmother00Status->clear();
	TTE_ElectronGenMatchGrandmother01Status->clear();
	TTE_ElectronGenMatchGrandmother10Status->clear();
	TTE_ElectronGenMatchGrandmother11Status->clear();
	TTE_DitauVisibleMass->clear();
	TTE_DitauMETMass->clear();
	TTE_DitauCosDeltaPhi->clear();
	TTE_DitauDeltaR->clear();
	TTE_Tau1ElectronDeltaR->clear();
	TTE_Tau2ElectronDeltaR->clear();
	TTE_HT->clear();
	TTE_NumCSVLbtagJets->clear();
	TTE_NumCSVMbtagJets->clear();
	TTE_NumCSVTbtagJets->clear();
	TTE_NumNonCSVLbtagJets->clear();
	TTE_NumNonCSVMbtagJets->clear();
	TTE_NumNonCSVTbtagJets->clear();
