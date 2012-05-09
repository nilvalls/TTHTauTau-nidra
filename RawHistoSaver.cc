/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			11 Jun 2011
    Description:	Plot stacking class.
    Notes:

*/

#include "RawHistoSaver.h"

#define RawHistoSaver_cxx
using namespace std;

#define AT __LINE__

// Default constructor
RawHistoSaver::RawHistoSaver(){
	cout << "WARNING: Using default constructor of RawHistoSaver." << endl;
}

// Default destructor
RawHistoSaver::~RawHistoSaver(){
	if(file!=NULL){ file->Close(); }
	delete file; file = NULL;
}

RawHistoSaver::RawHistoSaver(map<string,string>const & iParams, ProPack const & iProPack) {
	params = iParams;

	file = new TFile((params["rawHisto_file"]).c_str(), "RECREATE");
	file->cd();

	ProPack const * proPack = &iProPack;

	SaveRawHistos(proPack);

	proPack = NULL;

}

// Function to make the plots
void RawHistoSaver::SaveRawHistos(ProPack const * iProPack) const {

	if(iProPack->HaveCollisions()){		SaveRawHistos(iProPack->GetCollisions());		}
	if(iProPack->HaveMCbackgrounds()){	SaveRawHistos((iProPack->GetMCbackgrounds()));	}
	if(iProPack->HaveSignals()){		SaveRawHistos(iProPack->GetSignals());			}

}

// Run MakePlots for each process in the vector
void RawHistoSaver::SaveRawHistos(vector<Process> const * iProcesses) const {
	for(unsigned int p=0; p<iProcesses->size(); p++){ 
		SaveRawHistos(&(iProcesses->at(p))); 
	}
}

void RawHistoSaver::SaveRawHistos(Process const * iProcess) const {

	// Set up two HContainers, one for signal and another for QCD analysis
//	HContainer hContainerForSignal, hContainerForQCD;

	file->cd();
	TDirectory * processDir = file->mkdir(iProcess->GetShortName().c_str());
	TDirectory * osDir		= processDir->mkdir("OS");
	TDirectory * lsDir		= processDir->mkdir("LS");

	// Loop over all the HWrappers and save each histo
	vector<string> plotNames = iProcess->GetHContainerForSignal()->GetNames();

	string lastSavedPlotName = "";
	for(unsigned int p=0; p<plotNames.size(); p++){
		string plotName = plotNames.at(p);

		// TH1F or TH2F?
		if(iProcess->GetAvailableHWrapper(plotName)->IsTH1F()){
			osDir->cd();	
			TH1F * osHisto = new TH1F(*(TH1F*)(iProcess->GetHistoForSignal(plotName)->GetHisto()));
			osHisto->SetName(plotName.c_str());
			osHisto->Write();

			lsDir->cd();
			TH1F * lsHisto = new TH1F(*(TH1F*)(iProcess->GetHistoForQCD(plotName)->GetHisto()));
			lsHisto->SetName(plotName.c_str());
			lsHisto->Write();
		}else{
			osDir->cd();	
			TH2F * osHisto = new TH2F(*(TH2F*)(iProcess->GetHistoForSignal(plotName)->GetHisto()));
			osHisto->SetMarkerStyle(1);
			osHisto->SetName(plotName.c_str());
			osHisto->Write();

			lsDir->cd();
			TH2F * lsHisto = new TH2F(*(TH2F*)(iProcess->GetHistoForQCD(plotName)->GetHisto()));
			lsHisto->SetMarkerStyle(1);
			lsHisto->SetName(plotName.c_str());
			lsHisto->Write();
		}
	}



}

