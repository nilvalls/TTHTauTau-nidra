/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			11 Jun 2011
    Description:	Plot stacking class.
    Notes:

*/

#include "Cruncher.h"

#define Cruncher_cxx
using namespace std;

#define AT __LINE__

// Default constructor
Cruncher::Cruncher(map<string,string>* iParams){

	params = iParams;

	TopoPack* topologies = GetTopologies((*params)["topology_file"]);	

	collisions		= topologies->GetCollisions()->GetCutFlow();
	mcBackgrounds	= topologies->GetMCbackgroundsCutFlows();
	signals			= topologies->GetSignalsCutFlows();

}

// Default destructor
Cruncher::~Cruncher(){}


// Function to make the plots
void Cruncher::PrintCutEfficiencies(){

	cout << "\n=== Collisions ===" << endl;
	collisions->PrintTest();

	cout << "\n=== Front ===" << endl;
	mcBackgrounds->front()->PrintTest();


}


