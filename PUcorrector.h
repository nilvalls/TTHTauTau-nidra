
#ifndef PUcorrector_h
#define PUcorrector_h

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

#include "TH1D.h"
#include "TFile.h"


using namespace std;
//using namespace Common;


class PUcorrector{
	private:
		map<int,long double> weight;
		map<int,long double> generated;

	public :
		// Default constructor
		PUcorrector();
		PUcorrector(const string);
		PUcorrector(const PUcorrector&);
		virtual ~PUcorrector();
		virtual float const GetWeight(float const) const;

};

#endif

