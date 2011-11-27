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
Stacker::Stacker(map<string,string>* iParams){

	params = *iParams;

	TopoPack* topologies = GetTopologies(params["topology_file"]);	

	MakePlots(topologies);

}

// Default destructor
Stacker::~Stacker(){}


// Function to make the plots
void Stacker::MakePlots(TopoPack* iTopologies){

	cout << "Making plots..." << endl;

	// Draw horizontal error bars
 	gStyle->SetErrorX(0.5);


	// Figure out what we have and what we don't
	bool haveCollisions		= iTopologies->PrepareCollisions();	
	bool haveQCD			= iTopologies->PrepareQCD();
	bool haveMCbackgrounds	= iTopologies->HaveMCbackgrounds();
	bool haveSignals		= iTopologies->HaveSignals();

	// Loop over all the HistoWrappers and plot each
	for(unsigned int p=0; p<iTopologies->GetNumberOfPlots(); p++){

		// Get some generic information
		double maxY = iTopologies->GetMaxY(p);
		HistoWrapper* baseHisto = iTopologies->GetAvailableHistoWrapper();
		string plotName = iTopologies->GetAvailableTopology()->GetHistoForSignal(p)->GetName();

		// Plot a base histogram with only the axis
		TCanvas* canvas = new TCanvas(plotName.c_str(), plotName.c_str(), 800, 800); canvas->cd();
		baseHisto->GetHisto()->GetYaxis()->SetRangeUser(0.001,maxY);
		baseHisto->Draw("AXIS");

		// If we have backgrounds, make the stack and plot them first
		if(haveQCD || haveMCbackgrounds){
			THStack* stack = iTopologies->GetBackgroundStack(p);
			stack->Draw("HISTsame");
		} 

		// Then, if we have signals, plot them next
		if(haveSignals){ 
			vector<HistoWrapper*>* signals = iTopologies->GetSignals(p);
			for(unsigned int s = 0; s < signals->size(); s++){
				signals->at(s)->SetFillStyle(0);	
				signals->at(s)->SetLineWidth(3);	
				TH1* temp = signals->at(s)->GetHisto();
				temp->GetYaxis()->SetRangeUser(0.001, maxY);
				temp->Draw("HISTsame");
			}
		}
		
		// Finally plot the collisions if we have them
		if(haveCollisions){ 
			TH1* temp = iTopologies->GetCollisions()->GetHistoForSignal(p)->GetHisto();
			iTopologies->GetCollisions()->SetMarkerStyle(20);
			temp->Draw("EPsame");
		}	

		// Redraw the axes so they stay on top of everthing...
		baseHisto->Draw("AXISsame");

		// Take care of the legend
		GetLegend(iTopologies)->Draw();

		// Save canvas
		SaveCanvas(canvas, plotName);

		// Do we want a log version?
		SaveCanvasLog(canvas, plotName, baseHisto);

	}

}

// Check to see if we want this a copy of a plot with some log scales
void Stacker::SaveCanvasLog(TCanvas* iCanvas, string iPlotName, HistoWrapper* iRefHisto){
	bool logx = iRefHisto->GetLogX();
	bool logy = iRefHisto->GetLogY();
	bool logz = iRefHisto->GetLogZ();

	if(logx || logy || logz ){
		iCanvas->SetLogx(logx); 
		iCanvas->SetLogy(logy); 
		iCanvas->SetLogz(logz); 
		SaveCanvas(iCanvas, string(iPlotName+"_log"));
		iCanvas->SetLogx(0);
		iCanvas->SetLogy(0);
		iCanvas->SetLogz(0);
	}   
}




// Save canvas
void Stacker::SaveCanvas(TCanvas* canvas, string filename){

	string dir = params["stacks_output"];
	string lastSavedPlotName = "";

	if(lastSavedPlotName.length()>0){
		cout << string(lastSavedPlotName.length(),'\b'); cout.flush(); 
		cout << string(lastSavedPlotName.length(),' '); cout.flush();
		cout << string(lastSavedPlotName.length(),'\b'); cout.flush(); 
	}
	cout << filename; cout.flush();

	// Create output dir if it doesn't exists already
	TString sysCommand = "if [ ! -d " + dir + " ]; then mkdir -p " + dir + "; fi";
	if(gSystem->Exec(sysCommand) > 0){ cout << ">>> ERROR: problem creating dir for plots " << dir << endl; exit(1); }// exit(0);

	// Loop over all file format extensions choosen and save canvas
	vector<string> extension; extension.push_back(".png");
	for( unsigned int ext = 0; ext < extension.size(); ext++){
		canvas->SaveAs( (dir + filename + extension.at(ext)).c_str() );
	}

	lastSavedPlotName = filename;

}


TLegend* Stacker::GetLegend(TopoPack* iTopologies){

	float xLegend	= atof((params["xLegend"]).c_str());
	float yLegend	= atof((params["yLegend"]).c_str());
	float dxLegend	= atof((params["dxLegend"]).c_str());
	float dyLegend	= atof((params["dyLegend"]).c_str());
	TLegend* result = new TLegend(xLegend-dxLegend, yLegend-dyLegend, xLegend, yLegend, NULL, "brNDC");


	// Collisions come first
	if(iTopologies->PrepareCollisions()){
		TH1* temp = iTopologies->GetCollisions()->GetAvailableHistoWrapper()->GetHisto();
		result->AddEntry(temp,(iTopologies->GetCollisions()->GetLabelForLegend()).c_str(),"lep");
	}

	// QCD comes next
	if(iTopologies->PrepareQCD()){
		TH1* temp = iTopologies->GetQCD()->GetAvailableHistoWrapper()->GetHisto();
		result->AddEntry(temp,(iTopologies->GetQCD()->GetLabelForLegend()).c_str(),"f");
	}

	// Then MC backgrounds in reverse order as in the vector
	for(int b = iTopologies->GetMCbackgrounds()->size()-1; b >= 0; b--){
		TH1* temp = iTopologies->GetMCbackgrounds()->at(b)->GetAvailableHistoWrapper()->GetHisto();
		result->AddEntry(temp,(iTopologies->GetMCbackgrounds()->at(b)->GetLabelForLegend()).c_str(),"f");
	
	}

	// Finally signals also in reverse order as in the vector
	for(int s = iTopologies->GetSignals()->size()-1; s >= 0; s--){
		TH1* temp = iTopologies->GetSignals()->at(s)->GetAvailableHistoWrapper()->GetHisto();
		result->AddEntry(temp,(iTopologies->GetSignals()->at(s)->GetLabelForLegend()).c_str(),"l");
	}

	result->SetBorderSize(1);
	result->SetFillColor(kWhite);
	result->SetFillStyle(1001);

	return result;

}





