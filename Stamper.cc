/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			11 Jun 2011
    Description:	Plot stacking class.
    Notes:

*/

#include "Stamper.h"

#define Stamper_cxx
using namespace std;

#define AT __LINE__

// Default constructor
Stamper::Stamper(map<string,string> const & iParams){

	params = map<string,string>(iParams);

	Long_t *id,*size,*flags,*mt; id=NULL; size=NULL;flags=NULL;mt=NULL;
	bool badFile = gSystem->GetPathInfo((params["process_file"]).c_str(),id,size,flags,mt);
	if(badFile){ cerr << "ERROR: trying to stack plots but proPack file does not exist. Please run the event analysis first" << endl; exit(1); }

	file = new TFile((params["process_file"]).c_str(), "UPDATE");
	file->cd();

	proPack = (ProPack*)file->Get((params["propack_name"]).c_str());
	MakePlots(proPack);
}

// Default destructor
Stamper::~Stamper(){}

// Function to make the plots
void Stamper::MakePlots(ProPack * iProPack) {

	// Draw horizontal error bars
 	gStyle->SetErrorX(0.5);

	// Figure out what we have and what we don't
	bool haveCollisions		= iProPack->PrepareCollisions();	
	bool haveQCD			= iProPack->PrepareQCD();
	bool haveMCbackgrounds	= iProPack->PrepareMCbackgrounds();
	bool haveSignals		= iProPack->PrepareSignals();
	bool stackSignals		= (params["stackSignals"].compare("true")==0);

	// Loop over all the HWrappers and plot each
	vector<string> plotNames = iProPack->GetAvailableProcess().GetHContainerForSignal()->GetNames();

	string subdir = "";
	string lastSavedPlotName = "";
	for(unsigned int p=0; p<plotNames.size(); p++){
		string plotName = plotNames.at(p);

		// If the plot will be empty, skip it
		if(GetMaxIntegral(iProPack, plotName) <= 0){
			cout << "\nWARNING: HWrapper with name '" << plotName << 
					"' not filled. Perhaps it's a good idea to remove it from '" << 
					string((iProPack->GetAvailableHWrapper(plotName)).GetSubDir()+"\b.cfg") << "'." << endl;
			continue;
		}
		

		// Get some generic information
		double maxY = 1.2*GetMaximum(iProPack, plotName);
		HWrapper baseHisto((iProPack->GetAvailableHWrapper(plotName))); baseHisto.ScaleBy(0);
		subdir = baseHisto.GetSubDir();

		// Plot a base histogram with only the axis
		TCanvas* canvas = new TCanvas(plotName.c_str(), plotName.c_str(), 800, 800); canvas->cd();
		baseHisto.GetHisto()->GetYaxis()->SetRangeUser(0.001,maxY);

		// Now draw the axis from scratch using the baseHisto
		canvas->SetGrid(1,1);
		baseHisto.GetHisto()->GetYaxis()->SetTitle("A.U.");
		baseHisto.GetHisto()->Draw("HIST");

		// If we have signals, plot them next
		/*if(haveSignals){
			HContainer signalHistos = iProPack->GetSignalsHWrappers(plotName);
			for(unsigned int s = 0; s < signalHistos.size(); s++){
				string name = signalHistos.GetNames().at(s);
				HWrapper* toDraw = new HWrapper(*signalHistos.Get(name));
				toDraw->NormalizeTo(1.0);
				toDraw->SetFillStyle(0);	
				toDraw->SetLineWidth(3, iProPack->GetSignals()->at(s).GetColor());	
				toDraw->GetHisto()->GetYaxis()->SetRangeUser(0.001, maxY);
				if(toDraw->GetHisto()->Integral()>0){ toDraw->GetHisto()->Draw("HISTsame"); }
			}
		}//*/
				Process* signalToOptimize = iProPack->GetProcess(params.find("signalToOptimize")->second);
				HWrapper* toDrawS = new HWrapper(*(signalToOptimize->GetHistoForSignal(plotName)));
				toDrawS->NormalizeTo(1.0);
				toDrawS->SetFillStyle(0);	
				toDrawS->SetLineWidth(3, signalToOptimize->GetColor());
				toDrawS->GetHisto()->GetYaxis()->SetRangeUser(0.001, maxY);
				if(toDrawS->GetHisto()->Integral()>0){
					HWrapper* toDrawSerror = new HWrapper(*toDrawS);
					toDrawSerror->SetMarkerStyle(0);
					toDrawSerror->SetFillStyle(3001, signalToOptimize->GetColor());
					toDrawSerror->GetHisto()->Draw("E2same");
					toDrawS->GetHisto()->Draw("HISTsame");
				}

		// If we have backgrounds, plot them next
		/*if(haveMCbackgrounds){
			HContainer backgroundHistos = iProPack->GetMCbackgroundsHWrappers(plotName);
			for(unsigned int b = 0; b < backgroundHistos.size(); b++){
				string name = backgroundHistos.GetNames().at(b);
				HWrapper* toDraw = new HWrapper(*backgroundHistos.Get(name));
				toDraw->NormalizeTo(1.0);
				toDraw->SetFillStyle(0);	
				toDraw->SetLineWidth(3, iProPack->GetMCbackgrounds()->at(b).GetColor());	
				toDraw->GetHisto()->GetYaxis()->SetRangeUser(0.001, maxY);
				if(toDraw->GetHisto()->Integral()>0){ toDraw->GetHisto()->Draw("Psame"); }
			}
		}//*/
			Process* backgroundToOptimize = iProPack->GetProcess(params.find("backgroundToOptimize")->second);
			HWrapper* toDrawB = new HWrapper(*(backgroundToOptimize->GetHistoForSignal(plotName)));
			toDrawB->NormalizeTo(1.0);
			toDrawB->SetFillStyle(0);	
			toDrawB->GetHisto()->SetMarkerColor(backgroundToOptimize->GetColor());
			toDrawB->SetLineWidth(3, backgroundToOptimize->GetColor());
			toDrawB->GetHisto()->GetYaxis()->SetRangeUser(0.001, maxY);
			if(toDrawB->GetHisto()->Integral()>0){ toDrawB->GetHisto()->Draw("Psame"); }
		
		// Finally plot the collisions if we have them
		/*if(haveCollisions){ 
			if(!iProPack->GetCollisions()->Plot()){ continue; }
			HWrapper collisionsHisto = HWrapper(*iProPack->GetCollisions()->GetHContainerForSignal()->Get(plotName));
			collisionsHisto.SetMarkerStyle(20);
			collisionsHisto.GetHisto()->GetYaxis()->SetRangeUser(0.001, maxY);
			if(collisionsHisto.GetHisto()->Integral()>0){ collisionsHisto.GetHisto()->Draw("EPsame"); }
		}	//*/

		// Redraw the axes so they stay on top of everthing...
		baseHisto.GetHisto()->Draw("AXISsame");

		// Take care of the legend
		GetLegend(signalToOptimize, backgroundToOptimize)->Draw();

		// Take care of plot info
		GetPlotText(params.find("plotText")->second)->Draw();

		// Save canvas
		canvas->SetGrid(1,1);
		SaveCanvas(canvas, params["stamps_output"]+subdir, plotName);

		// Do we want a log version?
		SaveCanvasLog(canvas, params["stamps_output"]+subdir, plotName, baseHisto.GetLogX(), baseHisto.GetLogY(), baseHisto.GetLogZ());

		// Clean up canvas
		delete canvas;

		// Print info about the current histo
		lastSavedPlotName = plotName;

		if(lastSavedPlotName.length()>0){
			cout << string(lastSavedPlotName.length()+1,'\b'); cout.flush(); 
			cout << string(lastSavedPlotName.length()+1,' '); cout.flush();
			cout << string(lastSavedPlotName.length()+1,'\b'); cout.flush(); 
		}
		cout << plotName; cout.flush(); 
	}

	// Print done
	if(lastSavedPlotName.length()>0){
			cout << string(lastSavedPlotName.length()+1,'\b'); cout.flush(); 
			cout << string(lastSavedPlotName.length()+1,' '); cout.flush();
			cout << string(lastSavedPlotName.length()+1,'\b'); cout.flush(); 
	}

}




