//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun  7 03:28:02 2011 by ROOT version 5.27/06b
// from TTree HMTTree/TauTauTree
// found on file: ditau_nTuple.root
//////////////////////////////////////////////////////////

#ifndef DitauBranches_h
#define DitauBranches_h

#include <TROOT.h>
#include <math.h>
#include <map>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <utility>
#include <stdlib.h>
#include "TChain.h"



using namespace std;

class DitauBranches {
	private:
		TChain* fChain;
		Int_t           	fCurrent;

	public:
		void AlienSetChain(TChain*);
		void AlienInit();
		void AlienGetEntry(double);


	public:
		DitauBranches();
//		DitauBranches(DitauBranches const &);
		virtual ~DitauBranches();


		Double_t		runNumber;
		Double_t		eventNumber;
		Double_t		lumiBlock;
		Int_t			numInteractionsBXm1;
		Int_t			numInteractionsBX0;
		Int_t			numInteractionsBXp1;

		vector<bool>*	Tau1_ParentTauMatched;
		vector<bool>*	Tau2_ParentTauMatched;
		vector<bool>*	Tau1_MatchesGenHadronic;
		vector<bool>*	Tau2_MatchesGenHadronic;
		vector<bool>*	Tau1_ZtauMatched;
		vector<bool>*	Tau2_ZtauMatched;
		vector<bool>*	Tau1_ZeMatched;
		vector<bool>*	Tau2_ZeMatched;
		vector<float>	*Tau1GenPt;
		vector<float>	*Tau2GenPt;
		vector<float>	*Tau1GenE;
		vector<float>	*Tau2GenE;
		vector<float>	*Tau1GenEta;
		vector<float>	*Tau2GenEta;
		vector<float>	*Tau1GenPhi;
		vector<float>	*Tau2GenPhi;
		vector<bool>	*Tau1Matched;
		vector<bool>	*Tau2Matched;
		vector<int>		*Tau1MotherId;
		vector<int>		*Tau2MotherId;
		vector<int>		*Tau1PdgId;
		vector<int>		*Tau2PdgId;
		vector<int>		*Tau1MotherPdgId;
		vector<int>		*Tau2MotherPdgId;
		vector<int>		*NumPV;
		vector<float>	*Tau1E;
		vector<double>	*Tau2E;
		vector<float>	*Tau1Et;
		vector<float>	*Tau2Et;
		vector<float>	*Tau1Pt;
		vector<float>	*Tau2Pt;
		vector<float>	*Tau1LTPt;
		vector<float>	*Tau2LTPt;
		vector<int>		*Tau1Charge;
		vector<int>		*Tau2Charge;
		vector<float>	*Tau1Eta;
		vector<float>	*Tau2Eta;
		vector<float>	*Tau1Phi;
		vector<float>	*Tau2Phi;
		vector<float>	*Tau1LTIpVtdxy;
		vector<float>	*Tau1LTIpVtdz;
		vector<float>	*Tau1LTIpVtxError;
		vector<int>		*Tau1LTValidHits;
		vector<float>	*Tau1LTNormChiSqrd;
		vector<float>	*Tau2LTIpVtdxy;
		vector<float>	*Tau2LTIpVtdz;
		vector<float>	*Tau2LTIpVtxError;
		vector<int>		*Tau2LTValidHits;
		vector<float>	*Tau2LTNormChiSqrd;
		vector<int>		*Tau1NProngs;
		vector<int>		*Tau2NProngs;
		vector<float>	*Tau1EmFraction;
		vector<float>	*Tau2EmFraction;
		vector<float>	*Tau1HcalTotOverPLead;
		vector<float>	*Tau2HcalTotOverPLead;
		vector<float>	*Tau1HCalMaxOverPLead;
		vector<float>	*Tau2HCalMaxOverPLead;
		vector<float>	*Tau1HCal3x3OverPLead;
		vector<float>	*Tau2HCal3x3OverPLead;
		vector<bool>	*Tau1DiscAgainstElectron;
		vector<bool>	*Tau2DiscAgainstElectron;
		vector<bool>	*Tau1DiscAgainstMuon;
		vector<bool>	*Tau2DiscAgainstMuon;
		vector<int>		*Tau1IsInTheCracks;
		vector<int>		*Tau2IsInTheCracks;
		vector<float>	*Tau1DecayMode;
		vector<float>	*Tau2DecayMode;
		vector<float>	*MET;
		vector<float>	*TauTauVisibleMass;
		vector<float>	*TauTauVisPlusMetMass;
		vector<float>	*TauTauCollinearMetMass;
		vector<float>	*TauTauCosDPhi;
		vector<float>	*TauTauDeltaR;
		vector<float>	*TauTauPZeta;
		vector<float>	*TauTauPZetaVis;
		vector<float>	*Tau1MetCosDphi;
		vector<float>	*Tau2MetCosDphi;
		vector<double>	*Tau1MetMt;
		vector<double>	*Tau2MetMt;
		vector<float>	*nBtagsHiEffTrkCnt;
		vector<float>	*nBtagsHiPurityTrkCnt;
		vector<float>	*nBTagsHiEffSimpleSecVtx;
		vector<float>	*nBTagsHiPuritySimpleSecVtx;
		vector<float>	*nBTagsCombSecVtx;
		vector<float>	*jetSumEt;
		vector<float>	*jetMETSumEt;
		vector<int>		*nJets;
		vector<float>	*nExtraJets;
		vector<bool>	*Tau1hpsPFTauDiscriminationAgainstLooseElectron;
		vector<bool>	*Tau1hpsPFTauDiscriminationAgainstLooseMuon;
		vector<bool>	*Tau1hpsPFTauDiscriminationAgainstMediumElectron;
		vector<bool>	*Tau1hpsPFTauDiscriminationAgainstTightElectron;
		vector<bool>	*Tau1hpsPFTauDiscriminationAgainstTightMuon;
		vector<bool>	*Tau1hpsPFTauDiscriminationByDecayModeFinding;
		vector<bool>	*Tau1hpsPFTauDiscriminationByLooseIsolation;
		vector<bool>	*Tau1hpsPFTauDiscriminationByMediumIsolation;
		vector<bool>	*Tau1hpsPFTauDiscriminationByTightIsolation;
		vector<bool>	*Tau1hpsPFTauDiscriminationByVLooseIsolation;
		vector<bool>	*Tau2hpsPFTauDiscriminationAgainstLooseElectron;
		vector<bool>	*Tau2hpsPFTauDiscriminationAgainstLooseMuon;
		vector<bool>	*Tau2hpsPFTauDiscriminationAgainstMediumElectron;
		vector<bool>	*Tau2hpsPFTauDiscriminationAgainstTightElectron;
		vector<bool>	*Tau2hpsPFTauDiscriminationAgainstTightMuon;
		vector<bool>	*Tau2hpsPFTauDiscriminationByDecayModeFinding;
		vector<bool>	*Tau2hpsPFTauDiscriminationByLooseIsolation;
		vector<bool>	*Tau2hpsPFTauDiscriminationByMediumIsolation;
		vector<bool>	*Tau2hpsPFTauDiscriminationByTightIsolation;
		vector<bool>	*Tau2hpsPFTauDiscriminationByVLooseIsolation;
//*/


		void		SetPUweight(double);
		void		SetTriggerWeights(double, double);
		void		SetBestCombo(int);

		double		puWeight;
		double		tau1TriggerWeight;
		double		tau2TriggerWeight;
		int			bestCombo;

};

#endif










