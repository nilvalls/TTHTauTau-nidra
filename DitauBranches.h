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
#include "TFile.h"



using namespace std;

class DitauBranches {
	private:
		map<string,string>		params;
		TChain* fChain;
		Int_t	fCurrent;
		void	NullPointers();
		void	DeletePointers();
		TChain*	GetTChain(string);
		void	SetBranchAddresses();
		Long64_t LoadTree(Long64_t entry);

	public:
		void	SetChain(TChain*);
		void	Init();
		void	GetEntry(double);
		Long64_t GetEntries();



	public:
		DitauBranches();
		DitauBranches(map<string,string> const &, string const);
		virtual ~DitauBranches();
	
		#include "clarity/ditauBranches_declarations.h"

		void				SetBestCombo(int);
		unsigned int const	GetBestCombo() const;
		int					bestCombo;

};

#endif










