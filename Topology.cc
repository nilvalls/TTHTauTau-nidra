
#define Topology_cxx
#include "Topology.h"

using namespace std;



// Default constructor
Topology::Topology(){
	analyzed = false;
}


// Default destructor
Topology::~Topology(){
}


void Topology::SetHistos(vector<HistoWrapper*>* iHistos){
	histos = vector<HistoWrapper*>(*iHistos);
}

void Topology::SetHistosLS(vector<HistoWrapper*>* iHistos){
	histosLS = vector<HistoWrapper*>(*iHistos);
}

void Topology::SetCutFlow(CutFlow*){

}

void Topology::SetCutFlowLS(CutFlow*){

}


int Topology::GetOne() {
	histos.push_back(new HistoWrapper());
	return (histos.front())->GetNum();
}

int Topology::GetTwo(){
	histosLS.push_back(new HistoWrapper());
	return (histosLS.front())->GetNum();
}

void Topology::SetAnalyzed(){
	analyzed = true;
}

bool Topology::Analyzed(){
	return analyzed;
}


ClassImp(Topology)
