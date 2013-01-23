#define __Trigger_cc 

#include "Trigger.h"

using namespace std;

// Default constructor

Trigger::~Trigger(){}


Trigger::Trigger(float iTotalLumi){
	lowEdge.clear();
	weight.clear();
	SetEfficiency("0","1");

float totalLumi = iTotalLumi;
float intLumiPeriod1 = 313.086;
float intLumiPeriod2 = 785.444;
float intLumiPeriod3 = 744.073;
float intLumiPeriod4 = totalLumi - (intLumiPeriod1 + intLumiPeriod2 + intLumiPeriod3);

//if(intLumiPeriod4<0){ cerr << "ERROR: totalLumi< 1.8/fb which makes intLumiPeriod4 negative!" << endl; exit(1); }

float lumiFractionPeriod1 = intLumiPeriod1/totalLumi;
float lumiFractionPeriod2 = intLumiPeriod2/totalLumi;
float lumiFractionPeriod3 = intLumiPeriod3/totalLumi;
float lumiFractionPeriod4 = intLumiPeriod4/totalLumi;
	
stringstream eduMuTauSS; eduMuTauSS.str("");

eduMuTauSS << "(";

eduMuTauSS << "[0]*0.5*(TMath::Erf((x-[1])/2./[2]/sqrt(x))+1.)";
eduMuTauSS << "*";
eduMuTauSS << "[3]*0.5*(TMath::Erf((x-[4])/2./[5]/sqrt(x))+1.)";
eduMuTauSS << "*";
eduMuTauSS << "([6] - exp(([7]-x)*[8]))";
eduMuTauSS << "*" << lumiFractionPeriod1;

eduMuTauSS << ")+(";

eduMuTauSS << "[9]*0.5*(TMath::Erf((x-[10])/2./[11]/sqrt(x))+1.)";
eduMuTauSS << "*";
eduMuTauSS << "[12]*0.5*(TMath::Erf((x-[13])/2./[14]/sqrt(x))+1.)";
eduMuTauSS << "*";
eduMuTauSS << "([15] - exp(([16]-x)*[17]))";
eduMuTauSS << "*" << lumiFractionPeriod2;

eduMuTauSS << ")+(";

eduMuTauSS << "[18]*0.5*(TMath::Erf((x-[19])/2./[20]/sqrt(x))+1.)";
eduMuTauSS << "*";
eduMuTauSS << "[21]*0.5*(TMath::Erf((x-[22])/2./[23]/sqrt(x))+1.)";
eduMuTauSS << "*";
eduMuTauSS << "([24] - exp(([25]-x)*[26]))";
eduMuTauSS << "*" << lumiFractionPeriod3;


eduMuTauSS << ")+(";

eduMuTauSS << "[27]*0.5*(TMath::Erf((x-[28])/2./[29]/sqrt(x))+1.)";
eduMuTauSS << "*";
eduMuTauSS << "[30]*0.5*(TMath::Erf((x-[31])/2./[32]/sqrt(x))+1.)";
eduMuTauSS << "*";
eduMuTauSS << "([33] - exp(([34]-x)*[35]))";
eduMuTauSS << "*" << lumiFractionPeriod4;

eduMuTauSS << ")";

string eduMuTauString=eduMuTauSS.str();
//cout << eduMuTauString << endl;

eduMuTau	= new TF1("eduMuTau", eduMuTauString.c_str(),0,10000);

// Eduardo's trigger for tau
//Period 1
eduMuTau->SetParameter(0,  0.992646 );  
eduMuTau->SetParameter(1,  24.9424 );  
eduMuTau->SetParameter(2,  0.956838); 

eduMuTau->SetParameter(3,  0.999999 );  
eduMuTau->SetParameter(4,  15.2712 );  
eduMuTau->SetParameter(5,  1.11822); 

eduMuTau->SetParameter(6,  0.877186 );  
eduMuTau->SetParameter(7,  10.2638 );  
eduMuTau->SetParameter(8,  0.145561); 

//Period 2
eduMuTau->SetParameter(9,  0.992646 );  
eduMuTau->SetParameter(10, 24.9424 );  
eduMuTau->SetParameter(11, 0.956838); 

eduMuTau->SetParameter(12, 0.995771 );  
eduMuTau->SetParameter(13, 41.2435 );  
eduMuTau->SetParameter(14, 1.03623); 

eduMuTau->SetParameter(15, 0.887241 );  
eduMuTau->SetParameter(16, 18.7502 );  
eduMuTau->SetParameter(17, 0.158918); 

//Period 3
eduMuTau->SetParameter(18, 1 );  
eduMuTau->SetParameter(19, 27.1817 );  
eduMuTau->SetParameter(20, 0.995052); 

eduMuTau->SetParameter(21, 1 );  
eduMuTau->SetParameter(22, 52.4528 );  
eduMuTau->SetParameter(23, 0.943697); 

eduMuTau->SetParameter(24, 0.891006 );  
eduMuTau->SetParameter(25, 17.9944 );  
eduMuTau->SetParameter(26, 0.0956964);

//Period 4
eduMuTau->SetParameter(27, 0.991206);
eduMuTau->SetParameter(28, 30.41970);
eduMuTau->SetParameter(29, 0.971579);

eduMuTau->SetParameter(30, 0.983863);
eduMuTau->SetParameter(31, 49.98690);
eduMuTau->SetParameter(32, 0.673014);

eduMuTau->SetParameter(33, 0.910624);
eduMuTau->SetParameter(34, 8.396000);
eduMuTau->SetParameter(35, 0.073500);

//*/ 


	TF1 *l1p1, *l2p1, *l3p1;
	TF1 *l1p2, *l2p2, *l3p2;
	TF1 *l1p3, *l2p3, *l3p3;

	l1p1 = new TF1("l1p1","[0]*0.5*(TMath::Erf((x-[1])/2./[2]/sqrt(x))+1.)", 0, 100);
	l2p1 = new TF1("l2p1","[0]*0.5*(TMath::Erf((x-[1])/2./[2]/sqrt(x))+1.)", 0, 100);
	l3p1 = new TF1("l3p1","([0]-exp(([1]-x)*[2]))",0,100);
	l1p2 = new TF1("l1p2","[0]*0.5*(TMath::Erf((x-[1])/2./[2]/sqrt(x))+1.)", 0, 100);
	l2p2 = new TF1("l2p2","[0]*0.5*(TMath::Erf((x-[1])/2./[2]/sqrt(x))+1.)", 0, 100);
	l3p2 = new TF1("l3p2","([0]-exp(([1]-x)*[2]))",0,1000);
	l1p3 = new TF1("l1p3","[0]*0.5*(TMath::Erf((x-[1])/2./[2]/sqrt(x))+1.)", 0, 100);
	l2p3 = new TF1("l2p3","[0]*0.5*(TMath::Erf((x-[1])/2./[2]/sqrt(x))+1.)", 0, 100);
	l3p3 = new TF1("l3p3","([0]-exp(([1]-x)*[2]))",0,100);
	l1p1->SetParameter(0, 1);
	l1p1->SetParameter(1, 18.0459);
	l1p1->SetParameter(2, 0.158073);
	l2p1->SetParameter(0, 1);
	l2p1->SetParameter(1, 21.2584);
	l2p1->SetParameter(2, 0.155051);
	l3p1->SetParameter(0, 0.949259);
	l3p1->SetParameter(1, -61.808);
	l3p1->SetParameter(2, 0.0212594);
	l1p2->SetParameter(0, 0.998744);
	l1p2->SetParameter(1, 18.0459);
	l1p2->SetParameter(2, 0.158073);
	l2p2->SetParameter(0, 0.999495);
	l2p2->SetParameter(1, 36.3457);
	l2p2->SetParameter(2, 0.249992);
	l3p2->SetParameter(0, 0.918636);
	l3p2->SetParameter(1, -0.0453229);
	l3p2->SetParameter(2, 0.0542693);
	l1p3->SetParameter(0, 0.999149);
	l1p3->SetParameter(1, 19.6353);
	l1p3->SetParameter(2, 0.654677);
	l2p3->SetParameter(0, 1);
	l2p3->SetParameter(1, 46.7062);
	l2p3->SetParameter(2, 0.300785);
	l3p3->SetParameter(0, 0.954282);
	l3p3->SetParameter(1, -110.969);
	l3p3->SetParameter(2, 0.0153178);
	TF1* p1 = new TF1("p1","l1p1*l2p1*l3p1",0,100);
	TF1* p2 = new TF1("p2","l1p2*l2p2*l3p2",0,100);
	TF1* p3 = new TF1("p3","l1p3*l2p3*l3p3",0,100);
	TF1* trig = new TF1("trig","p1*([1]/[0])+p2*([2]/[0])+p3*([3]/[0])",0,100);
	trig->SetParameter(0,1959.704);
	trig->SetParameter(1,313.086);
	trig->SetParameter(2,785.444);
	trig->SetParameter(3,861.174);

	eduElectron = trig;

}

