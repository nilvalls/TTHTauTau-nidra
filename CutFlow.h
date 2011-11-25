
#ifndef CutFlow_h
#define CutFlow_h

#include <TROOT.h>
#include <map>
#include <vector>

using namespace std;


class CutFlow {
	private:
		vector<string>* cutNames;
		
		map<string, double>* eventsBeforeCut;
		map<string, double>* eventsAfterCut;
		map<string, double>* eventsBeforeCutError;
		map<string, double>* eventsAfterCutError;
		map<string, float>* scaleFactors;
		map<string, float>* scaleFactorsError;

//*/
	public :
		// Default constructor
		CutFlow();
		virtual ~CutFlow();

		void Reset();
		string test;
/*		
		void AddEvents(string, long int, float iScaleFactor=1.0);
		long int GetEventsBeforeCut(string);
		long int GetEventsBeforeCut(int);
		long int GetEventsAfterCut(string);
		long int GetEventsAfterCut(int);

		float GetRelativeEfficiency(string);
		float GetRelativeEfficiencyError(string);
		float GetRelativeEfficiency(int);
		float GetRelativeEfficiencyError(int);

		float GetCumulativeEfficiency(string);
		float GetCumulativeEfficiencyError(string);
		float GetCumulativeEfficiency(int);
		float GetCumulativeEfficiencyError(int);

		CutFlow* Clone();
*/
//		ClassDef(CutFlow, 1);
		
};

#endif

