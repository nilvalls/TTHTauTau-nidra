
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

using namespace std;
//using namespace Common;


class Process {
	protected:
		map<string, string> params;

	private:
		vector<pair<int, int> >	goodEventsForSignal;
		vector<pair<int, int> >	goodEventsForQCD;
		HContainer				hContainerForSignal;
		HContainer				hContainerForQCD;
		CutFlow					cutFlow;
		CutFlow					normalizedCutFlow;

		string shortName;
		string niceName;
		string labelForLegend;
		string type;
		string ntuplePath;
		int color;
		bool analyzed;


		float crossSection;
		float branchingRatio;
		float otherScaleFactor;

		double NOEinDS;
		double NOEinPATuple;
		double NOEinNtuple;
		double NOEanalyzed;
		double NOEexpectedForSignal;
		double NOEexpectedForQCD;

		bool obtainedGoodEventsForSignal;
		bool obtainedGoodEventsForQCD;
		bool filledHistosForSignal;
		bool filledHistosForQCD;
		bool normalizedHistosForSignal;
		bool normalizedHistosForQCD;
		

		void NormalizeTo(double const);
		void BookHistos(HContainer const *);

	public :
		// Default constructor
		Process();
		Process(Process const &);
		Process(string const, map<string,string> const &, Config const &);
		virtual ~Process();


		map<string, string> const GetParams() const;
		int const			GetNOEinDS() const;
		int const			GetNOEinPATuple() const;
		int const			GetNOEinNtuple() const;
		int const			GetNOEanalyzed() const;

		void				SetShortName(string const);
		void				SetNiceName(string const);
		void				SetLabelForLegend(string const);
		void				SetColor(int const);
		void				SetNOEanalyzed(double const);
		void				SetNOEinNtuple(double const);

		void				NormalizeToLumi(double const);
		void				NormalizeToOne();
		void				BuildNormalizedCutFlow();
		void				ScaleBy(double const);
		void				SetAnalyzed();
		bool const			Analyzed() const;

		vector<pair<int, int> > const 	GetGoodEventsForSignal() const;
		vector<pair<int, int> > const 	GetGoodEventsForQCD() const;
		void				SetHContainerForSignal(HContainer const &);
		void				SetHContainerForQCD(HContainer const &);
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
		string const		GetNtuplePath() const;
		string const		GetType() const;
		bool const			IsCollisions() const;
		bool const			IsQCD() const;
		bool const			IsMCbackground() const;
		bool const			IsSignal() const;
		bool const			IsMC() const;

		double const		GetCrossSection() const;
		double const		GetBranchingRatio() const;
		double const		GetOtherScaleFactor() const;
		double const		GetNOEexpectedForSignal() const;
		double const		GetNOEexpectedForQCD() const;
		bool const			ObtainedGoodEventsForSignal() const;
		bool const			ObtainedGoodEventsForQCD() const;
		bool const			FilledHistosForSignal() const;
		bool const			FilledHistosForQCD() const;
		bool const			NormalizedHistosForSignal() const;
		bool const			NormalizedHistosForQCD() const;


		HContainer *	GetHContainerForSignal();
		HContainer *	GetHContainerForQCD();
		HContainer const *	GetHContainerForSignal() const;
		HContainer const *	GetHContainerForQCD() const;

		HWrapper const *	GetAvailableHWrapper() const;
		HWrapper const *	GetAvailableHWrapper(string const) const;
		HWrapper const *	GetHistoForSignal(string const) const;
		HWrapper const *	GetHistoForQCD(string const) const;

		int const			GetNumberOfPlots() const;

		void				SetMarkerStyle(int const);
		void				SetFillColor(int const);
		void				SetFillStyle(int const);
		void				SetLineColor(int const);
		void				SetLineWidth(int const);
		void 				SetGoodEventsForSignal(vector<pair<int, int> > const);
		void 				SetGoodEventsForQCD(vector<pair<int, int> > const);

		ClassDef(Process, 1);
};

#endif

