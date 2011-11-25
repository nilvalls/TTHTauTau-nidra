
#define CutFlow_cxx
#include "CutFlow.h"

using namespace std;



// Default constructor
CutFlow::CutFlow(){

	cutNames				= new vector<string>();

	eventsBeforeCut			= new map<string, double>();
	eventsAfterCut			= new map<string, double>();
	eventsBeforeCutError	= new map<string, double>();
	eventsAfterCutError		= new map<string, double>();
	scaleFactors			= new map<string, float>();
	scaleFactorsError		= new map<string, float>();

	test = "IT WORKED!";
}


// Default destructor
CutFlow::~CutFlow(){
}

void CutFlow::Reset(){

	cutNames->clear();
	eventsBeforeCut->clear();
	eventsAfterCut->clear();
	eventsBeforeCutError->clear();
	eventsAfterCutError->clear();
	scaleFactors->clear();
	scaleFactorsError->clear();

}

/*

void CutFlow::AddEvents(string iName, long int iPassing, float iScaleFactor){
	cutNames->push_back(iName);	
	(*eventsAfterCut)[iName] = iPassing;

	(*scaleFactors)[iName] = iScaleFactor;

	if(cutNames->size()>1){
		(*eventsBeforeCut)[iName] = (*eventsAfterCut)[cutNames->at(cutNames->size()-2)];
	}else{
		(*eventsBeforeCut)[iName] = iPassing;
	}
}

long int CutFlow::GetEventsBeforeCut(string iName){
	return ((*eventsBeforeCut)[iName]);	
}

long int CutFlow::GetEventsBeforeCut(int iPos){
	return ((*eventsBeforeCut)[(cutNames->at(iPos))]);	
}

long int CutFlow::GetEventsAfterCut(string iName){
	return ((*eventsAfterCut)[iName]);	
}

long int CutFlow::GetEventsAfterCut(int iPos){
	return ((*eventsAfterCut)[(cutNames->at(iPos))]);	
}

float CutFlow::GetRelativeEfficiency(string iName){
	float result = 0;
	result = GetEventsAfterCut(iName)/GetEventsBeforeCut(iName);
	return result;
}

float CutFlow::GetRelativeEfficiencyError(string iName){
	float result = 0;
	result = GetRelativeEfficiency(iName)*sqrt(1/(double)GetEventsAfterCut(iName) - 1/(double)GetEventsBeforeCut(iName) ); // Binomial!!
	return result;
}

float CutFlow::GetRelativeEfficiency(int iPos){
	float result = 0;
	result = GetEventsAfterCut(iPos)/GetEventsBeforeCut(iPos);
	return result;
}

float CutFlow::GetRelativeEfficiencyError(int iPos){
	float result = 0;
	result = GetRelativeEfficiency(iPos)*sqrt(1/(double)GetEventsAfterCut(iPos) - 1/(double)GetEventsBeforeCut(iPos)); // Binomial!!
	return result;
}

float CutFlow::GetCumulativeEfficiency(string iName){
	float result = 0;
	result = GetEventsAfterCut(iName)/GetEventsBeforeCut(cutNames->front());
	return result;
}

float CutFlow::GetCumulativeEfficiencyError(string iName){
	float result = 0;
	result = GetCumulativeEfficiency(iName)*sqrt(1/(double)GetEventsAfterCut(iName) - 1/(double)GetEventsBeforeCut(cutNames->front()) ); // Binomial!!
	return result;
}

float CutFlow::GetCumulativeEfficiency(int iPos){
	float result = 0;
	result = GetEventsAfterCut(iPos)/GetEventsBeforeCut(iPos);
	return result;
}

float CutFlow::GetCumulativeEfficiencyError(int iPos){
	float result = 0;
	result = GetCumulativeEfficiency(iPos)*sqrt(1/(double)GetEventsAfterCut(iPos) - 1/(double)GetEventsBeforeCut(0)); // Binomial!!
	return result;
}

CutFlow* CutFlow::Clone(){
	CutFlow* result		= new CutFlow(*this);
	result->cutNames				= new vector<string>(*cutNames);
	result->eventsBeforeCut			= new map<string, double>(*eventsBeforeCut);
	result->eventsAfterCut			= new map<string, double>(*eventsAfterCut);
	result->eventsBeforeCutError	= new map<string, double>(*eventsBeforeCutError);
	result->eventsAfterCutError		= new map<string, double>(*eventsAfterCutError);
	result->scaleFactors			= new map<string, float>(*scaleFactors);
	result->scaleFactorsError		= new map<string, float>(*scaleFactorsError);
}

//*/

//ClassImp(CutFlow)