TLegend* Stamper::GetLegend(Process const * iSignal, Process const * iBackground){

	// Figure out how many rows we're going to have
	int numberOfRows = 2;
/*	if(iProPack->PrepareCollisions()){ numberOfRows++; }
	if(iProPack->PrepareQCD()){ numberOfRows++; }
	numberOfRows += iProPack->GetMCbackgrounds()->size();
	numberOfRows += iProPack->GetSignals()->size();//*/

	// Get legend sizes
	float xLegend	= atof((params["xLegend"]).c_str());
	float yLegend	= atof((params["yLegend"]).c_str());
	float dxLegend	= atof((params["dxLegend"]).c_str());
	//float dyLegend	= atof((params["dyLegend"]).c_str());
	float dyLegend	= 0.035*numberOfRows;
	TLegend* result = new TLegend(xLegend-dxLegend, yLegend-dyLegend, xLegend, yLegend, NULL, "brNDC");


	/*
	// Collisions come first
	if(iProPack->PrepareCollisions()){
		TH1 const * temp = iProPack->GetCollisions()->GetAvailableHWrapper()->GetHisto();
		result->AddEntry(temp,(iProPack->GetCollisions()->GetLabelForLegend()).c_str(),"lep");
	}

	// QCD comes next
	if(iProPack->PrepareQCD()){
		HWrapper * temp = new HWrapper(*iProPack->GetQCD()->GetAvailableHWrapper());
		temp->SetFillStyle(1001,iProPack->GetQCD()->GetColor());
		temp->SetLineWidth(0);
		result->AddEntry(temp->GetHisto(),(iProPack->GetQCD()->GetLabelForLegend()).c_str(),"f");
		delete temp;
	}//*/

	// Then MC background
	HWrapper* tempB = new HWrapper(*iBackground->GetAvailableHWrapper());
	tempB->SetFillStyle(1001,iBackground->GetColor());
	tempB->SetLineWidth(3);
	tempB->GetHisto()->SetMarkerColor(iBackground->GetColor());
	tempB->SetLineWidth(3, iBackground->GetColor());
	result->AddEntry(tempB->GetHisto(),(iBackground->GetLabelForLegend()).c_str(),"lep");

	HWrapper * tempS = new HWrapper(*iSignal->GetAvailableHWrapper());
	tempS->SetFillStyle(3001,iSignal->GetColor());
	tempS->SetLineWidth(3);
	tempS->SetLineWidth(3, iSignal->GetColor());
	result->AddEntry(tempS->GetHisto(),(iSignal->GetLabelForLegend()).c_str(),"lf");


	// Finally signals also in reverse order as in the vector
	/*for(int s = iProPack->GetSignals()->size()-1; s >= 0; s--){
		HWrapper * temp = new HWrapper(*iProPack->GetSignals()->at(s).GetAvailableHWrapper());
		temp->SetFillStyle(0,0);
		temp->SetLineWidth(3,iProPack->GetSignals()->at(s).GetColor());
		result->AddEntry(temp->GetHisto(),(iProPack->GetSignals()->at(s).GetLabelForLegend()).c_str(),"l");
	}//*/

	// Set some legend parameters
	result->SetBorderSize(1);
	result->SetFillColor(kWhite);
	result->SetFillStyle(1001);

	return result;

}

