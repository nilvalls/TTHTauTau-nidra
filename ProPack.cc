
#define ProPack_cxx
#include "ProPack.h"

using namespace std;



// Default constructor
ProPack::ProPack(){
	analyzed			= false;
	normalizedToLumi	= false;

	haveCollisions		= false;
	haveMCbackgrounds	= false;
	haveBackgrounds		= false;
	haveSignals			= false;

	prepareCollisions	= false;
}


ProPack::ProPack(ProPack const & iProPack){

	params					= iProPack.GetParams();
	collisions				= Process(*(iProPack.GetCollisions()));
	mcBackgrounds			= vector<Process>(*(iProPack.GetMCbackgrounds()));
	signals					= vector<Process>(*(iProPack.GetSignals()));
	pContainer				= PContainer(*(iProPack.GetPContainer()));

	analyzed				= iProPack.Analyzed();
	normalizedToLumi		= iProPack.NormalizedToLumi();
	integratedLumiInInvPb	= iProPack.GetIntegratedLumiInInvPb();

	haveCollisions			= iProPack.HaveCollisions();
	haveMCbackgrounds		= iProPack.HaveMCbackgrounds();
	haveBackgrounds			= iProPack.HaveBackgrounds();
	haveSignals				= iProPack.HaveSignals();

	prepareCollisions		= iProPack.PrepareCollisions();
	prepareMCbackgrounds	= iProPack.PrepareMCbackgrounds();
	prepareSignals			= iProPack.PrepareSignals();

}

ProPack::ProPack(const map<string,string>& iParams){

		mcBackgrounds.clear();
		signals.clear();

		params 					= iParams;

		analyzed				= false;

		haveCollisions			= false;
		haveMCbackgrounds		= false;
		haveBackgrounds			= false;
		haveSignals				= false;

		prepareCollisions		= false;
		prepareMCbackgrounds	= false;
		prepareSignals			= false;

		string lumiExpression	= params["luminosity"];
		integratedLumiInInvPb	= atof(lumiExpression.substr(0,lumiExpression.find('/')).c_str());
		string lumiUnits		= lumiExpression.substr(lumiExpression.find('/'));
}


// Default destructor
ProPack::~ProPack(){
}

// Update this ProPack with info from input ProPack
void ProPack::Update(ProPack * iProPack){
	vector<Process*> processes = GetProcesses();

	for(unsigned int p=0; p < processes.size(); p++){
		Process* processToUpdate = processes.at(p);
		string const processToUpdateName = processToUpdate->GetShortName();
		if(!iProPack->GetPContainer()->Exists(processToUpdateName)){ continue; }
		processToUpdate->Update((iProPack->GetPContainer()->Get(processToUpdateName)));
	}
}

bool const ProPack::Analyzed() const{ return analyzed; }
bool const ProPack::NormalizedToLumi() const{ return normalizedToLumi; }

Process* ProPack::GetCollisions(){ return &collisions; }
vector<Process>* ProPack::GetMCbackgrounds(){ return &mcBackgrounds; }
vector<Process>* ProPack::GetSignals(){ return &signals; }
PContainer* ProPack::GetPContainer(){ return &pContainer; }

Process const * ProPack::GetCollisions() const { return &collisions; }
vector<Process> const * ProPack::GetMCbackgrounds() const { return &mcBackgrounds; }
vector<Process> const * ProPack::GetSignals() const { return &signals; }
PContainer const * ProPack::GetPContainer() const { return &pContainer; }

void ProPack::SetAnalyzed(){
	analyzed = true;
}

void ProPack::SetCollisions(Process& iProcess, const vector<string> iNtuplePath) {
	collisions = Process(iProcess);
	if (iNtuplePath.size() != 0) { collisions.SetNtuplePaths(iNtuplePath); }
	haveCollisions = true;
	prepareCollisions = true;
}

void ProPack::AddMCbackground(Process& iProcess, const vector<string> iNtuplePath) {

	// Check that incoming process is not already present in the vector
	string newTopoShortName = iProcess.GetShortName();
	for(unsigned int t=0; t<mcBackgrounds.size(); t++){
		string thisTopoShortName = mcBackgrounds.at(t).GetShortName();
		if(thisTopoShortName.compare(newTopoShortName)==0){ cerr << "ERROR: trying to add process \"" << newTopoShortName << "\" but it already exists in the vector of MC backgrounds" << endl; exit(1);}
	}
	mcBackgrounds.push_back(iProcess);
	if (iNtuplePath.size() != 0) { mcBackgrounds.back().SetNtuplePaths(iNtuplePath); }

}

