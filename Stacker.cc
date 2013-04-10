/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			11 Jun 2011
    Description:	Plot stacking class.
    Notes:

*/

#include "Stacker.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TH1F.h"
#include "HContainer.h"

using namespace std;

// Default constructor
Stacker::Stacker(map<string,string> const & iParams, bool includeShapeSystematics) {

    minY = 0.001;

	params = iParams;
	Long_t *id,*size,*flags,*mt; id=NULL; size=NULL;flags=NULL;mt=NULL;
	bool badFile = gSystem->GetPathInfo((params["process_file"]).c_str(),id,size,flags,mt);
	if(badFile){ cerr << "ERROR: trying to stack plots but proPack file does not exist. Please run the event analysis first" << endl; exit(1); }

    file = new TFile((params["process_file"]).c_str(), "UPDATE");
   
    stacksFile = NULL;
    if(params.at("saveStackedHistos").compare("true") == 0) {
      std::cout << "opening stacked histo file " << params["stackedHisto_file"].c_str() << std::endl;
      stacksFile = new TFile((params["stackedHisto_file"]).c_str(), "UPDATE");
    }
    file->cd();

	proPack = (ProPack*)file->Get((params["propack_name"]).c_str());

    templateContainer = NULL;
    if(includeShapeSystematics) templateContainer = new TemplateContainer(params);

	MakePlots(proPack);
}

