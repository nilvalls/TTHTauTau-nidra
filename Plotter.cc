/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			11 Jun 2011
    Description:	Plot stacking class.
    Notes:

*/

#include "Plotter.h"

#define Plotter_cxx
using namespace std;

#define AT __LINE__

// Default constructor
Plotter::Plotter(){}

// A more useful constructor
TopoPack* Plotter::GetTopologies(string iInputFile) {

	TFile* file = new TFile(iInputFile.c_str());
	TopoPack* topologies = new TopoPack();

	TTree* tree = (TTree*)file->Get("nidraTree");
	tree->SetBranchAddress("topologies", &topologies);
	tree->GetEntry(0);

	// Make sure topologies have been analyzed
	if(!topologies->Analyzed()){ cerr << "ERROR: topologies not analyzed" << endl; exit(1); }

	return topologies;

}

// Default destructor
Plotter::~Plotter(){}

// Function to make the plots
void Plotter::MakePlots(TopoPack* iTopologies){}