// Figure out the maximum y value
double const Stamper::GetMaximum(ProPack const * iProPack, string const iName) const { return GetMaximum(iProPack, iName, false); }
double const Stamper::GetMaximumWithError(ProPack const * iProPack, string const iName) const { return GetMaximum(iProPack, iName, true); }
double const Stamper::GetMaximum(ProPack const * iProPack, string const iName, bool const iIncludeError) const {
	double result = 0;

	// Check max y for collisions
	if(iProPack->PrepareCollisions()){
		double thisMax = 0; 
		if(iIncludeError){	thisMax = iProPack->GetCollisions()->GetHistoForSignal(iName)->GetMaximumWithError(); }	
		else{				thisMax = iProPack->GetCollisions()->GetHistoForSignal(iName)->GetMaximum(); }	
		if(thisMax > result){ result = thisMax; }
	}

	// Check max y for backgrounds
	if(iProPack->PrepareMCbackgrounds()){
		for(unsigned int b = 0; b < iProPack->GetMCbackgrounds()->size(); b++){
			HWrapper tmpHWrapper(*(iProPack->GetMCbackgrounds()->at(b).GetHistoForSignal(iName)));
			tmpHWrapper.NormalizeTo(1.0);
			double thisMax = tmpHWrapper.GetMaximum();
			if(thisMax > result){ result = thisMax; }
		}
	}

	// Check max y for signals
	if(iProPack->PrepareSignals()){
		for(unsigned int s = 0; s < iProPack->GetSignals()->size(); s++){
			HWrapper tmpHWrapper(*(iProPack->GetSignals()->at(s).GetHistoForSignal(iName)));
			tmpHWrapper.NormalizeTo(1.0);
			double thisMax = tmpHWrapper.GetMaximum();
			if(thisMax > result){ result = thisMax; }
		}
	}
	
	return result;
}

