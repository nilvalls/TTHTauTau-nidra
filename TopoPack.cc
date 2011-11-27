
#define TopoPack_cxx
#include "TopoPack.h"

using namespace std;



// Default constructor
TopoPack::TopoPack(){
	//cout << "\n\n\t\tWARNING: called TopoPack's default constructor!!!\n\n" << endl;
	collisions			= NULL;
	qcd					= NULL;
	mcBackgrounds		= NULL;
	signals				= NULL;

	analyzed			= false;

	haveCollisions		= false;
	haveMCbackgrounds	= false;
	haveBackgrounds		= false;
	haveQCD				= false;
	haveSignals			= false;

	prepareCollisions	= false;
	prepareQCD			= false;
}

TopoPack::TopoPack(map<string,string>* iParams){
	params 				= *iParams;
	collisions			= NULL;
	qcd					= NULL;
	mcBackgrounds		= new vector<Topology*>();
	signals				= new vector<Topology*>();

	analyzed			= false;

	haveCollisions		= false;
	haveMCbackgrounds	= false;
	haveBackgrounds		= false;
	haveQCD				= false;
	haveSignals			= false;

	prepareCollisions	= false;
	prepareQCD			= false;

	string lumiExpression	= params["luminosity"];
	integratedLumiInInvPb	= atof(lumiExpression.substr(0,lumiExpression.find('/')).c_str());
	string lumiUnits		= lumiExpression.substr(lumiExpression.find('/'));

}


// Default destructor
TopoPack::~TopoPack(){
}

bool TopoPack::Analyzed(){
	return analyzed;
}

Topology* TopoPack::GetCollisions(){
	return collisions;
}

Topology* TopoPack::GetQCD(){
	return qcd;
}

vector<Topology*>* TopoPack::GetMCbackgrounds(){
	return mcBackgrounds;
}

vector<Topology*>* TopoPack::GetSignals(){
	return signals;
}

TopoPack* TopoPack::Clone(){
	TopoPack* result = new TopoPack(*this);
}

void TopoPack::SetAnalyzed(){
	analyzed = true;
}

void TopoPack::SetCollisions(Topology* iTopology){
	if(collisions != NULL){ cerr << "ERROR: trying to set collisions in topopack but collision topology already present" << endl; exit(1); }
	collisions = iTopology->Clone();
	haveCollisions = true;
}

void TopoPack::SetQCD(Topology* iTopology){
	if(qcd != NULL){ cerr << "ERROR: trying to set qcd in topopack but qcd topology already present" << endl; exit(1); }
	qcd = iTopology->Clone();
	haveQCD = true;
}

void TopoPack::AddMCbackground(Topology* iTopology){

	// Check that incoming topology is not already present in the vector
	string newTopoShortName = iTopology->GetShortName();
	for(unsigned int t=0; t<mcBackgrounds->size(); t++){
		string thisTopoShortName = mcBackgrounds->at(t)->GetShortName();
		if(thisTopoShortName.compare(newTopoShortName)==0){ cerr << "ERROR: trying to add topology \"" << newTopoShortName << "\" but it already exists in the vector of MC backgrounds" << endl; exit(1);}
	}
	mcBackgrounds->push_back(iTopology->Clone());

}

void TopoPack::AddSignal(Topology* iTopology){
	// Check that incoming topology is not already present in the vector
	string newTopoShortName = iTopology->GetShortName();
	for(unsigned int t=0; t<signals->size(); t++){
		string thisTopoShortName = signals->at(t)->GetShortName();
		if(thisTopoShortName.compare(newTopoShortName)==0){ cerr << "ERROR: trying to add topology \"" << newTopoShortName << "\" but it already exists in the vector of signals" << endl; exit(1);}
	}
	signals->push_back(iTopology->Clone());


}

bool TopoPack::HaveCollisions(){	return haveCollisions; }
bool TopoPack::HaveQCD(){			return haveQCD; }
bool TopoPack::HaveMCbackgrounds(){	return (mcBackgrounds->size()>0); }
bool TopoPack::HaveSignals(){		return (signals->size()>0); }

bool TopoPack::PrepareCollisions(){	return prepareCollisions; }
bool TopoPack::PrepareQCD(){		return prepareQCD; }

void TopoPack::PrepareCollisions(bool iVal){	prepareCollisions = (iVal && haveCollisions);	}
void TopoPack::PrepareQCD(bool iVal){			prepareQCD = (iVal && haveCollisions);			}

