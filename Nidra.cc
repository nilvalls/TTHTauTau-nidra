#include "Driver.cc"

#define Nidra_cxx
using namespace std;


int main(int argc, char **argv){

	Initialize(argc,argv);

	ReadConfig(string(argv[1]));
	BuildProPack(string(argv[1]));
	
	if(IsArgumentThere("-a")){ Analyze(); }

	if(IsArgumentThere("-p")){
	// Needed?	ReadConfig(string(argv[1]));
		DistributeProcesses();
		PreparePlots();
		CrunchNumbers();
		PlotStacks();
	//	PlotStamps();
		Optimize();
	}

	if(IsArgumentThere("-t")){
		DistributeProcesses();
		MakeTMVATrainingSample();
	}

	Finalize();

	return 0;
}


