
#define HistoWrapper_cxx
#include "HistoWrapper.h"

using namespace std;



// Default constructor
HistoWrapper::HistoWrapper(){ histo = NULL; }

HistoWrapper::HistoWrapper(string iName, string iType, Config* iConfig){
	
	if(iType.compare("th1f") == 0){ // Specific parameters for TH1F
		int nBinsX = iConfig->pInt("numBins");
		float xMin = iConfig->pDouble("xMin");
		float xMax = iConfig->pDouble("xMax");
		histo = new TH1F(iName.c_str(), iName.c_str(), nBinsX, xMin, xMax);
	}else if(iType.compare("th2f") == 0){ // Specific paramaters for TH2F
		int nBinsX = iConfig->pInt("numBinsX");
		int nBinsY = iConfig->pInt("numBinsY");
		float xMin = iConfig->pDouble("xMin");
		float xMax = iConfig->pDouble("xMax");
		float yMin = iConfig->pDouble("yMin");
		float yMax = iConfig->pDouble("yMax");
		histo = new TH2F(iName.c_str(), iName.c_str(), nBinsX, xMin, xMax, nBinsY, yMin, yMax);

		yMinVis = iConfig->pDouble("yMinVis");
		yMaxVis = iConfig->pDouble("yMaxVis");
		histo->GetYaxis()->SetRangeUser(yMinVis, yMaxVis);

		zTitle = iConfig->pString("zTitle");
		histo->GetZaxis()->SetTitle(zTitle.c_str());
	}

	// Visible x axis range
	xMinVis = iConfig->pDouble("xMinVis");
	xMaxVis = iConfig->pDouble("xMaxVis");
	histo->GetXaxis()->SetRangeUser(xMinVis, xMaxVis);

	// x,y axis titles
	xTitle = iConfig->pString("xTitle");
	yTitle = iConfig->pString("yTitle");
	histo->GetXaxis()->SetTitle(xTitle.c_str());
	histo->GetYaxis()->SetTitle(yTitle.c_str());

	logx = iConfig->pBool("logx");
	logy = iConfig->pBool("logy");
	logz = iConfig->pBool("logz");

	//showOF  = true



}

// Clone method
HistoWrapper* HistoWrapper::Clone(){
	HistoWrapper* result = new HistoWrapper(*this);
	result->SetHisto(histo);
	return result;
}

// Default destructor
HistoWrapper::~HistoWrapper(){}

// Getter methods
TH1* HistoWrapper::GetHisto(){	return histo; }

string HistoWrapper::GetName(){ return histo->GetName(); }

string  HistoWrapper::GetXtitle(){ return xTitle; }
string  HistoWrapper::GetYtitle(){ return yTitle; }
string  HistoWrapper::GetZtitle(){ return zTitle; }

float  HistoWrapper::GetXminVis(){ return xMinVis; }
float  HistoWrapper::GetXmaxVis(){ return xMaxVis; }
float  HistoWrapper::GetYminVis(){ return yMinVis; }
float  HistoWrapper::GetYmaxVis(){ return yMaxVis; }

bool HistoWrapper::GetLogX(){ return logx; }
bool HistoWrapper::GetLogY(){ return logy; }
bool HistoWrapper::GetLogZ(){ return logz; }

// Setter methods
void HistoWrapper::SetHisto(TH1* iHisto){ histo = (TH1*)iHisto->Clone(); }
void HistoWrapper::SetLineWidth(int iVal, int iColor){ histo->SetLineWidth(iVal); histo->SetLineColor(iColor); }

void HistoWrapper::SetFillStyle(int iVal, int iColor){
	histo->SetFillStyle(iVal);
	if(iVal==1001){ // Solid fill
		histo->SetFillColor(iColor);
		histo->SetLineColor(kBlack);
		histo->SetLineWidth(1);
	}
}

// Other methods
void HistoWrapper::Draw(string iOptions){ histo->Draw(iOptions.c_str()); }
void HistoWrapper::Add(TH1* iHisto, double iFactor){ histo->Add(iHisto, iFactor); }
void HistoWrapper::Add(HistoWrapper* iHisto, double iFactor){ histo->Add(iHisto->GetHisto(), iFactor); }
void HistoWrapper::ScaleBy(double iFactor){	histo->Scale(iFactor); }
void HistoWrapper::NormalizeTo(double iNormalization){	histo->Scale(iNormalization/(double)histo->Integral()); }

// Zero negative bins only
void HistoWrapper::Positivize(){
	for(unsigned int b = 1; b <= histo->GetNbinsX(); b++){
		float oldContent = histo->GetBinContent(b);
		if(oldContent < 0){ histo->SetBinContent(b, 0); }
	}
}

ClassImp(HistoWrapper)
