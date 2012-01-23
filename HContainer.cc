
#define HContainer_cxx
#include "HContainer.h"

using namespace std;



// Default constructor
HContainer::HContainer(){}

// Copy constructor
HContainer::HContainer(HContainer const & iHContainer){
	container = map<string,HWrapper>(iHContainer.GetContainer());
}

// Default destructor
HContainer::~HContainer(){}

void HContainer::Add(HWrapper const & iHWrapper) { container.insert(make_pair(iHWrapper.GetName(), HWrapper(iHWrapper))); }
void HContainer::Add(string const iName, HWrapper const & iHWrapper) { container.insert(make_pair(iName, HWrapper(iHWrapper))); }

HWrapper * HContainer::Get(string const iName){
	if(container.find(iName) == container.end()){ cerr << "ERROR: HWrapper named " << iName << " not found" << endl; exit(1); }
	return &(container.find(iName)->second);
}

HWrapper const * HContainer::Get(string const iName) const{
	if(container.find(iName) == container.end()){ cerr << "ERROR: HWrapper named " << iName << " not found" << endl; exit(1); }
	return &(container.find(iName)->second);
}

TH1 const * HContainer::GetHisto(string iName) const { return (Get(iName)->GetHisto()); }

vector<string> const HContainer::GetNames() const {
	vector<string> result;
	for(map<string,HWrapper>::const_iterator it = container.begin(); it != container.end(); it++){ result.push_back(it->first); }
	return result;
}

map<string,HWrapper> const & HContainer::GetContainer() const { return container; }

int const HContainer::size() const { return container.size(); }
void HContainer::clear(){ container.clear(); }

map<string, HWrapper>::const_iterator HContainer::begin() const { return (container.begin()); }
map<string, HWrapper>::const_iterator HContainer::end() const { return (container.end()); }


void HContainer::Fill(string const iName, double const iValue, float const iWeight){ if(Exists(iName)){ Get(iName)->Fill(iValue, iWeight); } }
void HContainer::Fill(string const iName, double const iValue1, double const iValue2, float const iWeight){ if(Exists(iName)){ Get(iName)->Fill(iValue1, iValue2, iWeight); } }

bool HContainer::Exists(string const iName){ return (container.find(iName) != container.end()); }

void HContainer::SetMarkerStyle(int const iValue){
	for(map<string, HWrapper>::iterator ite = container.begin(); ite != container.end(); ite++){ ite->second.SetMarkerStyle(iValue); }
}

void HContainer::SetFillStyle(int const iValue){
	for(map<string, HWrapper>::iterator ite = container.begin(); ite != container.end(); ite++){ ite->second.SetFillStyle(iValue); }
}
void HContainer::SetFillColor(int const iValue){
	for(map<string, HWrapper>::iterator ite = container.begin(); ite != container.end(); ite++){ ite->second.SetFillColor(iValue); }
}
void HContainer::SetLineColor(int const iValue){
	for(map<string, HWrapper>::iterator ite = container.begin(); ite != container.end(); ite++){ ite->second.SetLineColor(iValue); }
}
void HContainer::SetLineWidth(int const iValue1, int const iValue2){
	for(map<string, HWrapper>::iterator ite = container.begin(); ite != container.end(); ite++){ ite->second.SetLineWidth(iValue1, iValue2); }
}

void HContainer::NormalizeTo(double const iValue){
	for(map<string, HWrapper>::iterator ite = container.begin(); ite != container.end(); ite++){ ite->second.NormalizeTo(iValue); }
}

void HContainer::ScaleBy(double const iValue){
	for(map<string, HWrapper>::iterator ite = container.begin(); ite != container.end(); ite++){ ite->second.ScaleBy(iValue); }
}

void HContainer::ApplyRosls(double const iValue, CutFlow const * iCutFlow){
	bool chargeProductApplied = (iCutFlow->GetCutPosition("ChargeProduct") >= 0);
	bool osRequested = false;
	if(chargeProductApplied){ osRequested = (iCutFlow->GetMaxThresholds().find("ChargeProduct")->second == -1.0); }

	for(map<string, HWrapper>::iterator ite = container.begin(); ite != container.end(); ite++){
		if(ite->first.compare("ChargeProduct_LS") == 0){
			TH1F* histo = (TH1F*)ite->second.GetHisto();
			int osBin, lsBin;
			for(unsigned int b = 1; b <= histo->GetNbinsX(); b++){
				if(histo->GetBinLowEdge(b) == -1){ osBin = b; }	
				else if(histo->GetBinLowEdge(b) == 1){ lsBin = b; }	
			}

			if(!chargeProductApplied){ // Copy LS to OS and scale OS by Rosls 
				histo->SetBinContent(osBin, iValue*histo->GetBinContent(lsBin));
				histo->SetBinError(osBin, iValue*histo->GetBinError(lsBin));
			}else if(osRequested){ // Move LS to OS and scale it by Rosls
				histo->SetBinContent(osBin, iValue*histo->GetBinContent(lsBin));
				histo->SetBinError(osBin, iValue*histo->GetBinError(lsBin));
				histo->SetBinContent(lsBin,0);
				histo->SetBinError(lsBin,0);
			}
		}else{ // For all other plots...
			if(!chargeProductApplied){  ite->second.ScaleBy(1+iValue); } // Scale by 1+Rosls
			else if(osRequested){ ite->second.ScaleBy(iValue); } // Scale by Rosls
		}
	}
}

void HContainer::Add(HContainer const & iContainer, double const iFactor){
	for(map<string, HWrapper>::iterator ite = container.begin(); ite != container.end(); ite++){ 
		string name = ite->first;
		ite->second.Add(*(iContainer.Get(name)), iFactor);
	}
}

void HContainer::Positivize(){
	for(map<string, HWrapper>::iterator ite = container.begin(); ite != container.end(); ite++){ ite->second.Positivize(); }
}


ClassImp(HContainer)
