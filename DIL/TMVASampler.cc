/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			11 Jun 2011
    Description:	Plot stacking class.
    Notes:

*/

#include "TMVASampler.h"

#define DIL_TMVASampler_cxx
using namespace std;

#define AT __LINE__

DIL_TMVASampler::DIL_TMVASampler(map<string,string>const & iParams) : TMVASampler(iParams){
	MakeTrainingSample(proPack);
}

// Default destructor
DIL_TMVASampler::~DIL_TMVASampler(){}


void DIL_TMVASampler::FillTree(TTree* iTree, Process const * iProcess){

	// Define variables going into the trees
	float var1;

	// Define branches
	iTree->Branch("var1", &var1);

	// Instantiante Branches to read events more easily
	DILBranches* event = new DILBranches(params, iProcess->GetNtuplePath());

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
		var1	= event->Ev_eventNumber;

		// Fill tree
		iTree->Fill();
	}
	cout << endl;
}