// Default destructor
Stacker::~Stacker(){
    if(stacksFile!=NULL){
        stacksFile->Close();
        delete stacksFile; 
        stacksFile = NULL;
    }
    if(templateContainer!=NULL and templateContainer!=0){
        delete templateContainer;
        templateContainer=NULL;
    }
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
	bool doRatioPlot		= (params["doRatioPlot"].compare("true")==0);

    if( doRatioPlot && !(haveCollisions && haveMCbackgrounds) ) {
        std::cout << "[Stacker::MakePlots] Can't make data/MC ratio plot because either data or background MC are missing!" << std::endl 
          << "Ratio plots will not be made." << std::endl;
        doRatioPlot = false;
    }
	
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
		double maxY = max(1.2*GetMaximumWithError(iProPack, plotName),0.1);
		HWrapper baseHisto((iProPack->GetAvailableHWrapper(plotName))); baseHisto.ScaleBy(0);
		subdir = baseHisto.GetSubDir();

		// Skip if 2D (gotta change this)
		if(baseHisto.IsTH2F()){ continue; }

		TCanvas* canvas = NULL;
        // magic numbers for data/MC ratio plotting
        float padding      = 0.0001;
        float yDivide      = 0.25;
        float ratioPlotMax = 2.5;
        float bottomMargin = 0.35;
        float smallNumber  = 0.0001;
        if( doRatioPlot ) {
            minY = 0.002;
            canvas = new TCanvas(plotName.c_str(), plotName.c_str(), 800, 1000); 
            canvas->Divide(1,2);
            canvas->GetPad(1)->SetPad(0+padding, yDivide + padding, 1 - padding, 1 - padding);
            canvas->GetPad(1)->SetBottomMargin(0);
            canvas->GetPad(2)->SetPad(padding, padding, 1-padding, yDivide-padding);
            canvas->GetPad(2)->SetBottomMargin(bottomMargin);
            canvas->GetPad(2)->SetGrid(1,1);
            
            canvas->cd(1);
        } else {
            canvas = new TCanvas(plotName.c_str(), plotName.c_str(), 800, 800); canvas->cd();
        }
		baseHisto.GetHisto()->GetYaxis()->SetRangeUser(minY,maxY);
	
        // Get background and signal sums 
        HWrapper backgroundSum;
        if(haveMCbackgrounds) 
            backgroundSum = HWrapper(GetBackgroundSum(iProPack, plotName));
        HContainer signalHistos;
        if(haveSignals)
            signalHistos = HContainer(iProPack->GetSignalsHWrappers(plotName));

        // Add asymmetric errors from shape systematics, if requested
        TGraphAsymmErrors* absBackgroundErr = NULL;
        TGraphAsymmErrors* relBackgroundErr = NULL;
        if(templateContainer != NULL) {
            
            // asymmetric errors
            pair<TGraphAsymmErrors*,TGraphAsymmErrors*> backgroundErr = AddAsymmShapeSystematicErrors(backgroundSum,plotName);
            absBackgroundErr = backgroundErr.first;
            relBackgroundErr = backgroundErr.second;
        }

        // If we have backgrounds, make the stack and plot them first
		THStack* stack = NULL;
		if(haveQCD || haveMCbackgrounds){ stack = GetBackgroundStack(iProPack, plotName, maxY); } 

		// Now draw the axis from scratch using the baseHisto
		gPad->SetGrid(1,1);
	    baseHisto.GetHisto()->Draw("HIST");

		// Draw stack if we have backgrounds
		if((stack != NULL) ){
			if(backgroundSum.GetHisto()->Integral()>0){
				stack->Draw("HISTsame"); 
				// Draw background errors if we want them
				if(params["showBackgroundError"].compare("true")==0){
					backgroundSum.SetFillStyle(3004,kBlack);
					backgroundSum.SetMarkerStyle(0);
                    // if we're not using asymmetric errors,
                    // only draw statistical error 
					if(absBackgroundErr == NULL) {
                        backgroundSum.GetHisto()->Draw("E2same");
                    } else {
                        absBackgroundErr->SetMarkerStyle(0);
                        absBackgroundErr->SetFillStyle(3004);
                        absBackgroundErr->SetFillColor(kBlack);
                        absBackgroundErr->Draw("SAMEp2");
                    }
                }
			}
		}

		// Then, if we have signals, plot them next
		if(haveSignals){
			for(int s = 0; s < signalHistos.size(); s++){
                string name = signalHistos.GetNames().at(s);
                const Process *proc;

                // TODO remove this stupid hotfix:
                // GetSignals() returns an unsorted vector, while
                // everything returned by GetSignalsHWrappers() is going
                // through a map sort.
                for (const auto& p: *(iProPack->GetSignals()))
                    if (p.GetLabelForLegend() == name)
                        proc = &p;

                if (not proc->Plot())
                    continue;

				HWrapper* toDraw = new HWrapper(*signalHistos.Get(name));
				toDraw->SetFillStyle(0);	
				toDraw->SetLineWidth(3, proc->GetColor());
				toDraw->GetHisto()->GetYaxis()->SetRangeUser(minY, maxY);

				// If we want the signals on top of the stack, add the background sum
				if(stackSignals){ toDraw->Add(backgroundSum); }

				// Draw signal curves
				if(toDraw->GetHisto()->Integral()>0){
					toDraw->GetHisto()->Draw("HISTsame"); 
                }
				TH1F* histo = new TH1F(*(TH1F*)(toDraw->GetHisto()));
				histo->GetXaxis()->SetRangeUser(0,2000);
			}
		}

		// Finally plot the collisions if we have them
		if(haveCollisions){ 
			if(!iProPack->GetCollisions()->Plot()){ continue; }
			HWrapper collisionsHisto = HWrapper(*iProPack->GetCollisions()->GetHContainerForSignal()->Get(plotName));
			collisionsHisto.SetMarkerStyle(20);
			collisionsHisto.GetHisto()->GetYaxis()->SetRangeUser(minY, maxY);
			if(collisionsHisto.GetHisto()->Integral()>0){ collisionsHisto.GetHisto()->Draw("EPsame"); }
		}	

		// Redraw the axes so they stay on top of everthing...
		baseHisto.GetHisto()->Draw("AXISsame");

		// Take care of the legend
		GetLegend(iProPack)->Draw();

		// Take care of plot info
		GetPlotText(params.find("plotText")->second)->Draw();

        // If requested, do data/MC ratio plot
        if( doRatioPlot ) {
            canvas->cd(2);  

            // Get variable range 
            // (can be tricky when visible ranges are specified, still not completely correct)
			HWrapper collisionsHisto = HWrapper(*iProPack->GetCollisions()->GetHContainerForSignal()->Get(plotName));
            float xMin = backgroundSum.GetMinXVis();
            float xMax = backgroundSum.GetMaxXVis();

            // Get data/MC ratio
            TH1F* hData = (TH1F*)collisionsHisto.GetHisto();
            TH1F* hBackground = (TH1F*)backgroundSum.GetHisto();
            TH1F* hRatio = (TH1F*)hData->Clone();
            for( int iBin = 0; iBin <= hData->GetNbinsX(); iBin++) {
                float value = ((hBackground->GetBinContent(iBin) != 0) && (hData->GetBinContent(iBin) != 0)) ?
                    hData->GetBinContent(iBin)/hBackground->GetBinContent(iBin) : 0;
                hRatio->SetBinContent(iBin,value);
            }
            hRatio->GetXaxis()->SetRangeUser(xMin,xMax);

            // Fix sizes and locations
            hRatio->GetYaxis()->SetTitle("Data/MC");
            hRatio->GetYaxis()->CenterTitle();
            hRatio->GetYaxis()->SetTitleSize(0.15);
            hRatio->GetYaxis()->SetTitleOffset(0.4);
            hRatio->GetYaxis()->SetLabelSize(0.08);
            hRatio->GetXaxis()->SetTitleSize(0.15);
            hRatio->GetXaxis()->SetLabelSize(0.1);
            
            // Use hRatio only for axes; use errors (see below) to plots points 
            hRatio->GetYaxis()->SetRangeUser(minY,ratioPlotMax);
            hRatio->Draw("AXIS");
            
            // Get symmetric errors on MC background 
            TH1F* hBgErrors = (TH1F*)hRatio->Clone();
            for( int iBin = 1; iBin <= hBgErrors->GetXaxis()->GetNbins(); iBin++) {
                hBgErrors->SetBinContent(iBin,1);
                // use relative errors!
                float error = (hBackground->GetBinContent(iBin) < 0.001) ? 
                    0 : hBackground->GetBinError(iBin)/hBackground->GetBinContent(iBin);
                hBgErrors->SetBinError(iBin,error);
            }
            hBgErrors->GetXaxis()->SetRangeUser(xMin,xMax);
            hBgErrors->SetMarkerSize(0);
            hBgErrors->SetFillColor(29);
            
            // Draw MC uncertainty first, so it sits behind the data/MC ratio points
            if( relBackgroundErr != 0 ) {
                relBackgroundErr->SetMarkerSize(0);
                relBackgroundErr->SetFillColor(30);
                relBackgroundErr->Draw("same2");
            } else 
                hBgErrors->Draw("same E2");
            
            // Get asymetric errors for data/MC ratio
            TGraphAsymmErrors * ratioErr = new TGraphAsymmErrors(hRatio);
            for( int iBin = 0; iBin < ratioErr->GetN(); iBin++ ) {
                
                float xCoordinateValue = hRatio->GetBinCenter(iBin+1);
                float yRatioValue = hRatio->GetBinContent(iBin+1);
                float yDataValue = collisionsHisto.GetHisto()->GetBinContent(iBin+1);
                float yDataError = collisionsHisto.GetHisto()->GetBinError(iBin+1);
                float yBgValue = backgroundSum.GetHisto()->GetBinContent(iBin+1);
                
                if( yRatioValue > smallNumber && yRatioValue < ratioPlotMax*0.99) {
                    float yUp = (yBgValue > smallNumber) ? (yDataValue+yDataError)/yBgValue : 0;
                    float yDown = (yBgValue > smallNumber) ? (yDataValue-yDataError)/yBgValue : 0;
                    ratioErr->SetPoint(iBin,xCoordinateValue,yRatioValue);
                    ratioErr->SetPointEYhigh(iBin,yUp-yRatioValue);
                    ratioErr->SetPointEYlow(iBin,yRatioValue-yDown);
                    ratioErr->SetPointEXhigh(iBin,0);
                    ratioErr->SetPointEXlow(iBin,0);
                } else {
                    ratioErr->SetPoint(iBin,xCoordinateValue,999);
                }
            }
            ratioErr->SetMarkerSize(1.);
            ratioErr->SetMarkerStyle(8);
            // Draw the ratio points + errors on top of the background MC uncertainty
            ratioErr->Draw("P SAME Z");
            // Draw a good axis
            hRatio->Draw("AXIS SAME");
            
            // Make line at 1
            TLine line;
            line.SetLineColor(1);
            line.SetLineWidth(2);
            line.DrawLine(xMin,1,xMax,1);
           
        }
		// Save canvas
		SaveCanvas(canvas, params["stacks_output"]+subdir, plotName);
		// Do we want a log version?
		if(doRatioPlot) SaveCanvasLog(canvas, params["stacks_output"]+subdir, plotName, baseHisto.GetLogX(), baseHisto.GetLogY(), baseHisto.GetLogZ(),1);
        else SaveCanvasLog(canvas, params["stacks_output"]+subdir, plotName, baseHisto.GetLogX(), baseHisto.GetLogY(), baseHisto.GetLogZ(),0);

        // Save TCanvas if requested
        if(params.at("saveStackedHistos").compare("true") == 0) {
          stacksFile->cd();
          canvas->Write();
          file->cd();
        }

		// Clean up canvas
		delete canvas;
		stack = NULL; delete stack;

		// Print info about the current histo
		cout << "\r\033[K" << flush;
		cout << plotName; cout.flush(); 
	}

	// Print done
	cout << "\r\033[K" << flush;

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
	if(iProPack->PrepareCollisions() && iProPack->GetCollisions()->Plot()){
		TH1 const * temp = iProPack->GetCollisions()->GetAvailableHWrapper()->GetHisto();
		result->AddEntry(temp,(iProPack->GetCollisions()->GetLabelForLegend()).c_str(),"lep");
	}

	// Background errors if we want them and have them
	if(((iProPack->PrepareQCD()) || (iProPack->GetMCbackgrounds()->size() > 0)) && (params["showBackgroundError"].compare("true")==0)){
		HWrapper * temp = new HWrapper(GetBackgroundSum(iProPack, iProPack->GetAvailableHWrapper().GetName()));
		temp->SetFillStyle(3004,kBlack);
		temp->SetLineWidth(0);
		result->AddEntry(temp->GetHisto(),"Bkg. err. ","f");
	}

	// QCD comes next
	if(iProPack->PrepareQCD() && iProPack->GetQCD()->Plot()){
		HWrapper * temp = new HWrapper(*iProPack->GetQCD()->GetAvailableHWrapper());
		temp->SetFillStyle(1001,iProPack->GetQCD()->GetColor());
		temp->SetLineWidth(0);
		result->AddEntry(temp->GetHisto(),(iProPack->GetQCD()->GetLabelForLegend()).c_str(),"f");
		delete temp;
	}

	// Then MC backgrounds in reverse order as in the vector
	for(int b = iProPack->GetMCbackgrounds()->size()-1; b >= 0; b--){
		if(!iProPack->GetMCbackgrounds()->at(b).Plot()){ continue; }
		HWrapper * temp = new HWrapper(*iProPack->GetMCbackgrounds()->at(b).GetAvailableHWrapper());
		temp->SetFillStyle(1001,iProPack->GetMCbackgrounds()->at(b).GetColor());
		temp->SetLineWidth(0);
		result->AddEntry(temp->GetHisto(),(iProPack->GetMCbackgrounds()->at(b).GetLabelForLegend()).c_str(),"f");
	}

	// Finally signals also in reverse order as in the vector
	for(int s = iProPack->GetSignals()->size()-1; s >= 0; s--){
		if(!iProPack->GetSignals()->at(s).Plot()){ continue; }
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
THStack * Stacker::GetBackgroundStack(ProPack const * iProPack, string const iName, double const iMaxY) const {

	// Obtain a reference HWrapper from which to extract options
	HWrapper refHisto = HWrapper(*(iProPack->GetAvailableProcess().GetHistoForSignal(iName)));
	if(refHisto.IsTH2F()){ cerr << "ERROR: trying to build THStack from TH2F with plot named '" << iName << "'" << endl; exit(1); }

	// Figure out the maximum Y value
	//double maxY = max(1.2*Stacker::GetMaximumWithError(iProPack,iName),0.1);
	double maxY = iMaxY;
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
			toAdd.GetHisto()->GetYaxis()->SetRangeUser(minY,maxY);
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
		toAdd.GetHisto()->GetYaxis()->SetRangeUser(minY,maxY);
		toAdd.GetHisto()->GetXaxis()->SetRangeUser(toAdd.GetMinXVis(), toAdd.GetMaxXVis());
		result->Add((TH1F*)toAdd.GetHisto());
	}
	// Must call Draw before setting the options below
	result->Draw("HIST");
	result->GetXaxis()->SetRangeUser(refHisto.GetMinXVis(), refHisto.GetMaxXVis());
	result->GetXaxis()->SetTitle((refHisto.GetXTitle()).c_str());
	result->GetYaxis()->SetTitle((refHisto.GetYTitle()).c_str());
	result->SetMinimum(minY);
	result->SetMaximum(maxY);
	result->GetYaxis()->SetRangeUser(minY,maxY);
	return result;
}


