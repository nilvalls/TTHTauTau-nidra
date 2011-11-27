fChain->SetBranchAddress("runNumber", &runNumber);
fChain->SetBranchAddress("eventNumber", &eventNumber);
fChain->SetBranchAddress("lumiBlock", &lumiBlock);
fChain->SetBranchAddress("numInteractionsBXm1", &numInteractionsBXm1);
fChain->SetBranchAddress("numInteractionsBX0", &numInteractionsBX0);
fChain->SetBranchAddress("numInteractionsBXp1", &numInteractionsBXp1);
fChain->SetBranchAddress("Tau1_MatchesGenHadronic", &Tau1_MatchesGenHadronic);
fChain->SetBranchAddress("Tau2_MatchesGenHadronic", &Tau2_MatchesGenHadronic);
fChain->SetBranchAddress("Tau1_ParentTauMatched", &Tau1_ParentTauMatched);
fChain->SetBranchAddress("Tau2_ParentTauMatched", &Tau2_ParentTauMatched);
fChain->SetBranchAddress("Tau1_ZtauMatched", &Tau1_ZtauMatched);
fChain->SetBranchAddress("Tau2_ZtauMatched", &Tau2_ZtauMatched);
fChain->SetBranchAddress("Tau1_ZeMatched", &Tau1_ZeMatched);
fChain->SetBranchAddress("Tau2_ZeMatched", &Tau2_ZeMatched);

