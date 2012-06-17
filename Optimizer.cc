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

	file = new TFile((params["process_file"]).c_str(), "READ");
	file->cd();

	proPack = (ProPack*)file->Get((params["propack_name"]).c_str());
	MakePlots(proPack);
}


// Default destructor
Optimizer::~Optimizer(){}

void Optimizer::MakePlots(ProPack const * iProPack) {
	//MakeRightIntegratedSoverB(&(iProPack->GetSignals()->at(0)), iProPack->GetQCD());
	//Overlap2D(&(iProPack->GetSignals()->at(0)), iProPack->GetQCD());
	//MakeSoverB(&(iProPack->GetSignals()->at(0)), iProPack->GetQCD());

	MakeRightIntegratedSoverB(&(iProPack->GetSignals()->at(0)), &(iProPack->GetMCbackgrounds()->at(0)));
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

	string subdir = "";
	string lastSavedPlotName = "";
	for(unsigned int p=0; p<plotNames.size(); p++){
		string plotName = plotNames.at(p);

		// Skip it if it's not a TH1F
		if(!iSignal->GetAvailableHWrapper(plotName)->IsTH1F()){ continue; }

		// Get HWrappers
		HWrapper signal = HWrapper(*(iSignal->GetHistoForSignal(plotName)));
		HWrapper background = HWrapper(*(iBackground->GetHistoForSignal(plotName)));


		if((signal.GetHisto()->Integral() <= 0) && (background.GetHisto()->Integral() <= 0)){ 
			cout << "\nWARNING: HWrapper with name '" << plotName << "' not filled. Perhaps it's a good idea to remove it from '" << string(signal.GetSubDir()+"\b.cfg") << "'." << endl;
			continue;
		}
		subdir = signal.GetSubDir();

		// Obtain sOverRootB
		HWrapper rightIntegratedSoverRootB = HWrapper(signal);
		HWrapper leftIntegratedSoverRootB = HWrapper(signal);

		rightIntegratedSoverRootB.SetHisto(hmath.RightIntegratedStoRootB((TH1F*)(signal.GetHisto()), (TH1F*)(background.GetHisto())));
		leftIntegratedSoverRootB.SetHisto(hmath.LeftIntegratedStoRootB((TH1F*)(signal.GetHisto()), (TH1F*)(background.GetHisto())));


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

		// Plot a base histogram with only the axis
		TCanvas* canvas = new TCanvas(plotName.c_str(), plotName.c_str(), 800, 800); canvas->cd();
		canvas->Clear(); canvas->Divide(1,3);

		// First pad (signal)
		TVirtualPad* p1 = canvas->cd(1);
		p1->SetGridx(); p1->SetGridy();
		signalError.GetHisto()->GetYaxis()->SetRangeUser(0.001,1.1*signal.GetMaximumWithError());
		signalError.GetHisto()->GetYaxis()->SetTitle("Signal Events");
		signalError.GetHisto()->GetYaxis()->SetTitleSize(0.14);
		signalError.GetHisto()->GetYaxis()->SetTitleOffset(0.4);
		signalError.GetHisto()->Draw("E2");
		if(signal.GetHisto()->Integral() > 0){ signal.GetHisto()->Draw("HISTsame"); }

		// Second pad (background)
		TVirtualPad* p2 = canvas->cd(2);
		p2->SetGridx(); p2->SetGridy();
		backgroundError.GetHisto()->GetYaxis()->SetRangeUser(0.001,1.1*background.GetMaximumWithError());
		backgroundError.GetHisto()->GetYaxis()->SetTitle("Bkg Events");
		backgroundError.GetHisto()->GetYaxis()->SetTitleSize(0.14);
		backgroundError.GetHisto()->GetYaxis()->SetTitleOffset(0.4);

		bool skipBackground = false;
		if(background.GetHisto()->Integral() > 0){
			backgroundError.GetHisto()->Draw("E2");
			background.GetHisto()->Draw("HISTsame");
		}else{
			skipBackground = true;
			backgroundError.GetHisto()->GetYaxis()->SetLimits(0.001,1);
			backgroundError.GetHisto()->GetYaxis()->SetRangeUser(0.001,1);
			backgroundError.GetHisto()->GetXaxis()->SetLimits(backgroundError.GetMinXVis(), backgroundError.GetMaxXVis());
			backgroundError.GetHisto()->GetXaxis()->SetRangeUser(backgroundError.GetMinXVis(), backgroundError.GetMaxXVis());
			backgroundError.GetHisto()->Draw("AXIS");
		}

		// Third pad (rightIntegratedSoverRootB)
		TVirtualPad* p3 = canvas->cd(3);
		p3->SetGridx(); p3->SetGridy();
		rightIntegratedSoverRootBerror.GetHisto()->GetYaxis()->SetTitle("s / #sqrt{b}");
		rightIntegratedSoverRootBerror.GetHisto()->GetYaxis()->SetTitleSize(0.14);
		rightIntegratedSoverRootBerror.GetHisto()->GetYaxis()->SetTitleOffset(0.4);
		if(!skipBackground){
			double maxY = max(rightIntegratedSoverRootBerror.GetMaximumWithError(), leftIntegratedSoverRootBerror.GetMaximumWithError());
			rightIntegratedSoverRootBerror.GetHisto()->GetYaxis()->SetRangeUser(0.001,1.1*maxY);
			rightIntegratedSoverRootBerror.GetHisto()->Draw("E2");
			leftIntegratedSoverRootBerror.GetHisto()->Draw("E2same");
			rightIntegratedSoverRootB.GetHisto()->Draw("HISTsame");
			leftIntegratedSoverRootB.GetHisto()->Draw("HISTsame");
		}else{
			rightIntegratedSoverRootBerror.GetHisto()->GetYaxis()->SetLimits(0.001,1);
			rightIntegratedSoverRootBerror.GetHisto()->GetYaxis()->SetRangeUser(0.001,1);
			rightIntegratedSoverRootBerror.GetHisto()->GetXaxis()->SetLimits(rightIntegratedSoverRootBerror.GetMinXVis(), rightIntegratedSoverRootBerror.GetMaxXVis());
			rightIntegratedSoverRootBerror.GetHisto()->GetXaxis()->SetRangeUser(rightIntegratedSoverRootBerror.GetMinXVis(), rightIntegratedSoverRootBerror.GetMaxXVis());
			rightIntegratedSoverRootBerror.GetHisto()->Draw("AXIS");
		}

		TLegend* legend = new TLegend(0.3,0.92,0.8,1);
		legend->SetBorderSize(1);
		legend->SetFillColor(0);
		legend->SetNColumns(2);
		legend->AddEntry(rightIntegratedSoverRootB.GetHisto(), "Integral x #rightarrow #infty", "l");
		legend->AddEntry(leftIntegratedSoverRootB.GetHisto(), "Integral 0 #rightarrow x", "l");
		legend->Draw();


		// Save canvas
	//	if((signal.GetHisto()->Integral() > 0) || (background.GetHisto()->Integral() > 0)){
			SaveCanvas(canvas, params["optimization_output"]+subdir, string(plotName+"_int"));
	//	}

		// Do we want a log version?
//		SaveCanvasLog(canvas, params["optimization_output"], string(plotName+"_int"), signal.GetLogX(), signal.GetLogY(), signal.GetLogZ());

		// Clean up canvas
		delete canvas; canvas = NULL;

		// Print info about the current histo
		lastSavedPlotName = plotName;

		if(lastSavedPlotName.length()>0){
			cout << string(lastSavedPlotName.length()+10,'\b'); cout.flush(); 
			cout << string(lastSavedPlotName.length()+15,' '); cout.flush();
			cout << string(lastSavedPlotName.length()+20,'\b'); cout.flush(); 
		}   
		cout << plotName; cout.flush(); 

	}

}

