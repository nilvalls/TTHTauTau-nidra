//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun  7 03:28:02 2011 by ROOT version 5.27/06b
// from TTree HMTTree/TauTauTree
// found on file: ditau_nTuple.root
//////////////////////////////////////////////////////////

#ifndef Cruncher_h
#define Cruncher_h

#include <TROOT.h>
#include <TSystem.h>
#include <TFile.h>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "CutFlow.h"
#include "ProPack.h"

class Cruncher {

	public:
		Cruncher();
		Cruncher(map<string,string> const &);
		virtual ~Cruncher();

		void PrintEfficiencies(string const, string const);

	private: 
		map<string,string> params;
		ProPack* proPack;
		vector<Process*> processes;
		TFile* file;

		bool IsOptionThere(string const, string const);
		int GetNumberOfOptions(string const);
		void SaveToFile(stringstream const, string const);
		void SaveToFile(string const, string const);

};

#endif










