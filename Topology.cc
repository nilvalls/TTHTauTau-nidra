
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
	NOEinPATuple		= iConfig->pInt("NOEinPATuple");
	NOEinDS				= iConfig->pInt("NOEinDS");

	analyzed = false;
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

void Topology::SetCutFlow(CutFlow*){
	if(!valid){ cerr << "ERROR: topology not valid (used default constructor)" << endl; exit(1); }

}

void Topology::SetCutFlowLS(CutFlow*){
	if(!valid){ cerr << "ERROR: topology not valid (used default constructor)" << endl; exit(1); }

}

string Topology::GetShortName(){
	return shortName;
}

string Topology::GetNtuplePath(){
	if(!valid){ cerr << "ERROR: topology not valid (used default constructor)" << endl; exit(1); }
	return ntuplePath;
}

string Topology::GetType(){
	return type;
}


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




Topology* Topology::Clone(){
	Topology* result = new Topology(*this);
	result->SetHistosForSignal(new vector<HistoWrapper*>(histosForSignal));
	result->SetHistosForQCD(new vector<HistoWrapper*>(histosForQCD));

	return result;
}


ClassImp(Topology)
