
float weightFull	= iPuWeight;


// General =========================================================================================================================
hContainer->Fill("Events", 0, weightFull);
hContainer->Fill("MET", event->Ev_MET, weightFull);

if(iPuWeight!=0){
	hContainer->Fill("NumberPV_noPURW", event->Ev_numPrimaryVertices, weightFull/iPuWeight);
	hContainer->Fill("NumberBXm1_noPURW", event->Ev_numInteractionsBXm1, weightFull/iPuWeight);
	hContainer->Fill("NumberBX0_noPURW", event->Ev_numInteractionsBX0, weightFull/iPuWeight);
	hContainer->Fill("NumberBXp1_noPURW", event->Ev_numInteractionsBXp1, weightFull/iPuWeight);
}

if(IsFlagThere("PUcorr")){
	hContainer->Fill("NumberPV_afterPURW", event->Ev_numPrimaryVertices, weightFull);
	hContainer->Fill("NumberBXm1_afterPURW", event->Ev_numInteractionsBXm1, weightFull);
	hContainer->Fill("NumberBX0_afterPURW", event->Ev_numInteractionsBX0, weightFull);
	hContainer->Fill("NumberBXp1_afterPURW", event->Ev_numInteractionsBXp1, weightFull);
}


// Taus ============================================================================================================================
//hContainer->Fill("NumTaus", event->DIL_NumTaus, weightFull);

