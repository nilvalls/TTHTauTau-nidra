/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			11 Jun 2011
    Description:	Plot stacking class.
    Notes:

*/

#include "TMVASampler.h"

#define TTE_TMVASampler_cxx
using namespace std;

#define AT __LINE__

TTE_TMVASampler::TTE_TMVASampler(map<string,string>const & iParams) : TMVASampler(iParams){
	MakeTrainingSample(proPack);
}

// Default destructor
TTE_TMVASampler::~TTE_TMVASampler(){}


void TTE_TMVASampler::FillTree(TTree* iTree, Process const * iProcess){

	// Define variables going into the trees
	float Tau1Pt;
	float Tau2Pt;
	float Tau1Eta;
	float Tau2Eta;

	// Define branches
	iTree->Branch("Tau1Pt", &Tau1Pt);
	iTree->Branch("Tau2Pt", &Tau2Pt);
	iTree->Branch("Tau1AbsEta", &Tau1Eta);
	iTree->Branch("Tau2AbsEta", &Tau2Eta);

	// Instantiante Branches to read events more easily
	TTEBranches* event = new TTEBranches(params, iProcess->GetNtuplePath());

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
		Tau1Pt				= event->TTE_Tau1Pt->at(bestCombo);
		Tau2Pt				= event->TTE_Tau2Pt->at(bestCombo);
		Tau1Eta				= fabs(event->TTE_Tau1Eta->at(bestCombo));
		Tau2Eta				= fabs(event->TTE_Tau2Eta->at(bestCombo));

		// Fill tree
		iTree->Fill();
	}
	cout << endl;
}
