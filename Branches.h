//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun  7 03:28:02 2011 by ROOT version 5.27/06b
// from TTree HMTTree/TauTauTree
// found on file: ditau_nTuple.root
//////////////////////////////////////////////////////////

#ifndef Branches_h
#define Branches_h

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

class Branches {

	public:

	protected:
		map<string,string>		params;
		TChain* fChain;
		Int_t	fCurrent;

	private:
		int					bestCombo;


	protected:
		void				SetUp(map<string,string> const &, vector<string> const &);
		virtual void		Null();
		virtual void		Delete();
		virtual void		Clear();
		virtual Long64_t	LoadTree(Long64_t entry);
		virtual void		SetBranchAddresses();
		virtual void		SetChain(TChain*);

	public:
		void	Init();
		void	GetEntry(double);
		Long64_t GetEntries();

	public:
		Branches();
		virtual ~Branches();
	
		void				SetBestCombo(int);
		unsigned int const	GetBestCombo() const;
};

#endif










