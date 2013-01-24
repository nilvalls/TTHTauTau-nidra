/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			11 Jun 2011
    Description:	Plot stacking class.
    Notes:

*/

#include "Branches.h"

#define Branches_cxx
using namespace std;

#define AT __LINE__

// Default constructor
Branches::Branches(){
	fChain = NULL;
	Null();
}


void Branches::SetUp(map<string,string> const & iParams, string const iPath){

	params = iParams;
	//cout << "PATH: " << iPath << endl;
	fChain = GetTChain(iPath);
	Null();

	// Set branch addresses and branch pointers
	if (!fChain){ cerr << "ERROR: Trying to initialize NULL TChain" << endl; exit(1); }
	fCurrent = -1; 
	fChain->SetMakeClass(1);
	Init(); //*/

}


// Default destructor
Branches::~Branches(){

	if(fChain != NULL){ fChain->ResetBranchAddresses(); }
	if(fChain != NULL){ delete (fChain->GetCurrentFile()); }
	delete fChain; fChain = NULL;

//	Clear();
	Delete();
	Null();

}

void Branches::Null(){}
void Branches::Delete(){}
void Branches::Clear(){}
void Branches::SetBranchAddresses(){}

void Branches::SetBestCombo(int const iValue){ bestCombo = iValue; }
unsigned int const Branches::GetBestCombo() const { 
	if (bestCombo < 0){ cerr << "ERROR: 'bestCombo' is " << bestCombo << "." << endl; exit(1); }
	return bestCombo; 
}

void Branches::SetChain(TChain* iChain){ fChain = iChain; } 

void Branches::Init(){

	// Set branch addresses and branch pointers
	if (!fChain) return;
	fCurrent = -1; 
	fChain->SetMakeClass(1);
	fChain->ResetBranchAddresses();

	//Clear();
	Null();
	SetBranchAddresses();

}

void Branches::GetEntry(double iEntry){ fChain->GetEntry(iEntry); }

TChain* Branches::GetTChain(string iPath){

	// Chain to return
	TChain* result = new TChain((params["treeName"]).c_str());

	// Add all *.root files in iPath
	string pathToRootFiles = iPath + "/*.root";
	//cout << "PATH: " << pathToRootFiles << endl;
	result->Add(pathToRootFiles.c_str());

	// Return TChain
	return result;
}


Long64_t Branches::LoadTree(Long64_t entry){
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

Long64_t Branches::GetEntries(){
	if(fChain == NULL){ cerr << "ERROR: Trying to GetEntries() from a NULL TChain." << endl; exit(1); }
	return fChain->GetEntries();
}
