#ifndef GenHelper_h
#define GenHelper_h

#include "../Helper.h"
#include "Branches.h"

inline unsigned int NumGenTauHad(TLLBranches* iEvent){
	unsigned int result = 0;

	for(unsigned int t=0; t<iEvent->GT_Eta->size(); t++){
		if(iEvent->GT_ToHadrons->at(t)){ result++; }
	}

	return result;
}

inline unsigned int GetNumberOfGenHadTausFromH(TLLBranches* iEvent){
	unsigned int result = 0;
	for(unsigned int g = 0; g < iEvent->GT_ParentId->size(); g++){
	//	std::cout << g << " " << iEvent->GT_ToHadrons->at(g) << " " << iEvent->GT_ParentId->at(g) << std::endl;
		if(iEvent->GT_ToHadrons->at(g) && iEvent->GT_ParentId->at(g) == 25){ result++; }
	}
	if( result != 2){ std::cout << "Num: " << result << std::endl;
		for(unsigned int g = 0; g < iEvent->GT_ParentId->size(); g++){
			std::cout << "is had: " << iEvent->GT_ToHadrons->at(g) << "is ele: " << iEvent->GT_ToElectron->at(g) <<
				 " is mu: " << iEvent->GT_ToMuon->at(g) << "\tparentId" <<  iEvent->GT_ParentId->at(g) << std::endl;
		}
	
	}
	return result;
}


inline unsigned int TauReality(TLLBranches* iEvent, unsigned int iCombo){

	for(unsigned int t=0; t<iEvent->GT_Eta->size(); t++){
		// Run matching first
		//if(DeltaR(iEvent->GT_VisEta->at(t), iEvent->GT_VisPhi->at(t), iEvent->TLL_Tau1Eta->at(iCombo), iEvent->TLL_Tau1Phi->at(iCombo)) < 0.25){
		if(DeltaR(iEvent->GT_Eta->at(t), iEvent->GT_Phi->at(t), iEvent->TLL_TauEta->at(iCombo), iEvent->TLL_TauPhi->at(iCombo)) < 0.25){
			// Decay mode
			if(			iEvent->GT_ToHadrons->at(t)		){ return 1; }
			else if(	iEvent->GT_ToElectron->at(t)	){ return 2; }
			else if(	iEvent->GT_ToMuon->at(t)		){ return 3; }
			else{ std::cerr << "ERROR: GTau not going to hadrons, electron or muon" << std::endl; exit(1); }
		}
	}

	return 0;
}


inline double MinGenTauDeltaR(TLLBranches* iEvent, unsigned int iCombo){
	double result = 999;
	for(unsigned int t=0; t<iEvent->GT_Eta->size(); t++){
		// Run matching first
		double thisDeltaR = DeltaR(iEvent->GT_VisEta->at(t), iEvent->GT_VisPhi->at(t), iEvent->TLL_TauEta->at(iCombo), iEvent->TLL_TauPhi->at(iCombo));
		if(thisDeltaR < result){ result = thisDeltaR; }
	}
	return result;
}

inline int GetTauParentPDGid(TLLBranches* iEvent, unsigned int iCombo){
std::cout << "test" << std::endl;

	double minDeltaR	= 999;
	int tempParentPDGid	= 0;

	double recoEta = iEvent->TLL_TauEta->at(iCombo);
	double recoPhi = iEvent->TLL_TauPhi->at(iCombo);
	for(int g = 0; g < iEvent->GT_NumGenTaus; g++){
		double genEta = iEvent->GT_Eta->at(g);
		double genPhi = iEvent->GT_Phi->at(g);
		double currentDeltaR = DeltaR(recoEta, recoPhi, genEta, genPhi);
		std::cout << "currentDeltaR: " << currentDeltaR << std::endl;
		if(currentDeltaR < minDeltaR){
			minDeltaR = currentDeltaR;
			tempParentPDGid = iEvent->GT_ParentId->at(g);
		}
	}
	std::cout << tempParentPDGid << std::endl;

	if(minDeltaR < 0.25){ return tempParentPDGid; }
	return 0;
}


#endif