/*
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


		// Save canvas
		SaveCanvas(canvas, params["optimization_output"], plotName);

		// Do we want a log version?
	//	SaveCanvasLog(canvas, params["optimization_output"], plotName, signal.GetLogX(), signal.GetLogY(), signal.GetLogZ());

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
//*/


void Optimizer::Overlap2D(Process const * iSignal, Process const * iBackground){

	// Loop over all the HWrappers and plot each
	vector<string> plotNames = iSignal->GetHContainerForSignal()->GetNames();

	string subdir = "";
	string lastSavedPlotName = "";
	for(unsigned int p=0; p<plotNames.size(); p++){
		string plotName = plotNames.at(p);

		// Skip it if it's not a TH1F
		if(iSignal->GetAvailableHWrapper(plotName)->IsTH1F()){ continue; }

		// Get HWrappers
		HWrapper signal = HWrapper(*(iSignal->GetHistoForSignal(plotName)));
		HWrapper background = HWrapper(*(iBackground->GetHistoForSignal(plotName)));


		if((signal.GetHisto()->Integral() <= 0) && (background.GetHisto()->Integral() <= 0)){ 
			cout << "\nWARNING: HWrapper with name '" << plotName << "' not filled. Perhaps it's a good idea to remove it from '" << string(signal.GetSubDir()+"\b.cfg") << "'." << endl;
			continue;
		}
		subdir = signal.GetSubDir();


		// Plot a base histogram with only the axis
		TCanvas* canvas = new TCanvas(plotName.c_str(), plotName.c_str(), 800, 800); canvas->cd();
		canvas->Clear();

		// First pad (signal)
		TVirtualPad* p1 = canvas->cd(1);
		p1->SetGridx(); p1->SetGridy();

		signal.SetFillStyle(3001);
		signal.SetFillColor(iSignal->GetColor());
		signal.SetLineColor(iSignal->GetColor());
		signal.SetLineWidth(1);
		background.SetFillStyle(1000);
		background.SetFillColor(iBackground->GetColor());
		background.SetLineColor(iBackground->GetColor());
		background.SetLineWidth(1);

		signal.NormalizeTo(1.0);
		if(background.GetHisto()->Integral() > 0){
			background.NormalizeTo(1.0);
		//	background.GetHisto()->GetYaxis()->SetTitleSize(0.14);
		//	background.GetHisto()->GetYaxis()->SetTitleOffset(0.4);
			background.GetHisto()->Draw("BOX");
			signal.GetHisto()->Draw("BOXsame");
		}else{
			signal.GetHisto()->Draw("BOX");
		}


		TLegend* legend = new TLegend(0.2,0.92,0.9,0.98);
		legend->SetBorderSize(1);
		legend->SetFillColor(0);
		legend->SetNColumns(2);
		legend->AddEntry(signal.GetHisto(), "Area-normalized Signal", "f");
		legend->AddEntry(background.GetHisto(), "Area-normalized Background", "f");
		legend->Draw();

		// Save canvas
		SaveCanvas(canvas, params["optimization_output"]+subdir, string(plotName));

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

	// Print done
	if(lastSavedPlotName.length()>0){
			cout << string(lastSavedPlotName.length()+1,'\b'); cout.flush(); 
			cout << string(lastSavedPlotName.length()+1,' '); cout.flush();
			cout << string(lastSavedPlotName.length()+1,'\b'); cout.flush(); 
	}

}
