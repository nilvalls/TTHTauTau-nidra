
#define Topology_cxx
#include "Topology.h"

using namespace std;



// Default constructor
Topology::Topology(){
	valid = false;
	analyzed = false;
}

Topology::Topology(string iShortName, Config* iConfig){

	shortName			= iShortName;
	niceName			= iConfig->pString("niceName");
	labelForLegend		= iConfig->pString("labelForLegend");
	type				= iConfig->pString("type");
	ntuplePath			= iConfig->pString("ntuplePath");
	color				= iConfig->pInt("color");
	crossSection		= iConfig->pDouble("crossSection");
	branchingRatio		= iConfig->pDouble("branchingRatio");
	otherScaleFactor	= iConfig->pDouble("otherScaleFactor");
	NOEinDS				= iConfig->pInt("NOEinDS");
	NOEinPATuple		= iConfig->pInt("NOEinPATuple");
	NOEinNtuple			= 0;
	NOEanalyzed			= 0;

	analyzed = false;
	normalizedToLumi = false;
	lumiNorm = 0;
	valid = true;


}


// Default destructor
Topology::~Topology(){
}

void Topology::SetHistosForSignal(vector<HistoWrapper*>* iHistos){
	if(!valid){ cerr << "ERROR: topology not valid (used default constructor)" << endl; exit(1); }
	histosForSignal = vector<HistoWrapper*>(*iHistos);
}

void Topology::SetHistosForQCD(vector<HistoWrapper*>* iHistos){
	if(!valid){ cerr << "ERROR: topology not valid (used default constructor)" << endl; exit(1); }
	histosForQCD = vector<HistoWrapper*>(*iHistos);
}

void Topology::SetCutFlow(CutFlow* iCutFlow){
	if(!valid){ cerr << "ERROR: topology not valid (used default constructor)" << endl; exit(1); }
	cutFlow	= *iCutFlow;
}

void Topology::SetNOEanalyzed(double iEvents){ NOEanalyzed = iEvents; }
void Topology::SetNOEinNtuple(double iEvents){ NOEinNtuple = iEvents; }
void Topology::SetColor(int iColor){ color = iColor; }

CutFlow* Topology::GetCutFlow(){ return &cutFlow; }

string Topology::GetShortName(){		return shortName;		}
string Topology::GetNiceName(){			return niceName;		}
string Topology::GetLabelForLegend(){	return labelForLegend;	}
string Topology::GetType(){				return type;			}

bool Topology::IsMC(){ return ((type.compare("mcBackground")==0) || (type.compare("signal")==0)); }

string Topology::GetNtuplePath(){
	if(!valid){ cerr << "ERROR: topology not valid (used default constructor)" << endl; exit(1); }
	return ntuplePath;
}

int Topology::GetNOEinDS(){			return NOEinDS;		}
int Topology::GetNOEinPATuple(){	return NOEinPATuple;}
int Topology::GetNOEinNtuple(){		return NOEinNtuple; }
int Topology::GetNOEanalyzed(){		return NOEanalyzed; }



void Topology::SetShortName(string iVal){ shortName = iVal; }
void Topology::SetNiceName(string iVal){ niceName = iVal; }
void Topology::SetLabelForLegend(string iVal){ labelForLegend = iVal; }


void Topology::SetAnalyzed(){
	if(!valid){ cerr << "ERROR: topology not valid (used default constructor)" << endl; exit(1); }
	analyzed = true;
}

bool Topology::Analyzed(){
	if(!valid){ cerr << "ERROR: topology not valid (used default constructor)" << endl; exit(1); }
	return analyzed;
}


vector<HistoWrapper*>* Topology::GetHistosForSignal(){ return &histosForSignal; }

vector<HistoWrapper*>* Topology::GetHistosForQCD(){ return &histosForQCD; }

HistoWrapper* Topology::GetHistoForSignal(int iHisto){ 
	if(iHisto >= histosForSignal.size()){ cerr << "ERROR: trying to obtain histo for signal number " << iHisto << " but only have " << histosForSignal.size() << endl; }
	return (histosForSignal.at(iHisto));
}

int Topology::GetColor(){ return color; }

HistoWrapper* Topology::GetHistoForQCD(int iHisto){ 
	if(iHisto >= histosForQCD.size()){ cerr << "ERROR: trying to obtain histo for QCD number " << iHisto << " but only have " << histosForQCD.size() << endl; }
	return (histosForQCD.at(iHisto));
}


int Topology::GetNumberOfPlots(){
	return histosForSignal.size();
}

HistoWrapper* Topology::GetAvailableHistoWrapper(){
	if(histosForSignal.size()==0){ cerr << "ERROR: trying to obtain a sample HistoWrapper from topology but there are none" << endl; }
	return (histosForSignal.front());
}

// Massive set histogram properties
void Topology::SetMarkerStyle(int iVal){ for(unsigned int h = 0; h < histosForSignal.size(); h++){ histosForSignal.at(h)->GetHisto()->SetMarkerStyle(iVal); } }
void Topology::SetFillStyle(int iVal){ for(unsigned int h = 0; h < histosForSignal.size(); h++){ histosForSignal.at(h)->SetFillStyle(iVal,color); } }
void Topology::SetFillColor(int iVal){ for(unsigned int h = 0; h < histosForSignal.size(); h++){ histosForSignal.at(h)->GetHisto()->SetFillColor(iVal); } }
void Topology::SetLineColor(int iVal){ for(unsigned int h = 0; h < histosForSignal.size(); h++){ histosForSignal.at(h)->GetHisto()->SetLineColor(iVal); } }
void Topology::SetLineWidth(int iVal){ for(unsigned int h = 0; h < histosForSignal.size(); h++){ histosForSignal.at(h)->SetLineWidth(iVal,color); } }


Topology* Topology::Clone(){
	Topology* result = new Topology(*this);
	result->SetHistosForSignal(new vector<HistoWrapper*>(histosForSignal));
	result->SetHistosForQCD(new vector<HistoWrapper*>(histosForQCD));

	return result;
}

void Topology::NormalizeToLumi(double iIntLumi){
	if((type.compare("collisions")!=0) && !normalizedToLumi){
		double expectedNOE = iIntLumi*crossSection*branchingRatio*(GetNOEanalyzed()/(double)GetNOEinNtuple());	
		NormalizeTo(expectedNOE);
	}
	normalizedToLumi = true;
}

void Topology::NormalizeToOne(){ NormalizeTo(1); normalizedToLumi = false; }

void Topology::NormalizeTo(double iNormalization){
	for(unsigned int h = 0; h < histosForSignal.size(); h++){ 
		histosForSignal.at(h)->NormalizeTo(iNormalization);
		histosForQCD.at(h)->NormalizeTo(iNormalization);
	}
}

void Topology::ScaleBy(double iScale){
	for(unsigned int h = 0; h < histosForSignal.size(); h++){ 
		histosForSignal.at(h)->ScaleBy(iScale);
		histosForQCD.at(h)->ScaleBy(iScale);
	}
}


ClassImp(Topology)
