
#define TopoPack_cxx
#include "TopoPack.h"

using namespace std;



// Default constructor
TopoPack::TopoPack(){
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

void TopoPack::BuildQCD(){

}


ClassImp(TopoPack)
