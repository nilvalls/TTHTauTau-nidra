
#define HWrapper_cxx
#include "HWrapper.h"

using namespace std;

// Default constructor
HWrapper::HWrapper() : histo(0) {}

// Copy constructor
HWrapper::HWrapper(HWrapper const & iHWrapper){
	histo = NULL;
	isTH1F = iHWrapper.IsTH1F();
	isTH2F = iHWrapper.IsTH2F();
	if(isTH1F){ TH1Type = "th1f"; }
	this->SetHisto(*iHWrapper.GetHisto());

	name					= iHWrapper.GetName();
	subdir					= iHWrapper.GetSubDir();
	xMinVis					= iHWrapper.GetMinXVis();
	xMaxVis					= iHWrapper.GetMaxXVis();
	yMinVis					= iHWrapper.GetMinYVis();
	yMaxVis					= iHWrapper.GetMaxYVis();
	zMinVis					= iHWrapper.GetMinZVis();
	zMaxVis					= iHWrapper.GetMaxZVis();
	logx					= iHWrapper.GetLogX();
	logy					= iHWrapper.GetLogY();
	logz					= iHWrapper.GetLogZ();
	showOverFlow			= iHWrapper.ShowOverFlow();
	showUnderFlow			= iHWrapper.ShowUnderFlow();
	centerLabels			= iHWrapper.CenterLabels();
	hasVariableWidthBins	= iHWrapper.HasVariableWidthBins();
	NOEraw					= iHWrapper.GetNOEraw();
}


HWrapper::HWrapper(string iName, string iSubDir, string iType, const Config& iConfig){
	histo = NULL;
	name = iName;
	subdir = iSubDir;
	const int nBinsX = iConfig.pInt("numBinsX");
	const float xMin = iConfig.pDouble("xMin");
	const float xMax = iConfig.pDouble("xMax");

	if(iType.compare("th1f") == 0){ // Specific parameters for TH1F
		isTH1F = true; isTH2F = false;
		histo1 = TH1F(iName.c_str(), iName.c_str(), nBinsX, xMin, xMax);
		histo = &histo1;
		showOverFlow	= iConfig.pBool("showOF"); 
		showUnderFlow	= iConfig.pBool("showUF"); 
	}else if(iType.compare("th2f") == 0){ // Specific paramaters for TH2F
		isTH1F = false; isTH2F = true;
		const int nBinsY = iConfig.pInt("numBinsY");
		const float yMin = iConfig.pDouble("yMin");
		const float yMax = iConfig.pDouble("yMax");
		histo2 = TH2F(iName.c_str(), iName.c_str(), nBinsX, xMin, xMax, nBinsY, yMin, yMax);
		histo = &histo2;

		// Visible z axis range
		histo->GetZaxis()->SetTitle((iConfig.pString("zTitle")).c_str());
		logz = iConfig.pBool("logz");
	}else{
		cerr << "ERROR: trying to make a HWrapper but TH1 type \"" << iType << "\" invalid" << endl; exit(1);
	}

	// Error setup
	histo->SetDefaultSumw2(kFALSE);
	for(int bin=0; bin <= histo->GetNbinsX(); bin++){
		histo->SetBinError(bin,0);	
	}
	//histo->Sumw2();

	// Visible x axis range
	xMinVis = iConfig.pDouble("xMinVis");
	xMaxVis = iConfig.pDouble("xMaxVis");
	histo->GetXaxis()->SetRangeUser(xMinVis, xMaxVis);

	// Visible y axis range
	yMinVis = iConfig.pDouble("yMinVis");
	yMaxVis = iConfig.pDouble("yMaxVis");
	histo->GetYaxis()->SetRangeUser(yMinVis, yMaxVis);

	// x,y axis titles
	histo->GetXaxis()->SetTitle((iConfig.pString("xTitle")).c_str());
	histo->GetYaxis()->SetTitle((iConfig.pString("yTitle")).c_str());

	// Do log versions?
	logx = iConfig.pBool("logx");
	logy = iConfig.pBool("logy");
	
	// Other
	showText		= iConfig.pBool("showText");
	centerLabels	= iConfig.pBool("centerLabels");
	NOEraw			= 0;

}

// Default destructor
HWrapper::~HWrapper(){
	histo = NULL;
}

