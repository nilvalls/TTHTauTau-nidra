#ifndef CutFlow_h
#define CutFlow_h

#include <iostream>

#include <climits>
#include <map>
#include <vector>

#include "TTL/Branches.h"

class CutFlow {
	private:
        std::string cutsToApply;
        std::map< std::string, std::pair<float, float> > cuts_to_consider;

		bool eventForSignalPassed;

		bool comboIsForSignal;

		bool signalComboLocked;

		int bestComboForSignal;

		bool OutOfRange(float, float, float);

//*/
	public :
        struct Cut {
            // typedef decltype([](TTLBranches*, const int) -> float { return 0.; }) val_f;
            // typedef std::function<float (TTLBranches*, const int&)> val_f;
            typedef float (*val_f)(TTLBranches*&, const int&);

            string name;
            val_f GetVal;
            int rank;
            float min;
            float max;
            float passedSignalCombos;
            float passedSignalEvents;
            bool currentSignalResult;
            bool skip;

            bool Check(TTLBranches *b, const int, const bool bypass=false);

            Cut(const string n="", val_f=0, const int r=0, const float mn=0., const float mx=0.,
                    const double sig=0., bool bypass=false);

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

        void RegisterCut(string const, int const, double const sig=0.);
        void RegisterCut(const string, const int, Cut::val_f, bool bypass=false, const double sig=0.);
		void RegisterCutFromLast(string const, int const, double const);
		void SetCutCounts(string const, double const);

        bool CheckCuts(TTLBranches*&, const int&, const bool bypass=false);
		void StartOfEvent();
		void EndOfEvent();

		int const					GetCutRank(string const) const;
		int const					GetCutPosition(string const) const;
		float const					GetPassedEventsForSignal(string const) const;
		float const					GetRelEffForSignal(string const) const;
		float const					GetCumEffForSignal(string const) const;
		string const				GetCutsToApply() const;
        inline std::map< std::string, std::pair<float, float> > GetCutsToConsider() const { return cuts_to_consider; };
		string const				GetLastCut() const;
		double const				GetLastCountForSignal() const;
		void						Add(CutFlow const &, float const iFactor=1.0);
		void						BuildNormalizedCutFlow(CutFlow const *);
        void Zero();

    private:
        vector<CutFlow::Cut> cuts;
        map<string ,int> name2idx;

		ClassDef(CutFlow, 1);
};

#endif

