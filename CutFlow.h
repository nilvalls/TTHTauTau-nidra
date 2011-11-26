
#ifndef CutFlow_h
#define CutFlow_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <climits>
#include <float.h>

#include <TROOT.h>
#include <map>
#include <vector>


using namespace std;


class CutFlow {
	private:
		vector<string>		cutNames;
		map<string, float>	minThresholds;
		map<string, float>	maxThresholds;

		map<string, int>	thisCombosResults;
		map<string, float>	passedCombosForSignal;
		map<string, float>	passedCombosForQCD;
		map<string, float>	passedEventsForSignal;
		map<string, float>	passedEventsForQCD;

		bool eventForSignalPassed;
		bool eventForQCDPassed;

		bool comboIsForSignal;
		bool comboIsForQCD;		

		int heaviestComboForSignal;
		int heaviestComboForQCD;

		bool OutOfRange(float, float, float);

//*/
	public :
		// Default constructor
		CutFlow();
		CutFlow(string);
		virtual ~CutFlow();

		void Reset();
		string cutsToApply;
		string test;

		void RegisterCut(string);
		bool CheckCombo(string,float);
		void EndOfCombo(pair<bool,bool>,int);
		void EndOfEvent();

		bool HaveGoodCombos();

		bool EventForSignalPassed();
		bool EventForQCDPassed();

		int GetHeaviestComboForSignal();
		int GetHeaviestComboForQCD();

		int GetHeaviestCombo();
		int GetHeaviestLSCombo();
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

		pair<float,float> ExtractCutThresholds(string);
//		ClassDef(CutFlow, 1);
		
};

#endif