void TopoPack::BuildQCD(){
	if(!PrepareQCD()){ return; }
	NormalizeToLumi();

	Topology* qcdTemp = collisions->Clone();
	qcdTemp->SetShortName("QCD");
	qcdTemp->SetNiceName("QCD");
	qcdTemp->SetLabelForLegend("QCD");
	qcdTemp->SetColor(atoi((params["QCDcolor"]).c_str()));
	//qcdTemp->SetCutFlow(); !!!!!!!!!!!!!!!!!

		
	vector<HistoWrapper*>* qcdHistosForSignal = new vector<HistoWrapper*>(); qcdHistosForSignal->clear();
	for(unsigned int p = 0; p < GetNumberOfPlots(); p++){
		HistoWrapper* histo = GetCollisions()->GetHistoForQCD(p)->Clone();

		if(HaveMCbackgrounds()){
			for(unsigned int b = 0; b < GetMCbackgrounds()->size(); b++){
				HistoWrapper* mcHistoForQCD = GetMCbackgrounds()->at(b)->GetHistoForQCD(p);
				histo->Add(mcHistoForQCD, -1.0);
			}
		}

		histo->Positivize();
		histo->ScaleBy(atof((params["osls"]).c_str()));
		qcdHistosForSignal->push_back(histo);
	}

	qcdTemp->SetHistosForSignal(qcdHistosForSignal);
	qcdTemp->SetFillStyle(1001);
	SetQCD(qcdTemp);
}

Topology* TopoPack::GetAvailableTopology(){
	Topology* result = NULL;
	if(HaveCollisions()){			result = collisions;			}
	else if(HaveQCD()){				result = qcd;					}
	else if(HaveMCbackgrounds()){	result = mcBackgrounds->front();}	
	else if(HaveSignals()){			result = signals->front();		}

	return result;
}


// Cut flow getters
CutFlow*			TopoPack::GetCollisionsCutFlow(){
	if(!prepareCollisions){ cerr << "ERROR: trying to obtain Collisions cutflow but have no Collisions" << endl; exit(1); }
	return collisions->GetCutFlow();
}

CutFlow*			TopoPack::GetQCDCutFlow(){
	if(!prepareQCD){ cerr << "ERROR: trying to obtain QCD cutflow but have no QCD" << endl; exit(1); }
	return qcd->GetCutFlow();
}

vector<CutFlow*>*	TopoPack::GetMCbackgroundsCutFlows(){
	if(!HaveMCbackgrounds()){ cerr << "ERROR: trying to obtain mc background cutflows but have no none" << endl; exit(1); }
	vector<CutFlow*>* result = new vector<CutFlow*>();
	for(unsigned int b = 0; b < mcBackgrounds->size(); b++){
		result->push_back(mcBackgrounds->at(b)->GetCutFlow());
	}
	return result;
}

vector<CutFlow*>*	TopoPack::GetSignalsCutFlows(){
	if(!HaveSignals()){ cerr << "ERROR: trying to obtain signal cutflows but have no none" << endl; exit(1); }
	vector<CutFlow*>* result = new vector<CutFlow*>();
	for(unsigned int b = 0; b < signals->size(); b++){
		result->push_back(signals->at(b)->GetCutFlow());
	}
	return result;
}










HistoWrapper* TopoPack::GetAvailableHistoWrapper(){ return (GetAvailableTopology()->GetAvailableHistoWrapper()); }


int TopoPack::GetNumberOfPlots(){
	return GetAvailableTopology()->GetNumberOfPlots();
}

void TopoPack::DrawSignals(int iPlot, string iOptions){
	if(!HaveCollisions()){ return; }
	collisions->GetHistoForSignal(iPlot)->Draw(iOptions);
}

void TopoPack::DrawCollisions(int iPlot, string iOptions){
	if(!HaveSignals()){ return; }
	for(unsigned int s = 0; s < signals->size(); s++){
		signals->at(s)->GetHistoForSignal(iPlot)->Draw(iOptions);
	}
}

vector<HistoWrapper*>*	TopoPack::GetSignals(int iPlot){
	vector<HistoWrapper*>* result = new vector<HistoWrapper*>(); result->clear();
	for(unsigned int s = 0; s < signals->size(); s++){ result->push_back(signals->at(s)->GetHistoForSignal(iPlot)); }
	return result;
}

vector<HistoWrapper*>*	TopoPack::GetMCbackgrounds(int iPlot){
	vector<HistoWrapper*>* result = new vector<HistoWrapper*>(); result->clear();
	for(unsigned int b = 0; b < mcBackgrounds->size(); b++){ result->push_back(mcBackgrounds->at(b)->GetHistoForSignal(iPlot)); }
	return result;
}


