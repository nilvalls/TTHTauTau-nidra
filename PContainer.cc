
#define PContainer_cxx
#include "PContainer.h"

using namespace std;



// Default constructor
PContainer::PContainer(){}

// Copy constructor
PContainer::PContainer(PContainer const & iPContainer){
	container = map<string,Process>(*(iPContainer.GetContainer()));
}

// Default destructor
PContainer::~PContainer(){}

void PContainer::Add(Process const & iProcess) { container.insert(make_pair(iProcess.GetShortName(), Process(iProcess))); }
void PContainer::Add(string const iName, Process const & iProcess) { container.insert(make_pair(iName, Process(iProcess))); }

Process * PContainer::Get(string const iName){
	if(container.find(iName) == container.end()){ cerr << "ERROR: Process named " << iName << " not found" << endl; exit(1); }
	return &(container.find(iName)->second);
}

Process const * PContainer::Get(string const iName) const{
	if(container.find(iName) == container.end()){ cerr << "ERROR: Process named " << iName << " not found" << endl; exit(1); }
	return &(container.find(iName)->second);
}

vector<string> const PContainer::GetNames() const {
	vector<string> result;
	for(map<string,Process>::const_iterator it = container.begin(); it != container.end(); it++){ result.push_back(it->first); }
	return result;
}

map<string,Process> * PContainer::GetContainer(){ return &container; }
map<string,Process> const * PContainer::GetContainer() const { return &container; }

int const PContainer::size() const { return container.size(); }
void PContainer::clear(){ container.clear(); }

map<string, Process>::const_iterator PContainer::begin() const { return (container.begin()); }
map<string, Process>::const_iterator PContainer::end() const { return (container.end()); }


vector<Process*> PContainer::GetCollisionProcesses(){
	vector<Process*> result; result.clear();
	for(map<string,Process>::iterator p = container.begin(); p != container.end(); p++){
		if(p->second.IsCollisions()){ result.push_back(&(p->second)); }
	}
	return result;
}

vector<Process*> PContainer::GetQCDProcesses(){
	vector<Process*> result; result.clear();
	for(map<string,Process>::iterator p = container.begin(); p != container.end(); p++){
		if(p->second.IsQCD()){ result.push_back(&(p->second)); }
	}
	return result;
}

vector<Process*> PContainer::GetMCbackgroundProcesses(){
	vector<Process*> result; result.clear();
	for(map<string,Process>::iterator p = container.begin(); p != container.end(); p++){
		if(p->second.IsMCbackground()){ result.push_back(&(p->second)); } 
	}
	return result;
}

vector<Process*> PContainer::GetSignalProcesses(){
	vector<Process*> result; result.clear();
	for(map<string,Process>::iterator p = container.begin(); p != container.end(); p++){
		if(p->second.IsSignal()){ result.push_back(&(p->second)); }
	}
	return result;
}



int PContainer::GetNumberOfCollisionProcesses(){
	int result = 0;
	for(map<string,Process>::const_iterator p = container.begin(); p != container.end(); p++){
		if(p->second.IsCollisions()){ result++; }
	}
	return result;
}

int PContainer::GetNumberOfQCDProcesses(){
	int result = 0;
	for(map<string,Process>::const_iterator p = container.begin(); p != container.end(); p++){
		if(p->second.IsQCD()){ result++; }
	}
	return result;
}

int PContainer::GetNumberOfMCbackgroundProcesses(){
	int result = 0;
	for(map<string,Process>::const_iterator p = container.begin(); p != container.end(); p++){
		if(p->second.IsMCbackground()){ result++; }
	}
	return result;
}

int PContainer::GetNumberOfSignalProcesses(){
	int result = 0;
	for(map<string,Process>::const_iterator p = container.begin(); p != container.end(); p++){
		if(p->second.IsSignal()){ result++; }
	}
	return result;
}



ClassImp(PContainer)
