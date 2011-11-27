
#ifndef TopoPack_h
#define TopoPack_h

#include <TROOT.h>
#include <math.h>
#include <map>
#include <vector>
#include <sstream>
#include <iostream>
#include <utility>
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include <iomanip>

#include "THStack.h"

#include "HistoWrapper.h"
#include "Topology.h"

using namespace std;
//using namespace Common;


class TopoPack {
	private:
		map<string, string>	params;
		Topology*			collisions;
		Topology*			qcd;
		vector<Topology*>*	mcBackgrounds;
		vector<Topology*>*	signals;
		
		bool                analyzed;
		double				integratedLumiInInvPb;

		bool                haveCollisions;
		bool                haveQCD;
		bool                haveMCbackgrounds;
		bool                haveBackgrounds;
		bool                haveSignals;

		bool				prepareCollisions;
		bool				prepareQCD;


	public :
		// Default constructor
		TopoPack();
		TopoPack(map<string,string>*);
		virtual ~TopoPack();

		Topology*				GetCollisions();
		Topology*				GetQCD();
		vector<Topology*>*		GetMCbackgrounds();
		vector<Topology*>*		GetSignals();

		void					SetCollisions(Topology*);
		void					SetQCD(Topology*);
		void					AddMCbackground(Topology*);
		void					AddSignal(Topology*);

		bool					HaveCollisions();
		bool					PrepareCollisions();
		void					PrepareCollisions(bool);

		bool					HaveQCD();
		bool					PrepareQCD();
		void					PrepareQCD(bool);

		bool					HaveMCbackgrounds();
		bool					HaveSignals();

		void					BuildQCD();
		bool					Analyzed();
		void					SetAnalyzed();
		void					NormalizeToLumi();
		double					GetMaxY(int);



		// Cut flows
		CutFlow*			GetCollisionsCutFlow();
		CutFlow*			GetQCDCutFlow();
		vector<CutFlow*>*	GetMCbackgroundsCutFlows();
		vector<CutFlow*>*	GetSignalsCutFlows();


		// Useful for plotting
		int						GetNumberOfPlots();
		vector<HistoWrapper*>*	GetSignals(int);
		vector<HistoWrapper*>*	GetMCbackgrounds(int);
		THStack*				GetBackgroundStack(int);
		TH1*					GetBackgroundSum(int);
		HistoWrapper*			GetAvailableHistoWrapper();
		Topology*				GetAvailableTopology();
		void					DrawSignals(int, string);
		void					DrawCollisions(int, string);

		TopoPack* Clone();
		
		ClassDef(TopoPack, 1);
};

#endif

