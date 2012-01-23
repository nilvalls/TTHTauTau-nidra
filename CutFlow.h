
#ifndef CutFlow_h
#define CutFlow_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <climits>
#include <float.h>
#include <math.h>

#include <TROOT.h>
#include <map>
#include <vector>


using namespace std;


class CutFlow {
	private:
		vector<string>		cutNames;
		map<string, int>	cutNamesMap;
		map<string, int>	cutRanks;
		map<string, float>	minThresholds;
		map<string, float>	maxThresholds;

		map<string, bool>	thisCombosResultsForSignal;
		map<string, bool>	thisCombosResultsForQCD;
		map<string, float>	passedCombosForSignal;
		map<string, float>	passedCombosForQCD;
		map<string, float>	passedEventsForSignal;
		map<string, float>	passedEventsForQCD;

		string cutsToApply;

		bool eventForSignalPassed;
		bool eventForQCDPassed;

		bool comboIsForSignal;
		bool comboIsForQCD;		

		bool signalComboLocked;
		bool qcdComboLocked;

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

		void PrintTable();

		void Reset();
		void Zero();
		int const size() const;
		void InvertSignalAndQCD();

		void RegisterCut(string const, int const);
		void RegisterCut(string const, int const, double const, double const);
		void RegisterCutFromLast(string const, int const, double const, double const);
		void UpdateCutNamesMap();
		void SetCutCounts(string const, double const, double const);

		bool CheckComboAndStop(string const, float const, pair<bool,bool>, bool iBypassQCD=false);
		bool CheckComboDiscretely(string const, float const);
		void ComboIsGood(string const);
		void EndOfCombo(pair<bool, bool>, int const);
		void StartOfEvent();
		void EndOfEvent();

		bool HaveGoodCombos();

		bool EventForSignalPassed();
		bool EventForQCDPassed();

		int GetHeaviestComboForSignal();
		int GetHeaviestComboForQCD();

		vector<string> const		GetCutNames() const;
		map<string, int> const		GetCutRanks() const;
		int const					GetCutRank(string const) const;
		int const					GetCutPosition(string const) const;
		map<string, float> const	GetMinThresholds() const;
		map<string, float> const	GetMaxThresholds() const;
		map<string, float> const	GetPassedEventsForSignal() const;
		map<string, float> const	GetPassedEventsForQCD() const;
		float const					GetPassedEventsForSignal(string const) const;
		float const					GetPassedEventsForQCD(string const) const;
		float const					GetRelEffForSignal(string const) const;
		float const					GetRelEffForQCD(string const) const;
		float const					GetCumEffForSignal(string const) const;
		float const					GetCumEffForQCD(string const) const;
		string const				GetCutsToApply() const;
		string const				GetLastCut() const;
		double const				GetLastCountForSignal() const;
		double const				GetLastCountForQCD() const;
		void						Add(CutFlow const &, float const iFactor=1.0);
		void						BuildNormalizedCutFlow(CutFlow const *);
		void						ApplyRosls(double const);


		pair<float,float> ExtractCutThresholds(string);
		ClassDef(CutFlow, 1);
		
};

#endif

