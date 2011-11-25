/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			11 Jun 2011
    Description:	Plot stacking class.
    Notes:

*/

#include "Stacker.h"

#define Stacker_cxx
using namespace std;

#define AT __LINE__

// Default constructor
Stacker::Stacker(map<string,string>* params){

	TopoPack* topologies = GetTopologies((*params)["topology_file"]);	

	MakePlots(topologies);

}

// Default destructor
Stacker::~Stacker(){}


// Function to make the plots
void Stacker::MakePlots(TopoPack* iTopologies){

	cout <<	(iTopologies->GetCollisions()->cutFlow).test << endl;
}

THStack* Stacker::MakeStack(vector<TH1*>* iBackgrounds){

}

