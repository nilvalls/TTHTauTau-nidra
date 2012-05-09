/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			11 Jun 2011
    Description:	Plot stacking class.
    Notes:

*/

#include "TMVASampler.h"

#define TMVASampler_cxx
using namespace std;

#define AT __LINE__

// Default constructor
TMVASampler::TMVASampler(){
	file = NULL;
	proPack = NULL;
}

// Default destructor
TMVASampler::~TMVASampler(){
	if(file!=NULL){ file->Close(); }
	delete file; file = NULL;
	delete proPack; proPack = NULL;

}

TMVASampler::TMVASampler(map<string,string>const & iParams){
	params = iParams;
	Long_t *id,*size,*flags,*mt; id=NULL; size=NULL;flags=NULL;mt=NULL;
	bool badFile = gSystem->GetPathInfo((params["process_file"]).c_str(),id,size,flags,mt);
	if(badFile){ cerr << "ERROR: trying to make TMVA training sample but proPack file does not exist. Please run the event analysis first" << endl; exit(1); }

	file = new TFile((params["process_file"]).c_str(), "READ");
	file->cd();

	proPack = (ProPack*)file->Get((params["propack_name"]).c_str());

	MakeTrainingSample(proPack);

}

void TMVASampler::MakeTrainingSample(ProPack * iProPack){


	string signalName = iProPack->GetProcess(params.find("MVAsignal")->second)->GetShortName();
	string backgroundName = iProPack->GetProcess(params.find("MVAbackground")->second)->GetShortName();
	string outputName = (params.find("tmva_trainer")->second) + "_sig_" + signalName + "_bkg_" + backgroundName + ".root";
	
	TFile* output = new TFile(outputName.c_str(), "RECREATE"); output->cd();

	TTree* signalTree = new TTree("TreeS","TreeS");
	cout << "Filling signal tree with: " << signalName << endl;

	vector<pair<int,int> > * goodEventsSignal = new vector<pair<int,int> >(iProPack->GetProcess(params.find("MVAsignal")->second)->GetGoodEventsForSignal());
	FillTree(signalTree, iProPack->GetProcess(params.find("MVAsignal")->second), goodEventsSignal);
	delete goodEventsSignal; goodEventsSignal = NULL;
	

	output->cd();
	signalTree->Write();
	cout << "Signal tree contains " << signalTree->GetEntries() << " events." << endl;
	delete signalTree;

	TTree* backgroundTree = new TTree("TreeB","TreeB");
	cout << "Filling background tree with: " << backgroundName << endl;

	vector<pair<int,int> > * goodEventsBackground = new vector<pair<int,int> >(iProPack->GetProcess(params.find("MVAbackground")->second)->GetGoodEventsForSignal());
	FillTree(backgroundTree, iProPack->GetProcess(params.find("MVAbackground")->second), goodEventsBackground);
	delete goodEventsBackground; goodEventsBackground = NULL;

	output->cd();
	backgroundTree->Write();
	cout << "Background tree contains " << signalTree->GetEntries() << " events." << endl;
	delete backgroundTree;

	output->Close();
	cout << "Done! TMVA training sample: " << outputName << endl;

}

