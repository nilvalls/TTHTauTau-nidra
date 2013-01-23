	fChain->SetBranchAddress("Ev_runNumber", &Ev_runNumber);
	fChain->SetBranchAddress("Ev_eventNumber", &Ev_eventNumber);
	fChain->SetBranchAddress("Ev_lumiBlock", &Ev_lumiBlock);
	fChain->SetBranchAddress("Ev_numInteractionsBXm1", &Ev_numInteractionsBXm1);
	fChain->SetBranchAddress("Ev_numInteractionsBX0", &Ev_numInteractionsBX0);
	fChain->SetBranchAddress("Ev_numInteractionsBXp1", &Ev_numInteractionsBXp1);
	fChain->SetBranchAddress("Ev_numPrimaryVertices", &Ev_numPrimaryVertices);
	fChain->SetBranchAddress("Ev_puWeight", &Ev_puWeight);
	fChain->SetBranchAddress("Ev_MET", &Ev_MET);
	fChain->SetBranchAddress("Ev_METphi", &Ev_METphi);
	fChain->SetBranchAddress("GT_NumGenTaus", &GT_NumGenTaus);
	fChain->SetBranchAddress("GT_MomentumRank", &GT_MomentumRank);
	fChain->SetBranchAddress("GT_Pt", &GT_Pt);
	fChain->SetBranchAddress("GT_Eta", &GT_Eta);
	fChain->SetBranchAddress("GT_Phi", &GT_Phi);
	fChain->SetBranchAddress("GT_VisPt", &GT_VisPt);
	fChain->SetBranchAddress("GT_VisEta", &GT_VisEta);
	fChain->SetBranchAddress("GT_VisPhi", &GT_VisPhi);
	fChain->SetBranchAddress("GT_ToElectron", &GT_ToElectron);
	fChain->SetBranchAddress("GT_ToMuon", &GT_ToMuon);
	fChain->SetBranchAddress("GT_ToHadrons", &GT_ToHadrons);
	fChain->SetBranchAddress("GT_ParentId", &GT_ParentId);
	fChain->SetBranchAddress("GT_ParentP", &GT_ParentP);
	fChain->SetBranchAddress("GT_ParentPt", &GT_ParentPt);
	fChain->SetBranchAddress("GT_ParentEta", &GT_ParentEta);
	fChain->SetBranchAddress("GT_ParentPhi", &GT_ParentPhi);
	fChain->SetBranchAddress("GJ_NumGenJets", &GJ_NumGenJets);
	fChain->SetBranchAddress("GJ_MomentumRank", &GJ_MomentumRank);
	fChain->SetBranchAddress("GJ_Pt", &GJ_Pt);
	fChain->SetBranchAddress("GJ_Eta", &GJ_Eta);
	fChain->SetBranchAddress("GJ_Phi", &GJ_Phi);
	fChain->SetBranchAddress("GJ_IsBjet", &GJ_IsBjet);
	fChain->SetBranchAddress("T_NumTaus", &T_NumTaus);
	fChain->SetBranchAddress("T_MomentumRank", &T_MomentumRank);
	fChain->SetBranchAddress("T_Pt", &T_Pt);
	fChain->SetBranchAddress("T_Eta", &T_Eta);
	fChain->SetBranchAddress("T_Phi", &T_Phi);
	fChain->SetBranchAddress("T_NProngs", &T_NProngs);
	fChain->SetBranchAddress("T_NSignalGammas", &T_NSignalGammas);
	fChain->SetBranchAddress("T_NSignalNeutrals", &T_NSignalNeutrals);
	fChain->SetBranchAddress("T_DecayMode", &T_DecayMode);
	fChain->SetBranchAddress("T_EmFraction", &T_EmFraction);
	fChain->SetBranchAddress("T_IsInTheCracks", &T_IsInTheCracks);
	fChain->SetBranchAddress("T_HPSagainstElectronLoose", &T_HPSagainstElectronLoose);
	fChain->SetBranchAddress("T_HPSagainstElectronMVA", &T_HPSagainstElectronMVA);
	fChain->SetBranchAddress("T_HPSagainstElectronMedium", &T_HPSagainstElectronMedium);
	fChain->SetBranchAddress("T_HPSagainstElectronTight", &T_HPSagainstElectronTight);
	fChain->SetBranchAddress("T_HPSagainstMuonLoose", &T_HPSagainstMuonLoose);
	fChain->SetBranchAddress("T_HPSagainstMuonMedium", &T_HPSagainstMuonMedium);
	fChain->SetBranchAddress("T_HPSagainstMuonTight", &T_HPSagainstMuonTight);
	fChain->SetBranchAddress("T_HPSbyLooseCombinedIsolationDeltaBetaCorr", &T_HPSbyLooseCombinedIsolationDeltaBetaCorr);
	fChain->SetBranchAddress("T_HPSbyMediumCombinedIsolationDeltaBetaCorr", &T_HPSbyMediumCombinedIsolationDeltaBetaCorr);
	fChain->SetBranchAddress("T_HPSbyTightCombinedIsolationDeltaBetaCorr", &T_HPSbyTightCombinedIsolationDeltaBetaCorr);
	fChain->SetBranchAddress("T_HPSbyVLooseCombinedIsolationDeltaBetaCorr", &T_HPSbyVLooseCombinedIsolationDeltaBetaCorr);
	fChain->SetBranchAddress("T_HPSdecayModeFinding", &T_HPSdecayModeFinding);
	fChain->SetBranchAddress("T_LTPt", &T_LTPt);
	fChain->SetBranchAddress("T_Charge", &T_Charge);
	fChain->SetBranchAddress("T_LTvalid", &T_LTvalid);
	fChain->SetBranchAddress("T_LTIpVtdxy", &T_LTIpVtdxy);
	fChain->SetBranchAddress("T_LTIpVtdz", &T_LTIpVtdz);
	fChain->SetBranchAddress("T_LTIpVtdxyError", &T_LTIpVtdxyError);
	fChain->SetBranchAddress("T_LTIpVtdzError", &T_LTIpVtdzError);
	fChain->SetBranchAddress("T_LTvx", &T_LTvx);
	fChain->SetBranchAddress("T_LTvy", &T_LTvy);
	fChain->SetBranchAddress("T_LTvz", &T_LTvz);
	fChain->SetBranchAddress("T_LTValidHits", &T_LTValidHits);
	fChain->SetBranchAddress("T_LTNormChiSqrd", &T_LTNormChiSqrd);
	fChain->SetBranchAddress("E_NumElectrons", &E_NumElectrons);
	fChain->SetBranchAddress("E_MomentumRank", &E_MomentumRank);
	fChain->SetBranchAddress("E_Pt", &E_Pt);
	fChain->SetBranchAddress("E_Eta", &E_Eta);
	fChain->SetBranchAddress("E_Phi", &E_Phi);
	fChain->SetBranchAddress("E_IsTightElectron", &E_IsTightElectron);
	fChain->SetBranchAddress("E_IsLooseElectron", &E_IsLooseElectron);
	fChain->SetBranchAddress("M_NumMuons", &M_NumMuons);
	fChain->SetBranchAddress("M_MomentumRank", &M_MomentumRank);
	fChain->SetBranchAddress("M_Pt", &M_Pt);
	fChain->SetBranchAddress("M_Eta", &M_Eta);
	fChain->SetBranchAddress("M_Phi", &M_Phi);
	fChain->SetBranchAddress("M_RelIso", &M_RelIso);
	fChain->SetBranchAddress("M_IsTightMuon", &M_IsTightMuon);
	fChain->SetBranchAddress("M_IsLooseMuon", &M_IsLooseMuon);
	fChain->SetBranchAddress("J_NumJets", &J_NumJets);
	fChain->SetBranchAddress("J_MomentumRank", &J_MomentumRank);
	fChain->SetBranchAddress("J_Pt", &J_Pt);
	fChain->SetBranchAddress("J_Eta", &J_Eta);
	fChain->SetBranchAddress("J_Phi", &J_Phi);
	fChain->SetBranchAddress("J_combSecVtxBTag", &J_combSecVtxBTag);
	fChain->SetBranchAddress("J_combSecVtxLooseBTag", &J_combSecVtxLooseBTag);
	fChain->SetBranchAddress("J_combSecVtxMediumBTag", &J_combSecVtxMediumBTag);
	fChain->SetBranchAddress("J_combSecVtxTightBTag", &J_combSecVtxTightBTag);
	fChain->SetBranchAddress("TTM_NumTaus", &TTM_NumTaus);
	fChain->SetBranchAddress("TTM_NumMuons", &TTM_NumMuons);
	fChain->SetBranchAddress("TTM_NumCombos", &TTM_NumCombos);
	fChain->SetBranchAddress("TTM_MomentumRank", &TTM_MomentumRank);
	fChain->SetBranchAddress("TTM_Tau1MomentumRank", &TTM_Tau1MomentumRank);
	fChain->SetBranchAddress("TTM_Tau1Pt", &TTM_Tau1Pt);
	fChain->SetBranchAddress("TTM_Tau1Eta", &TTM_Tau1Eta);
	fChain->SetBranchAddress("TTM_Tau1Phi", &TTM_Tau1Phi);
	fChain->SetBranchAddress("TTM_Tau1NProngs", &TTM_Tau1NProngs);
	fChain->SetBranchAddress("TTM_Tau1NSignalGammas", &TTM_Tau1NSignalGammas);
	fChain->SetBranchAddress("TTM_Tau1NSignalNeutrals", &TTM_Tau1NSignalNeutrals);
	fChain->SetBranchAddress("TTM_Tau1DecayMode", &TTM_Tau1DecayMode);
	fChain->SetBranchAddress("TTM_Tau1EmFraction", &TTM_Tau1EmFraction);
	fChain->SetBranchAddress("TTM_Tau1IsInTheCracks", &TTM_Tau1IsInTheCracks);
	fChain->SetBranchAddress("TTM_Tau1HPSagainstElectronLoose", &TTM_Tau1HPSagainstElectronLoose);
	fChain->SetBranchAddress("TTM_Tau1HPSagainstElectronMVA", &TTM_Tau1HPSagainstElectronMVA);
	fChain->SetBranchAddress("TTM_Tau1HPSagainstElectronMedium", &TTM_Tau1HPSagainstElectronMedium);
	fChain->SetBranchAddress("TTM_Tau1HPSagainstElectronTight", &TTM_Tau1HPSagainstElectronTight);
	fChain->SetBranchAddress("TTM_Tau1HPSagainstMuonLoose", &TTM_Tau1HPSagainstMuonLoose);
	fChain->SetBranchAddress("TTM_Tau1HPSagainstMuonMedium", &TTM_Tau1HPSagainstMuonMedium);
	fChain->SetBranchAddress("TTM_Tau1HPSagainstMuonTight", &TTM_Tau1HPSagainstMuonTight);
	fChain->SetBranchAddress("TTM_Tau1HPSbyLooseCombinedIsolationDeltaBetaCorr", &TTM_Tau1HPSbyLooseCombinedIsolationDeltaBetaCorr);
	fChain->SetBranchAddress("TTM_Tau1HPSbyMediumCombinedIsolationDeltaBetaCorr", &TTM_Tau1HPSbyMediumCombinedIsolationDeltaBetaCorr);
	fChain->SetBranchAddress("TTM_Tau1HPSbyTightCombinedIsolationDeltaBetaCorr", &TTM_Tau1HPSbyTightCombinedIsolationDeltaBetaCorr);
	fChain->SetBranchAddress("TTM_Tau1HPSbyVLooseCombinedIsolationDeltaBetaCorr", &TTM_Tau1HPSbyVLooseCombinedIsolationDeltaBetaCorr);
	fChain->SetBranchAddress("TTM_Tau1HPSdecayModeFinding", &TTM_Tau1HPSdecayModeFinding);
	fChain->SetBranchAddress("TTM_Tau1LTPt", &TTM_Tau1LTPt);
	fChain->SetBranchAddress("TTM_Tau1Charge", &TTM_Tau1Charge);
	fChain->SetBranchAddress("TTM_Tau1LTvalid", &TTM_Tau1LTvalid);
	fChain->SetBranchAddress("TTM_Tau1LTIpVtdxy", &TTM_Tau1LTIpVtdxy);
	fChain->SetBranchAddress("TTM_Tau1LTIpVtdz", &TTM_Tau1LTIpVtdz);
	fChain->SetBranchAddress("TTM_Tau1LTIpVtdxyError", &TTM_Tau1LTIpVtdxyError);
	fChain->SetBranchAddress("TTM_Tau1LTIpVtdzError", &TTM_Tau1LTIpVtdzError);
	fChain->SetBranchAddress("TTM_Tau1LTvx", &TTM_Tau1LTvx);
	fChain->SetBranchAddress("TTM_Tau1LTvy", &TTM_Tau1LTvy);
	fChain->SetBranchAddress("TTM_Tau1LTvz", &TTM_Tau1LTvz);
	fChain->SetBranchAddress("TTM_Tau1LTValidHits", &TTM_Tau1LTValidHits);
	fChain->SetBranchAddress("TTM_Tau1LTNormChiSqrd", &TTM_Tau1LTNormChiSqrd);
	fChain->SetBranchAddress("TTM_Tau1MatchesGenHadTauFromH1", &TTM_Tau1MatchesGenHadTauFromH1);
	fChain->SetBranchAddress("TTM_Tau1MatchesGenHadTauFromH2", &TTM_Tau1MatchesGenHadTauFromH2);
	fChain->SetBranchAddress("TTM_Tau1MatchesGenHadTauFromW1", &TTM_Tau1MatchesGenHadTauFromW1);
	fChain->SetBranchAddress("TTM_Tau1MatchesGenHadTauFromW2", &TTM_Tau1MatchesGenHadTauFromW2);
	fChain->SetBranchAddress("TTM_Tau2MomentumRank", &TTM_Tau2MomentumRank);
	fChain->SetBranchAddress("TTM_Tau2Pt", &TTM_Tau2Pt);
	fChain->SetBranchAddress("TTM_Tau2Eta", &TTM_Tau2Eta);
	fChain->SetBranchAddress("TTM_Tau2Phi", &TTM_Tau2Phi);
	fChain->SetBranchAddress("TTM_Tau2NProngs", &TTM_Tau2NProngs);
	fChain->SetBranchAddress("TTM_Tau2NSignalGammas", &TTM_Tau2NSignalGammas);
	fChain->SetBranchAddress("TTM_Tau2NSignalNeutrals", &TTM_Tau2NSignalNeutrals);
	fChain->SetBranchAddress("TTM_Tau2DecayMode", &TTM_Tau2DecayMode);
	fChain->SetBranchAddress("TTM_Tau2EmFraction", &TTM_Tau2EmFraction);
	fChain->SetBranchAddress("TTM_Tau2IsInTheCracks", &TTM_Tau2IsInTheCracks);
	fChain->SetBranchAddress("TTM_Tau2HPSagainstElectronLoose", &TTM_Tau2HPSagainstElectronLoose);
	fChain->SetBranchAddress("TTM_Tau2HPSagainstElectronMVA", &TTM_Tau2HPSagainstElectronMVA);
	fChain->SetBranchAddress("TTM_Tau2HPSagainstElectronMedium", &TTM_Tau2HPSagainstElectronMedium);
	fChain->SetBranchAddress("TTM_Tau2HPSagainstElectronTight", &TTM_Tau2HPSagainstElectronTight);
	fChain->SetBranchAddress("TTM_Tau2HPSagainstMuonLoose", &TTM_Tau2HPSagainstMuonLoose);
	fChain->SetBranchAddress("TTM_Tau2HPSagainstMuonMedium", &TTM_Tau2HPSagainstMuonMedium);
	fChain->SetBranchAddress("TTM_Tau2HPSagainstMuonTight", &TTM_Tau2HPSagainstMuonTight);
	fChain->SetBranchAddress("TTM_Tau2HPSbyLooseCombinedIsolationDeltaBetaCorr", &TTM_Tau2HPSbyLooseCombinedIsolationDeltaBetaCorr);
	fChain->SetBranchAddress("TTM_Tau2HPSbyMediumCombinedIsolationDeltaBetaCorr", &TTM_Tau2HPSbyMediumCombinedIsolationDeltaBetaCorr);
	fChain->SetBranchAddress("TTM_Tau2HPSbyTightCombinedIsolationDeltaBetaCorr", &TTM_Tau2HPSbyTightCombinedIsolationDeltaBetaCorr);
	fChain->SetBranchAddress("TTM_Tau2HPSbyVLooseCombinedIsolationDeltaBetaCorr", &TTM_Tau2HPSbyVLooseCombinedIsolationDeltaBetaCorr);
	fChain->SetBranchAddress("TTM_Tau2HPSdecayModeFinding", &TTM_Tau2HPSdecayModeFinding);
	fChain->SetBranchAddress("TTM_Tau2LTPt", &TTM_Tau2LTPt);
	fChain->SetBranchAddress("TTM_Tau2Charge", &TTM_Tau2Charge);
	fChain->SetBranchAddress("TTM_Tau2LTvalid", &TTM_Tau2LTvalid);
	fChain->SetBranchAddress("TTM_Tau2LTIpVtdxy", &TTM_Tau2LTIpVtdxy);
	fChain->SetBranchAddress("TTM_Tau2LTIpVtdz", &TTM_Tau2LTIpVtdz);
	fChain->SetBranchAddress("TTM_Tau2LTIpVtdxyError", &TTM_Tau2LTIpVtdxyError);
	fChain->SetBranchAddress("TTM_Tau2LTIpVtdzError", &TTM_Tau2LTIpVtdzError);
	fChain->SetBranchAddress("TTM_Tau2LTvx", &TTM_Tau2LTvx);
	fChain->SetBranchAddress("TTM_Tau2LTvy", &TTM_Tau2LTvy);
	fChain->SetBranchAddress("TTM_Tau2LTvz", &TTM_Tau2LTvz);
	fChain->SetBranchAddress("TTM_Tau2LTValidHits", &TTM_Tau2LTValidHits);
	fChain->SetBranchAddress("TTM_Tau2LTNormChiSqrd", &TTM_Tau2LTNormChiSqrd);
	fChain->SetBranchAddress("TTM_Tau2MatchesGenHadTauFromH1", &TTM_Tau2MatchesGenHadTauFromH1);
	fChain->SetBranchAddress("TTM_Tau2MatchesGenHadTauFromH2", &TTM_Tau2MatchesGenHadTauFromH2);
	fChain->SetBranchAddress("TTM_Tau2MatchesGenHadTauFromW1", &TTM_Tau2MatchesGenHadTauFromW1);
	fChain->SetBranchAddress("TTM_Tau2MatchesGenHadTauFromW2", &TTM_Tau2MatchesGenHadTauFromW2);
	fChain->SetBranchAddress("TTM_MuonMomentumRank", &TTM_MuonMomentumRank);
	fChain->SetBranchAddress("TTM_MuonPt", &TTM_MuonPt);
	fChain->SetBranchAddress("TTM_MuonEta", &TTM_MuonEta);
	fChain->SetBranchAddress("TTM_MuonPhi", &TTM_MuonPhi);
	fChain->SetBranchAddress("TTM_MuonRelIso", &TTM_MuonRelIso);
	fChain->SetBranchAddress("TTM_MuonIsLooseMuon", &TTM_MuonIsLooseMuon);
	fChain->SetBranchAddress("TTM_MuonIsTightMuon", &TTM_MuonIsTightMuon);
	fChain->SetBranchAddress("TTM_DitauVisibleMass", &TTM_DitauVisibleMass);
	fChain->SetBranchAddress("TTM_DitauMETMass", &TTM_DitauMETMass);
	fChain->SetBranchAddress("TTM_DitauCosDeltaPhi", &TTM_DitauCosDeltaPhi);
	fChain->SetBranchAddress("TTM_DitauDeltaR", &TTM_DitauDeltaR);
	fChain->SetBranchAddress("TTM_Tau1MuonDeltaR", &TTM_Tau1MuonDeltaR);
	fChain->SetBranchAddress("TTM_Tau2MuonDeltaR", &TTM_Tau2MuonDeltaR);
	fChain->SetBranchAddress("TTM_HT", &TTM_HT);
	fChain->SetBranchAddress("TTM_NumCSVLbtagJets", &TTM_NumCSVLbtagJets);
	fChain->SetBranchAddress("TTM_NumCSVMbtagJets", &TTM_NumCSVMbtagJets);
	fChain->SetBranchAddress("TTM_NumCSVTbtagJets", &TTM_NumCSVTbtagJets);
	fChain->SetBranchAddress("TTM_NumNonCSVLbtagJets", &TTM_NumNonCSVLbtagJets);
	fChain->SetBranchAddress("TTM_NumNonCSVMbtagJets", &TTM_NumNonCSVMbtagJets);
	fChain->SetBranchAddress("TTM_NumNonCSVTbtagJets", &TTM_NumNonCSVTbtagJets);
