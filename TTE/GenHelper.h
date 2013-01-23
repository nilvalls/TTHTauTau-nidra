#ifndef GenHelper_h
#define GenHelper_h

#include "Branches.h"

using namespace std;

inline double DeltaR(double eta1, double phi1, double eta2, double phi2){
	return sqrt(pow(eta1-eta2, 2) + pow(phi1-phi2, 2));
}


inline unsigned int NumGenTauHad(TTEBranches* iEvent){
	unsigned int result = 0;

	for(unsigned int t=0; t<iEvent->GT_Eta->size(); t++){
		if(iEvent->GT_ToHadrons->at(t)){ result++; }
	}

	return result;
}

inline unsigned int GetNumberOfGenHadTausFromH(TTEBranches* iEvent){
	unsigned int result = 0;
	for(unsigned int g = 0; g < iEvent->GT_ParentId->size(); g++){
	//	cout << g << " " << iEvent->GT_ToHadrons->at(g) << " " << iEvent->GT_ParentId->at(g) << endl;
		if(iEvent->GT_ToHadrons->at(g) && iEvent->GT_ParentId->at(g) == 25){ result++; }
	}
	if( result != 2){ cout << "Num: " << result << endl;
		for(unsigned int g = 0; g < iEvent->GT_ParentId->size(); g++){
			cout << "is had: " << iEvent->GT_ToHadrons->at(g) << "is ele: " << iEvent->GT_ToElectron->at(g) <<
				 " is mu: " << iEvent->GT_ToMuon->at(g) << "\tparentId" <<  iEvent->GT_ParentId->at(g) << endl;
		}
	
	}
	return result;
}

inline unsigned int GetNumberOfGenHadTausFromHWithinDeltaR(TTEBranches* iEvent, float iDeltaR){
	unsigned int result = 0;
	for(unsigned int g = 0; g < iEvent->GT_ParentId->size(); g++){
		if(iEvent->GT_ToHadrons->at(g) && iEvent->GT_ParentId->at(g) == 25){
			cout << "checking" << endl;
			for(unsigned int r = 0; r < iEvent->TTE_NumCombos; r++){
				cout << "DeltaR1: " << DeltaR(iEvent->TTE_Tau1Eta->at(0), iEvent->TTE_Tau1Phi->at(0), iEvent->GT_Eta->at(g), iEvent->GT_Phi->at(g) ); 
				cout << "\tDeltaR2: " << DeltaR(iEvent->TTE_Tau2Eta->at(r), iEvent->TTE_Tau2Phi->at(r), iEvent->GT_Eta->at(g), iEvent->GT_Phi->at(g) ) << endl;
			if(r==0&&DeltaR(iEvent->TTE_Tau1Eta->at(0), iEvent->TTE_Tau1Phi->at(0), iEvent->GT_Eta->at(g), iEvent->GT_Phi->at(g) )<iDeltaR){ result++; break; }
				if(DeltaR(iEvent->TTE_Tau2Eta->at(r), iEvent->TTE_Tau2Phi->at(r), iEvent->GT_Eta->at(g), iEvent->GT_Phi->at(g) )<iDeltaR){ result++; break; }
			}
		}
	}


}


inline unsigned int Tau1Reality(TTEBranches* iEvent, unsigned int iCombo){

	for(unsigned int t=0; t<iEvent->GT_Eta->size(); t++){
		// Run matching first
		//if(DeltaR(iEvent->GT_VisEta->at(t), iEvent->GT_VisPhi->at(t), iEvent->TTE_Tau1Eta->at(iCombo), iEvent->TTE_Tau1Phi->at(iCombo)) < 0.25){
		if(DeltaR(iEvent->GT_Eta->at(t), iEvent->GT_Phi->at(t), iEvent->TTE_Tau1Eta->at(iCombo), iEvent->TTE_Tau1Phi->at(iCombo)) < 0.25){
			// Decay mode
			if(			iEvent->GT_ToHadrons->at(t)		){ return 1; }
			else if(	iEvent->GT_ToElectron->at(t)	){ return 2; }
			else if(	iEvent->GT_ToMuon->at(t)		){ return 3; }
			else{ cerr << "ERROR: GTau not going to hadrons, electron or muon" << endl; exit(1); }
		}
	}

	return 0;
}

