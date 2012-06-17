/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			11 Jun 2011
    Description:	Plot stacking class.
    Notes:

*/

#include "DitauBranches.h"

#define DitauBranches_cxx
using namespace std;

#define AT __LINE__

// Default constructor
DitauBranches::DitauBranches(){
	fChain = NULL;
	Null();
}


DitauBranches::DitauBranches(map<string,string> const & iParams, string const iPath){

	params = iParams;

	fChain = GetTChain(iPath);
	Null();

	// Set branch addresses and branch pointers
	if (!fChain){ cerr << "ERROR: Trying to initialize NULL TChain" << endl; exit(1); }
	fCurrent = -1; 
	fChain->SetMakeClass(1);
	Init();
}

// Default destructor
DitauBranches::~DitauBranches(){

	if(fChain != NULL){ fChain->ResetBranchAddresses(); }
	if(fChain != NULL){ delete (fChain->GetCurrentFile()); }
	delete fChain; fChain = NULL;

//	Clear();
	Delete();
	Null();

}

void DitauBranches::Null(){
	#include "clarity/ditauBranches_null.h"
}

void DitauBranches::Delete(){
	#include "clarity/ditauBranches_delete.h"
}

void DitauBranches::Clear(){
	#include "clarity/ditauBranches_clear.h"
}

void DitauBranches::SetBranchAddresses(){
	#include "clarity/ditauBranches_setBranchAddresses.h"
}


void DitauBranches::SetBestCombo(int const iValue){ bestCombo = iValue; }
unsigned int const DitauBranches::GetBestCombo() const { 

	if (bestCombo < 0){ cerr << "ERROR: 'bestCombo' is " << bestCombo << "." << endl; exit(1); }

	return bestCombo; 
}

void DitauBranches::SetChain(TChain* iChain){ fChain = iChain; } 

void DitauBranches::Init(){

	// Set branch addresses and branch pointers
	if (!fChain) return;
	fCurrent = -1; 
	fChain->SetMakeClass(1);
	fChain->ResetBranchAddresses();

	//Clear();
	Null();
	SetBranchAddresses();

}

void DitauBranches::GetEntry(double iEntry){ fChain->GetEntry(iEntry); }

TChain* DitauBranches::GetTChain(string iPath){

	// Chain to return
	TChain* result = new TChain((params["treeName"]).c_str());

	// Add all *.root files in iPath
	string pathToRootFiles = iPath + "/*.root";
	result->Add(pathToRootFiles.c_str());

	// Return TChain
	return result;
}


Long64_t DitauBranches::LoadTree(Long64_t entry){
	// Set the environment to read one entry
	if (!fChain) return -5;
	Long64_t centry = fChain->LoadTree(entry);
	if (centry < 0) return centry;
	if (!fChain->InheritsFrom(TChain::Class()))  return centry;
	TChain *chain = (TChain*)fChain;
	if (chain->GetTreeNumber() != fCurrent) {
		fCurrent = chain->GetTreeNumber();
	}
	return centry;
}

Long64_t DitauBranches::GetEntries(){
	if(fChain == NULL){ cerr << "ERROR: Trying to GetEntries() from a NULL TChain." << endl; exit(1); }
	return fChain->GetEntries();
}
