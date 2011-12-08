/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			11 Jun 2011
    Description:	Plot stacking class.
    Notes:

*/

#include "Plotter.h"

#define Plotter_cxx
using namespace std;

#define AT __LINE__

// Default constructor
Plotter::Plotter(){}

// Default destructor
Plotter::~Plotter(){}

// A more useful constructor
Plotter::Plotter(map<string,string>const & iParams){
	params = iParams;

	TFile* file = new TFile((params["process_file"]).c_str(), "UPDATE");
	file->cd();

	ProPack* proPack = (ProPack*)file->Get((params["propack_name"]).c_str());
	MakePlots(proPack);

	file->cd();
	proPack->Write((params["propack_name"]).c_str(), TObject::kOverwrite);

	file->Close();
	delete file;
}

// Function to make the plots
void Plotter::MakePlots(ProPack* iProPack){
	if(iProPack->HaveCollisions()){		MakePlots(iProPack->GetCollisions());		}
	if(iProPack->HaveMCbackgrounds()){	MakePlots((iProPack->GetMCbackgrounds()));		}
	if(iProPack->HaveSignals()){		MakePlots(iProPack->GetSignals());			}

	// Set analyzed flag in topoPack to true
	iProPack->NormalizeToLumi();
	iProPack->BuildQCD();
	iProPack->SetAnalyzed();
}

// Book and fill the plots with the good events
void Plotter::MakePlots(Process* iProcess){
	
	// Set up two HContainers, one for signal and another for QCD analysis
	HContainer hContainerForSignal, hContainerForQCD;

	// Book histos and place them in the process
	BookHistos(&hContainerForSignal);
	BookHistos(&hContainerForQCD);

	// Read in ntuple file
	Analyzer analyzer(params);
	analyzer.Init(iProcess->GetNtuplePath());

	// Loop over good signal events and fill histos accordingly
	vector<pair<int,int> > goodEventsForSignal = iProcess->GetGoodEventsForSignal();
	for(unsigned int i = 0; i < goodEventsForSignal.size(); i++){
		DitauBranches event = DitauBranches(*(analyzer.GetDitauBranches(goodEventsForSignal.at(i).first)));
		event.SetBestCombo(goodEventsForSignal.at(i).second);
		FillHistos(&hContainerForSignal,&event);
	}

	// Loop over good QCD events and fill histos accordingly
	vector<pair<int,int> > goodEventsForQCD = iProcess->GetGoodEventsForQCD();
	for(unsigned int i = 0; i < goodEventsForQCD.size(); i++){
		DitauBranches event = DitauBranches(*(analyzer.GetDitauBranches(goodEventsForQCD.at(i).first)));
		event.SetBestCombo(goodEventsForQCD.at(i).second);
		FillHistos(&hContainerForQCD,&event);
	}

	// Send the filled HContainers to the process
	iProcess->SetHContainerForSignal(hContainerForSignal);
	iProcess->SetHContainerForQCD(hContainerForQCD);

}

// Run MakePlots for each process in the vector
void Plotter::MakePlots(vector<Process>* iProcesses){
	for(unsigned int p=0; p<iProcesses->size(); p++){ 
		MakePlots(&(iProcesses->at(p))); 
	}
}

// Set up the configured histos and add them to the process
void Plotter::BookHistos(HContainer* iHContainer){

	// Reset input HContainer
	iHContainer->clear();

	// Obtain config file where histos are configured
	Config histosConfigFile = Config(params["histoCfg"]);
	map<string, Config*> histosConfigMap = histosConfigFile.getGroups();

	// Loop over histos in config file, and add them to HContainer
	string th1fPrefix = "th1f_";
	string th2fPrefix = "th2f_";
	for (map<string, Config*>::iterator i = histosConfigMap.begin(); i != histosConfigMap.end(); ++i){
		string groupName = i->first;
		Config* histoConfig = i->second;

		if (groupName.substr(0,th1fPrefix.length()) == th1fPrefix) {
			string name	= groupName.substr(th1fPrefix.length());
			iHContainer->Add(name, HWrapper(name, "th1f", *histoConfig));
		}else if (groupName.substr(0,th2fPrefix.length()) == th2fPrefix){
			string name	= groupName.substr(th2fPrefix.length());
			iHContainer->Add(name, HWrapper(name, "th2f", *histoConfig));
		}
	}
}

// Fill the histograms with the event passed
void Plotter::FillHistos(HContainer* iHContainer, DitauBranches* iEvent){
	HContainer* hContainer = iHContainer;
	DitauBranches* event = iEvent;
	int iCombo = event->bestCombo;

	float iPuWeight = event->puWeight;
	float iTau1TriggerWeight = event-> tau1TriggerWeight;
	float iTau2TriggerWeight = event-> tau2TriggerWeight;

	#include "clarity/fillHistos.h"
}

