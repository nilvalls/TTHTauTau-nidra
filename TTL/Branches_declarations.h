    Double_t Ev_runNumber;
    Double_t Ev_eventNumber;
    Double_t Ev_lumiBlock;
    Double_t Ev_puWeight;
    Double_t Ev_puWeightUp;
    Double_t Ev_puWeightDown;
    Double_t Ev_topPtWeight;
    Double_t Ev_topPtWeightUp;
    Double_t Ev_topPtWeightDown;
    Double_t Ev_q2WeightUp;
    Double_t Ev_q2WeightDown;
    Double_t Ev_MET;
    Double_t Ev_METphi;
    Bool_t Ev_IsTauEvent;
    Double_t Ev_puWeight2012A;
    Double_t Ev_puWeight2012B;
    Double_t Ev_puWeight2012C;
    Double_t Ev_puWeight2012D;
    Double_t Ev_puWeight2012AB;
    Double_t Ev_puWeight2012BC;
    Double_t Ev_puWeight2012CD;
    Double_t Ev_puWeight2012ABC;
    Int_t V_NumVertices;
    Double_t V_NumInteractionsBXm1;
    Double_t V_NumInteractionsBX0;
    Double_t V_NumInteractionsBXp1;
    std::vector<float>* V_Xcoord;
    std::vector<float>* V_XcoordErr;
    std::vector<float>* V_Ycoord;
    std::vector<float>* V_YcoordErr;
    std::vector<float>* V_Zcoord;
    std::vector<float>* V_ZcoordErr;
    std::vector<float>* V_Rho;
    std::vector<float>* V_NumDOF;
    std::vector<float>* V_NormChiSquared;
    Int_t GT_NumGenTaus;
    std::vector<float>* GT_MomentumRank;
    std::vector<float>* GT_Pt;
    std::vector<float>* GT_Eta;
    std::vector<float>* GT_Phi;
    std::vector<float>* GT_VisPt;
    std::vector<float>* GT_VisEta;
    std::vector<float>* GT_VisPhi;
    std::vector<bool>* GT_ToElectron;
    std::vector<bool>* GT_ToMuon;
    std::vector<bool>* GT_ToHadrons;
    std::vector<int>* GT_ParentId;
    std::vector<float>* GT_ParentP;
    std::vector<float>* GT_ParentPt;
    std::vector<float>* GT_ParentEta;
    std::vector<float>* GT_ParentPhi;
    Int_t GJ_NumGenJets;
    std::vector<float>* GJ_MomentumRank;
    std::vector<float>* GJ_Pt;
    std::vector<float>* GJ_Eta;
    std::vector<float>* GJ_Phi;
    std::vector<bool>* GJ_IsBjet;
    Int_t T_NumTaus;
    std::vector<float>* T_MomentumRank;
    std::vector<float>* T_Pt;
    std::vector<float>* T_Eta;
    std::vector<float>* T_Phi;
    std::vector<unsigned int>* T_NProngs;
    std::vector<unsigned int>* T_NSignalGammas;
    std::vector<unsigned int>* T_NSignalNeutrals;
    std::vector<unsigned int>* T_DecayMode;
    std::vector<float>* T_EmFraction;
    std::vector<bool>* T_IsInTheCracks;
    std::vector<bool>* T_HPSagainstElectronDeadECAL;
    std::vector<bool>* T_HPSagainstElectronLoose;
    std::vector<bool>* T_HPSagainstElectronLooseMVA2;
    std::vector<bool>* T_HPSagainstElectronLooseMVA3;
    std::vector<bool>* T_HPSagainstElectronMVA;
    std::vector<bool>* T_HPSagainstElectronMVA2category;
    std::vector<float>* T_HPSagainstElectronMVA2raw;
    std::vector<bool>* T_HPSagainstElectronMVA3category;
    std::vector<float>* T_HPSagainstElectronMVA3raw;
    std::vector<bool>* T_HPSagainstElectronMedium;
    std::vector<bool>* T_HPSagainstElectronMediumMVA2;
    std::vector<bool>* T_HPSagainstElectronMediumMVA3;
    std::vector<bool>* T_HPSagainstElectronTight;
    std::vector<bool>* T_HPSagainstElectronTightMVA2;
    std::vector<bool>* T_HPSagainstElectronTightMVA3;
    std::vector<bool>* T_HPSagainstElectronVLooseMVA2;
    std::vector<bool>* T_HPSagainstElectronVTightMVA3;
    std::vector<bool>* T_HPSagainstMuonLoose;
    std::vector<bool>* T_HPSagainstMuonLoose2;
    std::vector<bool>* T_HPSagainstMuonMedium;
    std::vector<bool>* T_HPSagainstMuonMedium2;
    std::vector<bool>* T_HPSagainstMuonTight;
    std::vector<bool>* T_HPSagainstMuonTight2;
    std::vector<float>* T_HPSbyCombinedIsolationDeltaBetaCorrRaw;
    std::vector<float>* T_HPSbyCombinedIsolationDeltaBetaCorrRaw3Hits;
    std::vector<float>* T_HPSbyIsolationMVA2raw;
    std::vector<bool>* T_HPSbyLooseCombinedIsolationDeltaBetaCorr;
    std::vector<bool>* T_HPSbyLooseCombinedIsolationDeltaBetaCorr3Hits;
    std::vector<bool>* T_HPSbyLooseIsolationMVA;
    std::vector<bool>* T_HPSbyLooseIsolationMVA2;
    std::vector<bool>* T_HPSbyMediumCombinedIsolationDeltaBetaCorr;
    std::vector<bool>* T_HPSbyMediumCombinedIsolationDeltaBetaCorr3Hits;
    std::vector<bool>* T_HPSbyMediumIsolationMVA;
    std::vector<bool>* T_HPSbyMediumIsolationMVA2;
    std::vector<bool>* T_HPSbyTightCombinedIsolationDeltaBetaCorr;
    std::vector<bool>* T_HPSbyTightCombinedIsolationDeltaBetaCorr3Hits;
    std::vector<bool>* T_HPSbyTightIsolationMVA;
    std::vector<bool>* T_HPSbyTightIsolationMVA2;
    std::vector<bool>* T_HPSbyVLooseCombinedIsolationDeltaBetaCorr;
    std::vector<bool>* T_HPSdecayModeFinding;
    std::vector<float>* T_HPSbyIsolationMVAraw;
    std::vector<float>* T_LTPt;
    std::vector<float>* T_Charge;
    std::vector<bool>* T_LTvalid;
    std::vector<float>* T_LTIpVtdxy;
    std::vector<float>* T_LTIpVtdz;
    std::vector<float>* T_LTIpVtdxyError;
    std::vector<float>* T_LTIpVtdzError;
    std::vector<float>* T_LTvx;
    std::vector<float>* T_LTvy;
    std::vector<float>* T_LTvz;
    std::vector<unsigned int>* T_LTValidHits;
    std::vector<float>* T_LTNormChiSqrd;
    std::vector<int>* T_TauGenMatchDaughter0Id;
    std::vector<int>* T_TauGenMatchDaughter1Id;
    std::vector<int>* T_TauGenMatchId;
    std::vector<int>* T_TauGenMatchMother0Id;
    std::vector<int>* T_TauGenMatchMother1Id;
    std::vector<int>* T_TauGenMatchGrandmother00Id;
    std::vector<int>* T_TauGenMatchGrandmother01Id;
    std::vector<int>* T_TauGenMatchGrandmother10Id;
    std::vector<int>* T_TauGenMatchGrandmother11Id;
    std::vector<int>* T_TauGenMatchDaughter0Status;
    std::vector<int>* T_TauGenMatchDaughter1Status;
    std::vector<int>* T_TauGenMatchStatus;
    std::vector<int>* T_TauGenMatchMother0Status;
    std::vector<int>* T_TauGenMatchMother1Status;
    std::vector<int>* T_TauGenMatchGrandmother00Status;
    std::vector<int>* T_TauGenMatchGrandmother01Status;
    std::vector<int>* T_TauGenMatchGrandmother10Status;
    std::vector<int>* T_TauGenMatchGrandmother11Status;
    Int_t E_NumElectrons;
    std::vector<float>* E_MomentumRank;
    std::vector<float>* E_Pt;
    std::vector<float>* E_Eta;
    std::vector<float>* E_Phi;
    std::vector<bool>* E_IsTightElectron;
    std::vector<bool>* E_IsLooseElectron;
    std::vector<int>* E_ElectronGenMatchDaughter0Id;
    std::vector<int>* E_ElectronGenMatchDaughter1Id;
    std::vector<int>* E_ElectronGenMatchId;
    std::vector<int>* E_ElectronGenMatchMother0Id;
    std::vector<int>* E_ElectronGenMatchMother1Id;
    std::vector<int>* E_ElectronGenMatchGrandmother00Id;
    std::vector<int>* E_ElectronGenMatchGrandmother01Id;
    std::vector<int>* E_ElectronGenMatchGrandmother10Id;
    std::vector<int>* E_ElectronGenMatchGrandmother11Id;
    std::vector<int>* E_ElectronGenMatchDaughter0Status;
    std::vector<int>* E_ElectronGenMatchDaughter1Status;
    std::vector<int>* E_ElectronGenMatchStatus;
    std::vector<int>* E_ElectronGenMatchMother0Status;
    std::vector<int>* E_ElectronGenMatchMother1Status;
    std::vector<int>* E_ElectronGenMatchGrandmother00Status;
    std::vector<int>* E_ElectronGenMatchGrandmother01Status;
    std::vector<int>* E_ElectronGenMatchGrandmother10Status;
    std::vector<int>* E_ElectronGenMatchGrandmother11Status;
    Int_t M_NumMuons;
    std::vector<float>* M_MomentumRank;
    std::vector<float>* M_Pt;
    std::vector<float>* M_Eta;
    std::vector<float>* M_Phi;
    std::vector<float>* M_RelIso;
    std::vector<bool>* M_IsTightMuon;
    std::vector<bool>* M_IsLooseMuon;
    std::vector<int>* M_MuonGenMatchDaughter0Id;
    std::vector<int>* M_MuonGenMatchDaughter1Id;
    std::vector<int>* M_MuonGenMatchId;
    std::vector<int>* M_MuonGenMatchMother0Id;
    std::vector<int>* M_MuonGenMatchMother1Id;
    std::vector<int>* M_MuonGenMatchGrandmother00Id;
    std::vector<int>* M_MuonGenMatchGrandmother01Id;
    std::vector<int>* M_MuonGenMatchGrandmother10Id;
    std::vector<int>* M_MuonGenMatchGrandmother11Id;
    std::vector<int>* M_MuonGenMatchDaughter0Status;
    std::vector<int>* M_MuonGenMatchDaughter1Status;
    std::vector<int>* M_MuonGenMatchStatus;
    std::vector<int>* M_MuonGenMatchMother0Status;
    std::vector<int>* M_MuonGenMatchMother1Status;
    std::vector<int>* M_MuonGenMatchGrandmother00Status;
    std::vector<int>* M_MuonGenMatchGrandmother01Status;
    std::vector<int>* M_MuonGenMatchGrandmother10Status;
    std::vector<int>* M_MuonGenMatchGrandmother11Status;
    Int_t J_NumJets;
    std::vector<float>* J_MomentumRank;
    std::vector<float>* J_Pt;
    std::vector<float>* J_Eta;
    std::vector<float>* J_Phi;
    std::vector<float>* J_combSecVtxBTag;
    std::vector<bool>* J_combSecVtxLooseBTag;
    std::vector<bool>* J_combSecVtxMediumBTag;
    std::vector<bool>* J_combSecVtxTightBTag;
    UInt_t TTL_NumTaus;
    UInt_t TTL_NumMuons;
    UInt_t TTL_NumElectrons;
    UInt_t TTL_NumLeptons;
    UInt_t TTL_NumCombos;
    std::vector<int>* TTL_MomentumRank;
    std::vector<int>* TTL_Tau1MomentumRank;
    std::vector<float>* TTL_Tau1Pt;
    std::vector<float>* TTL_Tau1Eta;
    std::vector<float>* TTL_Tau1Phi;
    std::vector<unsigned int>* TTL_Tau1NProngs;
    std::vector<unsigned int>* TTL_Tau1NSignalGammas;
    std::vector<unsigned int>* TTL_Tau1NSignalNeutrals;
    std::vector<unsigned int>* TTL_Tau1DecayMode;
    std::vector<float>* TTL_Tau1EmFraction;
    std::vector<bool>* TTL_Tau1IsInTheCracks;
    std::vector<bool>* TTL_Tau1HPSagainstElectronDeadECAL;
    std::vector<bool>* TTL_Tau1HPSagainstElectronLoose;
    std::vector<bool>* TTL_Tau1HPSagainstElectronLooseMVA2;
    std::vector<bool>* TTL_Tau1HPSagainstElectronLooseMVA3;
    std::vector<bool>* TTL_Tau1HPSagainstElectronMVA;
    std::vector<bool>* TTL_Tau1HPSagainstElectronMVA2category;
    std::vector<float>* TTL_Tau1HPSagainstElectronMVA2raw;
    std::vector<bool>* TTL_Tau1HPSagainstElectronMVA3category;
    std::vector<float>* TTL_Tau1HPSagainstElectronMVA3raw;
    std::vector<bool>* TTL_Tau1HPSagainstElectronMedium;
    std::vector<bool>* TTL_Tau1HPSagainstElectronMediumMVA2;
    std::vector<bool>* TTL_Tau1HPSagainstElectronMediumMVA3;
    std::vector<bool>* TTL_Tau1HPSagainstElectronTight;
    std::vector<bool>* TTL_Tau1HPSagainstElectronTightMVA2;
    std::vector<bool>* TTL_Tau1HPSagainstElectronTightMVA3;
    std::vector<bool>* TTL_Tau1HPSagainstElectronVLooseMVA2;
    std::vector<bool>* TTL_Tau1HPSagainstElectronVTightMVA3;
    std::vector<bool>* TTL_Tau1HPSagainstMuonLoose;
    std::vector<bool>* TTL_Tau1HPSagainstMuonLoose2;
    std::vector<bool>* TTL_Tau1HPSagainstMuonMedium;
    std::vector<bool>* TTL_Tau1HPSagainstMuonMedium2;
    std::vector<bool>* TTL_Tau1HPSagainstMuonTight;
    std::vector<bool>* TTL_Tau1HPSagainstMuonTight2;
    std::vector<float>* TTL_Tau1HPSbyCombinedIsolationDeltaBetaCorrRaw;
    std::vector<float>* TTL_Tau1HPSbyCombinedIsolationDeltaBetaCorrRaw3Hits;
    std::vector<float>* TTL_Tau1HPSbyIsolationMVA2raw;
    std::vector<bool>* TTL_Tau1HPSbyLooseCombinedIsolationDeltaBetaCorr;
    std::vector<bool>* TTL_Tau1HPSbyLooseCombinedIsolationDeltaBetaCorr3Hits;
    std::vector<bool>* TTL_Tau1HPSbyLooseIsolationMVA;
    std::vector<bool>* TTL_Tau1HPSbyLooseIsolationMVA2;
    std::vector<bool>* TTL_Tau1HPSbyMediumCombinedIsolationDeltaBetaCorr;
    std::vector<bool>* TTL_Tau1HPSbyMediumCombinedIsolationDeltaBetaCorr3Hits;
    std::vector<bool>* TTL_Tau1HPSbyMediumIsolationMVA;
    std::vector<bool>* TTL_Tau1HPSbyMediumIsolationMVA2;
    std::vector<bool>* TTL_Tau1HPSbyTightCombinedIsolationDeltaBetaCorr;
    std::vector<bool>* TTL_Tau1HPSbyTightCombinedIsolationDeltaBetaCorr3Hits;
    std::vector<bool>* TTL_Tau1HPSbyTightIsolationMVA;
    std::vector<bool>* TTL_Tau1HPSbyTightIsolationMVA2;
    std::vector<bool>* TTL_Tau1HPSbyVLooseCombinedIsolationDeltaBetaCorr;
    std::vector<bool>* TTL_Tau1HPSdecayModeFinding;
    std::vector<float>* TTL_Tau1HPSbyIsolationMVAraw;
    std::vector<float>* TTL_Tau1LTPt;
    std::vector<float>* TTL_Tau1Charge;
    std::vector<bool>* TTL_Tau1LTvalid;
    std::vector<float>* TTL_Tau1LTIpVtdxy;
    std::vector<float>* TTL_Tau1LTIpVtdz;
    std::vector<float>* TTL_Tau1LTIpVtdxyError;
    std::vector<float>* TTL_Tau1LTIpVtdzError;
    std::vector<float>* TTL_Tau1LTvx;
    std::vector<float>* TTL_Tau1LTvy;
    std::vector<float>* TTL_Tau1LTvz;
    std::vector<unsigned int>* TTL_Tau1LTValidHits;
    std::vector<float>* TTL_Tau1LTNormChiSqrd;
    std::vector<int>* TTL_Tau1GenMatchDaughter0Id;
    std::vector<int>* TTL_Tau1GenMatchDaughter1Id;
    std::vector<int>* TTL_Tau1GenMatchId;
    std::vector<int>* TTL_Tau1GenMatchMother0Id;
    std::vector<int>* TTL_Tau1GenMatchMother1Id;
    std::vector<int>* TTL_Tau1GenMatchGrandmother00Id;
    std::vector<int>* TTL_Tau1GenMatchGrandmother01Id;
    std::vector<int>* TTL_Tau1GenMatchGrandmother10Id;
    std::vector<int>* TTL_Tau1GenMatchGrandmother11Id;
    std::vector<int>* TTL_Tau1GenMatchDaughter0Status;
    std::vector<int>* TTL_Tau1GenMatchDaughter1Status;
    std::vector<int>* TTL_Tau1GenMatchStatus;
    std::vector<int>* TTL_Tau1GenMatchMother0Status;
    std::vector<int>* TTL_Tau1GenMatchMother1Status;
    std::vector<int>* TTL_Tau1GenMatchGrandmother00Status;
    std::vector<int>* TTL_Tau1GenMatchGrandmother01Status;
    std::vector<int>* TTL_Tau1GenMatchGrandmother10Status;
    std::vector<int>* TTL_Tau1GenMatchGrandmother11Status;
    std::vector<int>* TTL_Tau2MomentumRank;
    std::vector<float>* TTL_Tau2Pt;
    std::vector<float>* TTL_Tau2Eta;
    std::vector<float>* TTL_Tau2Phi;
    std::vector<unsigned int>* TTL_Tau2NProngs;
    std::vector<unsigned int>* TTL_Tau2NSignalGammas;
    std::vector<unsigned int>* TTL_Tau2NSignalNeutrals;
    std::vector<unsigned int>* TTL_Tau2DecayMode;
    std::vector<float>* TTL_Tau2EmFraction;
    std::vector<bool>* TTL_Tau2IsInTheCracks;
    std::vector<bool>* TTL_Tau2HPSagainstElectronDeadECAL;
    std::vector<bool>* TTL_Tau2HPSagainstElectronLoose;
    std::vector<bool>* TTL_Tau2HPSagainstElectronLooseMVA2;
    std::vector<bool>* TTL_Tau2HPSagainstElectronLooseMVA3;
    std::vector<bool>* TTL_Tau2HPSagainstElectronMVA;
    std::vector<bool>* TTL_Tau2HPSagainstElectronMVA2category;
    std::vector<float>* TTL_Tau2HPSagainstElectronMVA2raw;
    std::vector<bool>* TTL_Tau2HPSagainstElectronMVA3category;
    std::vector<float>* TTL_Tau2HPSagainstElectronMVA3raw;
    std::vector<bool>* TTL_Tau2HPSagainstElectronMedium;
    std::vector<bool>* TTL_Tau2HPSagainstElectronMediumMVA2;
    std::vector<bool>* TTL_Tau2HPSagainstElectronMediumMVA3;
    std::vector<bool>* TTL_Tau2HPSagainstElectronTight;
    std::vector<bool>* TTL_Tau2HPSagainstElectronTightMVA2;
    std::vector<bool>* TTL_Tau2HPSagainstElectronTightMVA3;
    std::vector<bool>* TTL_Tau2HPSagainstElectronVLooseMVA2;
    std::vector<bool>* TTL_Tau2HPSagainstElectronVTightMVA3;
    std::vector<bool>* TTL_Tau2HPSagainstMuonLoose;
    std::vector<bool>* TTL_Tau2HPSagainstMuonLoose2;
    std::vector<bool>* TTL_Tau2HPSagainstMuonMedium;
    std::vector<bool>* TTL_Tau2HPSagainstMuonMedium2;
    std::vector<bool>* TTL_Tau2HPSagainstMuonTight;
    std::vector<bool>* TTL_Tau2HPSagainstMuonTight2;
    std::vector<float>* TTL_Tau2HPSbyCombinedIsolationDeltaBetaCorrRaw;
    std::vector<float>* TTL_Tau2HPSbyCombinedIsolationDeltaBetaCorrRaw3Hits;
    std::vector<float>* TTL_Tau2HPSbyIsolationMVA2raw;
    std::vector<bool>* TTL_Tau2HPSbyLooseCombinedIsolationDeltaBetaCorr;
    std::vector<bool>* TTL_Tau2HPSbyLooseCombinedIsolationDeltaBetaCorr3Hits;
    std::vector<bool>* TTL_Tau2HPSbyLooseIsolationMVA;
    std::vector<bool>* TTL_Tau2HPSbyLooseIsolationMVA2;
    std::vector<bool>* TTL_Tau2HPSbyMediumCombinedIsolationDeltaBetaCorr;
    std::vector<bool>* TTL_Tau2HPSbyMediumCombinedIsolationDeltaBetaCorr3Hits;
    std::vector<bool>* TTL_Tau2HPSbyMediumIsolationMVA;
    std::vector<bool>* TTL_Tau2HPSbyMediumIsolationMVA2;
    std::vector<bool>* TTL_Tau2HPSbyTightCombinedIsolationDeltaBetaCorr;
    std::vector<bool>* TTL_Tau2HPSbyTightCombinedIsolationDeltaBetaCorr3Hits;
    std::vector<bool>* TTL_Tau2HPSbyTightIsolationMVA;
    std::vector<bool>* TTL_Tau2HPSbyTightIsolationMVA2;
    std::vector<bool>* TTL_Tau2HPSbyVLooseCombinedIsolationDeltaBetaCorr;
    std::vector<bool>* TTL_Tau2HPSdecayModeFinding;
    std::vector<float>* TTL_Tau2HPSbyIsolationMVAraw;
    std::vector<float>* TTL_Tau2LTPt;
    std::vector<float>* TTL_Tau2Charge;
    std::vector<bool>* TTL_Tau2LTvalid;
    std::vector<float>* TTL_Tau2LTIpVtdxy;
    std::vector<float>* TTL_Tau2LTIpVtdz;
    std::vector<float>* TTL_Tau2LTIpVtdxyError;
    std::vector<float>* TTL_Tau2LTIpVtdzError;
    std::vector<float>* TTL_Tau2LTvx;
    std::vector<float>* TTL_Tau2LTvy;
    std::vector<float>* TTL_Tau2LTvz;
    std::vector<unsigned int>* TTL_Tau2LTValidHits;
    std::vector<float>* TTL_Tau2LTNormChiSqrd;
    std::vector<int>* TTL_Tau2GenMatchDaughter0Id;
    std::vector<int>* TTL_Tau2GenMatchDaughter1Id;
    std::vector<int>* TTL_Tau2GenMatchId;
    std::vector<int>* TTL_Tau2GenMatchMother0Id;
    std::vector<int>* TTL_Tau2GenMatchMother1Id;
    std::vector<int>* TTL_Tau2GenMatchGrandmother00Id;
    std::vector<int>* TTL_Tau2GenMatchGrandmother01Id;
    std::vector<int>* TTL_Tau2GenMatchGrandmother10Id;
    std::vector<int>* TTL_Tau2GenMatchGrandmother11Id;
    std::vector<int>* TTL_Tau2GenMatchDaughter0Status;
    std::vector<int>* TTL_Tau2GenMatchDaughter1Status;
    std::vector<int>* TTL_Tau2GenMatchStatus;
    std::vector<int>* TTL_Tau2GenMatchMother0Status;
    std::vector<int>* TTL_Tau2GenMatchMother1Status;
    std::vector<int>* TTL_Tau2GenMatchGrandmother00Status;
    std::vector<int>* TTL_Tau2GenMatchGrandmother01Status;
    std::vector<int>* TTL_Tau2GenMatchGrandmother10Status;
    std::vector<int>* TTL_Tau2GenMatchGrandmother11Status;
    std::vector<int>* TTL_MuonMomentumRank;
    std::vector<int>* TTL_ElectronMomentumRank;
    std::vector<int>* TTL_LeptonMomentumRank;
    std::vector<float>* TTL_LeptonIsMuon;
    std::vector<float>* TTL_LeptonIsElectron;
    std::vector<float>* TTL_LeptonPt;
    std::vector<float>* TTL_LeptonEta;
    std::vector<float>* TTL_LeptonPhi;
    std::vector<float>* TTL_LeptonRelIso;
    std::vector<bool>* TTL_LeptonIsLoose;
    std::vector<bool>* TTL_LeptonIsTight;
    std::vector<unsigned int>* TTL_NumLooseMuons;
    std::vector<unsigned int>* TTL_NumExLooseMuons;
    std::vector<unsigned int>* TTL_NumTightMuons;
    std::vector<unsigned int>* TTL_NumLooseElectrons;
    std::vector<unsigned int>* TTL_NumExLooseElectrons;
    std::vector<unsigned int>* TTL_NumTightElectrons;
    std::vector<int>* TTL_LeptonGenMatchDaughter0Id;
    std::vector<int>* TTL_LeptonGenMatchDaughter1Id;
    std::vector<int>* TTL_LeptonGenMatchId;
    std::vector<int>* TTL_LeptonGenMatchMother0Id;
    std::vector<int>* TTL_LeptonGenMatchMother1Id;
    std::vector<int>* TTL_LeptonGenMatchGrandmother00Id;
    std::vector<int>* TTL_LeptonGenMatchGrandmother01Id;
    std::vector<int>* TTL_LeptonGenMatchGrandmother10Id;
    std::vector<int>* TTL_LeptonGenMatchGrandmother11Id;
    std::vector<int>* TTL_LeptonGenMatchDaughter0Status;
    std::vector<int>* TTL_LeptonGenMatchDaughter1Status;
    std::vector<int>* TTL_LeptonGenMatchStatus;
    std::vector<int>* TTL_LeptonGenMatchMother0Status;
    std::vector<int>* TTL_LeptonGenMatchMother1Status;
    std::vector<int>* TTL_LeptonGenMatchGrandmother00Status;
    std::vector<int>* TTL_LeptonGenMatchGrandmother01Status;
    std::vector<int>* TTL_LeptonGenMatchGrandmother10Status;
    std::vector<int>* TTL_LeptonGenMatchGrandmother11Status;
    std::vector<float>* TTL_DitauVisibleMass;
    std::vector<float>* TTL_DitauMETMass;
    std::vector<float>* TTL_DitauCosDeltaPhi;
    std::vector<float>* TTL_DitauDeltaR;
    std::vector<float>* TTL_Tau1LeptonDeltaR;
    std::vector<float>* TTL_Tau2LeptonDeltaR;
    std::vector<float>* TTL_HT;
    std::vector<unsigned int>* TTL_NumCSVLbtagJets;
    std::vector<unsigned int>* TTL_NumCSVMbtagJets;
    std::vector<unsigned int>* TTL_NumCSVTbtagJets;
    std::vector<unsigned int>* TTL_NumNonCSVLbtagJets;
    std::vector<unsigned int>* TTL_NumNonCSVMbtagJets;
    std::vector<unsigned int>* TTL_NumNonCSVTbtagJets;
    std::vector<unsigned int>* TTL_NumCleanCSVLbtagJets;
    std::vector<unsigned int>* TTL_NumCleanCSVMbtagJets;
    std::vector<unsigned int>* TTL_NumCleanCSVTbtagJets;
    std::vector<unsigned int>* TTL_NumCleanNonCSVLbtagJets;
    std::vector<unsigned int>* TTL_NumCleanNonCSVMbtagJets;
    std::vector<unsigned int>* TTL_NumCleanNonCSVTbtagJets;
    std::vector<float>* TTL_LeptonEventWeight;
    std::vector<float>* TTL_CSVeventWeight;
    std::vector<float>* TTL_CSVeventWeightHFdown;
    std::vector<float>* TTL_CSVeventWeightHFup;
    std::vector<float>* TTL_CSVeventWeightLFdown;
    std::vector<float>* TTL_CSVeventWeightLFup;
    std::vector<float>* TTL_CSVeventWeightHFStats1down;
    std::vector<float>* TTL_CSVeventWeightHFStats1up;
    std::vector<float>* TTL_CSVeventWeightLFStats1down;
    std::vector<float>* TTL_CSVeventWeightLFStats1up;
    std::vector<float>* TTL_CSVeventWeightHFStats2down;
    std::vector<float>* TTL_CSVeventWeightHFStats2up;
    std::vector<float>* TTL_CSVeventWeightLFStats2down;
    std::vector<float>* TTL_CSVeventWeightLFStats2up;
    std::vector<float>* TTL_CSVeventWeightCErr1up;
    std::vector<float>* TTL_CSVeventWeightCErr1down;
    std::vector<float>* TTL_CSVeventWeightCErr2up;
    std::vector<float>* TTL_CSVeventWeightCErr2down;