Trigger::Trigger(string iConfig){
	L1Triggers		= new vector<trigger*>();
	HLTriggers		= new vector<trigger*>();
	L1HLTriggers	= new vector<trigger*>();
	ParseConfig(iConfig);
}

// Constructor that takes in the strings for bins and weights
Trigger::Trigger(string iEdges, string iWeights){
	lowEdge.clear();
	weight.clear();
	SetEfficiency(iEdges,iWeights);
}

// Fill trigger efficiency vector
void Trigger::SetEfficiency(std::string iEdges, std::string iWeights){
	lowEdge.clear();
	weight.clear();

	ParseCSV(iEdges,',', lowEdge);
	ParseCSV(iWeights,',', weight);

}

void Trigger::SetEfficiency(string iFunction){
	function = new TF1("efficiency",iFunction.c_str(),0,2000);
}

// Parse comma-separated string
void Trigger::ParseCSV(const string& iS, char c, vector<float>& v) {

	string s = string(iS);

	// Put every number in the vector
	string::size_type curr = 0;
	string::size_type next = min(s.find(c), s.length());
	while (next < s.length()){
		string toAdd = string(s.substr(curr, next-curr));
		v.push_back(atof(toAdd.c_str()));

		curr = next+1;
		next = s.find(c, next+1);
	}
	v.push_back(atof((s.substr(curr, next-curr)).c_str()));
}