// Save canvas
void Plotter::SaveCanvas(TCanvas* iCanvas, string iDir, string iFilename){

	// Create output dir if it doesn't exists already
	TString sysCommand = "if [ ! -d " + iDir + " ]; then mkdir -p " + iDir + "; fi";
	if(gSystem->Exec(sysCommand) > 0){ cout << ">>> ERROR: problem creating dir for plots " << iDir << endl; exit(1); }

	// Loop over all file format extensions choosen and save canvas
	vector<string> extension; extension.push_back(".png");
	for( unsigned int ext = 0; ext < extension.size(); ext++){
		iCanvas->SaveAs( (iDir + iFilename + extension.at(ext)).c_str() );
	}

}

// Check to see if we want this a copy of a plot with some log scales
void Plotter::SaveCanvasLog(TCanvas* iCanvas, string iDir, string iFilename, bool iLogx, bool iLogy, bool iLogz){
	if(iLogx || iLogy || iLogz ){
		iCanvas->SetLogx(iLogx); 
		iCanvas->SetLogy(iLogy); 
		iCanvas->SetLogz(iLogz); 
		SaveCanvas(iCanvas, iDir, string(iFilename+"_log"));
		iCanvas->SetLogx(0);
		iCanvas->SetLogy(0);
		iCanvas->SetLogz(0);
	}   
}

/*
THStack* Plotter::GetBackgroundStack(int iPlot){

	double maxY = GetMaxY(iPlot);
	HWrapper* refHisto = GetAvailableProcess()->GetHistoForSignal(iPlot);
	string stackName = string(refHisto->GetName()+"_stack");
	THStack* result = new THStack(stackName.c_str(), stackName.c_str());

	// Add each MC background first if we have them
	if(HaveMCbackgrounds()){
		for(unsigned int b = 0; b < GetMCbackgrounds()->size(); b++){
			int color = GetMCbackgrounds()->at(b)->GetColor();
			GetMCbackgrounds()->at(b)->GetHistoForSignal(iPlot)->SetFillStyle(1001,color);
			TH1F* temp = (TH1F*)(GetMCbackgrounds()->at(b)->GetHistoForSignal(iPlot)->GetHisto());
			temp->GetYaxis()->SetRangeUser(0.001,maxY);
			result->Add(temp);
		}
	}

	// Then add QCD if we have it
	if(HaveQCD()){
		TH1* temp = GetQCD()->GetHistoForSignal(iPlot)->GetHisto();
		temp->GetYaxis()->SetRangeUser(0.001,maxY);
		result->Add(temp);
	}
	

	result->Draw("HIST");
	result->GetXaxis()->SetRangeUser(refHisto->GetXminVis(), refHisto->GetXmaxVis());
	result->GetXaxis()->SetTitle((refHisto->GetXtitle()).c_str());
	result->GetYaxis()->SetTitle((refHisto->GetYtitle()).c_str());
	result->SetMinimum(0.001);
	result->SetMaximum(maxY);
	result->GetYaxis()->SetRangeUser(0.001,maxY);


	return result;
}

TH1* Plotter::GetBackgroundSum(int iPlot){
	TH1* result = NULL;

	// Add each MC background first if we have them
	if(HaveMCbackgrounds()){
		for(unsigned int b = 0; b < GetMCbackgrounds()->size(); b++){
			TH1* histo = GetMCbackgrounds()->at(b)->GetHistoForSignal(iPlot)->GetHisto();
			if(result == NULL){ result = (TH1*)histo->Clone();	}
			else{				result->Add(histo);				}
		}
	}

}

// Figure out the maximum y value
double const ProPack::GetMaxY(string const iName) const {
	double result = 0;

	// Check max y for collisions
	if(PrepareCollisions()){
		double thisMax = collisions.GetHistoForSignal(iName)->GetHisto()->GetMaximum();	
		if(thisMax > result){ result = thisMax; }
	}

	// Check max y for mcBackgrounds
	for(unsigned int b = 0; b < GetMCbackgrounds()->size(); b++){
		double thisMax = mcBackgrounds.at(b).GetHistoForSignal(iName)->GetHisto()->GetMaximum();	
		if(thisMax > result){ result = thisMax; }
	}

	// Check max y for signals
	for(unsigned int s = 0; s < GetSignals()->size(); s++){
		double thisMax = signals.at(s).GetHistoForSignal(iName)->GetHisto()->GetMaximum();	
		if(thisMax > result){ result = thisMax; }
	}
	
	return result;
}

// Figure out the maximum integral value
double const ProPack::GetMaxIntegral(string const iName) const {
	double result = 0;

	// Check max integral for collisions
	if(PrepareCollisions()){
		double thisMax = collisions.GetHistoForSignal(iName)->GetHisto()->Integral();
		if(thisMax > result){ result = thisMax; }
	}

	// Check max integral for mcBackgrounds
	for(unsigned int b = 0; b < GetMCbackgrounds()->size(); b++){
		double thisMax = mcBackgrounds.at(b).GetHistoForSignal(iName)->GetHisto()->Integral();
		if(thisMax > result){ result = thisMax; }
	}

	// Check max integral for signals
	for(unsigned int s = 0; s < GetSignals()->size(); s++){
		double thisMax = signals.at(s).GetHistoForSignal(iName)->GetHisto()->Integral();
		if(thisMax > result){ result = thisMax; }
	}
	
	return result;
}


//*/

