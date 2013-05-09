
#ifndef Process_h
#define Process_h

#include <TROOT.h>
#include <math.h>
#include <map>
#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <utility>
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <vector>

#include "CutFlow.h"
#include "HWrapper.h"
#include "HContainer.h"

#include "configParser/config.h"

class Process {
    public:
        struct Event {
            Event(const int& n, const std::vector<int>& cs) : entry(n), combos(cs) {};
            Event(const Event& e) : entry(e.entry), combos(e.combos) {};
            Event() : entry(-1), combos() {};

            int entry;
            std::vector<int> combos;

            ClassDef(Process::Event, 1);
        };

	protected:
        std::map<std::string, std::string> params;

	private:
        std::vector<Process::Event> goodEventsForSignal;
		HContainer				hContainerForSignal;
		CutFlow					cutFlow;
		CutFlow					normalizedCutFlow;

		string shortName;
		string niceName;
		string labelForLegend;
		string type;
		bool checkReality;
        std::vector<std::string> ntuplePaths;
		int color;
		bool analyzed;
		bool plot;


		float crossSection;
		float branchingRatio;
		float otherScaleFactor;

		double NOEinDS;
		double NoEreadByNUTter;
		double NOEinNtuple;
		double NOEanalyzed;
		double NOEexpectedForSignal;

		bool obtainedGoodEventsForSignal;
		bool filledHistosForSignal;
		bool normalizedHistosForSignal;
		
        double relSysUncertainty;

		void NormalizeTo(double const);
		void BookHistos(HContainer const *);


		bool const IsStringThere(string, string) const;
		bool PlotProcess(string const);

	public :
		// Default constructor
		Process();
		Process(Process const &);
		Process(std::string const, std::map<std::string, std::string> const &, Config const &);
		virtual ~Process();
		void Update(Process const *);


        std::map<std::string, std::string> const GetParams() const;
		int const			GetNOEinDS() const;
		int const			GetNoEreadByNUTter() const;
		int const			GetNOEinNtuple() const;
		int const			GetNOEanalyzed() const;

		void				SetShortName(std::string const);
		void				SetNiceName(std::string const);
		void				SetLabelForLegend(std::string const);
		void				SetColor(int const);
		void				SetNOEanalyzed(double const);
		void				SetNOEinNtuple(double const);
		void				SetNtuplePaths(std::vector<std::string> const);
        void                SetRelSysUncertainty(double const);

		void				NormalizeToLumi(double const);
		void				NormalizeToOne();
		void				BuildNormalizedCutFlow();
		void				ScaleBy(double const);
		void				SetAnalyzed();
		bool const			Analyzed() const;

        std::vector<Event> const GetGoodEventsForSignal() const;
		void				SetHContainerForSignal(HContainer const &);
		void				SetCutFlow(CutFlow const &);
		void				SetNormalizedCutFlow(CutFlow const &);
		CutFlow *			GetCutFlow();
		CutFlow const *		GetCutFlow() const;
		CutFlow *			GetNormalizedCutFlow();
		CutFlow const *		GetNormalizedCutFlow() const;

		int const			GetColor() const;
		string const		GetShortName() const;
		string const		GetNiceName() const;
		string const		GetLabelForLegend() const;
        std::vector<std::string> const		GetNtuplePaths() const;
		string const		GetType() const;
		bool const			CheckReality() const;
		bool const			IsCollisions() const;
		bool const			IsMCbackground() const;
		bool const			IsSignal() const;
		bool const			IsMC() const;
		bool const			Plot() const;
		void				SetPlot(std::map<std::string, std::string> const &);

		double const		GetCrossSection() const;
		double const		GetBranchingRatio() const;
		double const		GetOtherScaleFactor() const;
		double const		GetNOEexpectedForSignal() const;
        double const        GetRelSysUncertainty() const;
		bool const			ObtainedGoodEventsForSignal() const;
		bool const			FilledHistosForSignal() const;
		bool const			NormalizedHistosForSignal() const;


		HContainer *	GetHContainerForSignal();
		HContainer const *	GetHContainerForSignal() const;

		HWrapper const *	GetAvailableHWrapper() const;
		HWrapper const *	GetAvailableHWrapper(string const) const;
		HWrapper const *	GetHistoForSignal(string const) const;

		int const			GetNumberOfPlots() const;

		void				SetMarkerStyle(int const);
		void				SetFillColor(int const);
		void				SetFillStyle(int const);
		void				SetLineColor(int const);
		void				SetLineWidth(int const);
		void 				SetGoodEventsForSignal(const std::vector<Process::Event>&);
		void				Add(Process*);

		ClassDef(Process, 1);
};

#endif