void TMVASampler::FillTree(TTree* iTree, Process const * iProcess, vector<pair<int,int> > const * iGoodEvents){

	float Tau1Pt;
	float Tau2Pt;
	float Tau1Eta;
	float Tau2Eta;
	float DitauPt;
	float DitauEta;
	float CosDeltaPhiDitau;
	float MET;

	iTree->Branch("Tau1Pt", &Tau1Pt);
	iTree->Branch("Tau2Pt", &Tau2Pt);
	iTree->Branch("Tau1Eta", &Tau1Eta);
	iTree->Branch("Tau2Eta", &Tau2Eta);
	iTree->Branch("DitauPt", &DitauPt);
	iTree->Branch("DitauEta", &DitauEta);
	iTree->Branch("CosDeltaPhiDitau", &CosDeltaPhiDitau);
	iTree->Branch("MET", &MET);

	float LogTau1Pt;
	float LogTau2Pt;
	float AbsTau1Eta;
	float AbsTau2Eta;
	float LogDitauPt;
	float AbsDitauEta;
	float LogCosDeltaPhiDitau;
	float LogMET;

	iTree->Branch("LogTau1Pt", &LogTau1Pt);
	iTree->Branch("LogTau2Pt", &LogTau2Pt);
	iTree->Branch("AbsTau1Eta", &AbsTau1Eta);
	iTree->Branch("AbsTau2Eta", &AbsTau2Eta);
	iTree->Branch("LogDitauPt", &LogDitauPt);
	iTree->Branch("AbsDitauEta", &AbsDitauEta);
	iTree->Branch("LogCosDeltaPhiDitau", &LogCosDeltaPhiDitau);
	iTree->Branch("LogMET", &LogMET);

	float NSVFitSystemEta;
	float NSVFitSystemPt;
	float NSVFitMass;
	float NSVFitMassUncert;
	float NSVFitMET;
	float DeltaR_recoTau1_SVFitTau1;
	float DeltaR_recoTau2_SVFitTau2;
	float BoostedSVFitTau1Pt;
	float BoostedSVFitTau2Pt;

	iTree->Branch("NSVFitSystemEta", &NSVFitSystemEta);
	iTree->Branch("NSVFitSystemPt", &NSVFitSystemPt);
	iTree->Branch("NSVFitMass", &NSVFitMass);
	iTree->Branch("NSVFitMassUncert", &NSVFitMassUncert);
	iTree->Branch("NSVFitMET", &NSVFitMET);
	iTree->Branch("DeltaR_recoTau1_SVFitTau1", &DeltaR_recoTau1_SVFitTau1);
	iTree->Branch("DeltaR_recoTau2_SVFitTau2", &DeltaR_recoTau2_SVFitTau2);
	iTree->Branch("BoostedSVFitTau1Pt", &BoostedSVFitTau1Pt);
	iTree->Branch("BoostedSVFitTau2Pt", &BoostedSVFitTau2Pt);


	float AbsNSVFitSystemEta;
	float LogNSVFitSystemPt;
	float SigNSVFitMassUncert;
	float LogNSVFitMET;
	float LogDeltaR_recoTau1_SVFitTau1;
	float LogDeltaR_recoTau2_SVFitTau2;
	float LogBoostedSVFitTau1Pt;
	float LogBoostedSVFitTau2Pt;

	iTree->Branch("AbsNSVFitSystemEta", &AbsNSVFitSystemEta);
	iTree->Branch("LogNSVFitSystemPt", &LogNSVFitSystemPt);
	iTree->Branch("NSVFitMass", &NSVFitMass);
	iTree->Branch("SigNSVFitMassUncert", &SigNSVFitMassUncert);
	iTree->Branch("LogNSVFitMET", &LogNSVFitMET);
	iTree->Branch("LogDeltaR_recoTau1_SVFitTau1", &LogDeltaR_recoTau1_SVFitTau1);
	iTree->Branch("LogDeltaR_recoTau2_SVFitTau2", &LogDeltaR_recoTau2_SVFitTau2);
	iTree->Branch("LogBoostedSVFitTau1Pt", &LogBoostedSVFitTau1Pt);
	iTree->Branch("LogBoostedSVFitTau2Pt", &LogBoostedSVFitTau2Pt);

	// Instantiante DitauBranches to read events more easily
	DitauBranches event = DitauBranches(params, ((params.find("ntuplesDir")->second) + (iProcess->GetNtuplePath())));

	vector<pair<int,int> > const * goodEvents = iGoodEvents;
	for(unsigned int i = 0; i < goodEvents->size(); i++){
		event.GetEntry(goodEvents->at(i).first);
		event.SetBestCombo(goodEvents->at(i).second);

		Tau1Pt				= event.Tau1Pt->at(goodEvents->at(i).second);
		Tau2Pt				= event.Tau2Pt->at(goodEvents->at(i).second);
		Tau1Eta				= event.Tau1Eta->at(goodEvents->at(i).second);
		Tau2Eta				= event.Tau2Eta->at(goodEvents->at(i).second);
		DitauPt				= event.DitauPt->at(goodEvents->at(i).second);
		DitauEta			= event.DitauEta->at(goodEvents->at(i).second);
		CosDeltaPhiDitau	= event.TauTauCosDPhi->at(goodEvents->at(i).second);
		MET					= event.METl1l2l3corr->at(goodEvents->at(i).second);

		NSVFitSystemEta				= event.NSVFitSystemEta->at(goodEvents->at(i).second);
		NSVFitSystemPt				= event.NSVFitSystemPt->at(goodEvents->at(i).second);
		NSVFitMass					= event.NSVFitMass->at(goodEvents->at(i).second);
		NSVFitMassUncert			= event.NSVFitMassUncert->at(goodEvents->at(i).second);
		NSVFitMET					= event.NSVFitMET->at(goodEvents->at(i).second);
		DeltaR_recoTau1_SVFitTau1	= event.DeltaR_recoTau1_SVFitTau1->at(goodEvents->at(i).second);
		DeltaR_recoTau2_SVFitTau2	= event.DeltaR_recoTau2_SVFitTau2->at(goodEvents->at(i).second);
		BoostedSVFitTau1Pt			= event.BoostedSVFitTau1Pt->at(goodEvents->at(i).second);
		BoostedSVFitTau2Pt			= event.BoostedSVFitTau2Pt->at(goodEvents->at(i).second);

		// Adjusted
		LogTau1Pt				= log10(event.Tau1Pt->at(goodEvents->at(i).second));
		LogTau2Pt				= log10(event.Tau2Pt->at(goodEvents->at(i).second));
		AbsTau1Eta				= fabs(event.Tau1Eta->at(goodEvents->at(i).second));
		AbsTau2Eta				= fabs(event.Tau2Eta->at(goodEvents->at(i).second));
		LogDitauPt				= log10(event.DitauPt->at(goodEvents->at(i).second));
		AbsDitauEta				= fabs(event.DitauEta->at(goodEvents->at(i).second));
		cout << i << " " << event.TauTauCosDPhi->at(goodEvents->at(i).second) << " " << log10(event.TauTauCosDPhi->at(goodEvents->at(i).second)) << endl;
		LogCosDeltaPhiDitau		= log10(event.TauTauCosDPhi->at(goodEvents->at(i).second));
		LogMET					= log10(event.METl1l2l3corr->at(goodEvents->at(i).second));

		AbsNSVFitSystemEta				= fabs(event.NSVFitSystemEta->at(goodEvents->at(i).second));
		LogNSVFitSystemPt				= log10(event.NSVFitSystemPt->at(goodEvents->at(i).second));
		NSVFitMass						= event.NSVFitMass->at(goodEvents->at(i).second);
		SigNSVFitMassUncert				= event.NSVFitMassUncert->at(goodEvents->at(i).second)/event.NSVFitMass->at(goodEvents->at(i).second);
		LogNSVFitMET					= log10(event.NSVFitMET->at(goodEvents->at(i).second));
		LogDeltaR_recoTau1_SVFitTau1	= log10(event.DeltaR_recoTau1_SVFitTau1->at(goodEvents->at(i).second));
		LogDeltaR_recoTau2_SVFitTau2	= log10(event.DeltaR_recoTau2_SVFitTau2->at(goodEvents->at(i).second));
		LogBoostedSVFitTau1Pt			= log10(event.BoostedSVFitTau1Pt->at(goodEvents->at(i).second));
		LogBoostedSVFitTau2Pt			= log10(event.BoostedSVFitTau2Pt->at(goodEvents->at(i).second));

		iTree->Fill();
	}

}


