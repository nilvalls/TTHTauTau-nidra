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
	ditauTrigger = NULL;
}

// Default destructor
Plotter::~Plotter(){

	delete ditauTrigger; ditauTrigger = NULL;
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
	ditauTrigger = new Trigger(proPack->GetIntegratedLumiInInvPb());

/*	MakePlots(proPack);

	delete puCorrector; puCorrector = NULL;
	delete ditauTrigger; ditauTrigger = NULL;

	file->cd();
	proPack->Write((params["propack_name"]).c_str(), TObject::kOverwrite);

	RawHistoSaver rawHistoSaver(params, *proPack);
	//*/

}

void Plotter::SaveFile(){
	file->cd();
	proPack->Write((params["propack_name"]).c_str(), TObject::kOverwrite);
	RawHistoSaver rawHistoSaver(params, *proPack);
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

	// Instantiante Branches to read events more easily
	//Branches event = Branches(params, iProcess->GetNtuplePath());
	Branches* event = NULL;
	string channel = params["channel"];
		 if(channel == "TTM"){	event = new TTMBranches(params, iProcess->GetNtuplePath()); }
	else if(channel == "TTE"){	event = new TTEBranches(params, iProcess->GetNtuplePath()); }

	// Get preexisting cutflow to potentially add cuts
	CutFlow* cutFlow = iProcess->GetCutFlow();

	// Recover the good events for signal and fill histos with them
	weightCounter weightCounterForSignal;
	weightCounterForSignal.puCorrection	= 0;
	weightCounterForSignal.tau1Trigger	= 0;
	weightCounterForSignal.tau2Trigger	= 0;
	weightCounterForSignal.total		= 0;

	vector<pair<int,int> > goodEventsForSignal = iProcess->GetGoodEventsForSignal();
	cout << "\n\tNow filling histos for " << iProcess->GetShortName() << endl;
	cout << "\t>>> OS, filling good events (total " << goodEventsForSignal.size() << "): "; cout.flush();
	stringstream goodEventsSS; goodEventsSS.str("");
	for(unsigned int i = 0; i < goodEventsForSignal.size(); i++){
		if(i>0 && (i%10) == 0){
			cout << string((goodEventsSS.str()).length(),'\b') << string((goodEventsSS.str()).length(),' ') << string((goodEventsSS.str()).length(),'\b'); cout.flush();
			goodEventsSS.str("");
			goodEventsSS << i;
			cout << goodEventsSS.str(); cout.flush();
		}

		event->GetEntry(goodEventsForSignal.at(i).first);
		event->SetBestCombo(goodEventsForSignal.at(i).second);
		FillHistos(&hContainerForSignal, event, iProcess->IsMC(), ditauTrigger, &weightCounterForSignal);
	}
	cout << endl;

	double puEfficiencyForSignal			= 0;
	double tau1TriggerEfficiencyForSignal	= 0;
	double tau2TriggerEfficiencyForSignal	= 0;
	if(weightCounterForSignal.total > 0){
		puEfficiencyForSignal			= weightCounterForSignal.puCorrection/weightCounterForSignal.total;
		tau1TriggerEfficiencyForSignal	= weightCounterForSignal.tau1Trigger/weightCounterForSignal.puCorrection;
		tau2TriggerEfficiencyForSignal	= weightCounterForSignal.tau2Trigger/weightCounterForSignal.tau1Trigger;//*/
	}
	if(weightCounterForSignal.total > 0){
		hContainerForSignal.ScaleErrorBy( sqrt(weightCounterForSignal.tau2Trigger/weightCounterForSignal.total) );
	}
	iProcess->SetHContainerForSignal(hContainerForSignal);

	// Recover the good events for QCD and fill histos with them
	weightCounter weightCounterForQCD;
	weightCounterForQCD.puCorrection	= 0;
	weightCounterForQCD.tau1Trigger		= 0;
	weightCounterForQCD.tau2Trigger		= 0;
	weightCounterForQCD.total			= 0;
	vector<pair<int,int> > goodEventsForQCD = iProcess->GetGoodEventsForQCD();
	double puEfficiencyForQCD			= 0;
	double tau1TriggerEfficiencyForQCD	= 0;
	double tau2TriggerEfficiencyForQCD	= 0;
	if(IsFlagThere("LS")){
		cout << "\t>>> LS, filling good events (total " << goodEventsForQCD.size() << "): "; cout.flush();
		goodEventsSS.str("");
		for(unsigned int i = 0; i < goodEventsForQCD.size(); i++){
			if(i>0 && (i%10) == 0){
				cout << string((goodEventsSS.str()).length(),'\b') << string((goodEventsSS.str()).length(),' ') << string((goodEventsSS.str()).length(),'\b'); cout.flush();
				goodEventsSS.str("");
				goodEventsSS << i;
				cout << goodEventsSS.str(); cout.flush();
			}

			event->GetEntry(goodEventsForQCD.at(i).first);
			event->SetBestCombo(goodEventsForQCD.at(i).second);
			FillHistos(&hContainerForQCD, event, iProcess->IsMC(), ditauTrigger, &weightCounterForQCD);
		}
		cout << endl;

		if(weightCounterForQCD.total > 0){
			puEfficiencyForQCD			= weightCounterForQCD.puCorrection/weightCounterForQCD.total;
			tau1TriggerEfficiencyForQCD	= weightCounterForQCD.tau1Trigger/weightCounterForQCD.puCorrection;
			tau2TriggerEfficiencyForQCD	= weightCounterForQCD.tau2Trigger/weightCounterForQCD.tau1Trigger;//*/
		}
		if(weightCounterForQCD.total > 0){
			hContainerForQCD.ScaleErrorBy( sqrt(weightCounterForQCD.tau2Trigger/weightCounterForQCD.total) );
		}
		iProcess->SetHContainerForQCD(hContainerForQCD);
	}

	// Add postCuts
	if(IsFlagThere("PUcorr")){ cutFlow->RegisterCut("PU reweighing", 2, puEfficiencyForSignal*cutFlow->GetLastCountForSignal(), puEfficiencyForQCD*cutFlow->GetLastCountForQCD()); }
	if(IsFlagThere("trigger")){ 
		cutFlow->RegisterCut("LL trigger", 2, tau1TriggerEfficiencyForSignal*cutFlow->GetLastCountForSignal(), tau1TriggerEfficiencyForQCD*cutFlow->GetLastCountForQCD()); 
		cutFlow->RegisterCut("SL trigger", 2, tau2TriggerEfficiencyForSignal*cutFlow->GetLastCountForSignal(), tau2TriggerEfficiencyForQCD*cutFlow->GetLastCountForQCD()); 
	}

	delete event; event = NULL;

}

