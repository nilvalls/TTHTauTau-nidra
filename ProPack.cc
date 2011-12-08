
#define ProPack_cxx
#include "ProPack.h"

using namespace std;



// Default constructor
ProPack::ProPack(){
	analyzed			= false;

	haveCollisions		= false;
	haveMCbackgrounds	= false;
	haveBackgrounds		= false;
	haveQCD				= false;
	haveSignals			= false;

	prepareCollisions	= false;
	prepareQCD			= false;
}


ProPack::ProPack(ProPack const & iProPack){

	params					= iProPack.GetParams();
	collisions				= Process(*(iProPack.GetCollisions()));
	qcd						= Process(*(iProPack.GetQCD()));
	mcBackgrounds			= vector<Process>(*(iProPack.GetMCbackgrounds()));
	signals					= vector<Process>(*(iProPack.GetSignals()));

	analyzed				= iProPack.Analyzed();
	integratedLumiInInvPb	= iProPack.GetIntegratedLumiInInvPb();

	haveCollisions			= iProPack.HaveCollisions();
	haveQCD					= iProPack.HaveQCD();
	haveMCbackgrounds		= iProPack.HaveMCbackgrounds();
	haveBackgrounds			= iProPack.HaveBackgrounds();
	haveSignals				= iProPack.HaveSignals();

	prepareCollisions		= iProPack.PrepareCollisions();
	prepareQCD				= iProPack.PrepareQCD();
	prepareMCbackgrounds	= iProPack.PrepareMCbackgrounds();
	prepareSignals			= iProPack.PrepareSignals();

}

ProPack::ProPack(const map<string,string>& iParams){

		mcBackgrounds.clear();
		signals.clear();

		params 					= iParams;

		analyzed				= false;

		haveCollisions			= false;
		haveQCD					= false;
		haveMCbackgrounds		= false;
		haveBackgrounds			= false;
		haveSignals				= false;

		prepareCollisions		= false;
		prepareQCD				= false;
		prepareMCbackgrounds	= false;
		prepareSignals			= false;

		string lumiExpression	= params["luminosity"];
		integratedLumiInInvPb	= atof(lumiExpression.substr(0,lumiExpression.find('/')).c_str());
		string lumiUnits		= lumiExpression.substr(lumiExpression.find('/'));

}


// Default destructor
ProPack::~ProPack(){
}

bool const ProPack::Analyzed() const{
	return analyzed;
}

Process* ProPack::GetCollisions(){ return &collisions; }
Process* ProPack::GetQCD(){ return &qcd; }
vector<Process>* ProPack::GetMCbackgrounds(){ return &mcBackgrounds; }
vector<Process>* ProPack::GetSignals(){ return &signals; }

Process const * ProPack::GetCollisions() const { cout << "const" << endl; return &collisions; }
Process const * ProPack::GetQCD() const { return &qcd; }
vector<Process> const * ProPack::GetMCbackgrounds() const { return &mcBackgrounds; }
vector<Process> const * ProPack::GetSignals() const { return &signals; }

void ProPack::SetAnalyzed(){
	analyzed = true;
}

void ProPack::SetCollisions(Process& iProcess){
	collisions = Process(iProcess);
	haveCollisions = true;
}

void ProPack::SetQCD(Process& iProcess){
	qcd = Process(iProcess);
	haveQCD = true;
}

void ProPack::AddMCbackground(Process& iProcess){

	// Check that incoming process is not already present in the vector
	string newTopoShortName = iProcess.GetShortName();
	for(unsigned int t=0; t<mcBackgrounds.size(); t++){
		string thisTopoShortName = mcBackgrounds.at(t).GetShortName();
		if(thisTopoShortName.compare(newTopoShortName)==0){ cerr << "ERROR: trying to add process \"" << newTopoShortName << "\" but it already exists in the vector of MC backgrounds" << endl; exit(1);}
	}
	mcBackgrounds.push_back(iProcess);

}

void ProPack::AddSignal(Process& iProcess){
	// Check that incoming process is not already present in the vector
	string newTopoShortName = iProcess.GetShortName();
	for(unsigned int t=0; t<signals.size(); t++){
		string thisTopoShortName = signals.at(t).GetShortName();
		if(thisTopoShortName.compare(newTopoShortName)==0){ cerr << "ERROR: trying to add process \"" << newTopoShortName << "\" but it already exists in the vector of signals" << endl; exit(1);}
	}
	signals.push_back(iProcess);
}

bool const ProPack::HaveCollisions() const { return haveCollisions; }
bool const ProPack::HaveQCD() const {			return haveQCD; }
bool const ProPack::HaveMCbackgrounds() const {	return (mcBackgrounds.size()>0); }
bool const ProPack::HaveBackgrounds() const {	return (mcBackgrounds.size()>0 || haveQCD); }
bool const ProPack::HaveSignals() const {		return (signals.size()>0); }
bool const ProPack::PrepareCollisions() const {	return prepareCollisions; }
bool const ProPack::PrepareQCD() const {		return prepareQCD; }
bool const ProPack::PrepareMCbackgrounds() const {	return HaveMCbackgrounds(); }
bool const ProPack::PrepareSignals() const {	return HaveSignals(); }
bool const ProPack::PrepareBackgrounds() const {	return HaveBackgrounds(); }
void ProPack::PrepareCollisions(bool const iVal){	prepareCollisions = (iVal && haveCollisions);	}
void ProPack::PrepareQCD(bool const iVal){			prepareQCD = (iVal && haveCollisions);			}


