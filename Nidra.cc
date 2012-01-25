#include "Driver.cc"

#define Nidra_cxx
using namespace std;


int main(int argc, char **argv){

	Initialize(argc,argv);

	ReadConfig(string(argv[1]));
	
	if(IsArgumentThere("-a")){ Analyze(); }

	DistributeProcesses();

	if(IsArgumentThere("-p")){
		PreparePlots();
		CrunchNumbers();
//		PlotStacks();
//		PlotStamps();
		Optimize();
	}

	Finalize();

	return 0;
}


