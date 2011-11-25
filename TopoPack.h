
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
		Topology* collisions;
		Topology* qcd;
		vector<Topology*>* mcBackgrounds;
		vector<Topology*>* signals;
		
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

		Topology* GetCollisions();

		int GetOne() const;
		int GetTwo();

		bool Analyzed();
		void SetAnalyzed();

		TopoPack* Clone();
		
		ClassDef(TopoPack, 1);
};

#endif

