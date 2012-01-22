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

#define NON_INTEGRATED 0
#define INTEGRATED_FROM_LEFT 1
#define INTEGRATED_FROM_RIGHT 2

// Constructor
Optimizer::Optimizer(map<string,string> const & iParams){

	params = map<string,string>(iParams);

	Long_t *id,*size,*flags,*mt; id=NULL; size=NULL;flags=NULL;mt=NULL;
	bool badFile = gSystem->GetPathInfo((params["process_file"]).c_str(),id,size,flags,mt);
	if(badFile){ cerr << "ERROR: trying to make optimization plots but proPack file does not exist. Please run the event analysis first" << endl; exit(1); }

	file = new TFile((params["process_file"]).c_str(), "UPDATE");
	file->cd();

	proPack = (ProPack*)file->Get((params["propack_name"]).c_str());
	MakePlots(proPack);
}


// Default destructor
Optimizer::~Optimizer(){
	if(file!=NULL){ file->Close(); }
	delete file; file = NULL;
	delete proPack; proPack = NULL;
}

void Optimizer::MakePlots(ProPack const * iProPack) {
	MakeLeftIntegratedSoverB(&(iProPack->GetSignals()->at(0)), iProPack->GetQCD());
	MakeRightIntegratedSoverB(&(iProPack->GetSignals()->at(0)), iProPack->GetQCD());
	MakeSoverB(&(iProPack->GetSignals()->at(0)), iProPack->GetQCD());
}

