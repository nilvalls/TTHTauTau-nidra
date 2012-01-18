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
Plotter::Plotter(){
	file = NULL;
	proPack = NULL;
}

// Default destructor
Plotter::~Plotter(){
	if(file!=NULL){ file->Close(); }
	delete file; file = NULL;
	delete proPack; proPack = NULL;
}

Plotter::Plotter(map<string,string>const & iParams){
	params = iParams;
	Long_t *id,*size,*flags,*mt; id=NULL; size=NULL;flags=NULL;mt=NULL;
	bool badFile = gSystem->GetPathInfo((params["process_file"]).c_str(),id,size,flags,mt);
	if(badFile){ cerr << "ERROR: trying to fill plots but proPack file does not exist. Please run the event analysis first" << endl; exit(1); }

	file = new TFile((params["process_file"]).c_str(), "UPDATE");
	file->cd();

	proPack = (ProPack*)file->Get((params["propack_name"]).c_str());

	MakePlots(proPack);

	file->cd();
	proPack->Write((params["propack_name"]).c_str(), TObject::kOverwrite);

}

// Function to make the plots
void Plotter::MakePlots(ProPack* iProPack){
	if(iProPack->HaveCollisions()){		MakePlots(iProPack->GetCollisions());		}
	if(iProPack->HaveMCbackgrounds()){	MakePlots((iProPack->GetMCbackgrounds()));	}
	if(iProPack->HaveSignals()){		MakePlots(iProPack->GetSignals());			}

	// Set analyzed flag in topoPack to true
	iProPack->NormalizeToLumi();
	iProPack->BuildQCD();
	iProPack->SetAnalyzed();
}

// Run MakePlots for each process in the vector
void Plotter::MakePlots(vector<Process>* iProcesses){
	for(unsigned int p=0; p<iProcesses->size(); p++){ 
		MakePlots(&(iProcesses->at(p))); 
	}
}

