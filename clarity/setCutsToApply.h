																											cutFlow.RegisterPreCut("Read from DS");
																											cutFlow.RegisterPreCut("skimming + PAT");
																											cutFlow.RegisterPreCut("nTuple making");
															if(atoi((params["maxEvents"]).c_str()) >= 0){ cutFlow.RegisterPreCut("User event limit"); }	
	 if(ApplyThisCut("RunNumber"				)){ CutOn_RunNumber					= 	true; cutFlow.RegisterCut("RunNumber");					}
	 if(ApplyThisCut("LumiSection"				)){ CutOn_LumiSection				= 	true; cutFlow.RegisterCut("LumiSection");				}
	 if(ApplyThisCut("EventNumber"				)){ CutOn_EventNumber				= 	true; cutFlow.RegisterCut("EventNumber");				}
	 if(ApplyThisCut("GenMatching"				)){ CutOn_GenMatching				= 	true; cutFlow.RegisterCut("GenMatching");				}
																//			if(selectedEvents.size() > 0){	  cutFlow.RegisterCut("Run:LS:Event");		}
	 if(ApplyThisCut("InvariantMass"			)){ CutOn_InvariantMass				= 	true; cutFlow.RegisterCut("InvariantMass");				}
	 if(ApplyThisCut("VisibleMass"				)){ CutOn_VisibleMass				= 	true; cutFlow.RegisterCut("VisibleMass");				}
	 if(ApplyThisCut("LL_pT"					)){ CutOn_LL_pT						= 	true; cutFlow.RegisterCut("LL_pT");						}
	 if(ApplyThisCut("SL_pT"					)){ CutOn_SL_pT						= 	true; cutFlow.RegisterCut("SL_pT");						}
	 if(ApplyThisCut("LL_Eta"					)){ CutOn_LL_Eta					= 	true; cutFlow.RegisterCut("LL_Eta");					}
	 if(ApplyThisCut("SL_Eta"					)){ CutOn_SL_Eta					= 	true; cutFlow.RegisterCut("SL_Eta");					}
	 if(ApplyThisCut("DeltaR"					)){ CutOn_DeltaR					= 	true; cutFlow.RegisterCut("DeltaR");					}
	 if(ApplyThisCut("LL_LTpT"					)){ CutOn_LL_LTpT					= 	true; cutFlow.RegisterCut("LL_LTpT");					}
	 if(ApplyThisCut("SL_LTpT"					)){ CutOn_SL_LTpT					= 	true; cutFlow.RegisterCut("SL_LTpT");					}
	 if(ApplyThisCut("LL_LTHits"				)){ CutOn_LL_LTHits					= 	true; cutFlow.RegisterCut("LL_LTHits");					}
	 if(ApplyThisCut("SL_LTHits"				)){ CutOn_SL_LTHits					= 	true; cutFlow.RegisterCut("SL_LTHits");					}
	 if(ApplyThisCut("LL_H3x3overP"				)){ CutOn_LL_H3x3overP				= 	true; cutFlow.RegisterCut("LL_H3x3overP");				}
	 if(ApplyThisCut("SL_H3x3overP"				)){ CutOn_SL_H3x3overP				= 	true; cutFlow.RegisterCut("SL_H3x3overP");				}
	 if(ApplyThisCut("LL_InCracks"				)){ CutOn_LL_InCracks				= 	true; cutFlow.RegisterCut("LL_InCracks");				}
	 if(ApplyThisCut("SL_InCracks"				)){ CutOn_SL_InCracks				= 	true; cutFlow.RegisterCut("SL_InCracks");				}
	 if(ApplyThisCut("LL_AgainstTightElectron"	)){ CutOn_LL_AgainstTightElectron	= 	true; cutFlow.RegisterCut("LL_AgainstTightElectron");	}
else if(ApplyThisCut("LL_AgainstMediumElectron"	)){ CutOn_LL_AgainstMediumElectron	= 	true; cutFlow.RegisterCut("LL_AgainstMediumElectron");	}
else if(ApplyThisCut("LL_AgainstLooseElectron" 	)){ CutOn_LL_AgainstLooseElectron	= 	true; cutFlow.RegisterCut("LL_AgainstLooseElectron");	}
	 if(ApplyThisCut("SL_AgainstTightElectron"	)){ CutOn_SL_AgainstTightElectron	= 	true; cutFlow.RegisterCut("SL_AgainstTightElectron");	}