// Getter methods
TH1 * 			HWrapper::GetHisto() { return (histo); }
TH1 const * 	HWrapper::GetHisto() const { return (histo); }
bool const		HWrapper::IsTH1F() const { return isTH1F; }
bool const		HWrapper::IsTH2F() const { return isTH2F; }
string			HWrapper::GetName() const { return name; }
string			HWrapper::GetSubDir() const { return subdir; }
string			HWrapper::GetXTitle() const { return string(histo->GetXaxis()->GetTitle()); }
string			HWrapper::GetYTitle() const { return string(histo->GetYaxis()->GetTitle()); }
string			HWrapper::GetZTitle() const { return string(histo->GetZaxis()->GetTitle()); }
float const		HWrapper::GetMinXVis() const { return xMinVis; }
float const		HWrapper::GetMaxXVis() const { return xMaxVis; }
float const		HWrapper::GetMinYVis() const { return yMinVis; }
float const		HWrapper::GetMaxYVis() const { return yMaxVis; }
float const		HWrapper::GetMinZVis() const { return zMinVis; }
float const		HWrapper::GetMaxZVis() const { return zMaxVis; }
bool const		HWrapper::GetLogX() const { return logx; }
bool const		HWrapper::GetLogY() const { return logy; }
bool const		HWrapper::GetLogZ() const { return logz; }
bool const		HWrapper::ShowOverFlow() const { return showOverFlow; }
bool const		HWrapper::ShowUnderFlow() const { return showUnderFlow; }
bool const		HWrapper::CenterLabels() const { return centerLabels; }
bool const		HWrapper::HasVariableWidthBins() const { return false; }
bool const		HWrapper::ShowText() const { return showText; }
double const	HWrapper::GetNOEraw() const { return NOEraw; }


// Setter methods
void HWrapper::SetIsTH1F(bool const iValue){
	isTH1F = iValue;
	isTH2F = !iValue;
}

void HWrapper::SetIsTH2F(bool const iValue){
	isTH1F = !iValue;
	isTH2F = iValue;
}

void HWrapper::SetHisto(TH1 const & iHisto){

	if(isTH1F && isTH2F) { cerr << "ERROR: trying to set histo in HWrapper but it's both a TH1F and a TH2F" << endl; exit(1); }
	else if(isTH1F){ histo = &histo1; }
	else if(isTH2F){ histo = &histo2; }
	else { cerr << "ERROR: trying to set histo in HWrapper but it's neither a TH1F nor a TH2F" << endl; exit(1); }

	TTimeStamp timestamp;
	TRandom random;
	stringstream ssName; ssName.str("");
	ssName << timestamp.GetTimeSpec().tv_sec << timestamp.GetTimeSpec().tv_nsec << random.Gaus();

	histo = (TH1*)iHisto.Clone((ssName.str()).c_str());
}

void HWrapper::SetHisto(TH1* iHisto){

	if(isTH1F && isTH2F){
		cerr << "ERROR: trying to set histo in HWrapper but it's both a TH1F and a TH2F" << endl;
		exit(1);
	}else if(isTH1F){
		histo1 = TH1F(*(TH1F*)iHisto);
		histo = &histo1;
	}else if(isTH2F){
		histo2 = TH2F(*(TH2F*)iHisto);
		histo = &histo2;
	}else { cerr << "ERROR: trying to set histo in HWrapper but it's neither a TH1F nor a TH2F" << endl; exit(1); }


}

void HWrapper::SetLineWidth(int iVal, int iColor){
	histo->SetLineWidth(iVal);
	histo->SetLineColor(iColor);
}

void HWrapper::SetFillStyle(int const iVal, int const iColor){
	histo->SetFillStyle(iVal);
	if(iVal!=0){ // Solid fill
		histo->SetFillColor(iColor);
		histo->SetLineColor(kBlack);
		histo->SetLineWidth(1);
	}
}

void HWrapper::SetMaximum(double const iValue){ histo->SetMaximum(iValue); }
void HWrapper::ResetMaximum(double const iFactor){ histo->SetMaximum(iFactor*histo->GetBinContent(histo->GetMaximumBin())); }
void HWrapper::SetFillColor(int const iValue){ histo->SetFillColor(iValue); }
void HWrapper::SetLineColor(int const iValue){ histo->SetLineColor(iValue); }
void HWrapper::SetMarkerStyle(int const iValue){ histo->SetMarkerStyle(iValue); }