// Return the trigger weight given the pT
float const Trigger::GetWeightFromFunc(float const pT) const {

	if (pT < 0){ return 0.0; }

	float result = 1.0;

	result = eduMuTau->Eval(pT);

	return result;

}

float Trigger::GetWeightFromFuncE(float pT){

	if (pT < 0){ return 0.0; }

	float result = 1.0;

	result = eduElectron->Eval(pT);

	return result;

}

// Return the trigger weight given the pT
float Trigger::GetWeightFromBins(float pT){

	if(lowEdge.size() != weight.size() ){
		cout << "ERROR: requested trigger efficiency from bins but the number of edges and weights do not match!" << endl; exit(1);
	}else if((lowEdge.size()<2) || (weight.size() < 2)){
		cout << "ERROR: requested trigger efficiency from bins but no bins were set up!" << endl; exit(1);
	}

	if (pT < 0){ return 0.0; }

	float result = 1.0;

	int b = lowEdge.size()-1;
	while ( 0 <= b && pT < lowEdge.at(b) ){ b--; }
	if (b < 0 ){ result = 0.0; }
	else{ result = weight.at(b); }

	return result;

}

// Return combined weight if input is a pair
float Trigger::GetWeightFromConf(float pT1, int iRunNum){

	if( ((L1Triggers->size() < 1) || (HLTriggers->size() < 1)) && (L1HLTriggers->size() < 1) ){
		cout << "ERROR: requested trigger efficiency from conf but triggers from conf were set up!" << endl; exit(1);
	}

	return ( GetXTriggerWeight(L1Triggers, pT1, iRunNum) * GetXTriggerWeight(HLTriggers, pT1, iRunNum) );
}


