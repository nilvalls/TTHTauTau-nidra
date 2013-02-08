																											cutFlow.RegisterCut("Read from DS", 0);
																											cutFlow.RegisterCut("skimming + PAT", 0);
																											cutFlow.RegisterCut("nTuple making", 0);
															if(atoi((params["maxEvents"]).c_str()) >= 0){ cutFlow.RegisterCut("User event limit", 0); }	
																											cutFlow.RegisterCut("TTE_AtLeastOneCombo", 0);
	 if(ApplyThisCut("RunNumber"				)){ CutOn_RunNumber					= 	true; cutFlow.RegisterCut("RunNumber", 1);					}
	 if(ApplyThisCut("LumiSection"				)){ CutOn_LumiSection				= 	true; cutFlow.RegisterCut("LumiSection", 1);				}
	 if(ApplyThisCut("EventNumber"				)){ CutOn_EventNumber				= 	true; cutFlow.RegisterCut("EventNumber", 1);				}
	 if(ApplyThisCut("GenMatching"				)){ CutOn_GenMatching				= 	true; cutFlow.RegisterCut("GenMatching", 1);				}
	 if(ApplyThisCut("NumHadronicGenTaus"		)){ CutOn_NumHadronicGenTaus		= 	true; cutFlow.RegisterCut("NumHadronicGenTaus", 1);			}
																//			if(selectedEvents.size() > 0){	  cutFlow.RegisterCut("Run:LS:Event", 1);		}
	 if(ApplyThisCut("InvariantMass"			)){ CutOn_InvariantMass				= 	true; cutFlow.RegisterCut("InvariantMass", 1);				}
	 if(ApplyThisCut("VisibleMass"				)){ CutOn_VisibleMass				= 	true; cutFlow.RegisterCut("VisibleMass", 1);				}

	 if(ApplyThisCut("G_NumGenHadTausFromH"		)){ CutOn_G_NumGenHadTausFromH		= 	true; cutFlow.RegisterCut("G_NumGenHadTausFromH", 1);		}

	 if(ApplyThisCut("J_NumCSVL"				)){ CutOn_J_NumCSVL					= 	true; cutFlow.RegisterCut("J_NumCSVL", 1);					}
	 if(ApplyThisCut("J_NumCSVM"				)){ CutOn_J_NumCSVM					= 	true; cutFlow.RegisterCut("J_NumCSVM", 1);					}
	 if(ApplyThisCut("J_NumCSVT"				)){ CutOn_J_NumCSVT					= 	true; cutFlow.RegisterCut("J_NumCSVT", 1);					}
	 if(ApplyThisCut("J_NumNonCSVL"				)){ CutOn_J_NumNonCSVL				= 	true; cutFlow.RegisterCut("J_NumNonCSVL", 1);				}
	 if(ApplyThisCut("J_NumNonCSVM"				)){ CutOn_J_NumNonCSVM				= 	true; cutFlow.RegisterCut("J_NumNonCSVM", 1);				}
	 if(ApplyThisCut("J_NumNonCSVT"				)){ CutOn_J_NumNonCSVT				= 	true; cutFlow.RegisterCut("J_NumNonCSVT", 1);				}
	 if(ApplyThisCut("J_NumInclusive"			)){ CutOn_J_NumInclusive			= 	true; cutFlow.RegisterCut("J_NumInclusive", 1);				}


	 if(ApplyThisCut("E_pT"						)){ CutOn_E_pT						= 	true; cutFlow.RegisterCut("E_pT", 1);						}
	 if(ApplyThisCut("E_Eta"					)){ CutOn_E_Eta						= 	true; cutFlow.RegisterCut("E_Eta", 1);						}
	 if(ApplyThisCut("E_IsLooseElectron"		)){ CutOn_E_IsLooseElectron			= 	true; cutFlow.RegisterCut("E_IsLooseElectron", 1);			}
	 if(ApplyThisCut("E_IsTightElectron"		)){ CutOn_E_IsTightElectron			= 	true; cutFlow.RegisterCut("E_IsTightElectron", 1);			}
	 if(ApplyThisCut("E_RelIso"					)){ CutOn_E_RelIso					= 	true; cutFlow.RegisterCut("E_RelIso", 1);					}
	 if(ApplyThisCut("NumOtherTightMuons"		)){ CutOn_NumOtherTightMuons		= 	true; cutFlow.RegisterCut("NumOtherTightMuons", 1);			}
	 if(ApplyThisCut("NumOtherLooseMuons"		)){ CutOn_NumOtherLooseMuons		= 	true; cutFlow.RegisterCut("NumOtherLooseMuons", 1);			}
	 if(ApplyThisCut("NumOtherTightElectrons"	)){ CutOn_NumOtherTightElectrons	= 	true; cutFlow.RegisterCut("NumOtherTightElectrons", 1);		}
	 if(ApplyThisCut("NumOtherLooseElectrons"	)){ CutOn_NumOtherLooseElectrons	= 	true; cutFlow.RegisterCut("NumOtherLooseElectrons", 1);		}

	 if(ApplyThisCut("T1_MatchAbsId"			)){ CutOn_T1_MatchAbsId				= 	true; cutFlow.RegisterCut("T1_MatchAbsId", 1);				}
	 if(ApplyThisCut("T2_MatchAbsId"			)){ CutOn_T2_MatchAbsId				= 	true; cutFlow.RegisterCut("T2_MatchAbsId", 1);				}
	 if(ApplyThisCut("T1_ParentAbsId"			)){ CutOn_T1_ParentAbsId			= 	true; cutFlow.RegisterCut("T1_ParentAbsId", 1);				}
	 if(ApplyThisCut("T2_ParentAbsId"			)){ CutOn_T2_ParentAbsId			= 	true; cutFlow.RegisterCut("T2_ParentAbsId", 1);				}

	 if(ApplyThisCut("T1_pT"					)){ CutOn_T1_pT						= 	true; cutFlow.RegisterCut("T1_pT", 1);						}
	 if(ApplyThisCut("T2_pT"					)){ CutOn_T2_pT						= 	true; cutFlow.RegisterCut("T2_pT", 1);						}
	 if(ApplyThisCut("T1_Eta"					)){ CutOn_T1_Eta					= 	true; cutFlow.RegisterCut("T1_Eta", 1);						}
	 if(ApplyThisCut("T2_Eta"					)){ CutOn_T2_Eta					= 	true; cutFlow.RegisterCut("T2_Eta", 1);						}
	 if(ApplyThisCut("T1_InCracks"				)){ CutOn_T1_InCracks				= 	true; cutFlow.RegisterCut("T1_InCracks", 1);				}
	 if(ApplyThisCut("T2_InCracks"				)){ CutOn_T2_InCracks				= 	true; cutFlow.RegisterCut("T2_InCracks", 1);				}
	 if(ApplyThisCut("TT_DeltaR"				)){ CutOn_TT_DeltaR					= 	true; cutFlow.RegisterCut("TT_DeltaR", 1);					}

	 if(ApplyThisCut("T1_DecayModeFinding"		)){ CutOn_T1_DecayModeFinding		= 	true; cutFlow.RegisterCut("T1_DecayModeFinding", 1);		}
	 if(ApplyThisCut("T2_DecayModeFinding"		)){ CutOn_T2_DecayModeFinding		= 	true; cutFlow.RegisterCut("T2_DecayModeFinding", 1);		}
	 if(ApplyThisCut("T1_LTvalid"				)){ CutOn_T1_LTvalid				= 	true; cutFlow.RegisterCut("T1_LTvalid", 1);					}
	 if(ApplyThisCut("T2_LTvalid"				)){ CutOn_T2_LTvalid				= 	true; cutFlow.RegisterCut("T2_LTvalid", 1);					}
	 if(ApplyThisCut("T1_LTpT"					)){ CutOn_T1_LTpT					= 	true; cutFlow.RegisterCut("T1_LTpT", 1);					}
	 if(ApplyThisCut("T2_LTpT"					)){ CutOn_T2_LTpT					= 	true; cutFlow.RegisterCut("T2_LTpT", 1);					}
	 if(ApplyThisCut("T1_NumProngs"				)){ CutOn_T1_NumProngs				= 	true; cutFlow.RegisterCut("T1_NumProngs", 1);				}
	 if(ApplyThisCut("T2_NumProngs"				)){ CutOn_T2_NumProngs				= 	true; cutFlow.RegisterCut("T2_NumProngs", 1);				}

	 if(ApplyThisCut("T1_AntiElectronMVA"		)){ CutOn_T1_AntiElectronMVA		= 	true; cutFlow.RegisterCut("T1_AntiElectronMVA", 1);		}
	 if(ApplyThisCut("T1_AntiElectronIndex"		)){ CutOn_T1_AntiElectronIndex		= 	true; cutFlow.RegisterCut("T1_AntiElectronIndex", 1);		}
	 if(ApplyThisCut("T2_AntiElectronMVA"		)){ CutOn_T2_AntiElectronMVA		= 	true; cutFlow.RegisterCut("T2_AntiElectronMVA", 1);		}
	 if(ApplyThisCut("T2_AntiElectronIndex"		)){ CutOn_T2_AntiElectronIndex		= 	true; cutFlow.RegisterCut("T2_AntiElectronIndex", 1);		}
	 if(ApplyThisCut("T1_AntiMuonIndex"			)){ CutOn_T1_AntiMuonIndex			= 	true; cutFlow.RegisterCut("T1_AntiMuonIndex", 1);			}
	 if(ApplyThisCut("T2_AntiMuonIndex"			)){ CutOn_T2_AntiMuonIndex			= 	true; cutFlow.RegisterCut("T2_AntiMuonIndex", 1);			}
	 if(ApplyThisCut("T1_IsolationIndex"		)){ CutOn_T1_IsolationIndex			= 	true; cutFlow.RegisterCut("T1_IsolationIndex", 1);			}
	 if(ApplyThisCut("T2_IsolationIndex"		)){ CutOn_T2_IsolationIndex			= 	true; cutFlow.RegisterCut("T2_IsolationIndex", 1);			}

	 if(ApplyThisCut("TT_ChargeProduct"			)){ CutOn_TT_ChargeProduct			= 	true; cutFlow.RegisterCut("TT_ChargeProduct", 1);			}
	 if(ApplyThisCut("TT_DeltaEta"				)){ CutOn_TT_DeltaEta				= 	true; cutFlow.RegisterCut("TT_DeltaEta", 1);				}
	 if(ApplyThisCut("TT_CosDeltaPhi"			)){ CutOn_TT_CosDeltaPhi			= 	true; cutFlow.RegisterCut("TT_CosDeltaPhi", 1);				}
	 if(ApplyThisCut("MET"						)){ CutOn_MET						= 	true; cutFlow.RegisterCut("MET", 1);						}

	 if(ApplyThisCut("G_NumTauHad"				)){ CutOn_G_NumTauHad				= 	true; cutFlow.RegisterCut("G_NumTauHad", 1);				}

	 if(ApplyThisCut("MVA"						)){ CutOn_MVA						= 	true; cutFlow.RegisterCut("MVA", 1);						}
	 //NEWCUT
