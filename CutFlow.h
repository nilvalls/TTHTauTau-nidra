
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
		vector<string>		preCutNames;
		vector<string>		postCutNames;
		map<string, float>	minThresholds;
		map<string, float>	maxThresholds;

		map<string, bool>	thisCombosResults;
		map<string, float>	passedCombosForSignal;
		map<string, float>	passedCombosForQCD;
		map<string, float>	passedEventsForSignal;
		map<string, float>	passedEventsForQCD;

		map<string, float>	passedEventsForSignalPreCuts;
		map<string, float>	passedEventsForQCDPreCuts;
		map<string, float>	passedEventsForSignalPostCuts;
		map<string, float>	passedEventsForQCDPostCuts;

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
		void Zero();
		string cutsToApply;

		void PrintTest();

		void RegisterCut(string);
		void RegisterPreCut(string);
		void RegisterPreCut(string, double);
		void RegisterPostCut(string);
		void RegisterPostCut(string, double);
		void SetPreCutForSignal(string, double);
		void SetPreCutForQCD(string, double);
		void SetPostCutForSignal(string, double);
		void SetPostCutForQCD(string, double);

		void AddPreCutEventForSignal(string, double);
		void AddPreCutEventForQCD(string, double);
		void AddPostCutEventForSignal(string, double);
		void AddPostCutEventForQCD(string, double);

		bool CheckCombo(string,float);
		void EndOfCombo(pair<bool,bool>,int);
		void StartOfEvent();
		void EndOfEvent();

		bool HaveGoodCombos();

		bool EventForSignalPassed();
		bool EventForQCDPassed();

		int GetHeaviestComboForSignal();
		int GetHeaviestComboForQCD();

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

