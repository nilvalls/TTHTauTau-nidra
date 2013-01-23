	double Ev_runNumber;
	double Ev_eventNumber;
	double Ev_lumiBlock;
	double Ev_numInteractionsBXm1;
	double Ev_numInteractionsBX0;
	double Ev_numInteractionsBXp1;
	double Ev_numPrimaryVertices;
	double Ev_puWeight;
	double Ev_MET;
	double Ev_METphi;
	int GT_NumGenTaus;
	vector<float>* GT_MomentumRank;
	vector<float>* GT_Pt;
	vector<float>* GT_Eta;
	vector<float>* GT_Phi;
	vector<float>* GT_VisPt;
	vector<float>* GT_VisEta;
	vector<float>* GT_VisPhi;
	vector<bool>* GT_ToElectron;
	vector<bool>* GT_ToMuon;
	vector<bool>* GT_ToHadrons;
	vector<int>* GT_ParentId;
	vector<float>* GT_ParentP;
	vector<float>* GT_ParentPt;
	vector<float>* GT_ParentEta;
	vector<float>* GT_ParentPhi;
	int GJ_NumGenJets;
	vector<float>* GJ_MomentumRank;
	vector<float>* GJ_Pt;
	vector<float>* GJ_Eta;
	vector<float>* GJ_Phi;
	vector<bool>* GJ_IsBjet;
	int T_NumTaus;
	vector<float>* T_MomentumRank;
	vector<float>* T_Pt;
	vector<float>* T_Eta;
	vector<float>* T_Phi;
	vector<unsigned int>* T_NProngs;
	vector<unsigned int>* T_NSignalGammas;
	vector<unsigned int>* T_NSignalNeutrals;
	vector<unsigned int>* T_DecayMode;
	vector<float>* T_EmFraction;
	vector<bool>* T_IsInTheCracks;
	vector<bool>* T_HPSagainstElectronLoose;
	vector<bool>* T_HPSagainstElectronMVA;
	vector<bool>* T_HPSagainstElectronMedium;
	vector<bool>* T_HPSagainstElectronTight;
	vector<bool>* T_HPSagainstMuonLoose;
	vector<bool>* T_HPSagainstMuonMedium;
	vector<bool>* T_HPSagainstMuonTight;
	vector<bool>* T_HPSbyLooseCombinedIsolationDeltaBetaCorr;
	vector<bool>* T_HPSbyMediumCombinedIsolationDeltaBetaCorr;
	vector<bool>* T_HPSbyTightCombinedIsolationDeltaBetaCorr;
	vector<bool>* T_HPSbyVLooseCombinedIsolationDeltaBetaCorr;
	vector<bool>* T_HPSdecayModeFinding;
	vector<float>* T_LTPt;
	vector<float>* T_Charge;
	vector<bool>* T_LTvalid;
	vector<float>* T_LTIpVtdxy;
	vector<float>* T_LTIpVtdz;
	vector<float>* T_LTIpVtdxyError;
	vector<float>* T_LTIpVtdzError;
	vector<float>* T_LTvx;
	vector<float>* T_LTvy;
	vector<float>* T_LTvz;
	vector<unsigned int>* T_LTValidHits;
	vector<float>* T_LTNormChiSqrd;
	int E_NumElectrons;
	vector<float>* E_MomentumRank;
	vector<float>* E_Pt;
	vector<float>* E_Eta;
	vector<float>* E_Phi;
	vector<bool>* E_IsTightElectron;
	vector<bool>* E_IsLooseElectron;
	int M_NumMuons;
	vector<float>* M_MomentumRank;
	vector<float>* M_Pt;
	vector<float>* M_Eta;
	vector<float>* M_Phi;
	vector<float>* M_RelIso;
	vector<bool>* M_IsTightMuon;
	vector<bool>* M_IsLooseMuon;
	int J_NumJets;
	vector<float>* J_MomentumRank;
	vector<float>* J_Pt;
	vector<float>* J_Eta;
	vector<float>* J_Phi;
	vector<float>* J_combSecVtxBTag;
	vector<bool>* J_combSecVtxLooseBTag;
	vector<bool>* J_combSecVtxMediumBTag;
	vector<bool>* J_combSecVtxTightBTag;
	unsigned int TTE_NumTaus;
	unsigned int TTE_NumElectrons;
	unsigned int TTE_NumCombos;
	vector<unsigned int>* TTE_MomentumRank;
	vector<unsigned int>* TTE_Tau1MomentumRank;
	vector<float>* TTE_Tau1Pt;
	vector<float>* TTE_Tau1Eta;
	vector<float>* TTE_Tau1Phi;
	vector<unsigned int>* TTE_Tau1NProngs;
	vector<unsigned int>* TTE_Tau1NSignalGammas;
	vector<unsigned int>* TTE_Tau1NSignalNeutrals;
	vector<unsigned int>* TTE_Tau1DecayMode;
	vector<float>* TTE_Tau1EmFraction;
	vector<bool>* TTE_Tau1IsInTheCracks;
	vector<bool>* TTE_Tau1HPSagainstElectronLoose;
	vector<bool>* TTE_Tau1HPSagainstElectronMVA;
	vector<bool>* TTE_Tau1HPSagainstElectronMedium;
	vector<bool>* TTE_Tau1HPSagainstElectronTight;
	vector<bool>* TTE_Tau1HPSagainstMuonLoose;
	vector<bool>* TTE_Tau1HPSagainstMuonMedium;
	vector<bool>* TTE_Tau1HPSagainstMuonTight;
	vector<bool>* TTE_Tau1HPSbyLooseCombinedIsolationDeltaBetaCorr;
	vector<bool>* TTE_Tau1HPSbyMediumCombinedIsolationDeltaBetaCorr;
	vector<bool>* TTE_Tau1HPSbyTightCombinedIsolationDeltaBetaCorr;
	vector<bool>* TTE_Tau1HPSbyVLooseCombinedIsolationDeltaBetaCorr;
	vector<bool>* TTE_Tau1HPSdecayModeFinding;
	vector<float>* TTE_Tau1LTPt;
	vector<float>* TTE_Tau1Charge;
	vector<bool>* TTE_Tau1LTvalid;
	vector<float>* TTE_Tau1LTIpVtdxy;
	vector<float>* TTE_Tau1LTIpVtdz;
	vector<float>* TTE_Tau1LTIpVtdxyError;
	vector<float>* TTE_Tau1LTIpVtdzError;
	vector<float>* TTE_Tau1LTvx;
	vector<float>* TTE_Tau1LTvy;
	vector<float>* TTE_Tau1LTvz;
	vector<unsigned int>* TTE_Tau1LTValidHits;
	vector<float>* TTE_Tau1LTNormChiSqrd;
	vector<bool>* TTE_Tau1MatchesGenHadTauFromH1;
	vector<bool>* TTE_Tau1MatchesGenHadTauFromH2;
	vector<bool>* TTE_Tau1MatchesGenHadTauFromW1;
	vector<bool>* TTE_Tau1MatchesGenHadTauFromW2;
	vector<unsigned int>* TTE_Tau2MomentumRank;
	vector<float>* TTE_Tau2Pt;
	vector<float>* TTE_Tau2Eta;
	vector<float>* TTE_Tau2Phi;
	vector<unsigned int>* TTE_Tau2NProngs;
	vector<unsigned int>* TTE_Tau2NSignalGammas;
	vector<unsigned int>* TTE_Tau2NSignalNeutrals;
	vector<unsigned int>* TTE_Tau2DecayMode;
	vector<float>* TTE_Tau2EmFraction;
	vector<bool>* TTE_Tau2IsInTheCracks;
	vector<bool>* TTE_Tau2HPSagainstElectronLoose;
	vector<bool>* TTE_Tau2HPSagainstElectronMVA;
	vector<bool>* TTE_Tau2HPSagainstElectronMedium;
	vector<bool>* TTE_Tau2HPSagainstElectronTight;
	vector<bool>* TTE_Tau2HPSagainstMuonLoose;
	vector<bool>* TTE_Tau2HPSagainstMuonMedium;
	vector<bool>* TTE_Tau2HPSagainstMuonTight;
	vector<bool>* TTE_Tau2HPSbyLooseCombinedIsolationDeltaBetaCorr;
	vector<bool>* TTE_Tau2HPSbyMediumCombinedIsolationDeltaBetaCorr;
	vector<bool>* TTE_Tau2HPSbyTightCombinedIsolationDeltaBetaCorr;
	vector<bool>* TTE_Tau2HPSbyVLooseCombinedIsolationDeltaBetaCorr;
	vector<bool>* TTE_Tau2HPSdecayModeFinding;
	vector<float>* TTE_Tau2LTPt;
	vector<float>* TTE_Tau2Charge;
	vector<bool>* TTE_Tau2LTvalid;
	vector<float>* TTE_Tau2LTIpVtdxy;
	vector<float>* TTE_Tau2LTIpVtdz;
	vector<float>* TTE_Tau2LTIpVtdxyError;
	vector<float>* TTE_Tau2LTIpVtdzError;
	vector<float>* TTE_Tau2LTvx;
	vector<float>* TTE_Tau2LTvy;
	vector<float>* TTE_Tau2LTvz;
	vector<unsigned int>* TTE_Tau2LTValidHits;
	vector<float>* TTE_Tau2LTNormChiSqrd;
	vector<bool>* TTE_Tau2MatchesGenHadTauFromH1;
	vector<bool>* TTE_Tau2MatchesGenHadTauFromH2;
	vector<bool>* TTE_Tau2MatchesGenHadTauFromW1;
	vector<bool>* TTE_Tau2MatchesGenHadTauFromW2;
	vector<unsigned int>* TTE_ElectronMomentumRank;
	vector<float>* TTE_ElectronPt;
	vector<float>* TTE_ElectronEta;
	vector<float>* TTE_ElectronPhi;
	vector<float>* TTE_ElectronRelIso;
	vector<int>* TTE_ElectronIsLooseElectron;
	vector<int>* TTE_ElectronIsTightElectron;
	vector<float>* TTE_DitauVisibleMass;
	vector<float>* TTE_DitauMETMass;
	vector<float>* TTE_DitauCosDeltaPhi;
	vector<float>* TTE_DitauDeltaR;
	vector<float>* TTE_Tau1ElectronDeltaR;
	vector<float>* TTE_Tau2ElectronDeltaR;
	vector<float>* TTE_HT;
	vector<unsigned int>* TTE_NumCSVLbtagJets;
	vector<unsigned int>* TTE_NumCSVMbtagJets;
	vector<unsigned int>* TTE_NumCSVTbtagJets;
	vector<unsigned int>* TTE_NumNonCSVLbtagJets;
	vector<unsigned int>* TTE_NumNonCSVMbtagJets;
	vector<unsigned int>* TTE_NumNonCSVTbtagJets;