inline unsigned int Tau2Reality(TTEBranches* iEvent, unsigned int iCombo){

	for(unsigned int t=0; t<iEvent->GT_Eta->size(); t++){
		// Run matching first
		//if(DeltaR(iEvent->GT_VisEta->at(t), iEvent->GT_VisPhi->at(t), iEvent->TTE_Tau2Eta->at(iCombo), iEvent->TTE_Tau2Phi->at(iCombo)) < 0.25){
		if(DeltaR(iEvent->GT_Eta->at(t), iEvent->GT_Phi->at(t), iEvent->TTE_Tau2Eta->at(iCombo), iEvent->TTE_Tau2Phi->at(iCombo)) < 0.25){
			// Decay mode
			if(			iEvent->GT_ToHadrons->at(t)		){ return 1; }
			else if(	iEvent->GT_ToElectron->at(t)	){ return 2; }
			else if(	iEvent->GT_ToMuon->at(t)		){ return 3; }
			else{ cerr << "ERROR: GTau not going to hadrons, electron or muon" << endl; exit(1); }
		}
	}
	return 0;
}


inline unsigned int DitauReality(TTEBranches* iEvent, unsigned int iCombo){
	unsigned int tau1Reality = Tau1Reality(iEvent, iCombo);
	unsigned int tau2Reality = Tau2Reality(iEvent, iCombo);

	// Produce enum
	if(	tau1Reality	== 0 && tau2Reality == 0	){ return 0; }
	if(	tau1Reality	== 0 && tau2Reality == 1	){ return 1; }
	if(	tau1Reality	== 0 && tau2Reality == 2	){ return 2; }
	if(	tau1Reality	== 0 && tau2Reality == 3	){ return 3; }
	if(	tau1Reality	== 1 && tau2Reality == 0	){ return 10; }
	if(	tau1Reality	== 1 && tau2Reality == 1	){ return 11; }
	if(	tau1Reality	== 1 && tau2Reality == 2	){ return 12; }
	if(	tau1Reality	== 1 && tau2Reality == 3	){ return 13; }
	if(	tau1Reality	== 2 && tau2Reality == 0	){ return 20; }
	if(	tau1Reality	== 2 && tau2Reality == 1	){ return 21; }
	if(	tau1Reality	== 2 && tau2Reality == 2	){ return 22; }
	if(	tau1Reality	== 2 && tau2Reality == 3	){ return 23; }
	if(	tau1Reality	== 3 && tau2Reality == 0	){ return 30; }
	if(	tau1Reality	== 3 && tau2Reality == 1	){ return 31; }
	if(	tau1Reality	== 3 && tau2Reality == 2	){ return 32; }
	if(	tau1Reality	== 3 && tau2Reality == 3	){ return 33; }

}


inline double MinGenTau1DeltaR(TTEBranches* iEvent, unsigned int iCombo){
	double result = 999;
	for(unsigned int t=0; t<iEvent->GT_Eta->size(); t++){
		// Run matching first
		double thisDeltaR = DeltaR(iEvent->GT_VisEta->at(t), iEvent->GT_VisPhi->at(t), iEvent->TTE_Tau1Eta->at(iCombo), iEvent->TTE_Tau1Phi->at(iCombo));
		if(thisDeltaR < result){ result = thisDeltaR; }
	}
	return result;
}

inline double MinGenTau2DeltaR(TTEBranches* iEvent, unsigned int iCombo){
	double result = 999;
	for(unsigned int t=0; t<iEvent->GT_Eta->size(); t++){
		// Run matching first
		double thisDeltaR = DeltaR(iEvent->GT_VisEta->at(t), iEvent->GT_VisPhi->at(t), iEvent->TTE_Tau2Eta->at(iCombo), iEvent->TTE_Tau2Phi->at(iCombo));
		if(thisDeltaR < result){ result = thisDeltaR; }
	}
	return result;
}


#endif
