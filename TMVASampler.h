//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun  7 03:28:02 2011 by ROOT version 5.27/06b
// from TTree HMTTree/TauTauTree
// found on file: ditau_nTuple.root
//////////////////////////////////////////////////////////

#ifndef TMVASampler_h
#define TMVASampler_h

#include <TROOT.h>
#include <TSystem.h>
#include <TFile.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "DitauBranches.h"
#include "Process.h"
#include "ProPack.h"
#include "Analyzer.h"

using namespace std;

class TMVASampler {

	public:
		TMVASampler();
		TMVASampler(map<string,string> const &);
		virtual ~TMVASampler();


	private: 
		void MakeTrainingSample(ProPack*);
		void FillTree(TTree*, Process const *, vector<pair<int,int> > const *);

	protected:
		TFile* file;
		ProPack* proPack;
		map<string,string>	params;

};

#endif