THStack* TopoPack::GetBackgroundStack(int iPlot){

	double maxY = GetMaxY(iPlot);
	HistoWrapper* refHisto = GetAvailableTopology()->GetHistoForSignal(iPlot);
	string stackName = string(refHisto->GetName()+"_stack");
	THStack* result = new THStack(stackName.c_str(), stackName.c_str());

	// Add each MC background first if we have them
	if(HaveMCbackgrounds()){
		for(unsigned int b = 0; b < GetMCbackgrounds()->size(); b++){
			int color = GetMCbackgrounds()->at(b)->GetColor();
			GetMCbackgrounds()->at(b)->GetHistoForSignal(iPlot)->SetFillStyle(1001,color);
			TH1F* temp = (TH1F*)(GetMCbackgrounds()->at(b)->GetHistoForSignal(iPlot)->GetHisto());
			temp->GetYaxis()->SetRangeUser(0.001,maxY);
			result->Add(temp);
		}
	}

	// Then add QCD if we have it
	if(HaveQCD()){
		TH1* temp = GetQCD()->GetHistoForSignal(iPlot)->GetHisto();
		temp->GetYaxis()->SetRangeUser(0.001,maxY);
		result->Add(temp);
	}
	

	result->Draw("HIST");
	result->GetXaxis()->SetRangeUser(refHisto->GetXminVis(), refHisto->GetXmaxVis());
	result->GetXaxis()->SetTitle((refHisto->GetXtitle()).c_str());
	result->GetYaxis()->SetTitle((refHisto->GetYtitle()).c_str());
	result->SetMaximum(maxY);
	result->GetYaxis()->SetRangeUser(0.001,maxY);


	return result;
}

TH1* TopoPack::GetBackgroundSum(int iPlot){
	TH1* result = NULL;

	// Add each MC background first if we have them
	if(HaveMCbackgrounds()){
		for(unsigned int b = 0; b < GetMCbackgrounds()->size(); b++){
			TH1* histo = GetMCbackgrounds()->at(b)->GetHistoForSignal(iPlot)->GetHisto();
			if(result == NULL){ result = (TH1*)histo->Clone();	}
			else{				result->Add(histo);				}
		}
	}

	// Then add QCD if we have it
	if(HaveQCD()){
		TH1* histo = GetQCD()->GetHistoForSignal(iPlot)->GetHisto();
		if(result == NULL){ result = (TH1*)histo->Clone();	}
		else{				result->Add(histo);				}
	}

	return result;
}


void TopoPack::NormalizeToLumi(){
	
	// Calculate effective integrated lumi in case we've only run on a fraction of the collision events
	float effectiveIntegratedLumi = integratedLumiInInvPb;
	if(PrepareCollisions()){
		float fractionCollisionsAnalyzed = collisions->GetNOEanalyzed()/(double)collisions->GetNOEinNtuple();
		effectiveIntegratedLumi = integratedLumiInInvPb*fractionCollisionsAnalyzed;
	}

	// Normalize MC backgrounds
	for(unsigned int b = 0; b < GetMCbackgrounds()->size(); b++){
		GetMCbackgrounds()->at(b)->NormalizeToLumi(effectiveIntegratedLumi);
	}

	// Normalize signals
	for(unsigned int s = 0; s < GetSignals()->size(); s++){
		GetSignals()->at(s)->NormalizeToLumi(effectiveIntegratedLumi);
	}

}

// Figure out the maximum y value
double TopoPack::GetMaxY(int iPlot){
	double result = 0;

	// Check max y for collisions
	if(PrepareCollisions()){
		double thisMax = collisions->GetHistoForSignal(iPlot)->GetHisto()->GetMaximum();	
		if(thisMax > result){ result = thisMax; }
	}

	// Check for the background sum
	TH1* backgroundSum = GetBackgroundSum(iPlot);
	if(backgroundSum != NULL){
		double thisMax = backgroundSum->GetMaximum();
		if(thisMax > result){ result = thisMax; }
	}

	// Check max y for signals
	for(unsigned int s = 0; s < GetSignals()->size(); s++){
		double thisMax = signals->at(s)->GetHistoForSignal(iPlot)->GetHisto()->GetMaximum();	
		if(thisMax > result){ result = thisMax; }
	}
	
	return result;
}

ClassImp(TopoPack)
