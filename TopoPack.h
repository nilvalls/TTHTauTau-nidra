
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

#include "HistoWrapper.h"
#include "Topology.h"

using namespace std;
//using namespace Common;


class TopoPack {
	private:
		Topology*			collisions;
		Topology*			qcd;
		vector<Topology*>*	mcBackgrounds;
		vector<Topology*>*	signals;
		
		bool                analyzed;

		bool                haveCollisions;
		bool                haveMCbackgrounds;
		bool                haveBackgrounds;
		bool                haveQCD;
		bool                haveSignals;


	public :
		// Default constructor
		TopoPack();
		virtual ~TopoPack();

		Topology*			GetCollisions();
		Topology*			GetQCD();
		vector<Topology*>*	GetMCbackgrounds();
		vector<Topology*>*	GetSignals();

		void SetCollisions(Topology*);
		void SetQCD(Topology*);
		void AddMCbackground(Topology*);
		void AddSignal(Topology*);

		bool HaveCollisions();
		bool HaveQCD();
		bool HaveMCbackgrounds();
		bool HaveSignals();

		void BuildQCD();
		bool Analyzed();
		void SetAnalyzed();

		TopoPack* Clone();
		
		ClassDef(TopoPack, 1);
};

#endif

