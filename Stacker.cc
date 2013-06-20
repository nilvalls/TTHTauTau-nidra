/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			11 Jun 2011
    Description:	Plot stacking class.
    Notes:

*/

#include "boost/lexical_cast.hpp"

#include "TCanvas.h"
#include "TFile.h"
#include "TFrame.h"
#include "TH1F.h"
#include "TStyle.h"
#include "TSystem.h"

#include "HContainer.h"
#include "Helper.h"
#include "Stacker.h"

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
void Stacker::MakePlots(ProPack * iProPack) {
    for (auto& p: *iProPack->GetMCbackgrounds())
        p.SetPlot(params);
    for (auto& p: *iProPack->GetSignals())
        p.SetPlot(params);
    iProPack->GetCollisions()->SetPlot(params);

	// Draw horizontal error bars
 	gStyle->SetErrorX(0.5);

	// Figure out what we have and what we don't
	bool haveCollisions		= iProPack->PrepareCollisions();	
	bool haveMCbackgrounds	= iProPack->PrepareMCbackgrounds();
	bool haveSignals		= iProPack->PrepareSignals();
	bool stackSignals		= (params["stackSignals"].compare("true")==0);
	bool doRatioPlot		= (params["doRatioPlot"].compare("true")==0);

    /*if( doRatioPlot && !(haveCollisions && haveMCbackgrounds) ) {
        std::cout << "[Stacker::MakePlots] Can't make data/MC ratio plot because either data or background MC are missing!" << std::endl 
          << "Ratio plots will not be made." << std::endl;
        cout << " haveCollisions = " <<haveCollisions<<endl;
        cout << " haveMCbackgrounds = " << haveMCbackgrounds<<endl;
        doRatioPlot = false;
    }*/
	
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
		double maxY = max(1.3 * GetMaximumWithError(iProPack, plotName),0.1);
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
            canvas->GetPad(1)->SetTopMargin(0.065);
            canvas->GetPad(1)->SetBottomMargin(0);
            canvas->GetPad(2)->SetPad(padding, padding, 1-padding, yDivide-padding);
            canvas->GetPad(2)->SetBottomMargin(bottomMargin);
            //canvas->GetPad(2)->SetGrid(1,1);

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
		if (haveMCbackgrounds) {
            stack = GetBackgroundStack(iProPack, plotName, maxY, true);
        }

		// Now draw the axis from scratch using the baseHisto
		//gPad->SetGrid(1,1);
	    baseHisto.GetHisto()->Draw("HIST");

		// Draw stack if we have backgrounds
		if((stack != NULL) ){
			if(backgroundSum.GetHisto()->Integral()>0){
				stack->Draw("HISTsame"); 
				// Draw background errors if we want them
				if(params["showBackgroundError"].compare("true")==0){
					//backgroundSum.SetFillStyle(3004,kBlack);
					backgroundSum.SetFillStyle(3654,kBlack); // matching DIL/LJ style
					backgroundSum.SetMarkerStyle(0);
                    // if we're not using asymmetric errors,
                    // only draw statistical error 
					if(absBackgroundErr == NULL) {
                        backgroundSum.GetHisto()->Draw("E2same");
                    } else {
                        absBackgroundErr->SetMarkerStyle(0);
                        //absBackgroundErr->SetFillStyle(3004);
                        absBackgroundErr->SetFillStyle(3654); // matching DIL/LJ style
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
                try {
                    using boost::lexical_cast;
                    toDraw->ScaleBy(lexical_cast<float>(params["signalScale"]));
                } catch (...) {};
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
		if (haveCollisions && iProPack->GetCollisions()->Plot()) {
			HWrapper collisionsHisto = HWrapper(*iProPack->GetCollisions()->GetHContainerForSignal()->Get(plotName));
			collisionsHisto.SetMarkerStyle(20);
			collisionsHisto.GetHisto()->GetYaxis()->SetRangeUser(minY, maxY);
			if(collisionsHisto.GetHisto()->Integral()>0){ 
                collisionsHisto.GetHisto()->SetLineWidth(2); 
                collisionsHisto.GetHisto()->Draw("E1Psame"); 
            }
		}	


		// Redraw the axes so they stay on top of everthing...
		baseHisto.GetHisto()->Draw("AXISsame");

		// Take care of the legend
		GetLegend(iProPack, baseHisto.GetHisto()->GetTickLength())->Draw();

		// Take care of plot info
		//GetPlotText(params.find("plotText")->second)->Draw();
		GetPlotTextLatex(params.find("plotText")->second)->Draw();

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
            //hBgErrors->SetFillColor(29);
            hBgErrors->SetFillColor(kGreen); // matching DIL/LJ style
            
            // Draw MC uncertainty first, so it sits behind the data/MC ratio points
            if( relBackgroundErr != 0 ) {
                relBackgroundErr->SetMarkerSize(0);
                //relBackgroundErr->SetFillColor(30);
                relBackgroundErr->SetFillColor(kGreen); // matching DIL/LJ style
                relBackgroundErr->Draw("same2");
            } else 
                hBgErrors->Draw("same E2");
            
            // Get asymetric errors for data/MC ratio
            TGraphAsymmErrors * ratioErr = new TGraphAsymmErrors(hRatio);
            for( int iBin = 0; iBin < ratioErr->GetN(); iBin++ ) {
                
                float xCoordinateValue = hRatio->GetBinCenter(iBin+1);
                float binWidth = hRatio->GetBinWidth(iBin+1);
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
                    ratioErr->SetPointEXhigh(iBin,binWidth/2);
                    ratioErr->SetPointEXlow(iBin,binWidth/2);
                } else {
                    ratioErr->SetPoint(iBin,xCoordinateValue,999);
                }
            }
            ratioErr->SetMarkerSize(1.);
            ratioErr->SetMarkerStyle(8);
            ratioErr->SetLineWidth(2);
            // Draw the ratio points + errors on top of the background MC uncertainty
            ratioErr->Draw("P SAME");
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

TLegend*
Stacker::GetLegend(ProPack const * iProPack, const float tick_length)
{
    using boost::lexical_cast;

    int n_items = 0;
    int n_cols = 1;
    try {
        n_cols = lexical_cast<int>(params["colLegend"]);
    } catch (...) {}

    n_items += iProPack->GetMCbackgrounds()->size();
    if ((iProPack->GetMCbackgrounds()->size() > 0) && (params["showBackgroundError"] == "true"))
        n_items++;

    int bkg_skip = 0;
    int sig_skip = 0;

    int n_rows = ceil(float(n_items) / n_cols);
    int bkg_mod = n_items % n_rows;
    if (bkg_mod > 1) {
        bkg_skip = n_cols - bkg_mod;
        n_items += bkg_skip;
    }

    if (iProPack->PrepareCollisions() && iProPack->GetCollisions()->Plot())
        n_items++;

    n_rows = ceil(float(n_items) / n_cols);
    int sig_mod = n_items % n_rows;
    int n_signals = iProPack->GetSignals()->size();
    if ((sig_mod + n_signals) % n_cols > 0) {
        sig_skip = n_cols - sig_mod;
        n_items += sig_skip;
    }

    n_items += iProPack->GetSignals()->size();
    n_rows = ceil(float(n_items) / n_cols);

    if (n_items < n_cols)
        n_cols = n_items;

    float x1Legend = lexical_cast<float>(params["x1Legend"]);
    float x2Legend = lexical_cast<float>(params["x2Legend"]);
    float yLegend = lexical_cast<float>(params["yLegend"]);
    float dxLegend = lexical_cast<float>(params["dxLegend"]) * n_cols;
    float dyLegend = lexical_cast<float>(params["dyLegend"]) * n_rows;

    x1Legend = gPad->GetLeftMargin() + tick_length;
    x2Legend = 1.0 - gPad->GetRightMargin() - tick_length;
    yLegend = 1.0 - gPad->GetTopMargin() - 0.001;

    TLegend* leg = new TLegend(x1Legend, yLegend - dyLegend, x2Legend, yLegend, NULL, "brNDC");
    leg->SetTextFont(42);
    leg->SetTextSize(0.035);
    leg->SetNColumns(n_cols);

    for (unsigned int b = 0; b < iProPack->GetMCbackgrounds()->size(); ++b) {
        if (!iProPack->GetMCbackgrounds()->at(b).Plot())
            continue;
        HWrapper * temp = new HWrapper(*iProPack->GetMCbackgrounds()->at(b).GetAvailableHWrapper());
        temp->SetFillStyle(1001,iProPack->GetMCbackgrounds()->at(b).GetColor());
        temp->SetLineWidth(0);
        leg->AddEntry(temp->GetHisto(),(iProPack->GetMCbackgrounds()->at(b).GetLabelForLegend()).c_str(),"f");
    }

    if (bkg_mod == 1) {
        if (iProPack->PrepareCollisions() && iProPack->GetCollisions()->Plot()) {
            TH1 const * temp = iProPack->GetCollisions()->GetAvailableHWrapper()->GetHisto();
            leg->AddEntry(temp,(iProPack->GetCollisions()->GetLabelForLegend()).c_str(),"lep");
        }

        if ((iProPack->GetMCbackgrounds()->size() > 0) && (params["showBackgroundError"].compare("true")==0)) {
            HWrapper * temp = new HWrapper(GetBackgroundSum(iProPack, iProPack->GetAvailableHWrapper().GetName()));
            //temp->SetFillStyle(3004,kBlack);
            temp->SetFillStyle(3654,kBlack); // match style
            temp->SetLineWidth(0);
            leg->AddEntry(temp->GetHisto(),"Bkg. err. ","f");
        }
    } else {
        if ((iProPack->GetMCbackgrounds()->size() > 0) && (params["showBackgroundError"].compare("true")==0)) {
            HWrapper * temp = new HWrapper(GetBackgroundSum(iProPack, iProPack->GetAvailableHWrapper().GetName()));
            //temp->SetFillStyle(3004,kBlack);
            temp->SetFillStyle(3654,kBlack); //match style
            temp->SetLineWidth(0);
            leg->AddEntry(temp->GetHisto(),"Bkg. err. ","f");
        }

        for (int i = 0; i < bkg_skip; ++i)
            leg->AddEntry((TObject*) 0, "", "");

        if (iProPack->PrepareCollisions() && iProPack->GetCollisions()->Plot()) {
            TH1 const * temp = iProPack->GetCollisions()->GetAvailableHWrapper()->GetHisto();
            leg->AddEntry(temp,(iProPack->GetCollisions()->GetLabelForLegend()).c_str(),"lep");
        }
    }

    sig_skip = 0;
    for (int i = 0; i < sig_skip; ++i)
        leg->AddEntry((TObject*) 0, "", "");

    string sig_add("");
    try {
        int scale = lexical_cast<int>(params["signalScale"]);
        ostringstream s("");
        s << " (#times " << scale << ")";
        sig_add = s.str();
    } catch (...) {};

    for(int s = iProPack->GetSignals()->size()-1; s >= 0; s--){
        if(!iProPack->GetSignals()->at(s).Plot()){ continue; }
        HWrapper * temp = new HWrapper(*iProPack->GetSignals()->at(s).GetAvailableHWrapper());
        temp->SetFillStyle(0,0);
        temp->SetLineWidth(3,iProPack->GetSignals()->at(s).GetColor());
        leg->AddEntry(temp->GetHisto(),(iProPack->GetSignals()->at(s).GetLabelForLegend() + sig_add).c_str(),"l");
    }

    leg->SetBorderSize(0);
    leg->SetFillColor(0);
    // leg->SetFillStyle(1001);

    return leg;
}

// Make background stack
THStack * Stacker::GetBackgroundStack(ProPack const * iProPack, string const iName, double const iMaxY, bool reverse) const {

	// Obtain a reference HWrapper from which to extract options
	HWrapper refHisto = HWrapper(*(iProPack->GetAvailableProcess().GetHistoForSignal(iName)));
	if(refHisto.IsTH2F()){ cerr << "ERROR: trying to build THStack from TH2F with plot named '" << iName << "'" << endl; exit(1); }

	double maxY = iMaxY;
	string stackName = string(iName+"_stack");
	THStack * result = new THStack(stackName.c_str(), stackName.c_str());

	// Add each MC background first if we have them
	if(iProPack->PrepareMCbackgrounds()){
        if(reverse) {
            for( auto it = iProPack->GetMCbackgrounds()->rbegin(); it != iProPack->GetMCbackgrounds()->rend(); ++it){
                if(!it->Plot()){ continue; }
                int color = it->GetColor();
                HWrapper toAdd(*(it->GetHistoForSignal(iName)));
                toAdd.SetFillStyle(1001,color);
                toAdd.SetLineWidth(0,color);
                toAdd.GetHisto()->GetYaxis()->SetRangeUser(minY,maxY);
                toAdd.GetHisto()->GetXaxis()->SetRangeUser(toAdd.GetMinXVis(), toAdd.GetMaxXVis());
                result->Add((TH1F*)toAdd.GetHisto());
            }
        } else {
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
	if (iProPack->PrepareMCbackgrounds()) {
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
			if (iProPack->PrepareMCbackgrounds() && stackSignals) {
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
pair<TGraphAsymmErrors*, TGraphAsymmErrors*>
Stacker::AddAsymmShapeSystematicErrors(HWrapper& backgroundSum, string plotName)
{
    float sum_err_up = 0.;
    float sum_err_down = 0.;
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

        sum_err_up += errorUpAbs;
        sum_err_down += errorDownAbs;

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

    if (plotName == "Events")
        std::cout << plotName << " integral: " << backgroundSumHisto->Integral()
            << " +" << sum_err_up << ", -" << sum_err_down << std::endl;

    pair<TGraphAsymmErrors*,TGraphAsymmErrors*> errPair(backgroundErrAbs,backgroundErrRel);
    return errPair;
}