// Set up the configured histos and add them to the process
void Plotter::BookHistos(HContainer* iHContainer){

	// Reset input HContainer
	iHContainer->clear();

	if((params.find("histoCfg")->second).length() > 0){
		LoopOverHistoCfgFile((params.find("histoCfg")->second), iHContainer);
	}else if((params.find("histoList")->second).length() > 0){

		string line;
		ifstream file((params.find("histoList")->second).c_str());
		if (file.is_open()){
			while ( file.good() ){
				getline(file, line);
				if(line.substr(0,1).compare("#")==0){ continue; }
				if(line.length()==0){ continue; }
				LoopOverHistoCfgFile(line, iHContainer);
			}
			file.close();
		}else{ cerr << "ERROR: Unable to open histoList file '" << (params.find("histoList")->second) << "'." << endl; exit(1); }
	}else{
		cerr << "ERROR: No valid histoCfg or histoList." << endl; exit(1);	
	}

}

void Plotter::LoopOverHistoCfgFile(const string iPath, HContainer* iHContainer){

		// Obtain config file where histos are configured
		if(iPath.substr(iPath.length()-4).compare(".cfg") != 0){ cerr << "ERROR: Histo config file '" << iPath << "' must have extension '.cfg'" << endl; exit(1); }
		Config histosConfigFile = Config(iPath);
		map<string, Config*> histosConfigMap = histosConfigFile.getGroups();

		string subdir = iPath.substr(0,iPath.length()-4)+"/"; subdir = subdir.substr(subdir.find("/")+1);

		// Loop over histos in config file, and add them to HContainer
		string th1fPrefix = "th1f_";
		string th2fPrefix = "th2f_";
		for (map<string, Config*>::iterator i = histosConfigMap.begin(); i != histosConfigMap.end(); ++i){
			string groupName = i->first;
			Config* histoConfig = i->second;

			if (groupName.substr(0,th1fPrefix.length()) == th1fPrefix) {
				string name	= groupName.substr(th1fPrefix.length());
				iHContainer->Add(name, HWrapper(name, subdir, "th1f", *histoConfig));
			}else if (groupName.substr(0,th2fPrefix.length()) == th2fPrefix){
				string name	= groupName.substr(th2fPrefix.length());
				iHContainer->Add(name, HWrapper(name, subdir, "th2f", *histoConfig));
			}
		}

}

// Fill the histograms with the event passed
void Plotter::FillHistos(HContainer* iHContainer, Branches* iEvent, bool const iIsMC, Trigger const * iTrigger, weightCounter* iWeightCounter){
	cerr << "Calling FillHistos(...) from " << __FILE__ << " is not allowed. It must be called from a derived class." << endl; exit(1);
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
			if(!iProPack->GetMCbackgrounds()->at(b).Plot()){ continue; }
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

/*
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
//*/

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
TPaveText * Plotter::GetPlotText(const string iString){

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
		/*textSS	<< "CMS Preliminary"
				<< "    4.9/fb" << " p-p #sqrt{s} = 7TeV"	
				<< "    #tau_{h}#tau_{h} channel"; //*/
		textSS << iString;
		plotInfo->AddText((textSS.str()).c_str());

		return plotInfo;

}

bool const Plotter::IsFlagThere(string const iFlag) const {
	string flags = params.find("flags")->second;
	size_t found = flags.find(iFlag);
	return ((0 <= found) && (found < flags.length()));
}


float const Plotter::DeltaR(const float iPhi1, const float iEta1, const float iPhi2, const float iEta2) const { return sqrt(pow((iPhi1-iPhi2),2)+pow((iEta1-iEta2),2)); }
float const Plotter::ThetaToEta(const float iTheta) const { return (-log(tan(iTheta/2.0))); }

