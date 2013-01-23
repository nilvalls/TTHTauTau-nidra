//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun  7 03:28:02 2011 by ROOT version 5.27/06b
// from TTree HMTTree/TauTauTree
// found on file: ditau_nTuple.root
//////////////////////////////////////////////////////////

#ifndef Combiner_h
#define Combiner_h

#include <TROOT.h>
#include <TSystem.h>
#include <TFile.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "TCanvas.h"
#include "CutFlow.h"
#include "Branches.h"
#include "Process.h"
#include "ProPack.h"

using namespace std;


class Combiner {

	public:
		Combiner();
		Combiner(map<string,string> const &);
		~Combiner();


	protected:

	private: 
		void Combine(ProPack*);

	protected:
		map<string,string>	params;

};

#endif










