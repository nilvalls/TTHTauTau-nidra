
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
		vector<string>		preCutNames;
		vector<string>		cutNames;
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

		string cutsToApply;

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
		CutFlow(CutFlow const &);
		CutFlow(string);
		virtual ~CutFlow();

		void Reset();
		void Zero();

		void PrintTest();

		void RegisterCut(string const);
		void RegisterPreCut(string const);
		void RegisterPreCut(string const, double const);
		void RegisterPostCut(string const);
		void RegisterPostCut(string const, double const);
		void SetPreCutForSignal(string const, double const);
		void SetPreCutForQCD(string const , double const);
		void SetPostCutForSignal(string const, double const);
		void SetPostCutForQCD(string const, double const);

		void AddPreCutEventForSignal(string const, double const);
		void AddPreCutEventForQCD(string const, double const);
		void AddPostCutEventForSignal(string const, double const);
		void AddPostCutEventForQCD(string const, double const);

		bool CheckCombo(string const, float const);
		void EndOfCombo(pair<bool, bool>, int const);
		void StartOfEvent();
		void EndOfEvent();

		bool HaveGoodCombos();

		bool EventForSignalPassed();
		bool EventForQCDPassed();

		int GetHeaviestComboForSignal();
		int GetHeaviestComboForQCD();

		vector<string> const		GetPreCutNames() const;
		vector<string> const		GetCutNames() const;
		vector<string> const		GetPostCutNames() const;
		map<string, float> const	GetMinThresholds() const;
		map<string, float> const	GetMaxThresholds() const;
		map<string, float> const	GetPassedEventsForSignal() const;
		map<string, float> const	GetPassedEventsForQCD() const;
		map<string, float> const	GetPassedEventsForSignalPreCuts() const;
		map<string, float> const	GetPassedEventsForQCDPreCuts() const;
		map<string, float> const	GetPassedEventsForSignalPostCuts() const;
		map<string, float> const	GetPassedEventsForQCDPostCuts() const;
		string const				GetCutsToApply() const;

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
		ClassDef(CutFlow, 1);
		
};

#endif

