#ifndef CutFlow_h
#define CutFlow_h

#include <climits>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class Branches;

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
            typedef float (*val_f)(Branches*, const int&);

            std::string name;
            val_f GetVal;
            int rank;
            float min;
            float max;
            float passedSignalCombos;
            float passedSignalEvents;
            bool currentSignalResult;
            bool skip;

            bool Check(Branches*, const int, const bool bypass=false);

            Cut(const std::string n="", val_f=0, const int r=0, const float mn=0., const float mx=0.,
                    const double sig=0., bool bypass=false);

            ClassDef(CutFlow::Cut, 1);
        };

        inline std::vector<CutFlow::Cut> GetCuts() const { return cuts; };

		// Default constructor
		CutFlow();
		CutFlow(CutFlow const &);
		CutFlow(std::string);
		virtual ~CutFlow();

		void Reset();
		int const size() const;

        void RegisterCut(std::string const, int const, double const sig=0.);
        void RegisterCut(const std::string, const int, Cut::val_f, bool bypass=false, const double sig=0.);
		void RegisterCutFromLast(std::string const, int const, double const);
		void SetCutCounts(std::string const, double const);

        bool CheckCuts(Branches*, const int&, const bool bypass=false);
		void StartOfEvent();
		void EndOfEvent();

		int const					GetCutRank(std::string const) const;
		int const					GetCutPosition(std::string const) const;
		float const					GetPassedEventsForSignal(std::string const) const;
		float const					GetRelEffForSignal(std::string const) const;
		float const					GetCumEffForSignal(std::string const) const;
        std::string const			GetCutsToApply() const;
        inline std::map< std::string, std::pair<float, float> > GetCutsToConsider() const { return cuts_to_consider; };
        std::string const			GetLastCut() const;
		double const				GetLastCountForSignal() const;
		void						Add(CutFlow const &, float const iFactor=1.0);
		void						BuildNormalizedCutFlow(CutFlow const *);
        void Zero();

    private:
        std::vector<CutFlow::Cut> cuts;
        std::map<std::string ,int> name2idx;

		ClassDef(CutFlow, 1);
};

#endif

