	Ev_runNumber = 0;
	Ev_eventNumber = 0;
	Ev_lumiBlock = 0;
	Ev_puWeight = 0;
	Ev_puWeightUp = 0;
	Ev_puWeightDown = 0;
	Ev_topPtWeight = 0;
	Ev_topPtWeightUp = 0;
	Ev_topPtWeightDown = 0;
	Ev_q2WeightUp = 0;
	Ev_q2WeightDown = 0;
	Ev_MET = 0;
	Ev_METphi = 0;
	Ev_IsTauEvent = 0;
	V_NumVertices = 0;
	V_NumInteractionsBXm1 = 0;
	V_NumInteractionsBX0 = 0;
	V_NumInteractionsBXp1 = 0;
	V_Xcoord->clear();
	V_XcoordErr->clear();
	V_Ycoord->clear();
	V_YcoordErr->clear();
	V_Zcoord->clear();
	V_ZcoordErr->clear();
	V_Rho->clear();
	V_NumDOF->clear();
	V_NormChiSquared->clear();
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
	T_HPSagainstElectronDeadECAL->clear();
	T_HPSagainstElectronLoose->clear();
	T_HPSagainstElectronLooseMVA2->clear();
	T_HPSagainstElectronLooseMVA3->clear();
	T_HPSagainstElectronMVA->clear();
	T_HPSagainstElectronMVA2category->clear();
	T_HPSagainstElectronMVA2raw->clear();
	T_HPSagainstElectronMVA3category->clear();
	T_HPSagainstElectronMVA3raw->clear();
	T_HPSagainstElectronMedium->clear();
	T_HPSagainstElectronMediumMVA2->clear();
	T_HPSagainstElectronMediumMVA3->clear();
	T_HPSagainstElectronTight->clear();
	T_HPSagainstElectronTightMVA2->clear();
	T_HPSagainstElectronTightMVA3->clear();
	T_HPSagainstElectronVLooseMVA2->clear();
	T_HPSagainstElectronVTightMVA3->clear();
	T_HPSagainstMuonLoose->clear();
	T_HPSagainstMuonLoose2->clear();
	T_HPSagainstMuonMedium->clear();
	T_HPSagainstMuonMedium2->clear();
	T_HPSagainstMuonTight->clear();
	T_HPSagainstMuonTight2->clear();
	T_HPSbyCombinedIsolationDeltaBetaCorrRaw->clear();
	T_HPSbyCombinedIsolationDeltaBetaCorrRaw3Hits->clear();
	T_HPSbyIsolationMVA2raw->clear();
	T_HPSbyLooseCombinedIsolationDeltaBetaCorr->clear();
	T_HPSbyLooseCombinedIsolationDeltaBetaCorr3Hits->clear();
	T_HPSbyLooseIsolationMVA->clear();
	T_HPSbyLooseIsolationMVA2->clear();
	T_HPSbyMediumCombinedIsolationDeltaBetaCorr->clear();
	T_HPSbyMediumCombinedIsolationDeltaBetaCorr3Hits->clear();
	T_HPSbyMediumIsolationMVA->clear();
	T_HPSbyMediumIsolationMVA2->clear();
	T_HPSbyTightCombinedIsolationDeltaBetaCorr->clear();
	T_HPSbyTightCombinedIsolationDeltaBetaCorr3Hits->clear();
	T_HPSbyTightIsolationMVA->clear();
	T_HPSbyTightIsolationMVA2->clear();
	T_HPSbyVLooseCombinedIsolationDeltaBetaCorr->clear();
	T_HPSdecayModeFinding->clear();
	T_HPSbyIsolationMVAraw->clear();
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
	TTL_NumTaus = 0;
	TTL_NumMuons = 0;
	TTL_NumElectrons = 0;
	TTL_NumLeptons = 0;
	TTL_NumCombos = 0;
	TTL_MomentumRank->clear();
	TTL_Tau1MomentumRank->clear();
	TTL_Tau1Pt->clear();
	TTL_Tau1Eta->clear();
	TTL_Tau1Phi->clear();
	TTL_Tau1NProngs->clear();
	TTL_Tau1NSignalGammas->clear();
	TTL_Tau1NSignalNeutrals->clear();
	TTL_Tau1DecayMode->clear();
	TTL_Tau1EmFraction->clear();
	TTL_Tau1IsInTheCracks->clear();
	TTL_Tau1HPSagainstElectronDeadECAL->clear();
	TTL_Tau1HPSagainstElectronLoose->clear();
	TTL_Tau1HPSagainstElectronLooseMVA2->clear();
	TTL_Tau1HPSagainstElectronLooseMVA3->clear();
	TTL_Tau1HPSagainstElectronMVA->clear();
	TTL_Tau1HPSagainstElectronMVA2category->clear();
	TTL_Tau1HPSagainstElectronMVA2raw->clear();
	TTL_Tau1HPSagainstElectronMVA3category->clear();
	TTL_Tau1HPSagainstElectronMVA3raw->clear();
	TTL_Tau1HPSagainstElectronMedium->clear();
	TTL_Tau1HPSagainstElectronMediumMVA2->clear();
	TTL_Tau1HPSagainstElectronMediumMVA3->clear();
	TTL_Tau1HPSagainstElectronTight->clear();
	TTL_Tau1HPSagainstElectronTightMVA2->clear();
	TTL_Tau1HPSagainstElectronTightMVA3->clear();
	TTL_Tau1HPSagainstElectronVLooseMVA2->clear();
	TTL_Tau1HPSagainstElectronVTightMVA3->clear();
	TTL_Tau1HPSagainstMuonLoose->clear();
	TTL_Tau1HPSagainstMuonLoose2->clear();
	TTL_Tau1HPSagainstMuonMedium->clear();
	TTL_Tau1HPSagainstMuonMedium2->clear();
	TTL_Tau1HPSagainstMuonTight->clear();
	TTL_Tau1HPSagainstMuonTight2->clear();
	TTL_Tau1HPSbyCombinedIsolationDeltaBetaCorrRaw->clear();
	TTL_Tau1HPSbyCombinedIsolationDeltaBetaCorrRaw3Hits->clear();
	TTL_Tau1HPSbyIsolationMVA2raw->clear();
	TTL_Tau1HPSbyLooseCombinedIsolationDeltaBetaCorr->clear();
	TTL_Tau1HPSbyLooseCombinedIsolationDeltaBetaCorr3Hits->clear();
	TTL_Tau1HPSbyLooseIsolationMVA->clear();
	TTL_Tau1HPSbyLooseIsolationMVA2->clear();
	TTL_Tau1HPSbyMediumCombinedIsolationDeltaBetaCorr->clear();
	TTL_Tau1HPSbyMediumCombinedIsolationDeltaBetaCorr3Hits->clear();
	TTL_Tau1HPSbyMediumIsolationMVA->clear();
	TTL_Tau1HPSbyMediumIsolationMVA2->clear();
	TTL_Tau1HPSbyTightCombinedIsolationDeltaBetaCorr->clear();
	TTL_Tau1HPSbyTightCombinedIsolationDeltaBetaCorr3Hits->clear();
	TTL_Tau1HPSbyTightIsolationMVA->clear();
	TTL_Tau1HPSbyTightIsolationMVA2->clear();
	TTL_Tau1HPSbyVLooseCombinedIsolationDeltaBetaCorr->clear();
	TTL_Tau1HPSdecayModeFinding->clear();
	TTL_Tau1HPSbyIsolationMVAraw->clear();
	TTL_Tau1LTPt->clear();
	TTL_Tau1Charge->clear();
	TTL_Tau1LTvalid->clear();
	TTL_Tau1LTIpVtdxy->clear();
	TTL_Tau1LTIpVtdz->clear();
	TTL_Tau1LTIpVtdxyError->clear();
	TTL_Tau1LTIpVtdzError->clear();
	TTL_Tau1LTvx->clear();
	TTL_Tau1LTvy->clear();
	TTL_Tau1LTvz->clear();
	TTL_Tau1LTValidHits->clear();
	TTL_Tau1LTNormChiSqrd->clear();
	TTL_Tau1GenMatchDaughter0Id->clear();
	TTL_Tau1GenMatchDaughter1Id->clear();
	TTL_Tau1GenMatchId->clear();
	TTL_Tau1GenMatchMother0Id->clear();
	TTL_Tau1GenMatchMother1Id->clear();
	TTL_Tau1GenMatchGrandmother00Id->clear();
	TTL_Tau1GenMatchGrandmother01Id->clear();
	TTL_Tau1GenMatchGrandmother10Id->clear();
	TTL_Tau1GenMatchGrandmother11Id->clear();
	TTL_Tau1GenMatchDaughter0Status->clear();
	TTL_Tau1GenMatchDaughter1Status->clear();
	TTL_Tau1GenMatchStatus->clear();
	TTL_Tau1GenMatchMother0Status->clear();
	TTL_Tau1GenMatchMother1Status->clear();
	TTL_Tau1GenMatchGrandmother00Status->clear();
	TTL_Tau1GenMatchGrandmother01Status->clear();
	TTL_Tau1GenMatchGrandmother10Status->clear();
	TTL_Tau1GenMatchGrandmother11Status->clear();
	TTL_Tau2MomentumRank->clear();
	TTL_Tau2Pt->clear();
	TTL_Tau2Eta->clear();
	TTL_Tau2Phi->clear();
	TTL_Tau2NProngs->clear();
	TTL_Tau2NSignalGammas->clear();
	TTL_Tau2NSignalNeutrals->clear();
	TTL_Tau2DecayMode->clear();
	TTL_Tau2EmFraction->clear();
	TTL_Tau2IsInTheCracks->clear();
	TTL_Tau2HPSagainstElectronDeadECAL->clear();
	TTL_Tau2HPSagainstElectronLoose->clear();
	TTL_Tau2HPSagainstElectronLooseMVA2->clear();
	TTL_Tau2HPSagainstElectronLooseMVA3->clear();
	TTL_Tau2HPSagainstElectronMVA->clear();
	TTL_Tau2HPSagainstElectronMVA2category->clear();
	TTL_Tau2HPSagainstElectronMVA2raw->clear();
	TTL_Tau2HPSagainstElectronMVA3category->clear();
	TTL_Tau2HPSagainstElectronMVA3raw->clear();
	TTL_Tau2HPSagainstElectronMedium->clear();
	TTL_Tau2HPSagainstElectronMediumMVA2->clear();
	TTL_Tau2HPSagainstElectronMediumMVA3->clear();
	TTL_Tau2HPSagainstElectronTight->clear();
	TTL_Tau2HPSagainstElectronTightMVA2->clear();
	TTL_Tau2HPSagainstElectronTightMVA3->clear();
	TTL_Tau2HPSagainstElectronVLooseMVA2->clear();
	TTL_Tau2HPSagainstElectronVTightMVA3->clear();
	TTL_Tau2HPSagainstMuonLoose->clear();
	TTL_Tau2HPSagainstMuonLoose2->clear();
	TTL_Tau2HPSagainstMuonMedium->clear();
	TTL_Tau2HPSagainstMuonMedium2->clear();
	TTL_Tau2HPSagainstMuonTight->clear();
	TTL_Tau2HPSagainstMuonTight2->clear();
	TTL_Tau2HPSbyCombinedIsolationDeltaBetaCorrRaw->clear();
	TTL_Tau2HPSbyCombinedIsolationDeltaBetaCorrRaw3Hits->clear();
	TTL_Tau2HPSbyIsolationMVA2raw->clear();
	TTL_Tau2HPSbyLooseCombinedIsolationDeltaBetaCorr->clear();
	TTL_Tau2HPSbyLooseCombinedIsolationDeltaBetaCorr3Hits->clear();
	TTL_Tau2HPSbyLooseIsolationMVA->clear();
	TTL_Tau2HPSbyLooseIsolationMVA2->clear();
	TTL_Tau2HPSbyMediumCombinedIsolationDeltaBetaCorr->clear();
	TTL_Tau2HPSbyMediumCombinedIsolationDeltaBetaCorr3Hits->clear();
	TTL_Tau2HPSbyMediumIsolationMVA->clear();
	TTL_Tau2HPSbyMediumIsolationMVA2->clear();
	TTL_Tau2HPSbyTightCombinedIsolationDeltaBetaCorr->clear();
	TTL_Tau2HPSbyTightCombinedIsolationDeltaBetaCorr3Hits->clear();
	TTL_Tau2HPSbyTightIsolationMVA->clear();
	TTL_Tau2HPSbyTightIsolationMVA2->clear();
	TTL_Tau2HPSbyVLooseCombinedIsolationDeltaBetaCorr->clear();
	TTL_Tau2HPSdecayModeFinding->clear();
	TTL_Tau2HPSbyIsolationMVAraw->clear();
	TTL_Tau2LTPt->clear();
	TTL_Tau2Charge->clear();
	TTL_Tau2LTvalid->clear();
	TTL_Tau2LTIpVtdxy->clear();
	TTL_Tau2LTIpVtdz->clear();
	TTL_Tau2LTIpVtdxyError->clear();
	TTL_Tau2LTIpVtdzError->clear();
	TTL_Tau2LTvx->clear();
	TTL_Tau2LTvy->clear();
	TTL_Tau2LTvz->clear();
	TTL_Tau2LTValidHits->clear();
	TTL_Tau2LTNormChiSqrd->clear();
	TTL_Tau2GenMatchDaughter0Id->clear();
	TTL_Tau2GenMatchDaughter1Id->clear();
	TTL_Tau2GenMatchId->clear();
	TTL_Tau2GenMatchMother0Id->clear();
	TTL_Tau2GenMatchMother1Id->clear();
	TTL_Tau2GenMatchGrandmother00Id->clear();
	TTL_Tau2GenMatchGrandmother01Id->clear();
	TTL_Tau2GenMatchGrandmother10Id->clear();
	TTL_Tau2GenMatchGrandmother11Id->clear();
	TTL_Tau2GenMatchDaughter0Status->clear();
	TTL_Tau2GenMatchDaughter1Status->clear();
	TTL_Tau2GenMatchStatus->clear();
	TTL_Tau2GenMatchMother0Status->clear();
	TTL_Tau2GenMatchMother1Status->clear();
	TTL_Tau2GenMatchGrandmother00Status->clear();
	TTL_Tau2GenMatchGrandmother01Status->clear();
	TTL_Tau2GenMatchGrandmother10Status->clear();
	TTL_Tau2GenMatchGrandmother11Status->clear();
	TTL_MuonMomentumRank->clear();
	TTL_ElectronMomentumRank->clear();
	TTL_LeptonMomentumRank->clear();
	TTL_LeptonIsMuon->clear();
	TTL_LeptonIsElectron->clear();
	TTL_LeptonPt->clear();
	TTL_LeptonEta->clear();
	TTL_LeptonPhi->clear();
	TTL_LeptonRelIso->clear();
	TTL_LeptonIsLoose->clear();
	TTL_LeptonIsTight->clear();
	TTL_NumLooseMuons->clear();
	TTL_NumExLooseMuons->clear();
	TTL_NumTightMuons->clear();
	TTL_NumLooseElectrons->clear();
	TTL_NumExLooseElectrons->clear();
	TTL_NumTightElectrons->clear();
	TTL_LeptonEventWeight->clear();
	TTL_LeptonGenMatchDaughter0Id->clear();
	TTL_LeptonGenMatchDaughter1Id->clear();
	TTL_LeptonGenMatchId->clear();
	TTL_LeptonGenMatchMother0Id->clear();
	TTL_LeptonGenMatchMother1Id->clear();
	TTL_LeptonGenMatchGrandmother00Id->clear();
	TTL_LeptonGenMatchGrandmother01Id->clear();
	TTL_LeptonGenMatchGrandmother10Id->clear();
	TTL_LeptonGenMatchGrandmother11Id->clear();
	TTL_LeptonGenMatchDaughter0Status->clear();
	TTL_LeptonGenMatchDaughter1Status->clear();
	TTL_LeptonGenMatchStatus->clear();
	TTL_LeptonGenMatchMother0Status->clear();
	TTL_LeptonGenMatchMother1Status->clear();
	TTL_LeptonGenMatchGrandmother00Status->clear();
	TTL_LeptonGenMatchGrandmother01Status->clear();
	TTL_LeptonGenMatchGrandmother10Status->clear();
	TTL_LeptonGenMatchGrandmother11Status->clear();
	TTL_DitauVisibleMass->clear();
	TTL_DitauMETMass->clear();
	TTL_DitauCosDeltaPhi->clear();
	TTL_DitauDeltaR->clear();
	TTL_Tau1LeptonDeltaR->clear();
	TTL_Tau2LeptonDeltaR->clear();
	TTL_HT->clear();
	TTL_NumCSVLbtagJets->clear();
	TTL_NumCSVMbtagJets->clear();
	TTL_NumCSVTbtagJets->clear();
	TTL_NumNonCSVLbtagJets->clear();
	TTL_NumNonCSVMbtagJets->clear();
	TTL_NumNonCSVTbtagJets->clear();
	TTL_NumCleanCSVLbtagJets->clear();
	TTL_NumCleanCSVMbtagJets->clear();
	TTL_NumCleanCSVTbtagJets->clear();
	TTL_NumCleanNonCSVLbtagJets->clear();
	TTL_NumCleanNonCSVMbtagJets->clear();
	TTL_NumCleanNonCSVTbtagJets->clear();
