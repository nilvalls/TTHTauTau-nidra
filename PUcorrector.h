
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


using namespace std;
//using namespace Common;


class PUcorrector{
	private:

	public :
		// Default constructor
		PUcorrector();
		PUcorrector(const PUcorrector&);
		virtual ~PUcorrector();
		virtual float const GetWeight(float const) const;

};

#endif

