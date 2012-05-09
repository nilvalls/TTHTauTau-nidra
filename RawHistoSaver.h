//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun  7 03:28:02 2011 by ROOT version 5.27/06b
// from TTree HMTTree/TauTauTree
// found on file: ditau_nTuple.root
//////////////////////////////////////////////////////////

#ifndef RawHistoSaver_h
#define RawHistoSaver_h

#include <TROOT.h>
#include <TSystem.h>
#include <TFile.h>
#include <iostream>
#include "Process.h"
#include "ProPack.h"

using namespace std;

class RawHistoSaver {

	public:
		RawHistoSaver();
		RawHistoSaver(map<string,string> const &, ProPack const &);
		virtual ~RawHistoSaver();


	private: 
		void SaveRawHistos();
		map<string,string>	params;
		TFile* file;
		virtual void SaveRawHistos(ProPack const *) const;
		virtual void SaveRawHistos(Process const *) const;
		virtual void SaveRawHistos(vector<Process> const *) const;


};

#endif










