/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			11 Jun 2011
    Description:	Plot stacking class.
    Notes:

*/


#define DILBranches_cxx
#include "Branches.h"

using namespace std;

#define AT __LINE__

// Default constructor
DILBranches::DILBranches() : Branches(){}

DILBranches::DILBranches(map<string,string> const & iParams, string const iPath){ 
	cout << __LINE__ << " " << __FILE__ << " " << iPath << endl;
SetUp(iParams, iPath); }

// Default destructor
DILBranches::~DILBranches(){

	if(fChain != NULL){ fChain->ResetBranchAddresses(); }
	if(fChain != NULL){ delete (fChain->GetCurrentFile()); }
	delete fChain; fChain = NULL;

	Delete();
	Null();

}

void DILBranches::Null(){
	#include "Branches_null.h"
}

void DILBranches::Delete(){
	#include "Branches_delete.h"
}

void DILBranches::Clear(){
	#include "Branches_clear.h"
}

void DILBranches::SetBranchAddresses(){
	#include "Branches_setBranchAddress.h"
}

