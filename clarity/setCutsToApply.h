																											cutFlow.RegisterCut("Read from DS", 0);
																											cutFlow.RegisterCut("skimming + PAT", 0);
																											cutFlow.RegisterCut("nTuple making", 0);
															if(atoi((params["maxEvents"]).c_str()) >= 0){ cutFlow.RegisterCut("User event limit", 0); }	
	 if(ApplyThisCut("RunNumber"				)){ CutOn_RunNumber					= 	true; cutFlow.RegisterCut("RunNumber", 1);					}
	 if(ApplyThisCut("LumiSection"				)){ CutOn_LumiSection				= 	true; cutFlow.RegisterCut("LumiSection", 1);				}
	 if(ApplyThisCut("EventNumber"				)){ CutOn_EventNumber				= 	true; cutFlow.RegisterCut("EventNumber", 1);				}
	 if(ApplyThisCut("GenMatching"				)){ CutOn_GenMatching				= 	true; cutFlow.RegisterCut("GenMatching", 1);				}
																//			if(selectedEvents.size() > 0){	  cutFlow.RegisterCut("Run:LS:Event", 1);		}
	 if(ApplyThisCut("InvariantMass"			)){ CutOn_InvariantMass				= 	true; cutFlow.RegisterCut("InvariantMass", 1);				}
	 if(ApplyThisCut("VisibleMass"				)){ CutOn_VisibleMass				= 	true; cutFlow.RegisterCut("VisibleMass", 1);				}
	 if(ApplyThisCut("LL_pT"					)){ CutOn_LL_pT						= 	true; cutFlow.RegisterCut("LL_pT", 1);						}
	 if(ApplyThisCut("SL_pT"					)){ CutOn_SL_pT						= 	true; cutFlow.RegisterCut("SL_pT", 1);						}
	 if(ApplyThisCut("LL_Eta"					)){ CutOn_LL_Eta					= 	true; cutFlow.RegisterCut("LL_Eta", 1);						}
	 if(ApplyThisCut("SL_Eta"					)){ CutOn_SL_Eta					= 	true; cutFlow.RegisterCut("SL_Eta", 1);						}
	 if(ApplyThisCut("DeltaR"					)){ CutOn_DeltaR					= 	true; cutFlow.RegisterCut("DeltaR", 1);						}
	 if(ApplyThisCut("DDMI"						)){ CutOn_DDMI                      =   true; cutFlow.RegisterCut("DDMI", 1);              		    }
	 if(ApplyThisCut("DTMI"						)){ CutOn_DTMI                      =   true; cutFlow.RegisterCut("DTMI", 1);  			            }
	 if(ApplyThisCut("LL_LTpT"					)){ CutOn_LL_LTpT					= 	true; cutFlow.RegisterCut("LL_LTpT", 1);					}
	 if(ApplyThisCut("SL_LTpT"					)){ CutOn_SL_LTpT					= 	true; cutFlow.RegisterCut("SL_LTpT", 1);					}
	 if(ApplyThisCut("LL_LTHits"				)){ CutOn_LL_LTHits					= 	true; cutFlow.RegisterCut("LL_LTHits", 1);					}
	 if(ApplyThisCut("SL_LTHits"				)){ CutOn_SL_LTHits					= 	true; cutFlow.RegisterCut("SL_LTHits", 1);					}
	 if(ApplyThisCut("LL_H3x3overP"				)){ CutOn_LL_H3x3overP				= 	true; cutFlow.RegisterCut("LL_H3x3overP", 1);				}
	 if(ApplyThisCut("SL_H3x3overP"				)){ CutOn_SL_H3x3overP				= 	true; cutFlow.RegisterCut("SL_H3x3overP", 1);				}
	 if(ApplyThisCut("LL_InCracks"				)){ CutOn_LL_InCracks				= 	true; cutFlow.RegisterCut("LL_InCracks", 1);				}
	 if(ApplyThisCut("SL_InCracks"				)){ CutOn_SL_InCracks				= 	true; cutFlow.RegisterCut("SL_InCracks", 1);				}
	 if(ApplyThisCut("LL_AgainstTightElectron"	)){ CutOn_LL_AgainstTightElectron	= 	true; cutFlow.RegisterCut("LL_AgainstTightElectron", 1);	}
else if(ApplyThisCut("LL_AgainstMediumElectron"	)){ CutOn_LL_AgainstMediumElectron	= 	true; cutFlow.RegisterCut("LL_AgainstMediumElectron", 1);	}
else if(ApplyThisCut("LL_AgainstLooseElectron" 	)){ CutOn_LL_AgainstLooseElectron	= 	true; cutFlow.RegisterCut("LL_AgainstLooseElectron", 1);	}
	 if(ApplyThisCut("SL_AgainstTightElectron"	)){ CutOn_SL_AgainstTightElectron	= 	true; cutFlow.RegisterCut("SL_AgainstTightElectron", 1);	}
