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
#include <iostream>
#include <fstream>
#include <sstream>
#include "CutFlow.h"
#include "ProPack.h"
#include "Analyzer.h"

using namespace std;

class Cruncher {

	public:
		Cruncher();
		Cruncher(map<string,string> const &);
		virtual ~Cruncher();

		void PrintEfficiencies(string const, string const);
		void PrintEfficienciesForQCD(string const, string const);

	private: 
		map<string,string> params;
		ProPack* proPack;
		vector<Process*> processes;
		TFile* file;

		string GetDocumentHeader(string const);
		string GetDocumentFooter(string const);
		string GetTableHeader(string const, string const);
		string GetTableSubHeader(string const, string const);
		string GetTableFooter(string const);
		string GetOptionsHeader(string const, string const);
		string GetCutLine(string const, string const, string const);
		string GetCutTriplet(string const, string const, string const, CutFlow const *);
		string GetEfficiencies(string const, string const);
		string GetCutLineForQCD(string const, string const, string const);
		string GetCutTripletForQCD(string const, string const, string const, CutFlow const *);
		string GetEfficienciesForQCD(string const, string const);
		bool IsOptionThere(string const, string const);
		int GetNumberOfOptions(string const);
		void SaveToFile(stringstream const, string const);
		void SaveToFile(string const, string const);

};

#endif










