																											cutFlow.RegisterCut("Read from DS", 0);
																											cutFlow.RegisterCut("skimming + PAT", 0);
																											cutFlow.RegisterCut("nTuple making", 0);
															if(atoi((params["maxEvents"]).c_str()) >= 0){ cutFlow.RegisterCut("User event limit", 0); }	
	 if(ApplyThisCut("RunNumber"				)){ CutOn_RunNumber					= 	true; cutFlow.RegisterCut("RunNumber", 1);					}
	 if(ApplyThisCut("LumiSection"				)){ CutOn_LumiSection				= 	true; cutFlow.RegisterCut("LumiSection", 1);				}
	 if(ApplyThisCut("EventNumber"				)){ CutOn_EventNumber				= 	true; cutFlow.RegisterCut("EventNumber", 1);				}
	 if(ApplyThisCut("GenMatching"				)){ CutOn_GenMatching				= 	true; cutFlow.RegisterCut("GenMatching", 1);				}
	 if(ApplyThisCut("NumHadronicGenTaus"		)){ CutOn_NumHadronicGenTaus		= 	true; cutFlow.RegisterCut("NumHadronicGenTaus", 1);			}
																//			if(selectedEvents.size() > 0){	  cutFlow.RegisterCut("Run:LS:Event", 1);		}
	 if(ApplyThisCut("InvariantMass"			)){ CutOn_InvariantMass				= 	true; cutFlow.RegisterCut("InvariantMass", 1);				}
	 if(ApplyThisCut("VisibleMass"				)){ CutOn_VisibleMass				= 	true; cutFlow.RegisterCut("VisibleMass", 1);				}

	 if(ApplyThisCut("T1_pT"					)){ CutOn_T1_pT						= 	true; cutFlow.RegisterCut("T1_pT", 1);						}
	 if(ApplyThisCut("T2_pT"					)){ CutOn_T2_pT						= 	true; cutFlow.RegisterCut("T2_pT", 1);						}
	 if(ApplyThisCut("T1_Eta"					)){ CutOn_T1_Eta					= 	true; cutFlow.RegisterCut("T1_Eta", 1);						}
	 if(ApplyThisCut("T2_Eta"					)){ CutOn_T2_Eta					= 	true; cutFlow.RegisterCut("T2_Eta", 1);						}
	 if(ApplyThisCut("TT_DeltaR"				)){ CutOn_TT_DeltaR					= 	true; cutFlow.RegisterCut("TT_DeltaR", 1);					}
	 if(ApplyThisCut("T1_LTvalid"				)){ CutOn_T1_LTvalid				= 	true; cutFlow.RegisterCut("T1_LTvalid", 1);					}
	 if(ApplyThisCut("T2_LTvalid"				)){ CutOn_T2_LTvalid				= 	true; cutFlow.RegisterCut("T2_LTvalid", 1);					}
	 if(ApplyThisCut("T1_LTpT"					)){ CutOn_T1_LTpT					= 	true; cutFlow.RegisterCut("T1_LTpT", 1);					}
	 if(ApplyThisCut("T2_LTpT"					)){ CutOn_T2_LTpT					= 	true; cutFlow.RegisterCut("T2_LTpT", 1);					}
	 if(ApplyThisCut("T1_InCracks"				)){ CutOn_T1_InCracks				= 	true; cutFlow.RegisterCut("T1_InCracks", 1);				}
	 if(ApplyThisCut("T2_InCracks"				)){ CutOn_T2_InCracks				= 	true; cutFlow.RegisterCut("T2_InCracks", 1);				}
	 if(ApplyThisCut("T1_AntiElectronIndex"		)){ CutOn_T1_AntiElectronIndex		= 	true; cutFlow.RegisterCut("T1_AntiElectronIndex", 1);		}
	 if(ApplyThisCut("T2_AntiElectronIndex"		)){ CutOn_T2_AntiElectronIndex		= 	true; cutFlow.RegisterCut("T2_AntiElectronIndex", 1);		}
	 if(ApplyThisCut("T1_AntiMuonIndex"			)){ CutOn_T1_AntiMuonIndex			= 	true; cutFlow.RegisterCut("T1_AntiMuonIndex", 1);			}
	 if(ApplyThisCut("T2_AntiMuonIndex"			)){ CutOn_T2_AntiMuonIndex			= 	true; cutFlow.RegisterCut("T2_AntiMuonIndex", 1);			}
	 if(ApplyThisCut("T1_IsolationIndex"		)){ CutOn_T1_IsolationIndex			= 	true; cutFlow.RegisterCut("T1_IsolationIndex", 1);			}
	 if(ApplyThisCut("T2_IsolationIndex"		)){ CutOn_T2_IsolationIndex			= 	true; cutFlow.RegisterCut("T2_IsolationIndex", 1);			}
	 if(ApplyThisCut("T1_NumProngs"				)){ CutOn_T1_NumProngs				= 	true; cutFlow.RegisterCut("T1_NumProngs", 1);				}
	 if(ApplyThisCut("T2_NumProngs"				)){ CutOn_T2_NumProngs				= 	true; cutFlow.RegisterCut("T2_NumProngs", 1);				}

	 if(ApplyThisCut("TT_ChargeProduct"			)){ CutOn_TT_ChargeProduct			= 	true; cutFlow.RegisterCut("TT_ChargeProduct", 1);			}
	 if(ApplyThisCut("TT_DeltaEta"				)){ CutOn_TT_DeltaEta				= 	true; cutFlow.RegisterCut("TT_DeltaEta", 1);				}
	 if(ApplyThisCut("TT_CosDeltaPhi"			)){ CutOn_TT_CosDeltaPhi			= 	true; cutFlow.RegisterCut("TT_CosDeltaPhi", 1);				}
	 if(ApplyThisCut("MET"						)){ CutOn_MET						= 	true; cutFlow.RegisterCut("MET", 1);						}
	 if(ApplyThisCut("Btags"					)){ CutOn_Btags						= 	true; cutFlow.RegisterCut("Btags", 1);						}
	 //NEWCUT
