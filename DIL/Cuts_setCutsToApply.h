																											
																											cutFlow.RegisterCut("Read from DS", 0);
																											cutFlow.RegisterCut("skimming + PAT", 0);
																											cutFlow.RegisterCut("nTuple making", 0);
															if(atoi((params["maxEvents"]).c_str()) >= 0){ cutFlow.RegisterCut("User event limit", 0); }	
																											cutFlow.RegisterCut("DIL_AtLeastOneCombo", 0);

	if(ApplyThisCut("Trigger"	)){ CutOn_Trigger		= true; cutFlow.RegisterCut("Trigger", 1);	}
	if(ApplyThisCut("NumJets"	)){ CutOn_NumJets		= true; cutFlow.RegisterCut("NumJets", 1);	}
	if(ApplyThisCut("NumCSVM"	)){ CutOn_NumCSVM		= true; cutFlow.RegisterCut("NumCSVM", 1);	}
	if(ApplyThisCut("DIL"		)){ CutOn_DIL			= true; cutFlow.RegisterCut("DIL", 1);		}
																											
	 //NEWCUT
