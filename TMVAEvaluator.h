//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun  7 03:28:02 2011 by ROOT version 5.27/06b
// from TTree HMTTree/TauTauTree
// found on file: ditau_nTuple.root
//////////////////////////////////////////////////////////

#ifndef TMVAEvaluator_h
#define TMVAEvaluator_h

#include <TROOT.h>
#include <TSystem.h>
#include <TFile.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "DitauBranches.h"
#include "TMVA/Reader.h"
//#include "TMVA/Tools.h"

using namespace std;

class TMVAEvaluator {

	public:
		TMVAEvaluator();
		TMVAEvaluator(map<string,string> const &);
		virtual ~TMVAEvaluator();

		float Evaluate(DitauBranches const *, int);


	private: 
		TMVA::Reader* tmvaReader;

		float NSVFitSystemEta;
		float NSVFitSystemPt;
		float NSVFitMass;
//		float NSVFitMassUncert;
		float NSVFitMET;
		float DeltaR_recoTau1_SVFitTau1;
		float BoostedSVFitTau1Pt;

		DitauBranches * event;

	protected:
		map<string,string>	params;

};

#endif