// Figure out the maximum y value
double const Stacker::GetMaximum(ProPack const * iProPack, string const iName) const { return GetMaximum(iProPack, iName, false); }
double const Stacker::GetMaximumWithError(ProPack const * iProPack, string const iName) const { return Stacker::GetMaximum(iProPack, iName, true); }
	//return GetMaximum(iProPack, iName, true); }
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
// only use if errors are symmetric 
void Stacker::AddShapeSystematicErrors(HWrapper& backgroundSum, string plotName ) {

    for( int iBin = 0; iBin < backgroundSum.GetHisto()->GetNbinsX(); iBin++ ) {
        float relativeError = 0;
        if( backgroundSum.GetHisto()->GetBinContent(iBin) > 0.001) relativeError = templateContainer->GetAbsoluteError(plotName,iBin,backgroundSum.GetHisto()->GetBinContent(iBin));
        backgroundSum.AddRelErrorInQuadrature(relativeError,iBin);
    }    
}
// must use TGraphAsymmErrors class to draw asymmetric error bars
pair<TGraphAsymmErrors*,TGraphAsymmErrors*> Stacker::AddAsymmShapeSystematicErrors(HWrapper& backgroundSum, string plotName) {
   
    // NOTE: bin 0 for TH1's is the underflow bin
    // so bin n for the TGraph corresponds to bin n+1 for the TH1
    TH1F* backgroundSumHisto = (TH1F*)backgroundSum.GetHisto();
    TGraphAsymmErrors* backgroundErrAbs = new TGraphAsymmErrors(backgroundSumHisto);
    TGraphAsymmErrors* backgroundErrRel = new TGraphAsymmErrors(backgroundSumHisto);
    for( int iBin = 0; iBin < backgroundErrAbs->GetN(); iBin++ ) {
       
        float binContent = backgroundSumHisto->GetBinContent(iBin+1);
        float binError = backgroundSumHisto->GetBinError(iBin+1);
        // Get errors from shape systematics
        float errorUpAbs = templateContainer->GetAbsoluteErrorUp(plotName,iBin+1,binContent);
        float errorDownAbs = templateContainer->GetAbsoluteErrorDown(plotName,iBin+1,binContent);
        
        // Add rate systematics and statistical errors
        float errorUpRel = 0;
        float errorDownRel = 0;
        if( binContent > 0.001) {
            errorUpRel = sqrt(errorUpAbs*errorUpAbs + binError*binError)/binContent;
            errorDownRel = sqrt(errorDownAbs*errorDownAbs + binError*binError)/binContent;
        }

        float binWidth = backgroundSumHisto->GetBinWidth(iBin+1);
        float xCoordinateValue = backgroundSumHisto->GetBinCenter(iBin+1);
        float yCoordinateValue = backgroundSumHisto->GetBinContent(iBin+1);

        // set y value to one for relative rrrors, since this is for data/MC ratio
        backgroundErrRel->SetPoint(iBin,xCoordinateValue,1);
        backgroundErrAbs->SetPoint(iBin,xCoordinateValue,yCoordinateValue);
        
        backgroundErrAbs->SetPointEXlow(iBin,binWidth/2);
        backgroundErrAbs->SetPointEXhigh(iBin,binWidth/2);
        backgroundErrAbs->SetPointEYlow(iBin,errorDownAbs);
        backgroundErrAbs->SetPointEYhigh(iBin,errorUpAbs);
        
        backgroundErrRel->SetPointEXlow(iBin,binWidth/2);
        backgroundErrRel->SetPointEXhigh(iBin,binWidth/2);
        backgroundErrRel->SetPointEYlow(iBin,errorDownRel);
        backgroundErrRel->SetPointEYhigh(iBin,errorUpRel);
    }
    pair<TGraphAsymmErrors*,TGraphAsymmErrors*> errPair(backgroundErrAbs,backgroundErrRel);
    return errPair;
}