void Optimizer::MakeLeftIntegratedSoverB(Process const * iSignal, Process const * iBackground){ MakeIntegratedSoverB(iSignal, iBackground, INTEGRATED_FROM_LEFT); }
void Optimizer::MakeRightIntegratedSoverB(Process const * iSignal, Process const * iBackground){ MakeIntegratedSoverB(iSignal, iBackground, INTEGRATED_FROM_RIGHT); }
void Optimizer::MakeIntegratedSoverB(Process const * iSignal, Process const * iBackground, int iIntegrate){

	// Draw horizontal error bars
 	gStyle->SetErrorX(0.5);

	// Histogram math class
	HMath hmath;

	// Loop over all the HWrappers and plot each
	vector<string> plotNames = iSignal->GetHContainerForSignal()->GetNames();

	string lastSavedPlotName = "";
	for(unsigned int p=0; p<plotNames.size(); p++){
		string plotName = plotNames.at(p);
		cout << __FILE__ << ":" << __LINE__ << endl;

		// If the plot will be empty, skip it
		if(max(iSignal->GetAvailableHWrapper()->GetHisto()->Integral(), iBackground->GetAvailableHWrapper()->GetHisto()->Integral()) <= 0){ continue; }

		cout << __FILE__ << ":" << __LINE__ << endl;
		// Skip it if it's not a TH1F
		if(!iSignal->GetAvailableHWrapper()->IsTH1F()){ continue; }
		cout << __FILE__ << ":" << __LINE__ << endl;

		// Get HWrappers, obtain sOverRootB
		HWrapper signal = HWrapper(*(iSignal->GetHistoForSignal(plotName)));
		cout << __FILE__ << ":" << __LINE__ << endl;
		HWrapper background = HWrapper(*(iBackground->GetHistoForSignal(plotName)));
		cout << __FILE__ << ":" << __LINE__ << endl;
		HWrapper rightIntegratedSoverRootB = HWrapper(signal);
		cout << __FILE__ << ":" << __LINE__ << endl;
		HWrapper leftIntegratedSoverRootB = HWrapper(signal);
		cout << __FILE__ << ":" << __LINE__ << endl;

		rightIntegratedSoverRootB.SetHisto(hmath.RightIntegratedStoRootB((TH1F*)(signal.GetHisto()), (TH1F*)(background.GetHisto())));
		cout << __FILE__ << ":" << __LINE__ << endl;
		leftIntegratedSoverRootB.SetHisto(hmath.LeftIntegratedStoRootB((TH1F*)(signal.GetHisto()), (TH1F*)(background.GetHisto())));


		cout << __FILE__ << ":" << __LINE__ << endl;
		// Reset maxima
		signal.ResetMaximum();
		background.ResetMaximum();
		rightIntegratedSoverRootB.ResetMaximum();
		leftIntegratedSoverRootB.ResetMaximum();

		// Set line width and color
		signal.SetLineWidth(3, iSignal->GetColor());
		background.SetLineWidth(3, iBackground->GetColor());
		rightIntegratedSoverRootB.SetLineWidth(3, kViolet);
		leftIntegratedSoverRootB.SetLineWidth(3, kOrange+8);

		// Make copies for errors
		HWrapper signalError = HWrapper(signal); signalError.SetFillStyle(3004, iSignal->GetColor());
		HWrapper backgroundError = HWrapper(background); backgroundError.SetFillStyle(3004, iBackground->GetColor());
		HWrapper rightIntegratedSoverRootBerror = HWrapper(rightIntegratedSoverRootB); rightIntegratedSoverRootBerror.SetFillStyle(3004,kViolet);
		HWrapper leftIntegratedSoverRootBerror = HWrapper(leftIntegratedSoverRootB); leftIntegratedSoverRootBerror.SetFillStyle(3005,kOrange+8);
		rightIntegratedSoverRootBerror.ResetMaximum();
		leftIntegratedSoverRootBerror.ResetMaximum();

		// Unset markers for error plots
		signalError.SetMarkerStyle(0);
		backgroundError.SetMarkerStyle(0);
		rightIntegratedSoverRootBerror.SetMarkerStyle(0);
		leftIntegratedSoverRootBerror.SetMarkerStyle(0);
		cout << __FILE__ << ":" << __LINE__ << endl;

		// Plot a base histogram with only the axis
		TCanvas* canvas = new TCanvas(plotName.c_str(), plotName.c_str(), 800, 800); canvas->cd();
		canvas->Clear(); canvas->Divide(1,3);

		// First pad (signal)
		TVirtualPad* p1 = canvas->cd(1);
		p1->SetGridx(); p1->SetGridy();
		signalError.GetHisto()->GetYaxis()->SetRangeUser(0.001,1.1*signalError.GetMaximumWithError());
		signalError.GetHisto()->Draw("E2");
		signal.GetHisto()->Draw("HISTsame");

		// Second pad (background)
		TVirtualPad* p2 = canvas->cd(2);
		p2->SetGridx(); p2->SetGridy();
		backgroundError.GetHisto()->GetYaxis()->SetRangeUser(0.001,1.1*backgroundError.GetMaximumWithError());
		backgroundError.GetHisto()->Draw("E2");
		background.GetHisto()->Draw("HISTsame");

		// Third pad (rightIntegratedSoverRootB)
		TVirtualPad* p3 = canvas->cd(3);
		p3->SetGridx(); p3->SetGridy();
		double maxY = max(rightIntegratedSoverRootBerror.GetMaximumWithError(), leftIntegratedSoverRootBerror.GetMaximumWithError());
		rightIntegratedSoverRootBerror.GetHisto()->GetYaxis()->SetRangeUser(0.001,1.1*maxY);
		rightIntegratedSoverRootBerror.GetHisto()->Draw("E2");
		leftIntegratedSoverRootBerror.GetHisto()->Draw("E2same");
		rightIntegratedSoverRootB.GetHisto()->Draw("HISTsame");
		leftIntegratedSoverRootB.GetHisto()->Draw("HISTsame");

		TLegend* legend = new TLegend(0.2,0.92,0.8,1);
		legend->SetFillColor(0);
		legend->SetNColumns(2);
		legend->AddEntry(leftIntegratedSoverRootB.GetHisto(), "Integral x #rightarrow #infty", "l");
		legend->AddEntry(rightIntegratedSoverRootB.GetHisto(), "Integral 0 #rightarrow x", "l");
		legend->Draw();


		// Take care of the legend
		//GetLegend(iProPack)->Draw();

		// Take care of plot info
		//GetPlotText()->Draw();

		// Save canvas
		SaveCanvas(canvas, params["optimization_output"], string(plotName+"_int"));

		// Do we want a log version?
		SaveCanvasLog(canvas, params["optimization_output"], string(plotName+"_int"), signal.GetLogX(), signal.GetLogY(), signal.GetLogZ());

		// Clean up canvas
		delete canvas; canvas = NULL;

		// Print info about the current histo
		lastSavedPlotName = plotName;

		if(lastSavedPlotName.length()>0){
			cout << string(lastSavedPlotName.length()+1,'\b'); cout.flush(); 
			cout << string(lastSavedPlotName.length()+1,' '); cout.flush();
			cout << string(lastSavedPlotName.length()+1,'\b'); cout.flush(); 
		}   
		cout << plotName; cout.flush(); 

	}

}