fChain->SetBranchAddress("Tau1GenPt", &Tau1GenPt);
fChain->SetBranchAddress("Tau2GenPt", &Tau2GenPt);
fChain->SetBranchAddress("Tau1GenE", &Tau1GenE);
fChain->SetBranchAddress("Tau2GenE", &Tau2GenE);
fChain->SetBranchAddress("Tau1GenEta", &Tau1GenEta);
fChain->SetBranchAddress("Tau2GenEta", &Tau2GenEta);
fChain->SetBranchAddress("Tau1GenPhi", &Tau1GenPhi);
fChain->SetBranchAddress("Tau2GenPhi", &Tau2GenPhi);
fChain->SetBranchAddress("Tau1Matched", &Tau1Matched);
fChain->SetBranchAddress("Tau2Matched", &Tau2Matched);
fChain->SetBranchAddress("Tau1MotherId", &Tau1MotherId);
fChain->SetBranchAddress("Tau2MotherId", &Tau2MotherId);
fChain->SetBranchAddress("Tau1PdgId", &Tau1PdgId);
fChain->SetBranchAddress("Tau2PdgId", &Tau2PdgId);
fChain->SetBranchAddress("Tau1MotherPdgId", &Tau1MotherPdgId);
fChain->SetBranchAddress("Tau2MotherPdgId", &Tau2MotherPdgId);
fChain->SetBranchAddress("NumPV", &NumPV);
fChain->SetBranchAddress("Tau1MetMt", &Tau1MetMt);
fChain->SetBranchAddress("Tau2MetMt", &Tau2MetMt);
fChain->SetBranchAddress("Tau1E", &Tau1E);
fChain->SetBranchAddress("Tau2E", &Tau2E);
fChain->SetBranchAddress("Tau1Et", &Tau1Et);
fChain->SetBranchAddress("Tau2Et", &Tau2Et);
fChain->SetBranchAddress("Tau1Pt", &Tau1Pt);
fChain->SetBranchAddress("Tau2Pt", &Tau2Pt);
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
fChain->SetBranchAddress("Tau1LTIpVtxError", &Tau1LTIpVtxError);
fChain->SetBranchAddress("Tau1LTValidHits", &Tau1LTValidHits);
fChain->SetBranchAddress("Tau1LTNormChiSqrd", &Tau1LTNormChiSqrd);
fChain->SetBranchAddress("Tau2LTIpVtdxy", &Tau2LTIpVtdxy);
fChain->SetBranchAddress("Tau2LTIpVtdz", &Tau2LTIpVtdz);
fChain->SetBranchAddress("Tau2LTIpVtxError", &Tau2LTIpVtxError);
fChain->SetBranchAddress("Tau2LTValidHits", &Tau2LTValidHits);
fChain->SetBranchAddress("Tau2LTNormChiSqrd", &Tau2LTNormChiSqrd);
fChain->SetBranchAddress("Tau1NProngs", &Tau1NProngs);
fChain->SetBranchAddress("Tau2NProngs", &Tau2NProngs);
fChain->SetBranchAddress("Tau1EmFraction", &Tau1EmFraction);
fChain->SetBranchAddress("Tau2EmFraction", &Tau2EmFraction);
fChain->SetBranchAddress("Tau1HcalTotOverPLead", &Tau1HcalTotOverPLead);
fChain->SetBranchAddress("Tau2HcalTotOverPLead", &Tau2HcalTotOverPLead);
fChain->SetBranchAddress("Tau1HCalMaxOverPLead", &Tau1HCalMaxOverPLead);
fChain->SetBranchAddress("Tau2HCalMaxOverPLead", &Tau2HCalMaxOverPLead);
fChain->SetBranchAddress("Tau1HCal3x3OverPLead", &Tau1HCal3x3OverPLead);
fChain->SetBranchAddress("Tau2HCal3x3OverPLead", &Tau2HCal3x3OverPLead);
fChain->SetBranchAddress("Tau1DiscAgainstElectron", &Tau1DiscAgainstElectron);
fChain->SetBranchAddress("Tau2DiscAgainstElectron", &Tau2DiscAgainstElectron);
fChain->SetBranchAddress("Tau1DiscAgainstMuon", &Tau1DiscAgainstMuon);
fChain->SetBranchAddress("Tau2DiscAgainstMuon", &Tau2DiscAgainstMuon);
fChain->SetBranchAddress("Tau1IsInTheCracks", &Tau1IsInTheCracks);
fChain->SetBranchAddress("Tau2IsInTheCracks", &Tau2IsInTheCracks);
fChain->SetBranchAddress("Tau1DecayMode", &Tau1DecayMode);
fChain->SetBranchAddress("Tau2DecayMode", &Tau2DecayMode);
fChain->SetBranchAddress("MET", &MET);
fChain->SetBranchAddress("TauTauVisibleMass", &TauTauVisibleMass);
fChain->SetBranchAddress("TauTauVisPlusMetMass", &TauTauVisPlusMetMass);
fChain->SetBranchAddress("TauTauCollinearMetMass", &TauTauCollinearMetMass);
fChain->SetBranchAddress("TauTauCosDPhi", &TauTauCosDPhi);
fChain->SetBranchAddress("TauTauDeltaR", &TauTauDeltaR);
fChain->SetBranchAddress("TauTauPZeta", &TauTauPZeta);
fChain->SetBranchAddress("TauTauPZetaVis", &TauTauPZetaVis);
fChain->SetBranchAddress("Tau1MetCosDphi", &Tau1MetCosDphi);
fChain->SetBranchAddress("Tau2MetCosDphi", &Tau2MetCosDphi);
fChain->SetBranchAddress("nBtagsHiEffTrkCnt", &nBtagsHiEffTrkCnt);
fChain->SetBranchAddress("nBtagsHiPurityTrkCnt", &nBtagsHiPurityTrkCnt);
fChain->SetBranchAddress("nBTagsHiEffSimpleSecVtx", &nBTagsHiEffSimpleSecVtx);
fChain->SetBranchAddress("nBTagsHiPuritySimpleSecVtx", &nBTagsHiPuritySimpleSecVtx);
fChain->SetBranchAddress("nBTagsCombSecVtx", &nBTagsCombSecVtx);
fChain->SetBranchAddress("jetSumEt", &jetSumEt);
fChain->SetBranchAddress("jetMETSumEt", &jetMETSumEt);
fChain->SetBranchAddress("nJets", &nJets);
fChain->SetBranchAddress("nExtraJets", &nExtraJets);
fChain->SetBranchAddress("Tau1hpsPFTauDiscriminationAgainstLooseElectron", &Tau1hpsPFTauDiscriminationAgainstLooseElectron);
fChain->SetBranchAddress("Tau1hpsPFTauDiscriminationAgainstLooseMuon", &Tau1hpsPFTauDiscriminationAgainstLooseMuon);
fChain->SetBranchAddress("Tau1hpsPFTauDiscriminationAgainstMediumElectron", &Tau1hpsPFTauDiscriminationAgainstMediumElectron);
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
fChain->SetBranchAddress("Tau2hpsPFTauDiscriminationAgainstTightElectron", &Tau2hpsPFTauDiscriminationAgainstTightElectron);
fChain->SetBranchAddress("Tau2hpsPFTauDiscriminationAgainstTightMuon", &Tau2hpsPFTauDiscriminationAgainstTightMuon);
fChain->SetBranchAddress("Tau2hpsPFTauDiscriminationByDecayModeFinding", &Tau2hpsPFTauDiscriminationByDecayModeFinding);
fChain->SetBranchAddress("Tau2hpsPFTauDiscriminationByLooseIsolation", &Tau2hpsPFTauDiscriminationByLooseIsolation);
fChain->SetBranchAddress("Tau2hpsPFTauDiscriminationByMediumIsolation", &Tau2hpsPFTauDiscriminationByMediumIsolation);
fChain->SetBranchAddress("Tau2hpsPFTauDiscriminationByTightIsolation", &Tau2hpsPFTauDiscriminationByTightIsolation);
fChain->SetBranchAddress("Tau2hpsPFTauDiscriminationByVLooseIsolation", &Tau2hpsPFTauDiscriminationByVLooseIsolation);