// Other methods
void HWrapper::Add(TH1 const & iHisto, double iFactor){ 
	if(iFactor != iFactor){ cerr << "ERROR: trying to Add(TH1&, nan)" << endl; exit(1); }
		cout << &iHisto << endl;
	histo->Add(&iHisto, iFactor);
}
void HWrapper::Add(HWrapper const & iHisto, double const iFactor){ 
	histo->Add((iHisto.GetHisto()), iFactor);
}
void HWrapper::ScaleBy(double const iFactor){
	if(iFactor != iFactor){ cerr << "ERROR: trying to ScaleBy(nan)" << endl; exit(1); }
	histo->Scale(iFactor);
}

void HWrapper::ScaleErrorBy(double const iFactor){	
	if(iFactor != iFactor){ cerr << "ERROR: trying to ScaleErrorBy(nan)" << endl; exit(1); }
	for(int b=0; b<=histo->GetNbinsX(); b++){ histo->SetBinError(b, iFactor*(histo->GetBinError(b))); }
}

void HWrapper::AddRelErrorInQuadrature(double const iError){	
	if(iError != iError){ cerr << "ERROR: trying to AddRelErrorInQuadrature(nan)" << endl; exit(1); }
	for(int b=0; b<=histo->GetNbinsX(); b++){ 
        AddRelErrorInQuadrature(iError, b); 
    }
}

void HWrapper::AddRelErrorInQuadrature(double const iError, int iBin){	
	if(iError != iError){ cerr << "ERROR: trying to AddRelErrorInQuadrature(nan)" << endl; exit(1); }
    double newError = sqrt(histo->GetBinError(iBin)*histo->GetBinError(iBin) + iError*histo->GetBinContent(iBin)*iError*histo->GetBinContent(iBin));
    histo->SetBinError(iBin,newError); 
}

void HWrapper::NormalizeTo(double const iNormalization){	ScaleBy(iNormalization/(double)histo->Integral()); }

void HWrapper::Fill(double iValue, double iWeight){ 
	if(!isTH1F){ cerr << "ERROR: trying to use Fill(double, double) on a TH2F. Must use Fill(double, double, double)" << endl; exit(1); }
	((TH1F*)histo)->Fill(iValue, iWeight);
	NOEraw++;
}


void HWrapper::Fill(double iValue1, double iValue2, double iWeight){
	if(!isTH2F){ cerr << "ERROR: trying to use Fill(double, double, double) on a TH1F. Must use Fill(double, double)" << endl; exit(1); }
	((TH2F*)histo)->Fill(iValue1, iValue2, iWeight);
	NOEraw++;
}

// Zero negative bins only
void HWrapper::Positivize(){
	if(isTH1F){
		for(int b = 1; b <= histo->GetNbinsX(); b++){
			float oldContent = histo->GetBinContent(b);
			if(oldContent < 0){ histo->SetBinContent(b, 0); }
		}
	}else{
		for(int bx = 1; bx <= histo->GetNbinsX(); bx++){
			for(int by = 1; by <= histo->GetNbinsY(); by++){
				float oldContent = histo->GetBinContent(bx,by);
				if(oldContent < 0){ histo->SetBinContent(bx, by, 0); }
			}
		}
	
	}
}

void HWrapper::FillRandom(string const iFunction){ histo->FillRandom(iFunction.c_str()); }

double const HWrapper::GetMaximum() const { return histo->GetBinContent(histo->GetMaximumBin()); }
double const HWrapper::GetMaximumWithError() const {
	double result = 0;
	for(int b = 1; b <= histo->GetNbinsX(); b++){
		double content = histo->GetBinContent(b);	
		double error = histo->GetBinError(b);	
		if((content+error) > result){ result = content+error; }
	}
	return result;
}

void HWrapper::PrintInfo(){
	cout << "\n\n" << endl;
	cout << "\tName......." << GetName() << endl;
	cout << "\tType......." << TH1Type  << endl;
	cout << "\tNbinsX....." << histo->GetNbinsX() << endl;
	cout << "\tMin X......" << histo->GetBinLowEdge(1) << endl;
	cout << "\tMax X......" << histo->GetBinLowEdge(histo->GetNbinsX()) << endl;
	cout << "\tIntegral..." << histo->Integral() << endl;
	cout << "\tMax........" << GetMaximum() << endl;
	cout << "\tMax w err.." << GetMaximumWithError() << endl;
	cout << "--------------------------" << endl;

	for(int b=0; b <= histo->GetNbinsX(); b++){
		cout << "\t" << b << "\t" << histo->GetBinLowEdge(b) << "\t" << histo->GetBinContent(b) << "\t+/-\t" << histo->GetBinError(b) << endl;
	}
	cout << "==========================\n\n" << endl;



}

ClassImp(HWrapper)