void ProPack::CombineAndRemoveMCbackgrounds(const vector<string> iBackgrounds, const string iShortName, const string iNiceName, const string iLabelForLegend, const int iColor){
	cout << "\tCombining into '" << iNiceName << "' the following: ";
	for(unsigned int b = 0; b < iBackgrounds.size(); b++){
		cout << iBackgrounds.at(b);
		if(b != (iBackgrounds.size()-1)){ cout << ", "; }
	}
	cout << endl;

    vector<string> bkg_to_remove;
	unsigned int numberOfProcessesCombined = 0;
    // TODO Should never use a pointer into a vector (the Process pointed to
    // changes when a Process positioned before it is deleted)
	Process* result = NULL;
	for (const auto& backgroundToAdd: iBackgrounds) {
		if (!HaveMCbackground(backgroundToAdd)) {
            cout << RED << "WARNING: trying to combine background '" << backgroundToAdd << "' but it is not in background vector." << NOCOLOR << endl;
            continue;
        }
		if(result == NULL){
			result = GetProcess(backgroundToAdd);
		}else{
			result->Add(GetProcess(backgroundToAdd));
			bkg_to_remove.push_back(backgroundToAdd);
		}
		numberOfProcessesCombined++;
	}

	if(numberOfProcessesCombined > 0){
		result->SetShortName(iShortName);
        result->SetNiceName(iNiceName);
		result->SetLabelForLegend(iLabelForLegend);
		result->SetColor(iColor);
	}

    // Remove backgrounds now that everything else is handled
    for (const auto& bkg: bkg_to_remove) {
        vector<Process>::iterator ibkg;
        for (ibkg = mcBackgrounds.begin(); ibkg->GetShortName() != bkg and ibkg != mcBackgrounds.end(); ++ibkg);
        if (ibkg != mcBackgrounds.end())
            mcBackgrounds.erase(ibkg);
    }
}

void ProPack::AddSignal(Process& iProcess, const vector<string> iNtuplePath) {
	// Check that incoming process is not already present in the vector
	string newTopoShortName = iProcess.GetShortName();
	for(unsigned int t=0; t<signals.size(); t++){
		string thisTopoShortName = signals.at(t).GetShortName();
		if(thisTopoShortName.compare(newTopoShortName)==0){ cerr << "ERROR: trying to add process \"" << newTopoShortName << "\" but it already exists in the vector of signals" << endl; exit(1);}
	}
	signals.push_back(iProcess);
	if (iNtuplePath.size() != 0) { signals.back().SetNtuplePaths(iNtuplePath); }
}

bool const ProPack::HaveCollisions() const { return haveCollisions; }
bool const ProPack::HaveMCbackgrounds() const {	return (mcBackgrounds.size()>0); }
bool const
ProPack::HaveBackgrounds() const
{
    return mcBackgrounds.size() > 0;
}

bool const ProPack::HaveMCbackground(const string iShortName){
	bool result = false;
	for(unsigned int t=0; t<mcBackgrounds.size(); t++){
		if(mcBackgrounds.at(t).GetShortName().compare(iShortName)==0){ return true; }
	}
	return result;
}
bool const ProPack::HaveSignals() const {		return (signals.size()>0); }
bool const ProPack::PrepareCollisions() const {	return prepareCollisions; }
bool const ProPack::PrepareMCbackgrounds() const {	
	for(unsigned int b = 0; b < GetMCbackgrounds()->size(); b++){ if(GetMCbackgrounds()->at(b).Plot()){ return true; } }
	return false;
}
bool const ProPack::PrepareSignals() const {	return HaveSignals(); }
bool const ProPack::PrepareBackgrounds() const {	return HaveBackgrounds(); }
void ProPack::PrepareCollisions(bool const iVal){	prepareCollisions = (iVal && haveCollisions && GetCollisions()->Plot());	}

map<string,string> const ProPack::GetParams() const { return params; }
double const ProPack::GetIntegratedLumiInInvPb() const { return integratedLumiInInvPb; }

Process ProPack::GetAvailableProcess() const {
	Process const * result = NULL;
	if(HaveCollisions()){			result = &collisions;			 }
	else if(HaveMCbackgrounds()){	result = &mcBackgrounds.front(); }	
	else if(HaveSignals()){			result = &signals.front();		 }

	return (*result);
}