// Get weight from trigger vector
float Trigger::GetXTriggerWeight(vector<trigger*>* iTriggerVector, float iPt, int iRunNum){

	if (iTriggerVector==NULL){ return 1.0; }
	if (iTriggerVector->size()==0){ return 1.0; }

	for (unsigned int v=0; v < iTriggerVector->size(); v++){
		int firstRun	= iTriggerVector->at(v)->startRun;	
		int lastRun 	= iTriggerVector->at(v)->endRun;	

		if( (firstRun <= iRunNum) && (iRunNum <= lastRun) ){
			return (iTriggerVector->at(v)->efficiency->Eval(iPt));	
		}
	}

	return 1.0;
}


void Trigger::ParseConfig(string iConfig){

	Config* triggerConfig = new Config(iConfig);

	map<string, Config*> inputTriggers = triggerConfig->getGroups();
	string inputTriggersPrefix;

	// Get L1 triggers
	inputTriggersPrefix = "L1Trigger_";
	for (map<string, Config*>::iterator i = inputTriggers.begin(); i != inputTriggers.end(); ++i) {
		string groupName = i->first;
		Config* group = i->second;
		if (groupName.substr(0, inputTriggersPrefix.length()) == inputTriggersPrefix) {

			string triggerName		= groupName.substr(inputTriggersPrefix.length());

			int firstRun		= group->pInt("firstRun");
			int lastRun			= group->pInt("lastRun");
			string function		= group->pString("function");

			double p0			= group->pDouble("p0");
			double p1			= group->pDouble("p1");
			double p2			= group->pDouble("p2");

			InsertTrigger(L1Triggers, triggerName, firstRun, lastRun, function, p0, p1, p2); 

		}
	}

	// Get HL triggers
	inputTriggersPrefix = "HLTrigger_";
	for (map<string, Config*>::iterator i = inputTriggers.begin(); i != inputTriggers.end(); ++i) {
		string groupName = i->first;
		Config* group = i->second;
		if (groupName.substr(0, inputTriggersPrefix.length()) == inputTriggersPrefix) {

			string triggerName		= groupName.substr(inputTriggersPrefix.length());

			int firstRun		= group->pInt("firstRun");
			int lastRun			= group->pInt("lastRun");
			string function		= group->pString("function");

			double p0			= group->pDouble("p0");
			double p1			= group->pDouble("p1");
			double p2			= group->pDouble("p2");

			InsertTrigger(HLTriggers, triggerName, firstRun, lastRun, function, p0, p1, p2); 

		}
	}

}

void Trigger::InsertTrigger(vector<trigger*>* iTriggers, string iName, int iFirstRun, int iLastRun, string iFunction, double iP0, double iP1, double iP2){

	trigger* toInsert		= new trigger();
	string fixedFunction 	= Replace(iFunction,"<","[");
	fixedFunction 			= Replace(fixedFunction,">","]");
	TF1* efficiency			= new TF1(iName.c_str(),fixedFunction.c_str(),0,10000);
	efficiency->SetParameters(iP0,iP1,iP2);

	toInsert->startRun		= iFirstRun;
	toInsert->endRun		= iLastRun;
	toInsert->efficiency	= efficiency;

	if(iTriggers != NULL){
		iTriggers->push_back(toInsert);
	}else{
		cout << "ERROR: trigger vector null!!!" << endl; exit(1);
	}

}

string Trigger::Replace(string input, string oldStr, string newStr){
	string toReturn = string(input);
	size_t pos = 0;
	while((pos = toReturn.find(oldStr, pos)) != std::string::npos){
		toReturn.replace(pos, oldStr.length(), newStr);
		pos += newStr.length();
	}

	return toReturn;
}

