
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
#include "HWrapper.h"
#include "Process.h"
#include "ProPack.h"
#include "TFile.h"
#include "TTree.h"


using namespace std;



class RootFileMaker {
	private :
		map<string,string> params;

	public :
		// Default constructor
		RootFileMaker();
		RootFileMaker(map<string,string> const &);
		virtual ~RootFileMaker();
		void MakeFile(ProPack*, string);
};

#endif