else if(ApplyThisCut("SL_AgainstMediumElectron"	)){ CutOn_SL_AgainstMediumElectron	= 	true; cutFlow.RegisterCut("SL_AgainstMediumElectron", 1);	}
else if(ApplyThisCut("SL_AgainstLooseElectron" 	)){ CutOn_SL_AgainstLooseElectron	= 	true; cutFlow.RegisterCut("SL_AgainstLooseElectron", 1);	}
	 if(ApplyThisCut("LL_AgainstTightMuon" 		)){ CutOn_LL_AgainstTightMuon		= 	true; cutFlow.RegisterCut("LL_AgainstTightMuon", 1);		}
else if(ApplyThisCut("LL_AgainstLooseMuon" 		)){ CutOn_LL_AgainstLooseMuon		= 	true; cutFlow.RegisterCut("LL_AgainstLooseMuon", 1);		}
	 if(ApplyThisCut("SL_AgainstTightMuon" 		)){ CutOn_SL_AgainstTightMuon		= 	true; cutFlow.RegisterCut("SL_AgainstTightMuon", 1);		}
else if(ApplyThisCut("SL_AgainstLooseMuon" 		)){ CutOn_SL_AgainstLooseMuon		= 	true; cutFlow.RegisterCut("SL_AgainstLooseMuon", 1);		}
	 if(ApplyThisCut("LL_TightIso"				)){ CutOn_LL_TightIso				= 	true; cutFlow.RegisterCut("LL_TightIso", 1);				}
else if(ApplyThisCut("LL_MediumIso"				)){ CutOn_LL_MediumIso				= 	true; cutFlow.RegisterCut("LL_MediumIso", 1);				}
else if(ApplyThisCut("LL_LooseIso"				)){ CutOn_LL_LooseIso				= 	true; cutFlow.RegisterCut("LL_LooseIso", 1);				}
else if(ApplyThisCut("LL_VLooseIso"				)){ CutOn_LL_VLooseIso				= 	true; cutFlow.RegisterCut("LL_VLooseIso", 1);				}
	 if(ApplyThisCut("SL_TightIso"				)){ CutOn_SL_TightIso				= 	true; cutFlow.RegisterCut("SL_TightIso", 1);				}
else if(ApplyThisCut("SL_MediumIso"				)){ CutOn_SL_MediumIso				= 	true; cutFlow.RegisterCut("SL_MediumIso", 1);				}
else if(ApplyThisCut("SL_LooseIso"				)){ CutOn_SL_LooseIso				= 	true; cutFlow.RegisterCut("SL_LooseIso", 1);				}
else if(ApplyThisCut("SL_VLooseIso"				)){ CutOn_SL_VLooseIso				= 	true; cutFlow.RegisterCut("SL_VLooseIso", 1);				}
	 if(ApplyThisCut("LL_DecayModeFinding"		)){ CutOn_LL_DecayModeFinding		= 	true; cutFlow.RegisterCut("LL_DecayModeFinding", 1);		}
	 if(ApplyThisCut("SL_DecayModeFinding"		)){ CutOn_SL_DecayModeFinding		= 	true; cutFlow.RegisterCut("SL_DecayModeFinding", 1);		}
	 if(ApplyThisCut("LL_DecayMode"				)){ CutOn_LL_DecayMode				= 	true; cutFlow.RegisterCut("LL_DecayMode", 1);				}
	 if(ApplyThisCut("SL_DecayMode"				)){ CutOn_SL_DecayMode				= 	true; cutFlow.RegisterCut("SL_DecayMode", 1);				}
	 if(ApplyThisCut("LL_NumProngs"				)){ CutOn_LL_NumProngs				= 	true; cutFlow.RegisterCut("LL_NumProngs", 1);				}
	 if(ApplyThisCut("SL_NumProngs"				)){ CutOn_SL_NumProngs				= 	true; cutFlow.RegisterCut("SL_NumProngs", 1);				}
	 if(ApplyThisCut("ChargeProduct"			)){ CutOn_ChargeProduct				= 	true; cutFlow.RegisterCut("ChargeProduct", 1);				}
	 if(ApplyThisCut("DeltaEta"					)){ CutOn_DeltaEta					= 	true; cutFlow.RegisterCut("DeltaEta", 1);					}
	 if(ApplyThisCut("CosDeltaPhi"				)){ CutOn_CosDeltaPhi				= 	true; cutFlow.RegisterCut("CosDeltaPhi", 1);				}
	 if(ApplyThisCut("MET"						)){ CutOn_MET						= 	true; cutFlow.RegisterCut("MET", 1);						}
	 if(ApplyThisCut("Zeta"						)){ CutOn_Zeta						= 	true; cutFlow.RegisterCut("Zeta", 1);						}
	 if(ApplyThisCut("Btags"					)){ CutOn_Btags						= 	true; cutFlow.RegisterCut("Btags", 1);						}
	 //NEWCUT
