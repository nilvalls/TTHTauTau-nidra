/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			11 Jun 2011
    Description:	Plot stacking class.
    Notes:

*/

#include "Stacker.h"

#define Stacker_cxx
using namespace std;

#define AT __LINE__

// Default constructor
Stacker::Stacker(map<string,string> const & iParams){

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
Stacker::~Stacker(){
	if(file!=NULL){ file->Close(); }
	delete file; file = NULL;
	delete proPack; proPack = NULL;

}

// Function to make the plots
void Stacker::MakePlots(ProPack const * iProPack) {

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
		if(GetMaxIntegral(iProPack, plotName) <= 0){ continue; }

		// Get some generic information
		double maxY = max(1.2*GetMaximumWithError(iProPack, plotName),0.1);
		HWrapper baseHisto((iProPack->GetAvailableHWrapper(plotName))); baseHisto.ScaleBy(0);
		subdir = baseHisto.GetSubDir();

		// Skip if 2D (gotta change this)
		if(baseHisto.IsTH2F()){ continue; }

		// Plot a base histogram with only the axis
		TCanvas* canvas = new TCanvas(plotName.c_str(), plotName.c_str(), 800, 800); canvas->cd();
		baseHisto.GetHisto()->GetYaxis()->SetRangeUser(0.001,maxY);

		// If we have backgrounds, make the stack and plot them first
		THStack* stack = NULL;
		if(haveQCD || haveMCbackgrounds){ stack = GetBackgroundStack(iProPack, plotName); } 

		// Now draw the axis from scratch using the baseHisto
		canvas->SetGrid(1,1);
		baseHisto.GetHisto()->Draw("HIST");

		// Draw stack if we have backgrounds
		if((stack != NULL) ){
			HWrapper backgroundSum = HWrapper(GetBackgroundSum(iProPack, plotName));
			if(backgroundSum.GetHisto()->Integral()>0){
				stack->Draw("HISTsame"); 
				// Draw background errors if we want them
				if(params["showBackgroundError"].compare("true")==0){
					backgroundSum.SetFillStyle(3004,kBlack);
					backgroundSum.SetMarkerStyle(0);
					backgroundSum.GetHisto()->Draw("E2same");
				}
			}
		}

		//TFile* file = new TFile("./test.root","RECREATE");
		//file->cd();
		// Then, if we have signals, plot them next
		if(haveSignals){
			HContainer signalHistos = iProPack->GetSignalsHWrappers(plotName);
			for(unsigned int s = 0; s < signalHistos.size(); s++){
				if(!iProPack->GetSignals()->at(s).Plot()){ continue; }
				string name = signalHistos.GetNames().at(s);
				HWrapper* toDraw = new HWrapper(*signalHistos.Get(name));
				toDraw->SetFillStyle(0);	
				toDraw->SetLineWidth(3, iProPack->GetSignals()->at(s).GetColor());	
				toDraw->GetHisto()->GetYaxis()->SetRangeUser(0.001, maxY);

				// If we want the signals on top of the stack, add the background sum
				if(stackSignals){ toDraw->Add(GetBackgroundSum(iProPack, plotName)); }

				// Draw signal curves
				if(toDraw->GetHisto()->Integral()>0){
					toDraw->GetHisto()->Draw("HISTsame"); }

				TH1F* histo = new TH1F(*(TH1F*)(toDraw->GetHisto()));
				histo->GetXaxis()->SetRangeUser(0,2000);
				//histo->Write();
			}
		}

		//file->Close();

		
		// Finally plot the collisions if we have them
		if(haveCollisions){ 
			if(!iProPack->GetCollisions()->Plot()){ continue; }
			HWrapper collisionsHisto = HWrapper(*iProPack->GetCollisions()->GetHContainerForSignal()->Get(plotName));
			collisionsHisto.SetMarkerStyle(20);
			collisionsHisto.GetHisto()->GetYaxis()->SetRangeUser(0.001, maxY);
			if(collisionsHisto.GetHisto()->Integral()>0){ collisionsHisto.GetHisto()->Draw("EPsame"); }
		}	

		// Redraw the axes so they stay on top of everthing...
		baseHisto.GetHisto()->Draw("AXISsame");

		// Take care of the legend
		GetLegend(iProPack)->Draw();

		// Take care of plot info
		GetPlotText()->Draw();

		// Save canvas
		canvas->SetGrid(1,1);
		SaveCanvas(canvas, params["stacks_output"]+subdir, plotName);

		// Do we want a log version?
		SaveCanvasLog(canvas, params["stacks_output"]+subdir, plotName, baseHisto.GetLogX(), baseHisto.GetLogY(), baseHisto.GetLogZ());

		// Clean up canvas
		delete canvas;
		stack = NULL; delete stack;

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




TLegend* Stacker::GetLegend(ProPack const * iProPack){

	// Figure out how many rows we're going to have
	int numberOfRows = 0;
	if(iProPack->PrepareCollisions()){ numberOfRows++; }
	if(iProPack->PrepareQCD()){ numberOfRows++; }
	numberOfRows += iProPack->GetMCbackgrounds()->size();
	numberOfRows += iProPack->GetSignals()->size();
	if(((iProPack->PrepareQCD()) || (iProPack->GetMCbackgrounds()->size() > 0)) && (params["showBackgroundError"].compare("true")==0)){ numberOfRows++; }

	// Get legend sizes
	float xLegend	= atof((params["xLegend"]).c_str());
	float yLegend	= atof((params["yLegend"]).c_str());
	float dxLegend	= atof((params["dxLegend"]).c_str());
	//float dyLegend	= atof((params["dyLegend"]).c_str());
	float dyLegend	= 0.035*numberOfRows;
	TLegend* result = new TLegend(xLegend-dxLegend, yLegend-dyLegend, xLegend, yLegend, NULL, "brNDC");


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
	}

	// Then MC backgrounds in reverse order as in the vector
	for(int b = iProPack->GetMCbackgrounds()->size()-1; b >= 0; b--){
		HWrapper * temp = new HWrapper(*iProPack->GetMCbackgrounds()->at(b).GetAvailableHWrapper());
		temp->SetFillStyle(1001,iProPack->GetMCbackgrounds()->at(b).GetColor());
		temp->SetLineWidth(0);
		result->AddEntry(temp->GetHisto(),(iProPack->GetMCbackgrounds()->at(b).GetLabelForLegend()).c_str(),"f");
	}

	// Background errors if we want them and have them
	if(((iProPack->PrepareQCD()) || (iProPack->GetMCbackgrounds()->size() > 0)) && (params["showBackgroundError"].compare("true")==0)){
		HWrapper * temp = new HWrapper(GetBackgroundSum(iProPack, iProPack->GetAvailableHWrapper().GetName()));
		temp->SetFillStyle(3004,kBlack);
		temp->SetLineWidth(0);
		result->AddEntry(temp->GetHisto(),"Bkg. stat. err. ","f");
	}

	// Finally signals also in reverse order as in the vector
	for(int s = iProPack->GetSignals()->size()-1; s >= 0; s--){
		HWrapper * temp = new HWrapper(*iProPack->GetSignals()->at(s).GetAvailableHWrapper());
		temp->SetFillStyle(0,0);
		temp->SetLineWidth(3,iProPack->GetSignals()->at(s).GetColor());
		result->AddEntry(temp->GetHisto(),(iProPack->GetSignals()->at(s).GetLabelForLegend()).c_str(),"l");
	}

	// Set some legend parameters
	result->SetBorderSize(1);
	result->SetFillColor(kWhite);
	result->SetFillStyle(1001);

	return result;

}

// Make background stack
THStack * Stacker::GetBackgroundStack(ProPack const * iProPack, string const iName) const {

	// Obtain a reference HWrapper from which to extract options
	HWrapper refHisto = HWrapper(*(iProPack->GetAvailableProcess().GetHistoForSignal(iName)));
	if(refHisto.IsTH2F()){ cerr << "ERROR: trying to build THStack from TH2F with plot named '" << iName << "'" << endl; exit(1); }

	// Figure out the maximum Y value
	double maxY = max(1.2*GetMaximumWithError(iProPack,iName),0.1);
	string stackName = string(iName+"_stack");
	THStack * result = new THStack(stackName.c_str(), stackName.c_str());

	// Add each MC background first if we have them
	if(iProPack->PrepareMCbackgrounds()){
		for(unsigned int b = 0; b < iProPack->GetMCbackgrounds()->size(); b++){
			if(!iProPack->GetMCbackgrounds()->at(b).Plot()){ continue; }
			int color = iProPack->GetMCbackgrounds()->at(b).GetColor();
			HWrapper toAdd(*(iProPack->GetMCbackgrounds()->at(b).GetHistoForSignal(iName)));
			toAdd.SetFillStyle(1001,color);
			toAdd.SetLineWidth(0,color);
			toAdd.GetHisto()->GetYaxis()->SetRangeUser(0.001,maxY);
			toAdd.GetHisto()->GetXaxis()->SetRangeUser(toAdd.GetMinXVis(), toAdd.GetMaxXVis());
			result->Add((TH1F*)toAdd.GetHisto());
		}
	}

	// Then add QCD if we have it
	if(iProPack->PrepareQCD()){
		int color = iProPack->GetQCD()->GetColor();
		HWrapper toAdd(*(iProPack->GetQCD()->GetHistoForSignal(iName)));
		toAdd.SetFillStyle(1001,color);
		toAdd.SetLineWidth(0,color);
		toAdd.GetHisto()->GetYaxis()->SetRangeUser(0.001,maxY);
		toAdd.GetHisto()->GetXaxis()->SetRangeUser(toAdd.GetMinXVis(), toAdd.GetMaxXVis());
		result->Add((TH1F*)toAdd.GetHisto());
	}

	// Must call Draw before setting the options below
	result->Draw("HIST");

	result->GetXaxis()->SetRangeUser(refHisto.GetMinXVis(), refHisto.GetMaxXVis());
	result->GetXaxis()->SetTitle((refHisto.GetXTitle()).c_str());
	result->GetYaxis()->SetTitle((refHisto.GetYTitle()).c_str());
	result->SetMinimum(0.001);
	result->SetMaximum(maxY);
	result->GetYaxis()->SetRangeUser(0.001,maxY);

	return result;
}


// Figure out the maximum y value
double const Stacker::GetMaximum(ProPack const * iProPack, string const iName) const { return GetMaximum(iProPack, iName, false); }
double const Stacker::GetMaximumWithError(ProPack const * iProPack, string const iName) const { return GetMaximum(iProPack, iName, true); }
double const Stacker::GetMaximum(ProPack const * iProPack, string const iName, bool const iIncludeError) const {
	double result = 0;

	// Check max y for collisions
	if(iProPack->PrepareCollisions()){
		double thisMax = 0; 
		if(iIncludeError){	thisMax = iProPack->GetCollisions()->GetHistoForSignal(iName)->GetMaximumWithError(); }	
		else{				thisMax = iProPack->GetCollisions()->GetHistoForSignal(iName)->GetMaximum(); }	
		if(thisMax > result){ result = thisMax; }
	}

	// Check max y for backgrounds
	if(iProPack->PrepareQCD() || iProPack->PrepareMCbackgrounds()){
		double thisMax = 0;
		if(iIncludeError){	thisMax = GetBackgroundSum(iProPack, iName).GetMaximumWithError(); }
		else{				thisMax = GetBackgroundSum(iProPack, iName).GetMaximum(); }
		if(thisMax > result){ result = thisMax; }
	}

	// Check max y for signals
	bool stackSignals		= ((string(params.find("stackSignals")->second)).compare("true")==0);
	if(iProPack->PrepareSignals()){
		for(unsigned int s = 0; s < iProPack->GetSignals()->size(); s++){
			double thisMax = iProPack->GetSignals()->at(s).GetHistoForSignal(iName)->GetMaximum();

			// If we have backgrounds AND we want to stack the signals on them, account for that
			if((iProPack->PrepareQCD() || iProPack->PrepareMCbackgrounds()) && stackSignals){
				thisMax += GetBackgroundSum(iProPack, iName).GetMaximum();
			}

			if(thisMax > result){ result = thisMax; }
		}
	}
	
	return result;
}