void Optimizer::MakeSoverB(Process const * iSignal, Process const * iBackground){

	// Draw horizontal error bars
 	gStyle->SetErrorX(0.5);

	// Histogram math class
	HMath hmath;

	// Loop over all the HWrappers and plot each
	vector<string> plotNames = iSignal->GetHContainerForSignal()->GetNames();

	string lastSavedPlotName = "";
	for(unsigned int p=0; p<plotNames.size(); p++){
		string plotName = plotNames.at(p);

		// If the plot will be empty, skip it
		if(max(iSignal->GetAvailableHWrapper()->GetHisto()->Integral(), iBackground->GetAvailableHWrapper()->GetHisto()->Integral()) <= 0){ continue; }

		// Skip it if it's not a TH1F
		if(!iSignal->GetAvailableHWrapper()->IsTH1F()){ continue; }

		// Get HWrappers, obtain sOverRootB
		HWrapper signal = HWrapper(*(iSignal->GetHistoForSignal(plotName)));
		HWrapper background = HWrapper(*(iBackground->GetHistoForSignal(plotName)));
		HWrapper sOverRootB = HWrapper(signal); sOverRootB.SetHisto(hmath.StoRootB((TH1F*)(signal.GetHisto()), (TH1F*)(background.GetHisto())));

		// Reset maxima
		signal.ResetMaximum();
		background.ResetMaximum();
		sOverRootB.ResetMaximum();

		// Set line width and color
		signal.SetLineWidth(3, 3);
		background.SetLineWidth(3, 2);
		sOverRootB.SetLineWidth(3, 6);

		// Make copies for errors
		HWrapper signalError = HWrapper(signal); signalError.SetFillStyle(3004, 3);
		HWrapper backgroundError = HWrapper(background); backgroundError.SetFillStyle(3004, 2);
		HWrapper sOverRootBerror = HWrapper(sOverRootB); sOverRootBerror.SetFillStyle(3004,6);

		// Unset markers for error plots
		signalError.SetMarkerStyle(0);
		backgroundError.SetMarkerStyle(0);
		sOverRootBerror.SetMarkerStyle(0);

		// Plot a base histogram with only the axis
		TCanvas* canvas = new TCanvas(plotName.c_str(), plotName.c_str(), 800, 800); canvas->cd();
		canvas->Clear(); canvas->Divide(1,3);

		// First pad (signal)
		TVirtualPad* p1 = canvas->cd(1);
		p1->SetGridx(); p1->SetGridy();
		signalError.GetHisto()->Draw("E2");
		signal.GetHisto()->Draw("HISTsame");

		// Second pad (background)
		TVirtualPad* p2 = canvas->cd(2);
		p2->SetGridx(); p2->SetGridy();
		backgroundError.GetHisto()->Draw("E2");
		background.GetHisto()->Draw("HISTsame");

		// Third pad (SoverRootB)
		TVirtualPad* p3 = canvas->cd(3);
		p3->SetGridx(); p3->SetGridy();
		sOverRootBerror.GetHisto()->Draw("E2");
		sOverRootB.GetHisto()->Draw("HISTsame");

		// Take care of the legend
		//GetLegend(iProPack)->Draw();

		// Take care of plot info
		//GetPlotText()->Draw();

		// Save canvas
		SaveCanvas(canvas, params["optimization_output"], plotName);

		// Do we want a log version?
		SaveCanvasLog(canvas, params["optimization_output"], plotName, signal.GetLogX(), signal.GetLogY(), signal.GetLogZ());

		// Clean up canvas
		delete canvas; canvas = NULL;

		// Print info about the current histo
		lastSavedPlotName = plotName;

		if(lastSavedPlotName.length()>0){
			cout << string(lastSavedPlotName.length()+1,'\b'); cout.flush(); 
			cout << string(lastSavedPlotName.length()+1,' '); cout.flush();
			cout << string(lastSavedPlotName.length()+1,'\b'); cout.flush(); 
		}   
		cout << plotName; cout.flush(); 

	}

}






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