void Plotter::MakePlots(Process* iProcess){

	// Set up two HContainers, one for signal and another for QCD analysis
	HContainer hContainerForSignal, hContainerForQCD;

	// Book histos and place them in the process
	BookHistos(&hContainerForSignal);
	BookHistos(&hContainerForQCD);

	// Instantiante Analyzer to read events more easily
	Analyzer analyzer(params);	
	DitauBranches * event = analyzer.Init(iProcess->GetNtuplePath());

	// Get preexisting cutflow to potentially add cuts
	CutFlow* cutFlow = iProcess->GetCutFlow();

	// Triggers and PUcorrectors
	PUcorrector puCorrector;
	Trigger trigger(4600);

	// Recover the good events for signal and fill histos with them
	weightCounter weightCounterForSignal;
	vector<pair<int,int> > goodEventsForSignal = iProcess->GetGoodEventsForSignal();
	for(unsigned int i = 0; i < goodEventsForSignal.size(); i++){
		event->AlienGetEntry(goodEventsForSignal.at(i).first);
		event->SetBestCombo(goodEventsForSignal.at(i).second);
		FillHistos(&hContainerForSignal,event,iProcess->IsMC(), &trigger, &puCorrector, &weightCounterForSignal);
	}
	iProcess->SetHContainerForSignal(hContainerForSignal);
	double puEfficiencyForSignal			= weightCounterForSignal.puCorrection/weightCounterForSignal.total;
	double tau1TriggerEfficiencyForSignal	= weightCounterForSignal.tau1Trigger/weightCounterForSignal.total;
	double tau2TriggerEfficiencyForSignal	= weightCounterForSignal.tau2Trigger/weightCounterForSignal.total;

	// Recover the good events for QCD and fill histos with them
	weightCounter weightCounterForQCD;
	vector<pair<int,int> > goodEventsForQCD = iProcess->GetGoodEventsForQCD();
	for(unsigned int i = 0; i < goodEventsForQCD.size(); i++){
		event->AlienGetEntry(goodEventsForQCD.at(i).first);
		event->SetBestCombo(goodEventsForQCD.at(i).second);
		FillHistos(&hContainerForQCD,event,iProcess->IsMC(), &trigger, &puCorrector, &weightCounterForQCD);
	}
	iProcess->SetHContainerForQCD(hContainerForQCD);
	double puEfficiencyForQCD			= weightCounterForQCD.puCorrection/weightCounterForQCD.total;
	double tau1TriggerEfficiencyForQCD	= weightCounterForQCD.tau1Trigger/weightCounterForQCD.total;
	double tau2TriggerEfficiencyForQCD	= weightCounterForQCD.tau2Trigger/weightCounterForQCD.total;

	// Add postCuts
	if(IsFlagThere("PUcorr")){ cutFlow->RegisterCut("PU reweighing", 2, puEfficiencyForSignal*cutFlow->GetLastCountForSignal(), puEfficiencyForQCD*cutFlow->GetLastCountForQCD()); }
	if(IsFlagThere("trigger")){ 
		cutFlow->RegisterCut("LL trigger", 2, tau1TriggerEfficiencyForSignal*cutFlow->GetLastCountForSignal(), tau1TriggerEfficiencyForQCD*cutFlow->GetLastCountForQCD()); 
		cutFlow->RegisterCut("SL trigger", 2, tau2TriggerEfficiencyForSignal*cutFlow->GetLastCountForSignal(), tau2TriggerEfficiencyForQCD*cutFlow->GetLastCountForQCD()); 
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
void Plotter::FillHistos(HContainer* iHContainer, DitauBranches* iEvent, bool iIsMC, Trigger const* iTrigger, PUcorrector const * iPUcorrector, weightCounter* iWeightCounter){
	HContainer* hContainer = iHContainer;
	DitauBranches* event = iEvent;
	int iCombo = event->bestCombo;

	float iPuWeight = 1.0;
	float iTau1TriggerWeight = 1.0;
	float iTau2TriggerWeight = 1.0;

	if(iIsMC){
		if(IsFlagThere("PUcorr")){ iPuWeight = iPUcorrector->GetWeight(event->numInteractionsBX0); }
		if(IsFlagThere("trigger")){ 
			iTau1TriggerWeight = iTrigger->GetWeightFromFunc(event->Tau1Pt->at(event->bestCombo));
			iTau2TriggerWeight = iTrigger->GetWeightFromFunc(event->Tau2Pt->at(event->bestCombo));
		}
	}

	iWeightCounter->puCorrection	+= iPuWeight;
	iWeightCounter->tau1Trigger		+= iTau1TriggerWeight;
	iWeightCounter->tau2Trigger		+= iTau2TriggerWeight;
	iWeightCounter->total++;
	
	#include "clarity/fillHistos.h"
}

// Save canvas
void Plotter::SaveCanvas(TCanvas const * iCanvas, string iDir, string iFilename) const {

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


// Sum all the backgrounds and return the resulting HWrapper
HWrapper const Plotter::GetBackgroundSum(ProPack const * iProPack, string const iName) const {
	HWrapper* buffer = NULL;

	// Add each MC background first if we have them
	if(iProPack->HaveMCbackgrounds()){
		for(unsigned int b = 0; b < iProPack->GetMCbackgrounds()->size(); b++){
			if(buffer == NULL){	buffer = new HWrapper(*(iProPack->GetMCbackgrounds()->at(b).GetHistoForSignal(iName))); }
			else{ buffer->Add(*(iProPack->GetMCbackgrounds()->at(b).GetHistoForSignal(iName))); }
		}
	}
	// Add QCD if we have it
	if(iProPack->PrepareQCD()){
		if(buffer == NULL){	buffer = new HWrapper(*(iProPack->GetQCD()->GetHistoForSignal(iName))); }
		else{ buffer->Add(*(iProPack->GetQCD()->GetHistoForSignal(iName))); }
	}

	if(buffer == NULL){ cerr << "ERROR: requested sum of backgrounds for " << iName << " but result came out NULL" << endl; exit(1); }
	HWrapper result = HWrapper(*buffer);

	delete buffer;
	return result;
}


// Figure out the maximum y value
double const Plotter::GetMaximum(ProPack const * iProPack, string const iName) const { return GetMaximum(iProPack, iName, false); }
double const Plotter::GetMaximumWithError(ProPack const * iProPack, string const iName) const { return GetMaximum(iProPack, iName, true); }
double const Plotter::GetMaximum(ProPack const * iProPack, string const iName, bool const iIncludeError) const {
	double result = 0;

	// Check max y for collisions
	if(iProPack->PrepareCollisions()){
		double thisMax = 0; 
		if(iIncludeError){	thisMax = iProPack->GetCollisions()->GetHistoForSignal(iName)->GetMaximumWithError(); }	
		else{				thisMax = iProPack->GetCollisions()->GetHistoForSignal(iName)->GetMaximum(); }	
		if(thisMax > result){ result = thisMax; }
	}

		
	// Check max y for QCD
	if(iProPack->PrepareQCD()){
		double thisMax = 0;
		if(iIncludeError){	thisMax = iProPack->GetQCD()->GetHistoForSignal(iName)->GetMaximumWithError(); }	
		else{				thisMax = iProPack->GetQCD()->GetHistoForSignal(iName)->GetMaximum(); }	
		if(thisMax > result){ result = thisMax; }
	}

	// Check max y for mcBackgrounds
	if(iProPack->PrepareMCbackgrounds()){
		for(unsigned int b = 0; b < iProPack->GetMCbackgrounds()->size(); b++){
			double thisMax = 0;
			if(iIncludeError){  thisMax = iProPack->GetMCbackgrounds()->at(b).GetHistoForSignal(iName)->GetMaximumWithError(); }
			else{				thisMax = iProPack->GetMCbackgrounds()->at(b).GetHistoForSignal(iName)->GetMaximum(); }	
			if(thisMax > result){ result = thisMax; }
		}
	}

	// Check max y for signals
	if(iProPack->PrepareSignals()){
		for(unsigned int s = 0; s < iProPack->GetSignals()->size(); s++){
			double thisMax = 0;
			thisMax = iProPack->GetSignals()->at(s).GetHistoForSignal(iName)->GetMaximum();
			if(thisMax > result){ result = thisMax; }
		}
	}
	
	return result;
}


// Figure out the maximum integral value
double const Plotter::GetMaxIntegral(ProPack const * iProPack, string const iName) const {
	double result = 0;

	// Check max y for collisions
	if(iProPack->PrepareCollisions()){
		double thisMax = iProPack->GetCollisions()->GetHistoForSignal(iName)->GetHisto()->Integral();	
		if(thisMax > result){ result = thisMax; }
	}

	// Check max y for QCD
	if(iProPack->PrepareQCD()){
		double thisMax = iProPack->GetQCD()->GetHistoForSignal(iName)->GetHisto()->Integral();	
		if(thisMax > result){ result = thisMax; }
	}

	// Check max y for mcBackgrounds
	if(iProPack->PrepareMCbackgrounds()){
		for(unsigned int b = 0; b < iProPack->GetMCbackgrounds()->size(); b++){
			double thisMax = iProPack->GetMCbackgrounds()->at(b).GetHistoForSignal(iName)->GetHisto()->Integral();	
			if(thisMax > result){ result = thisMax; }
		}
	}

	// Check max y for signals
	if(iProPack->PrepareSignals()){
		for(unsigned int s = 0; s < iProPack->GetSignals()->size(); s++){
			double thisMax = iProPack->GetSignals()->at(s).GetHistoForSignal(iName)->GetHisto()->Integral();	
			if(thisMax > result){ result = thisMax; }
		}
	}
	
	return result;
}

// Return TPaveText with some generic plot info
TPaveText * Plotter::GetPlotText(){

		// Extra plot info
		float xPlotInfo		= 0.15;
		float yPlotInfo		= 1.01;

		float dxPlotInfo	= 0.85;
		float dyPlotInfo	= 0.07; 

		TPaveText *plotInfo = new TPaveText(xPlotInfo, yPlotInfo-dyPlotInfo, xPlotInfo+dxPlotInfo, yPlotInfo, "brNDC");

		plotInfo->SetBorderSize(0);
		plotInfo->SetLineColor(0);
		plotInfo->SetFillStyle(0);

		stringstream textSS; textSS.str("");
		textSS	<< "CMS Preliminary"
				<< "    4.6/fb" << " p-p #sqrt{s} = 7TeV"	
				<< "    #tau_{h}#tau_{h} channel";
		plotInfo->AddText((textSS.str()).c_str());

		return plotInfo;

}

bool const Plotter::IsFlagThere(string const iFlag) const {
	string flags = params.find("flags")->second;
	size_t found = flags.find(iFlag);
	return ((0 <= found) && (found < flags.length()));
}

