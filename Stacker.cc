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

	params = iParams;

	TFile* file = new TFile((params["process_file"]).c_str(), "UPDATE");
	file->cd();

	ProPack* proPack = (ProPack*)file->Get((params["propack_name"]).c_str());
	MakePlots(proPack);

	file->Close();
	delete file;
}

// Default destructor
Stacker::~Stacker(){}



// Function to make the plots
void Stacker::MakePlots(ProPack const * iProPack) const {

	// Draw horizontal error bars
 	gStyle->SetErrorX(0.5);


	// Figure out what we have and what we don't
	bool haveCollisions		= iProPack->PrepareCollisions();	
	bool haveQCD			= iProPack->PrepareQCD();
	bool haveMCbackgrounds	= iProPack->PrepareMCbackgrounds();
	bool haveSignals		= iProPack->PrepareSignals();

	// Loop over all the HWrappers and plot each
	vector<string> plotNames = iProPack->GetAvailableProcess().GetHContainerForSignal()->GetNames();
	/*
	for(unsigned int p=0; p<plotNames.size(); p++){
		string name = plotNames.at(p);

		// If the plot will be empty, skip it
		if(iProPack->GetMaxIntegral(name) <= 0){ continue; }

		// Get some generic information
		double maxY = iProPack->GetMaxY(name);
		HWrapper* baseHisto = iProPack->GetAvailableHWrapper();
		string plotName = iProPack->GetAvailableProcess()->GetHistoForSignal(p)->GetName();

		// Plot a base histogram with only the axis
		TCanvas* canvas = new TCanvas(plotName.c_str(), plotName.c_str(), 800, 800); canvas->cd();
		baseHisto->GetHisto()->GetYaxis()->SetRangeUser(0.001,maxY);
		baseHisto->Draw("AXIS");

		// If we have backgrounds, make the stack and plot them first
		if(haveQCD || haveMCbackgrounds){
			THStack* stack = iProPack->GetBackgroundStack(p);
			stack->Draw("HISTsame");
		} 

		// Then, if we have signals, plot them next
		if(haveSignals){ 
			vector<HWrapper*>* signals = iProPack->GetSignals(p);
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
			TH1* temp = iProPack->GetCollisions()->GetHistoForSignal(p)->GetHisto();
			iProPack->GetCollisions()->SetMarkerStyle(20);
			temp->Draw("EPsame");
		}	

		// Redraw the axes so they stay on top of everthing...
		baseHisto->Draw("AXISsame");

		// Take care of the legend
		GetLegend(iProPack)->Draw();

		// Save canvas
		SaveCanvas(canvas, params["stacks_output"], plotName);

		// Do we want a log version?
		SaveCanvasLog(canvas, params["stacks_output"], plotName, baseHisto->GetLogX(), baseHisto->GetLogY(), baseHisto->GetLogZ());

	string lastSavedPlotName = "";

	if(lastSavedPlotName.length()>0){
		cout << string(lastSavedPlotName.length(),'\b'); cout.flush(); 
		cout << string(lastSavedPlotName.length(),' '); cout.flush();
		cout << string(lastSavedPlotName.length(),'\b'); cout.flush(); 
	}
	cout << filename; cout.flush(); 


	}

//*/
}

/*


TLegend* Stacker::GetLegend(ProPack* iProPack){

	float xLegend	= atof((params["xLegend"]).c_str());
	float yLegend	= atof((params["yLegend"]).c_str());
	float dxLegend	= atof((params["dxLegend"]).c_str());
	float dyLegend	= atof((params["dyLegend"]).c_str());
	TLegend* result = new TLegend(xLegend-dxLegend, yLegend-dyLegend, xLegend, yLegend, NULL, "brNDC");


	// Collisions come first
	if(iProPack->PrepareCollisions()){
		TH1* temp = iProPack->GetCollisions()->GetAvailableHWrapper()->GetHisto();
		result->AddEntry(temp,(iProPack->GetCollisions()->GetLabelForLegend()).c_str(),"lep");
	}

	// QCD comes next
	if(iProPack->PrepareQCD()){
		TH1* temp = iProPack->GetQCD()->GetAvailableHWrapper()->GetHisto();
		result->AddEntry(temp,(iProPack->GetQCD()->GetLabelForLegend()).c_str(),"f");
	}

	// Then MC backgrounds in reverse order as in the vector
	for(int b = iProPack->GetMCbackgrounds()->size()-1; b >= 0; b--){
		TH1* temp = iProPack->GetMCbackgrounds()->at(b)->GetAvailableHWrapper()->GetHisto();
		result->AddEntry(temp,(iProPack->GetMCbackgrounds()->at(b)->GetLabelForLegend()).c_str(),"f");
	
	}

	// Finally signals also in reverse order as in the vector
	for(int s = iProPack->GetSignals()->size()-1; s >= 0; s--){
		TH1* temp = iProPack->GetSignals()->at(s)->GetAvailableHWrapper()->GetHisto();
		result->AddEntry(temp,(iProPack->GetSignals()->at(s)->GetLabelForLegend()).c_str(),"l");
	}

	result->SetBorderSize(1);
	result->SetFillColor(kWhite);
	result->SetFillStyle(1001);

	return result;

}

//*/



