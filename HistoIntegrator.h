#ifndef HistoIntegrator_h
#define HistoIntegrator_h

#include <iostream>
#include <utility>
#include <algorithm>
#include <TFile.h>
#include "HistoWrapper.h"

using namespace std;

class HistoIntegrator{
	private:
	map<int,double> weight;
	map<int,double> generated;

	public:
		// Default constructor
		HistoIntegrator(){
		}

		HistoWrapper* Integrate(HistoWrapper* iHistoWrapper, bool fromLeft){
			HistoWrapper* result = new HistoWrapper(*iHistoWrapper);
			TH1F* histo = new TH1F(*(TH1F*)(iHistoWrapper->GetHisto()));

			float sum = 0;
			if(fromLeft){
				for(int bin=1; bin <= histo->GetNbinsX(); bin++){
					sum += histo->GetBinContent(bin);	
					histo->SetBinContent(bin, sum);	
				}
				histo->SetName((string(histo->GetName())+"_LeftIntegrated").c_str());
				result->SetYlabel("Accumulated Events");
				result->SetOutputFilename((result->GetOutputFilename())+"_LeftIntegrated");

			}else{
				for(int bin=histo->GetNbinsX(); bin >= 1; bin--){
					sum += histo->GetBinContent(bin);	
					histo->SetBinContent(bin, sum);	
				}
				histo->SetName((string(histo->GetName())+"_RightIntegrated").c_str());
				result->SetYlabel("Accumulated Events");
				result->SetOutputFilename((result->GetOutputFilename())+"_RightIntegrated");
			}

			result->SetHisto(histo);

			return result;
		}

		TH1F* Integrate(TH1F* iHisto, bool fromLeft){
			TH1F* histo = (TH1F*)iHisto->Clone((string(string(iHisto->GetName())+"_LeftIntegrated")).c_str());

			float sum = 0;
			if(fromLeft){
				for(int bin=1; bin <= histo->GetNbinsX(); bin++){
					sum += histo->GetBinContent(bin);	
					histo->SetBinContent(bin, sum);	
				}

			}else{
				for(int bin=histo->GetNbinsX(); bin >= 1; bin--){
					sum += histo->GetBinContent(bin);	
					histo->SetBinContent(bin, sum);	
				}
			}

			return histo;
		}


		HistoWrapper* IntegrateFromLeft (HistoWrapper* iMassWrapper){ return Integrate(iMassWrapper,true); }
		HistoWrapper* IntegrateFromRight(HistoWrapper* iMassWrapper){ return Integrate(iMassWrapper,false); }
		TH1F* IntegrateFromLeft (TH1F* iHisto){ return Integrate(iHisto,true); }
		TH1F* IntegrateFromRight(TH1F* iHisto){ return Integrate(iHisto,false); }


		TH1F* SoverSqrtSpB_Right(TH1F* iSignal, TH1F* iBackground){
			TH1F* bkg	= IntegrateFromRight((TH1F*)(iBackground->Clone()));
			TH1F* sig	= IntegrateFromRight((TH1F*)(iSignal->Clone()));
			TH1F* result = (TH1F*)sig->Clone();
			cout << "bkg: " << bkg->Integral() << " sig: " << sig->Integral() << endl;
			cout << bkg->GetNbinsX() << " bins" << endl;

			for(int bin=1; bin <= bkg->GetNbinsX(); bin++){
				double bkgContent = bkg->GetBinContent(bin);
				double sigContent = sig->GetBinContent(bin);
				double content = 0;
				if((bkgContent+sigContent)>0){
					content = sigContent/(double)sqrt(sigContent+bkgContent);
				}
				result->SetBinContent(bin, content);	
			}

			return result;
			
		}

		TH1F* SoverSqrtSpB_Left(TH1F* iSignal, TH1F* iBackground){
			TH1F* bkg	= IntegrateFromLeft((TH1F*)(iBackground->Clone()));
			TH1F* sig	= IntegrateFromLeft((TH1F*)(iSignal->Clone()));
			TH1F* result = (TH1F*)sig->Clone();

			for(int bin=1; bin <= bkg->GetNbinsX(); bin++){
				double bkgContent = bkg->GetBinContent(bin);
				double sigContent = sig->GetBinContent(bin);
				double content = 0;

				if((bkgContent+sigContent)>0){
					content = sigContent/(double)sqrt(sigContent+bkgContent);
				}

				result->SetBinContent(bin, content);	
			}

			return result;
			
		}

};

#endif
