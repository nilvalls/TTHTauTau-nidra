fChain->SetBranchAddress("runNumber", &runNumber);
fChain->SetBranchAddress("eventNumber", &eventNumber);
fChain->SetBranchAddress("lumiBlock", &lumiBlock);
fChain->SetBranchAddress("numInteractionsBXm1", &numInteractionsBXm1);
fChain->SetBranchAddress("numInteractionsBX0", &numInteractionsBX0);
fChain->SetBranchAddress("numInteractionsBXp1", &numInteractionsBXp1);
fChain->SetBranchAddress("GenMET", &GenMET);
fChain->SetBranchAddress("GenMETphi", &GenMETphi);
fChain->SetBranchAddress("Tau1GenPt", &Tau1GenPt);
fChain->SetBranchAddress("Tau2GenPt", &Tau2GenPt);
fChain->SetBranchAddress("Tau1GenE", &Tau1GenE);
fChain->SetBranchAddress("Tau2GenE", &Tau2GenE);
fChain->SetBranchAddress("Tau1GenEta", &Tau1GenEta);
fChain->SetBranchAddress("Tau2GenEta", &Tau2GenEta);
fChain->SetBranchAddress("Tau1GenPhi", &Tau1GenPhi);
fChain->SetBranchAddress("Tau2GenPhi", &Tau2GenPhi);
fChain->SetBranchAddress("Tau1GenParentMass", &Tau1GenParentMass);
fChain->SetBranchAddress("Tau2GenParentMass", &Tau2GenParentMass);
fChain->SetBranchAddress("TauTauPlusMetGenMass", &TauTauPlusMetGenMass);
fChain->SetBranchAddress("Tau1Matched", &Tau1Matched);
fChain->SetBranchAddress("Tau2Matched", &Tau2Matched);
fChain->SetBranchAddress("Tau1MotherId", &Tau1MotherId);
fChain->SetBranchAddress("Tau2MotherId", &Tau2MotherId);
fChain->SetBranchAddress("Tau1PdgId", &Tau1PdgId);
fChain->SetBranchAddress("Tau2PdgId", &Tau2PdgId);
fChain->SetBranchAddress("Tau1MotherPdgId", &Tau1MotherPdgId);
fChain->SetBranchAddress("Tau2MotherPdgId", &Tau2MotherPdgId);
fChain->SetBranchAddress("Tau1_ParentTauMatched", &Tau1_ParentTauMatched);
fChain->SetBranchAddress("Tau2_ParentTauMatched", &Tau2_ParentTauMatched);
fChain->SetBranchAddress("Tau1_ZtauMatched", &Tau1_ZtauMatched);
fChain->SetBranchAddress("Tau2_ZtauMatched", &Tau2_ZtauMatched);
fChain->SetBranchAddress("Tau1_ZeMatched", &Tau1_ZeMatched);
fChain->SetBranchAddress("Tau2_ZeMatched", &Tau2_ZeMatched);
fChain->SetBranchAddress("Tau1_MatchesGenHadronic", &Tau1_MatchesGenHadronic);
fChain->SetBranchAddress("Tau2_MatchesGenHadronic", &Tau2_MatchesGenHadronic);
fChain->SetBranchAddress("NumPV", &NumPV);
fChain->SetBranchAddress("Tau1E", &Tau1E);
fChain->SetBranchAddress("Tau2E", &Tau2E);
fChain->SetBranchAddress("Tau1Et", &Tau1Et);
fChain->SetBranchAddress("Tau2Et", &Tau2Et);
fChain->SetBranchAddress("Tau1Pt", &Tau1Pt);
fChain->SetBranchAddress("Tau2Pt", &Tau2Pt);
fChain->SetBranchAddress("Tau1LTvalid", &Tau1LTvalid);
fChain->SetBranchAddress("Tau2LTvalid", &Tau2LTvalid);
fChain->SetBranchAddress("Tau1LTPt", &Tau1LTPt);
fChain->SetBranchAddress("Tau2LTPt", &Tau2LTPt);
fChain->SetBranchAddress("Tau1Charge", &Tau1Charge);
fChain->SetBranchAddress("Tau2Charge", &Tau2Charge);
fChain->SetBranchAddress("Tau1Eta", &Tau1Eta);
fChain->SetBranchAddress("Tau2Eta", &Tau2Eta);
fChain->SetBranchAddress("Tau1Phi", &Tau1Phi);
fChain->SetBranchAddress("Tau2Phi", &Tau2Phi);
fChain->SetBranchAddress("Tau1LTIpVtdxy", &Tau1LTIpVtdxy);
fChain->SetBranchAddress("Tau1LTIpVtdz", &Tau1LTIpVtdz);
fChain->SetBranchAddress("Tau1LTIpVtdxyError", &Tau1LTIpVtdxyError);
fChain->SetBranchAddress("Tau1LTIpVtdzError", &Tau1LTIpVtdzError);
fChain->SetBranchAddress("Tau1LTvx", &Tau1LTvx);
fChain->SetBranchAddress("Tau1LTvy", &Tau1LTvy);
fChain->SetBranchAddress("Tau1LTvz", &Tau1LTvz);
fChain->SetBranchAddress("Tau1LTValidHits", &Tau1LTValidHits);
fChain->SetBranchAddress("Tau1LTNormChiSqrd", &Tau1LTNormChiSqrd);
fChain->SetBranchAddress("Tau2LTIpVtdxy", &Tau2LTIpVtdxy);
fChain->SetBranchAddress("Tau2LTIpVtdz", &Tau2LTIpVtdz);
fChain->SetBranchAddress("Tau2LTIpVtdxyError", &Tau2LTIpVtdxyError);
fChain->SetBranchAddress("Tau2LTIpVtdzError", &Tau2LTIpVtdzError);
fChain->SetBranchAddress("Tau2LTvx", &Tau2LTvx);
fChain->SetBranchAddress("Tau2LTvy", &Tau2LTvy);
fChain->SetBranchAddress("Tau2LTvz", &Tau2LTvz);
fChain->SetBranchAddress("Tau2LTValidHits", &Tau2LTValidHits);
fChain->SetBranchAddress("Tau2LTNormChiSqrd", &Tau2LTNormChiSqrd);
fChain->SetBranchAddress("Tau1NProngs", &Tau1NProngs);
fChain->SetBranchAddress("Tau2NProngs", &Tau2NProngs);
fChain->SetBranchAddress("Tau1NSignalGammas", &Tau1NSignalGammas);
fChain->SetBranchAddress("Tau2NSignalGammas", &Tau2NSignalGammas);
fChain->SetBranchAddress("Tau1NSignalNeutrals", &Tau1NSignalNeutrals);
fChain->SetBranchAddress("Tau2NSignalNeutrals", &Tau2NSignalNeutrals);
fChain->SetBranchAddress("Tau1NSignalPiZeros", &Tau1NSignalPiZeros);
fChain->SetBranchAddress("Tau2NSignalPiZeros", &Tau2NSignalPiZeros);
fChain->SetBranchAddress("Tau1DecayMode", &Tau1DecayMode);
fChain->SetBranchAddress("Tau2DecayMode", &Tau2DecayMode);
fChain->SetBranchAddress("Tau1EmFraction", &Tau1EmFraction);
fChain->SetBranchAddress("Tau2EmFraction", &Tau2EmFraction);
fChain->SetBranchAddress("Tau1IsInTheCracks", &Tau1IsInTheCracks);
fChain->SetBranchAddress("Tau2IsInTheCracks", &Tau2IsInTheCracks);
fChain->SetBranchAddress("MET", &MET);
fChain->SetBranchAddress("METphi", &METphi);
fChain->SetBranchAddress("METl1l2l3corr", &METl1l2l3corr);
fChain->SetBranchAddress("METl1l2l3corrPhi", &METl1l2l3corrPhi);
fChain->SetBranchAddress("METsignificance", &METsignificance);
fChain->SetBranchAddress("TauTauVisibleMass", &TauTauVisibleMass);
fChain->SetBranchAddress("TauTauVisPlusMetMass", &TauTauVisPlusMetMass);
fChain->SetBranchAddress("TauTauCollinearMetMass", &TauTauCollinearMetMass);
fChain->SetBranchAddress("TauTauCosDPhi", &TauTauCosDPhi);
fChain->SetBranchAddress("TauTauDeltaR", &TauTauDeltaR);
fChain->SetBranchAddress("TauTauPZeta", &TauTauPZeta);
fChain->SetBranchAddress("TauTauPZetaVis", &TauTauPZetaVis);
fChain->SetBranchAddress("Tau1MetCosDphi", &Tau1MetCosDphi);
fChain->SetBranchAddress("Tau2MetCosDphi", &Tau2MetCosDphi);
fChain->SetBranchAddress("Tau1MetMt", &Tau1MetMt);
fChain->SetBranchAddress("Tau2MetMt", &Tau2MetMt);
fChain->SetBranchAddress("nBtagsHiEffTrkCnt", &nBtagsHiEffTrkCnt);
fChain->SetBranchAddress("nBtagsHiPurityTrkCnt", &nBtagsHiPurityTrkCnt);
fChain->SetBranchAddress("nBTagsHiEffSimpleSecVtx", &nBTagsHiEffSimpleSecVtx);
fChain->SetBranchAddress("nBTagsHiPuritySimpleSecVtx", &nBTagsHiPuritySimpleSecVtx);
fChain->SetBranchAddress("nBTagsCombSecVtx", &nBTagsCombSecVtx);
fChain->SetBranchAddress("jetSumEt", &jetSumEt);
fChain->SetBranchAddress("jetMETSumEt", &jetMETSumEt);
fChain->SetBranchAddress("nJets", &nJets);
fChain->SetBranchAddress("nExtraJets", &nExtraJets);
fChain->SetBranchAddress("Tau1Tau2LeadingJetPtSum", &Tau1Tau2LeadingJetPtSum);
fChain->SetBranchAddress("Tau1LeadingJetDeltaPhi", &Tau1LeadingJetDeltaPhi);
fChain->SetBranchAddress("Tau2LeadingJetDeltaPhi", &Tau2LeadingJetDeltaPhi);
fChain->SetBranchAddress("Tau1hpsPFTauDiscriminationAgainstLooseElectron", &Tau1hpsPFTauDiscriminationAgainstLooseElectron);
fChain->SetBranchAddress("Tau1hpsPFTauDiscriminationAgainstLooseMuon", &Tau1hpsPFTauDiscriminationAgainstLooseMuon);
fChain->SetBranchAddress("Tau1hpsPFTauDiscriminationAgainstMediumElectron", &Tau1hpsPFTauDiscriminationAgainstMediumElectron);
fChain->SetBranchAddress("Tau1hpsPFTauDiscriminationAgainstMediumMuon", &Tau1hpsPFTauDiscriminationAgainstMediumMuon);
fChain->SetBranchAddress("Tau1hpsPFTauDiscriminationAgainstTightElectron", &Tau1hpsPFTauDiscriminationAgainstTightElectron);
fChain->SetBranchAddress("Tau1hpsPFTauDiscriminationAgainstTightMuon", &Tau1hpsPFTauDiscriminationAgainstTightMuon);
fChain->SetBranchAddress("Tau1hpsPFTauDiscriminationByDecayModeFinding", &Tau1hpsPFTauDiscriminationByDecayModeFinding);
fChain->SetBranchAddress("Tau1hpsPFTauDiscriminationByLooseIsolation", &Tau1hpsPFTauDiscriminationByLooseIsolation);
fChain->SetBranchAddress("Tau1hpsPFTauDiscriminationByMediumIsolation", &Tau1hpsPFTauDiscriminationByMediumIsolation);
fChain->SetBranchAddress("Tau1hpsPFTauDiscriminationByTightIsolation", &Tau1hpsPFTauDiscriminationByTightIsolation);
fChain->SetBranchAddress("Tau1hpsPFTauDiscriminationByVLooseIsolation", &Tau1hpsPFTauDiscriminationByVLooseIsolation);
fChain->SetBranchAddress("Tau2hpsPFTauDiscriminationAgainstLooseElectron", &Tau2hpsPFTauDiscriminationAgainstLooseElectron);
fChain->SetBranchAddress("Tau2hpsPFTauDiscriminationAgainstLooseMuon", &Tau2hpsPFTauDiscriminationAgainstLooseMuon);
fChain->SetBranchAddress("Tau2hpsPFTauDiscriminationAgainstMediumElectron", &Tau2hpsPFTauDiscriminationAgainstMediumElectron);
fChain->SetBranchAddress("Tau2hpsPFTauDiscriminationAgainstMediumMuon", &Tau2hpsPFTauDiscriminationAgainstMediumMuon);
fChain->SetBranchAddress("Tau2hpsPFTauDiscriminationAgainstTightElectron", &Tau2hpsPFTauDiscriminationAgainstTightElectron);
fChain->SetBranchAddress("Tau2hpsPFTauDiscriminationAgainstTightMuon", &Tau2hpsPFTauDiscriminationAgainstTightMuon);
fChain->SetBranchAddress("Tau2hpsPFTauDiscriminationByDecayModeFinding", &Tau2hpsPFTauDiscriminationByDecayModeFinding);
fChain->SetBranchAddress("Tau2hpsPFTauDiscriminationByLooseIsolation", &Tau2hpsPFTauDiscriminationByLooseIsolation);
fChain->SetBranchAddress("Tau2hpsPFTauDiscriminationByMediumIsolation", &Tau2hpsPFTauDiscriminationByMediumIsolation);
fChain->SetBranchAddress("Tau2hpsPFTauDiscriminationByTightIsolation", &Tau2hpsPFTauDiscriminationByTightIsolation);
fChain->SetBranchAddress("Tau2hpsPFTauDiscriminationByVLooseIsolation", &Tau2hpsPFTauDiscriminationByVLooseIsolation);
fChain->SetBranchAddress("Tau1hpsPFTauDiscriminationByVLooseIsolationDBSumPtCorr", &Tau1hpsPFTauDiscriminationByVLooseIsolationDBSumPtCorr);
fChain->SetBranchAddress("Tau1hpsPFTauDiscriminationByLooseIsolationDBSumPtCorr", &Tau1hpsPFTauDiscriminationByLooseIsolationDBSumPtCorr);
fChain->SetBranchAddress("Tau1hpsPFTauDiscriminationByMediumIsolationDBSumPtCorr", &Tau1hpsPFTauDiscriminationByMediumIsolationDBSumPtCorr);
fChain->SetBranchAddress("Tau1hpsPFTauDiscriminationByTightIsolationDBSumPtCorr", &Tau1hpsPFTauDiscriminationByTightIsolationDBSumPtCorr);
fChain->SetBranchAddress("Tau1hpsPFTauDiscriminationByVLooseCombinedIsolationDBSumPtCorr", &Tau1hpsPFTauDiscriminationByVLooseCombinedIsolationDBSumPtCorr);
fChain->SetBranchAddress("Tau1hpsPFTauDiscriminationByLooseCombinedIsolationDBSumPtCorr", &Tau1hpsPFTauDiscriminationByLooseCombinedIsolationDBSumPtCorr);
fChain->SetBranchAddress("Tau1hpsPFTauDiscriminationByMediumCombinedIsolationDBSumPtCorr", &Tau1hpsPFTauDiscriminationByMediumCombinedIsolationDBSumPtCorr);
fChain->SetBranchAddress("Tau1hpsPFTauDiscriminationByTightCombinedIsolationDBSumPtCorr", &Tau1hpsPFTauDiscriminationByTightCombinedIsolationDBSumPtCorr);
fChain->SetBranchAddress("Tau2hpsPFTauDiscriminationByVLooseIsolationDBSumPtCorr", &Tau2hpsPFTauDiscriminationByVLooseIsolationDBSumPtCorr);
fChain->SetBranchAddress("Tau2hpsPFTauDiscriminationByLooseIsolationDBSumPtCorr", &Tau2hpsPFTauDiscriminationByLooseIsolationDBSumPtCorr);
fChain->SetBranchAddress("Tau2hpsPFTauDiscriminationByMediumIsolationDBSumPtCorr", &Tau2hpsPFTauDiscriminationByMediumIsolationDBSumPtCorr);
fChain->SetBranchAddress("Tau2hpsPFTauDiscriminationByTightIsolationDBSumPtCorr", &Tau2hpsPFTauDiscriminationByTightIsolationDBSumPtCorr);
fChain->SetBranchAddress("Tau2hpsPFTauDiscriminationByVLooseCombinedIsolationDBSumPtCorr", &Tau2hpsPFTauDiscriminationByVLooseCombinedIsolationDBSumPtCorr);
fChain->SetBranchAddress("Tau2hpsPFTauDiscriminationByLooseCombinedIsolationDBSumPtCorr", &Tau2hpsPFTauDiscriminationByLooseCombinedIsolationDBSumPtCorr);
fChain->SetBranchAddress("Tau2hpsPFTauDiscriminationByMediumCombinedIsolationDBSumPtCorr", &Tau2hpsPFTauDiscriminationByMediumCombinedIsolationDBSumPtCorr);
fChain->SetBranchAddress("Tau2hpsPFTauDiscriminationByTightCombinedIsolationDBSumPtCorr", &Tau2hpsPFTauDiscriminationByTightCombinedIsolationDBSumPtCorr);
fChain->SetBranchAddress("Tau1hpsPFTauDiscriminationByRawCombinedIsolationDBSumPtCorr", &Tau1hpsPFTauDiscriminationByRawCombinedIsolationDBSumPtCorr);
fChain->SetBranchAddress("Tau1hpsPFTauDiscriminationByRawChargedIsolationDBSumPtCorr", &Tau1hpsPFTauDiscriminationByRawChargedIsolationDBSumPtCorr);
fChain->SetBranchAddress("Tau1hpsPFTauDiscriminationByRawGammaIsolationDBSumPtCorr", &Tau1hpsPFTauDiscriminationByRawGammaIsolationDBSumPtCorr);
fChain->SetBranchAddress("Tau2hpsPFTauDiscriminationByRawCombinedIsolationDBSumPtCorr", &Tau2hpsPFTauDiscriminationByRawCombinedIsolationDBSumPtCorr);
fChain->SetBranchAddress("Tau2hpsPFTauDiscriminationByRawChargedIsolationDBSumPtCorr", &Tau2hpsPFTauDiscriminationByRawChargedIsolationDBSumPtCorr);
fChain->SetBranchAddress("Tau2hpsPFTauDiscriminationByRawGammaIsolationDBSumPtCorr", &Tau2hpsPFTauDiscriminationByRawGammaIsolationDBSumPtCorr);


