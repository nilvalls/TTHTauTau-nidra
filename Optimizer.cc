/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			11 Jun 2011
    Description:	Plot stacking class.
    Notes:

*/

#include "Optimizer.h"

#define Optimizer_cxx
using namespace std;

#define AT __LINE__

#define FROM_LEFT 1
#define FROM_RIGHT 2

// Default constructor
Optimizer::Optimizer(map<string,string>* iParams){

//	params = *iParams;

//	ProPack* topologies = GetTopologies(params["process_file"]);	

//	MakePlots(topologies);
//	MakePlots(topologies, FROM_LEFT);
//	MakePlots(topologies, FROM_RIGHT);

}

// Default destructor
Optimizer::~Optimizer(){}

/*


// Function to make the plots
void Optimizer::MakePlots(ProPack* iTopologies, int iIntegral){

	cout << "Making optimization plots..." << endl;

	// Draw horizontal error bars
 	gStyle->SetErrorX(0.5);


	// Figure out what we have and what we don't
	bool haveQCD			= iTopologies->PrepareQCD();
	bool haveMCbackgrounds	= iTopologies->HaveMCbackgrounds();
	bool haveSignals		= iTopologies->HaveSignals();

	// If we have backgrounds, make the stack and plot them first
	if(!((haveQCD || haveMCbackgrounds) && haveSignals)){ return; }
	
	// Loop over all the HWrappers and plot each
	for(unsigned int p=0; p<iTopologies->GetNumberOfPlots(); p++){

		// Get some generic information
		HWrapper* baseHisto = iTopologies->GetAvailableHWrapper();
		string plotName = iTopologies->GetAvailableProcess()->GetHistoForSignal(p)->GetName();

		// Set up canvas
		TCanvas* canvas = new TCanvas(plotName.c_str(), plotName.c_str(), 800, 800); canvas->cd();

		// Obtain background plot
		TH1* background = iTopologies->GetBackgroundSum(p);

		vector<TH1pair> sbPlots; sbPlots.clear();
		float yMin = FLT_MAX; float yMax = -FLT_MAX;

		vector<HWrapper*>* signals = iTopologies->GetSignals(p);
		for(unsigned int s = 0; s < signals->size(); s++){

			// Obtain signal plots
			TH1* signal = signals->at(s)->GetHisto();

			// Combite s/sqrt(s+b)
			TH1pair sbPair; 
			sbPair.fromLeft		= GetSoSSB(signal, background, FROM_LEFT);
			sbPair.fromRight	= GetSoSSB(signal, background, FROM_RIGHT);
			sbPlots.push_back(sbPair);

			float thisYmax = sbPair.fromLeft->GetMaximum();
			float thisYmin = sbPair.fromLeft->GetMinimum();
			if(thisYmax > yMax){ yMax = thisYmax; }
			if(thisYmin < yMin){ yMin = thisYmin; }
			thisYmax = sbPair.fromRight->GetMaximum();
			thisYmin = sbPair.fromRight->GetMinimum();
			if(thisYmax > yMax){ yMax = thisYmax; }
			if(thisYmin < yMin){ yMin = thisYmin; }
		}

		for(unsigned int h = 0; h < sbPlots.size(); h++){
			TH1* fromLeft	= sbPlots.at(h).fromLeft;
			TH1* fromRight	= sbPlots.at(h).fromRight;
			fromLeft->SetLineColor(iTopologies->GetSignals()->at(h)->GetColor());
			fromLeft->SetLineWidth(3);
			fromLeft->GetYaxis()->SetRangeUser(yMin, 1.2*yMax);
			fromLeft->GetYaxis()->SetTitle("s / #sqrt{s+b}");
			fromRight->SetLineColor(iTopologies->GetSignals()->at(h)->GetColor());
			fromRight->SetLineWidth(3);
			fromRight->GetYaxis()->SetRangeUser(yMin, 1.2*yMax);
			fromRight->GetYaxis()->SetTitle("s / #sqrt{s+b}");
			if(h==0){
				fromLeft->Draw("HIST");
				fromRight->Draw("HISTsame");
			}else{ 
				fromLeft->Draw("HISTsame");
				fromRight->Draw("HISTsame");
			}
		}

		// Take care of the legend

		// Save canvas
		if(iIntegral == FROM_LEFT){			plotName += "_intFromLeft";	}
		else if(iIntegral == FROM_RIGHT){	plotName += "_intFromRight";}
		SaveCanvas(canvas, params["optimization_output"], plotName);
	}
}


TH1* Optimizer::GetSoSSB(TH1* iSignal, TH1* iBackground, int iIntegral){
	TH1* result = NULL;

	HMath integrator;

	TH1* signalPlot = NULL;
	TH1* backgroundPlot = NULL;

	if(iIntegral == FROM_LEFT){
		signalPlot		= integrator.IntegrateFromLeft((TH1F*)iSignal);
		backgroundPlot	= integrator.IntegrateFromLeft((TH1F*)iBackground);
	}else if(iIntegral == FROM_RIGHT){
		signalPlot		= integrator.IntegrateFromRight((TH1F*)iSignal);
		backgroundPlot	= integrator.IntegrateFromRight((TH1F*)iBackground);
	}else{
		signalPlot		= iSignal;
		backgroundPlot	= iBackground;
	}

	for(unsigned int bin = 0; bin < signalPlot->GetNbinsX(); bin++){
		result = (TH1*)signalPlot->Clone();
		float signal		= signalPlot->GetBinContent(bin);	
		float background	= backgroundPlot->GetBinContent(bin);	
		float significance	= 0;
		if((signal+background) != 0){ significance = signal/sqrt(signal+background); }
		result->SetBinContent(bin, significance);
	}

	return result;
}
//*/

