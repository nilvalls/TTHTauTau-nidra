 #pragma warning

#define HMath_cxx
#include "HMath.h"

using namespace std;


// Default constructor
HMath::HMath(){}

// Copy constructor
HMath::HMath(HMath const & iHMath){}

// Default destructor
HMath::~HMath(){}


TH1F const & HMath::Integrated(TH1F const & iHisto, bool const fromLeft) const{
	TH1F result = *(TH1F*)iHisto.Clone((string(string(iHisto.GetName())+"_int")).c_str());

	float sum = 0;
	float error = 0;
	if(fromLeft){
		for(int bin=0; bin <= result.GetNbinsX()+1; bin++){
			sum += result.GetBinContent(bin);	
			error = sqrt(pow(error,2)+pow(result.GetBinContent(bin),2)); 
			result.SetBinContent(bin, sum);	
			result.SetBinError(bin, error);	
		}
		result.SetName((string(string(result.GetName())+"_LeftIntegrated")).c_str());
	}else{
		for(int bin=result.GetNbinsX()+1; bin >= 0; bin--){
			sum += result.GetBinContent(bin);	
			error = sqrt(pow(error,2)+pow(result.GetBinContent(bin),2)); 
			result.SetBinContent(bin, sum);	
			result.SetBinError(bin, error);	
		}
		result.SetName((string(string(result.GetName())+"_RightIntegrated")).c_str());
	}

	return result;
}

HWrapper const & HMath::Integrated(HWrapper const & iHWrapper, bool const fromLeft) const {
	if(iHWrapper.IsTH2F()){ cerr << "ERROR: trying to integrate a TH2F: " << iHWrapper.GetName() << endl; exit(1); }
	HWrapper result = HWrapper(iHWrapper);
	TH1* histo = new TH1(iHWrapper.GetHisto());
	result.SetHisto(Integrated(*(TH1F*)histo, fromLeft));
	delete histo;
	return result;
}


HWrapper const & HMath::IntegratedFromLeft (HWrapper const & iMassWrapper) const { return Integrated(iMassWrapper,true); }
HWrapper const & HMath::IntegratedFromRight(HWrapper const & iMassWrapper) const { return Integrated(iMassWrapper,false); }
TH1F const & HMath::IntegratedFromLeft (TH1F const & iHisto) const { return Integrated(iHisto,true); }
TH1F const & HMath::IntegratedFromRight(TH1F const & iHisto) const { return Integrated(iHisto,false); }


TH1F const & HMath::RightIntegratedStoRootB(TH1F const & iSignal, TH1F const & iBackground) const {
	return StoRootB(IntegratedFromRight(iSignal),IntegratedFromRight(iBackground));
}

TH1F const & HMath::LeftIntegratedStoRootB(TH1F const & iSignal, TH1F const & iBackground) const {
	return StoRootB(IntegratedFromLeft(iSignal),IntegratedFromLeft(iBackground));
}


TH1F const & HMath::StoRootB(TH1F const & iSignal, TH1F const & iBackground) const {
	TH1F bkg	= TH1F(iBackground);
	TH1F sig	= TH1F(iSignal);
	TH1F result	= TH1F(iSignal);

	for(int bin=0; bin <= bkg.GetNbinsX()+1; bin++){
		double bkgContent = bkg.GetBinContent(bin);
		double sigContent = sig.GetBinContent(bin);
		double content	= 0;
		double bkgError = bkg.GetBinError(bin);
		double sigError = sig.GetBinError(bin);
		double error	= 0;
		if(bkgContent>0){
			content = sigContent/(double)sqrt(bkgContent);
			error	= sqrt(pow(sigError,2)/bkgContent + (0.25*pow(sigContent*bkgError,2)/pow(bkgContent,3)));
		}
		result.SetBinContent(bin, content);	
		result.SetBinContent(bin, error);	
	}
	result.SetName((string(string(result.GetName())+"_StoRootB")).c_str());

	return result;
}


ClassImp(HMath);