/*// Cut flow getters
CutFlow ProPack::GetCollisionsCutFlow() const {
	if(!prepareCollisions){ cerr << "ERROR: trying to obtain Collisions cutflow but have no Collisions" << endl; exit(1); }
	return CutFlow(*collisions.GetCutFlow());
}

vector<CutFlow>	ProPack::GetMCbackgroundsCutFlows() const {
	if(!PrepareMCbackgrounds()){ cerr << "ERROR: trying to obtain mc background cutflows but have no none" << endl; exit(1); }
	vector<CutFlow> result;
	for(unsigned int b = 0; b < mcBackgrounds.size(); b++){ result.push_back(*mcBackgrounds.at(b).GetCutFlow()); }
	return result;
}

vector<CutFlow>	ProPack::GetSignalsCutFlows() const {
	if(!PrepareSignals()){ cerr << "ERROR: trying to obtain signal cutflows but have no none" << endl; exit(1); }
	vector<CutFlow> result;
	for(unsigned int b = 0; b < signals.size(); b++){
		result.push_back(*signals.at(b).GetCutFlow());
	}
	return result;
} //*/

HWrapper const ProPack::GetAvailableHWrapper() const { return (*(GetAvailableProcess().GetAvailableHWrapper())); }
HWrapper const ProPack::GetAvailableHWrapper(string const iName) const { 
	HWrapper result = (*(GetAvailableProcess().GetAvailableHWrapper(iName))); 
	return result;
}




int const ProPack::GetNumberOfPlots() const { return GetAvailableProcess().GetNumberOfPlots(); }

HContainer const ProPack::GetSignalsHWrappers(string const iName) const {
	HContainer result;
	for(unsigned int s = 0; s < signals.size(); s++){ 
		//if(!signals.at(s).Plot()){ continue; }
		result.Add(signals.at(s).GetLabelForLegend(), *(signals.at(s).GetHContainerForSignal()->Get(iName)));
	}
	return result;
}

HContainer const ProPack::GetMCbackgroundsHWrappers(string const iName) const {
	HContainer result;
	for(unsigned int s = 0; s < mcBackgrounds.size(); s++){
		//if(!mcBackgrounds.at(s).Plot()){ continue; }
		result.Add(mcBackgrounds.at(s).GetLabelForLegend(), *(mcBackgrounds.at(s).GetHContainerForSignal()->Get(iName)));
	}
	return result;
}

HContainer const ProPack::GetBackgroundsHWrappers(string const iName) const {
	HContainer result;
	for(unsigned int s = 0; s < mcBackgrounds.size(); s++){
		//if(!mcBackgrounds.at(s).Plot()){ continue; }
		result.Add(mcBackgrounds.at(s).GetLabelForLegend(), *(mcBackgrounds.at(s).GetHContainerForSignal()->Get(iName)));
	}
	return result;
}


void ProPack::NormalizeToLumi(){

	if(!NormalizedToLumi()){
		// Calculate effective integrated lumi in case we've only run on a fraction of the collision events
		float effectiveIntegratedLumi = integratedLumiInInvPb;
		if(PrepareCollisions()){
			float fractionCollisionsAnalyzed = collisions.GetNOEanalyzed()/(double)collisions.GetNOEinNtuple();
			effectiveIntegratedLumi = integratedLumiInInvPb*fractionCollisionsAnalyzed;
			collisions.GetCutFlow()->RegisterCutFromLast("Lumi norm", 2, 1);
			collisions.BuildNormalizedCutFlow();
		}

		// Normalize MC backgrounds
		for(unsigned int b = 0; b < GetMCbackgrounds()->size(); b++){
			GetMCbackgrounds()->at(b).NormalizeToLumi(effectiveIntegratedLumi);
			GetMCbackgrounds()->at(b).BuildNormalizedCutFlow();
		}

		// Normalize signals
		for(unsigned int s = 0; s < GetSignals()->size(); s++){
			GetSignals()->at(s).NormalizeToLumi(effectiveIntegratedLumi);
			GetSignals()->at(s).BuildNormalizedCutFlow();
		}
	}

	normalizedToLumi = true;

}