fChain->SetBranchAddress("NSVFitStatus", &NSVFitStatus);
fChain->SetBranchAddress("NSVFitMass", &NSVFitMass);
fChain->SetBranchAddress("NSVFitMET", &NSVFitMET);
fChain->SetBranchAddress("NSVFitMETphi", &NSVFitMETphi);
fChain->SetBranchAddress("NSVFitSystemPt", &NSVFitSystemPt);
fChain->SetBranchAddress("NSVFitSystemMag", &NSVFitSystemMag);
fChain->SetBranchAddress("NSVFitSystemPhi", &NSVFitSystemPhi);
fChain->SetBranchAddress("NSVFitSystemEta", &NSVFitSystemEta);



fChain->SetBranchAddress("DeltaOmegaBoostAndBoostedSVFitTau1", &DeltaOmegaBoostAndBoostedSVFitTau1);
fChain->SetBranchAddress("DeltaOmegaBoostAndBoostedSVFitTau2", &DeltaOmegaBoostAndBoostedSVFitTau2);
fChain->SetBranchAddress("DeltaOmegaBoostedSVFitTau1AndBoostedSVFitTau2", &DeltaOmegaBoostedSVFitTau1AndBoostedSVFitTau2);
fChain->SetBranchAddress("DeltaPhiBoostAndBoostedSVFitTau1", &DeltaPhiBoostAndBoostedSVFitTau1);
fChain->SetBranchAddress("DeltaPhiBoostAndBoostedSVFitTau2", &DeltaPhiBoostAndBoostedSVFitTau2);
fChain->SetBranchAddress("DeltaPhiBoostedSVFitTau1AndBoostedSVFitTau2", &DeltaPhiBoostedSVFitTau1AndBoostedSVFitTau2);

