 #pragma warning

#define HMath_cxx
#include "HMath.h"

using namespace std;


// Default ructor
HMath::HMath(){}

// Copy ructor
HMath::HMath(HMath const & iHMath){}

// Default destructor
HMath::~HMath(){}


TH1F  * HMath::Integrated(TH1F * iHisto, bool  fromLeft) {
	TH1F * result = (TH1F*)iHisto->Clone((string(string(iHisto->GetName())+"_int")).c_str());

	float sum = 0;
	float error = 0;
	if(fromLeft){
		for(int bin=0; bin <= result->GetNbinsX()+1; bin++){
			sum += result->GetBinContent(bin);	
			error = sqrt(pow(error,2)+pow(result->GetBinContent(bin),2)); 
			result->SetBinContent(bin, sum);	
			result->SetBinError(bin, error);	
		}
		result->SetName((string(string(result->GetName())+"_LeftIntegrated")).c_str());
	}else{
		for(int bin=result->GetNbinsX()+1; bin >= 0; bin--){
			sum += result->GetBinContent(bin);	
			error = sqrt(pow(error,2)+pow(result->GetBinContent(bin),2)); 
			result->SetBinContent(bin, sum);	
			result->SetBinError(bin, error);	
		}
		result->SetName((string(string(result->GetName())+"_RightIntegrated")).c_str());
	}

	return result;
}

HWrapper  * HMath::Integrated(HWrapper  * iHWrapper, bool  fromLeft)  {
	if(iHWrapper->IsTH2F()){ cerr << "ERROR: trying to integrate a TH2F: " << iHWrapper->GetName() << endl; exit(1); }
	HWrapper * result = new HWrapper(*iHWrapper);
	TH1* histo = new TH1(*(iHWrapper->GetHisto()));
	result->SetHisto(Integrated((TH1F*)histo, fromLeft));
	delete histo;
	return result;
}


HWrapper  * HMath::IntegratedFromLeft (HWrapper  * iMassWrapper)  { return Integrated(iMassWrapper,true); }
HWrapper  * HMath::IntegratedFromRight(HWrapper  * iMassWrapper)  { return Integrated(iMassWrapper,false); }
TH1F  * HMath::IntegratedFromLeft (TH1F  * iHisto)  { return Integrated(iHisto,true); }
TH1F  * HMath::IntegratedFromRight(TH1F  * iHisto)  { return Integrated(iHisto,false); }


TH1F  * HMath::RightIntegratedStoRootB(TH1F  * iSignal, TH1F  * iBackground)  {
		cout << __FILE__ << ":" << __LINE__ << endl;
		IntegratedFromRight(iSignal);
		cout << __FILE__ << ":" << __LINE__ << endl;
		IntegratedFromRight(iBackground);
		cout << __FILE__ << ":" << __LINE__ << endl;
	return StoRootB(IntegratedFromRight(iSignal),IntegratedFromRight(iBackground));
}

TH1F  * HMath::LeftIntegratedStoRootB(TH1F  * iSignal, TH1F  * iBackground)  {
	return StoRootB(IntegratedFromLeft(iSignal),IntegratedFromLeft(iBackground));
}

TH1F * HMath::StoRootB(TH1F  * iSignal, TH1F  * iBackground)  {
		cout << __FILE__ << ":" << __LINE__ << endl;
	TH1F * result	= new TH1F(*iSignal);
		cout << __FILE__ << ":" << __LINE__ << endl;
		cout << "result content: " << result->GetBinLowEdge(1) << " " << result->GetBinContent(1) << endl;

	for(int bin=0; bin <= iBackground->GetNbinsX()+1; bin++){
		double bkgContent = iBackground->GetBinContent(bin);
		double sigContent = iSignal->GetBinContent(bin);
		double content	= 0;
		double bkgError = iBackground->GetBinError(bin);
		double sigError = iSignal->GetBinError(bin);
		double error	= 0;
		if(bkgContent>0){
			content = sigContent/(double)sqrt(bkgContent);
			error	= sqrt(pow(sigError,2)/bkgContent + (0.25*pow(sigContent*bkgError,2)/pow(bkgContent,3)));
		}
		cout << __FILE__ << ":" << __LINE__ << endl;
		cout << bin << " " << content << " " << error << endl;
		result->SetBinContent(bin, content);	
		cout << __FILE__ << ":" << __LINE__ << endl;
		result->SetBinError(bin, error);	
		cout << __FILE__ << ":" << __LINE__ << endl;
	}
		cout << __FILE__ << ":" << __LINE__ << endl;
	result->SetName((string(string(result->GetName())+"_StoRootB")).c_str());
	result->SetMaximum(result->GetBinContent(result->GetMaximumBin()));

	return result;
}