// Take processes from the PContainer and distribute them appropriately in the ProPack
void ProPack::DistributeProcesses(){
	if(pContainer.size()==0){ cerr << "ERROR: PContainer contains zero processes" << endl; exit(1); }
	if(pContainer.GetNumberOfCollisionProcesses()>1){ cerr << "ERROR: PContainer contains " << pContainer.GetNumberOfCollisionProcesses() << " processes with type \"collisions\"" << endl; exit(1); }
	if(pContainer.GetNumberOfMCbackgroundProcesses()<1){ cout << "WARNING: Zero MC background processes found in PContainer" << endl; }

	mcBackgrounds.clear();
	signals.clear();
	vector<string> names = pContainer.GetNames();
	cout << endl;
	for(unsigned int n = 0; n < names.size(); n++){
		Process * process = pContainer.Get(names.at(n));
		process->SetPlot(params);
		string name = string(30-process->GetShortName().length(), ' ');
		name += process->GetShortName() + "  ";
		if(process->Plot()){ name += "[   plotting   ]"; }
		else{ name += "[ NOT plotting ]"; }

		if(process->IsCollisions()){		cout << "\tSetting  collisions    with name: " << name << endl; SetCollisions(*process); }
		if(process->IsMCbackground()){ 		cout << "\tAdding   mcBackground  with name: " << name << endl; AddMCbackground(*process); }
		if(process->IsSignal()){			cout << "\tAdding   signal        with name: " << name << endl; AddSignal(*process); }
	}
	cout << endl;

	normalizedToLumi = false;

}

vector<Process*> ProPack::GetProcesses(){
	vector<Process*> result;
	if(PrepareCollisions()){	result.push_back(GetCollisions()); };

	for(unsigned int b = 0; b < GetMCbackgrounds()->size(); b++ ){ result.push_back(&GetMCbackgrounds()->at(b)); }
	for(unsigned int s = 0; s < GetSignals()->size(); s++ ){ result.push_back(&GetSignals()->at(s)); }

	return result;
}


Process* ProPack::GetProcess(string const iName) {
	
	
	Process* result = NULL;

	// Look in Collisions
	if(PrepareCollisions()){
		if(GetCollisions()->GetShortName().compare(iName) == 0){ result = GetCollisions(); }
	}

	// Look in MC backgrounds
	for(unsigned int b = 0; b < GetMCbackgrounds()->size(); b++ ){ 
		Process* thisProcess = &GetMCbackgrounds()->at(b);
		if(thisProcess->GetShortName().compare(iName)==0){
			if(result != NULL){ cerr << "ERROR: Trying to get process with short name '" << iName << "' but there is more than one process with that name." << endl; PrintProcessList(); exit(1); }
			result = thisProcess;
		}
	}

	// Look in Signals
	for(unsigned int s = 0; s < GetSignals()->size(); s++ ){
		Process* thisProcess = &GetSignals()->at(s);
		if(thisProcess->GetShortName().compare(iName)==0){
			if(result != NULL){ cerr << "ERROR: Trying to get process with short name '" << iName << "' but there is more than one process with that name." << endl; PrintProcessList(); exit(1); }
			result = thisProcess;
		}
	}

	// Check we found one!
	if(result == NULL){ cerr << "ERROR: Trying to get process with short name '" << iName << "' but there is no process with that name." << endl; PrintProcessList(); exit(1); }

	return result;
	
}

string ProPack::GetProccessNamesToAnalyze(){
	string result = "";
	vector<string> names = pContainer.GetNames();
	for(unsigned int n = 0; n < names.size(); n++){ result += (" " + names.at(n)); }
	return result;
}

string ProPack::GetProccessNamesToPlot(){
	string result = "";
	vector<string> names = pContainer.GetNames();
	for(unsigned int n = 0; n < names.size(); n++){ 
		if(PlotProcess(names.at(n))){ result += (" " + names.at(n)); }
	}
	return result;
}

bool ProPack::PlotProcess(string const iThisProcess){
	bool result;
	if(params["plot"].compare("All")==0){
		result = true;
	}else{
		string enabledProcesses = " " + params["plot"] + " ";
		string thisProcess			 = " " + iThisProcess + " ";
		result = IsStringThere(thisProcess,enabledProcesses);
	}
	return result;
}

bool const ProPack::IsStringThere(string const iNeedle, string const iHaystack) const {
	string haystack = iHaystack;
	string needle = iNeedle;
	bool const result = ((haystack.find(needle) < haystack.length()));
	return result;
}

void ProPack::PrintProcessList() const {
	cout << "\t--- Process List ---" << endl;
	if(PrepareCollisions()){	cout << "\tCollisions........" << GetCollisions()->GetShortName() << endl; }
	for(unsigned int b = 0; b < GetMCbackgrounds()->size(); b++ ){ cout << "\tMC background....." << (GetMCbackgrounds()->at(b).GetShortName()) << endl; }
	for(unsigned int s = 0; s < GetSignals()->size(); s++ ){ cout << "\tSignal............" << (GetSignals()->at(s).GetShortName()) << endl; }

}

ClassImp(ProPack)