else if(ApplyThisCut("SL_AgainstMediumElectron"	)){ CutOn_SL_AgainstMediumElectron	= 	true; cutFlow.RegisterCut("SL_AgainstMediumElectron");	}
else if(ApplyThisCut("SL_AgainstLooseElectron" 	)){ CutOn_SL_AgainstLooseElectron	= 	true; cutFlow.RegisterCut("SL_AgainstLooseElectron");	}
	 if(ApplyThisCut("LL_AgainstTightMuon" 		)){ CutOn_LL_AgainstTightMuon		= 	true; cutFlow.RegisterCut("LL_AgainstTightMuon");		}
else if(ApplyThisCut("LL_AgainstLooseMuon" 		)){ CutOn_LL_AgainstLooseMuon		= 	true; cutFlow.RegisterCut("LL_AgainstLooseMuon");		}
	 if(ApplyThisCut("SL_AgainstTightMuon" 		)){ CutOn_SL_AgainstTightMuon		= 	true; cutFlow.RegisterCut("SL_AgainstTightMuon");		}
else if(ApplyThisCut("SL_AgainstLooseMuon" 		)){ CutOn_SL_AgainstLooseMuon		= 	true; cutFlow.RegisterCut("SL_AgainstLooseMuon");		}
	 if(ApplyThisCut("LL_TightIso"				)){ CutOn_LL_TightIso				= 	true; cutFlow.RegisterCut("LL_TightIso");				}
else if(ApplyThisCut("LL_MediumIso"				)){ CutOn_LL_MediumIso				= 	true; cutFlow.RegisterCut("LL_MediumIso");				}
else if(ApplyThisCut("LL_LooseIso"				)){ CutOn_LL_LooseIso				= 	true; cutFlow.RegisterCut("LL_LooseIso");				}
else if(ApplyThisCut("LL_VLooseIso"				)){ CutOn_LL_VLooseIso				= 	true; cutFlow.RegisterCut("LL_VLooseIso");				}
	 if(ApplyThisCut("SL_TightIso"				)){ CutOn_SL_TightIso				= 	true; cutFlow.RegisterCut("SL_TightIso");				}
else if(ApplyThisCut("SL_MediumIso"				)){ CutOn_SL_MediumIso				= 	true; cutFlow.RegisterCut("SL_MediumIso");				}
else if(ApplyThisCut("SL_LooseIso"				)){ CutOn_SL_LooseIso				= 	true; cutFlow.RegisterCut("SL_LooseIso");				}
else if(ApplyThisCut("SL_VLooseIso"				)){ CutOn_SL_VLooseIso				= 	true; cutFlow.RegisterCut("SL_VLooseIso");				}
	 if(ApplyThisCut("LL_DecayModeFinding"		)){ CutOn_LL_DecayModeFinding		= 	true; cutFlow.RegisterCut("LL_DecayModeFinding");		}
	 if(ApplyThisCut("SL_DecayModeFinding"		)){ CutOn_SL_DecayModeFinding		= 	true; cutFlow.RegisterCut("SL_DecayModeFinding");		}
	 if(ApplyThisCut("LL_DecayMode"				)){ CutOn_LL_DecayMode				= 	true; cutFlow.RegisterCut("LL_DecayMode");				}
	 if(ApplyThisCut("SL_DecayMode"				)){ CutOn_SL_DecayMode				= 	true; cutFlow.RegisterCut("SL_DecayMode");				}
	 if(ApplyThisCut("LL_NumProngs"				)){ CutOn_LL_NumProngs				= 	true; cutFlow.RegisterCut("LL_NumProngs");				}
	 if(ApplyThisCut("SL_NumProngs"				)){ CutOn_SL_NumProngs				= 	true; cutFlow.RegisterCut("SL_NumProngs");				}
	 if(ApplyThisCut("ChargeProduct"			)){ CutOn_ChargeProduct				= 	true; cutFlow.RegisterCut("ChargeProduct");				}
	 if(ApplyThisCut("CosDeltaPhi"				)){ CutOn_CosDeltaPhi				= 	true; cutFlow.RegisterCut("CosDeltaPhi");				}
	 if(ApplyThisCut("MET"						)){ CutOn_MET						= 	true; cutFlow.RegisterCut("MET");						}
	 if(ApplyThisCut("Zeta"						)){ CutOn_Zeta						= 	true; cutFlow.RegisterCut("Zeta");						}
	 if(ApplyThisCut("Btags"					)){ CutOn_Btags						= 	true; cutFlow.RegisterCut("Btags");						}
	 //NEWCUT