map<string,string> const ProPack::GetParams() const { return params; }
double const ProPack::GetIntegratedLumiInInvPb() const { return integratedLumiInInvPb; }











void ProPack::BuildQCD(){
	if(!PrepareQCD()){ return; }
	NormalizeToLumi();

	Process qcdTemp = Process(collisions);
	qcdTemp.SetShortName("QCD");
	qcdTemp.SetNiceName("QCD");
	qcdTemp.SetLabelForLegend("QCD");
	qcdTemp.SetColor(atoi((params["QCDcolor"]).c_str()));
	//qcdTemp->SetCutFlow(); !!!!!!!!!!!!!!!!!

	// Subtract MC backgrounds from collisions, positivize and scale by Ros/ls	
	HContainer hContainerForQCD = HContainer(*(collisions.GetHContainerForQCD()));
	for(unsigned int b = 0; b < GetMCbackgrounds()->size(); b++){
		hContainerForQCD.Add(*(GetMCbackgrounds()->at(b).GetHContainerForQCD()), -1);
	}
	hContainerForQCD.Positivize(); 
	hContainerForQCD.ScaleBy(atof((params["osls"]).c_str()));

	// Set colors and put it in process here
}

Process ProPack::GetAvailableProcess() const {
	Process const * result = NULL;
	if(HaveCollisions()){			result = &collisions;			 }
	else if(HaveQCD()){				result = &qcd;					 }
	else if(HaveMCbackgrounds()){	result = &mcBackgrounds.front();}	
	else if(HaveSignals()){			result = &signals.front();		 }

	return *result;
}


// Cut flow getters
CutFlow ProPack::GetCollisionsCutFlow() const {
	if(!prepareCollisions){ cerr << "ERROR: trying to obtain Collisions cutflow but have no Collisions" << endl; exit(1); }
	return CutFlow(*collisions.GetCutFlow());
}

CutFlow ProPack::GetQCDCutFlow() const {
	if(!prepareQCD){ cerr << "ERROR: trying to obtain QCD cutflow but have no QCD" << endl; exit(1); }
	return CutFlow(*qcd.GetCutFlow());
}

vector<CutFlow>	ProPack::GetMCbackgroundsCutFlows() const {
	if(!PrepareMCbackgrounds()){ cerr << "ERROR: trying to obtain mc background cutflows but have no none" << endl; exit(1); }
	vector<CutFlow> result;
	for(unsigned int b = 0; b < mcBackgrounds.size(); b++){
		result.push_back(*mcBackgrounds.at(b).GetCutFlow());
	}
	return result;
}

vector<CutFlow>	ProPack::GetSignalsCutFlows() const {
	if(!PrepareSignals()){ cerr << "ERROR: trying to obtain signal cutflows but have no none" << endl; exit(1); }
	vector<CutFlow> result;
	for(unsigned int b = 0; b < signals.size(); b++){
		result.push_back(*signals.at(b).GetCutFlow());
	}
	return result;
}

HWrapper const ProPack::GetAvailableHWrapper() const { return (*(GetAvailableProcess().GetAvailableHWrapper())); }
int const ProPack::GetNumberOfPlots() const { return GetAvailableProcess().GetNumberOfPlots(); }

HContainer const ProPack::GetSignalsHWrappers(string const iName) const {
	HContainer result;
	for(unsigned int s = 0; s < signals.size(); s++){ result.Add(signals.at(s).GetLabelForLegend(), *(signals.at(s).GetHContainerForSignal()->Get(iName))); }
	return result;
}

HContainer const ProPack::GetMCbackgroundsHWrappers(string const iName) const {
	HContainer result;
	for(unsigned int s = 0; s < mcBackgrounds.size(); s++){ result.Add(mcBackgrounds.at(s).GetLabelForLegend(), *(mcBackgrounds.at(s).GetHContainerForSignal()->Get(iName))); }
	return result;
}

HContainer const ProPack::GetBackgroundsHWrappers(string const iName) const {
	HContainer result;
	for(unsigned int s = 0; s < mcBackgrounds.size(); s++){ result.Add(mcBackgrounds.at(s).GetLabelForLegend(), *(mcBackgrounds.at(s).GetHContainerForSignal()->Get(iName))); }
	if(prepareQCD){ result.Add(qcd.GetLabelForLegend(), *(qcd.GetHContainerForSignal()->Get(iName))); }
	return result;
}


void ProPack::NormalizeToLumi(){
	
	// Calculate effective integrated lumi in case we've only run on a fraction of the collision events
	float effectiveIntegratedLumi = integratedLumiInInvPb;
	if(PrepareCollisions()){
		float fractionCollisionsAnalyzed = collisions.GetNOEanalyzed()/(double)collisions.GetNOEinNtuple();
		effectiveIntegratedLumi = integratedLumiInInvPb*fractionCollisionsAnalyzed;
	}

	// Normalize MC backgrounds
	for(unsigned int b = 0; b < GetMCbackgrounds()->size(); b++){
		GetMCbackgrounds()->at(b).NormalizeToLumi(effectiveIntegratedLumi);
	}

	// Normalize signals
	for(unsigned int s = 0; s < GetSignals()->size(); s++){
		GetSignals()->at(s).NormalizeToLumi(effectiveIntegratedLumi);
	}

}


ClassImp(ProPack)
