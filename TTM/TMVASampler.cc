/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			11 Jun 2011
    Description:	Plot stacking class.
    Notes:

*/

#include "TMVASampler.h"

#define TTM_TMVASampler_cxx
using namespace std;

#define AT __LINE__

TTM_TMVASampler::TTM_TMVASampler(map<string,string>const & iParams) : TMVASampler(iParams){
	MakeTrainingSample(proPack);
}

// Default destructor
TTM_TMVASampler::~TTM_TMVASampler(){}


void TTM_TMVASampler::FillTree(TTree* iTree, Process const * iProcess){

	// Define variables going into the trees
	float Tau1Pt;
	float Tau2Pt;
    unsigned int Tau1DecayMode;
    unsigned int Tau2DecayMode;
    unsigned int Tau1IsolationIndex;
    unsigned int Tau2IsolationIndex;
    float Tau1LTPt;
    float Tau2LTPt;
    unsigned int Tau1NProngs;
    unsigned int Tau2NProngs;
    float DitauVisibleMass;

	// Define branches
	iTree->Branch("Tau1Pt", &Tau1Pt);
	iTree->Branch("Tau2Pt", &Tau2Pt);
    iTree->Branch("Tau1DecayMode", &Tau1DecayMode);
    iTree->Branch("Tau2DecayMode", &Tau2DecayMode);
    iTree->Branch("Tau1IsolationIndex", &Tau1IsolationIndex);
    iTree->Branch("Tau2IsolationIndex", &Tau2IsolationIndex);
    iTree->Branch("Tau1LTPt", &Tau1LTPt);
    iTree->Branch("Tau2LTPt", &Tau2LTPt);
    iTree->Branch("Tau1NProngs", &Tau1NProngs);
    iTree->Branch("Tau2NProngs", &Tau2NProngs);
    iTree->Branch("DitauVisibleMass", &DitauVisibleMass);

	// Instantiante Branches to read events more easily
	TTMBranches* event = new TTMBranches(params, iProcess->GetNtuplePath());

	// Loop over good events
	vector<pair<int,int> > goodEventsForSignal = iProcess->GetGoodEventsForSignal();
	cout << "\n\tNow filling tree for " << iProcess->GetShortName() << endl;
	cout << "\t>>> OS, filling good events (total " << goodEventsForSignal.size() << "): "; cout.flush();
	stringstream goodEventsSS; goodEventsSS.str("");
	for(unsigned int i = 0; i < goodEventsForSignal.size(); i++){
		if(i>0 && (i%10) == 0){
			cout << string((goodEventsSS.str()).length(),'\b') << string((goodEventsSS.str()).length(),' ') << string((goodEventsSS.str()).length(),'\b'); cout.flush();
			goodEventsSS.str("");
			goodEventsSS << i;
			cout << goodEventsSS.str(); cout.flush();
		}

		event->GetEntry(goodEventsForSignal.at(i).first);
		event->SetBestCombo(goodEventsForSignal.at(i).second);
		unsigned int bestCombo = event->bestCombo;

		// Assign values
		Tau1Pt = event->TTM_Tau1Pt->at(bestCombo);
		Tau2Pt = event->TTM_Tau2Pt->at(bestCombo);
        Tau1DecayMode = event->TTM_Tau1DecayMode->at(bestCombo);
        Tau2DecayMode = event->TTM_Tau2DecayMode->at(bestCombo);
        Tau1IsolationIndex = event->GetTau1IsolationIndex(bestCombo);
        Tau2IsolationIndex = event->GetTau2IsolationIndex(bestCombo);
        Tau1LTPt = event->TTM_Tau1LTPt->at(bestCombo);
        Tau2LTPt = event->TTM_Tau2LTPt->at(bestCombo);
        Tau1NProngs = event->TTM_Tau1NProngs->at(bestCombo);
        Tau2NProngs = event->TTM_Tau2NProngs->at(bestCombo);
        DitauVisibleMass = event->TTM_DitauVisibleMass->at(bestCombo);

		// Fill tree
		iTree->Fill();
	}
	cout << endl;
}
