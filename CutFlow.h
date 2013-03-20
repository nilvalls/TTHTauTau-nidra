
#ifndef CutFlow_h
#define CutFlow_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <climits>
#include <float.h>
#include <math.h>

#include <iomanip>
#include <TROOT.h>
#include <map>
#include <vector>


using namespace std;


class CutFlow {
	private:
		string cutsToApply;

		bool eventForSignalPassed;
		bool eventForQCDPassed;

		bool comboIsForSignal;
		bool comboIsForQCD;		

		bool signalComboLocked;
		bool qcdComboLocked;

		int bestComboForSignal;
		int bestComboForQCD;

		bool OutOfRange(float, float, float);

//*/
	public :
        struct Cut {
            string name;
            int rank;
            float min;
            float max;
            bool currentSignalResult;
            bool currentQCDResult;
            float passedSignalCombos;
            float passedQCDCombos;
            float passedSignalEvents;
            float passedQCDEvents;

            Cut(const string n="", const int r=0, const float mn=0., const float=0., const double sig=0., const double qcd=0.);

            ClassDef(CutFlow::Cut, 1);
        };

        inline vector<CutFlow::Cut> GetCuts() const { return cuts; };

		// Default constructor
		CutFlow();
		CutFlow(CutFlow const &);
		CutFlow(string);
		virtual ~CutFlow();

		void Reset();
		int const size() const;
		void InvertSignalAndQCD();

		void RegisterCut(string const, int const, double const sig=0., double const qcd=0.);
		void RegisterCutFromLast(string const, int const, double const, double const);
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

		int GetBestComboForSignal();
		int GetBestComboForQCD();

		int const					GetCutRank(string const) const;
		int const					GetCutPosition(string const) const;
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
        void Zero();


		pair<float,float> ExtractCutThresholds(string);
    private:
        vector<CutFlow::Cut> cuts;
        map<string ,int> name2idx;

		ClassDef(CutFlow, 1);
		
};

#endif

