
#ifndef RootFileMaker_h
#define RootFileMaker_h

#include <math.h>
#include <map>
#include <vector>
#include <sstream>
#include <iostream>
#include <utility>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include "HistoWrapper.h"
#include "Topology.h"
#include "TopoPack.h"
#include "TFile.h"
#include "TTree.h"


using namespace std;



class RootFileMaker {
	private :

	public :
		// Default constructor
		RootFileMaker();
		virtual ~RootFileMaker();
		virtual void MakeFile(TopoPack*, string);
};

#endif

