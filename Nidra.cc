#include "Driver.cc"

#define Nidra_cxx
using namespace std;


int main(int argc, char **argv){

	cout << "\n>>>>>>>> Initialize Nidra" << endl;
	Initialize(argc,argv);

	cout << "\n>>>>>>>> Read config file" << endl;
	ReadConfig(string(argv[1]));
	
	if(IsArgumentThere("-a")){
		cout << "\n>>>>>>>> Analyze events" << endl;
		Analyze();
	}

//	cout << ">>>>>>>> Crunch numbers" << endl;
	//CrunchNumbers();

	cout << "\n>>>>>>>> Prepare Plots" << endl;
	PreparePlots();

	cout << "\n>>>>>>>> Plot Stacks" << endl;
	PlotStacks();

	//cout << "\n>>>>>>>> Plot Stamps" << endl;
	//PlotStamps();

	//cout << "\n>>>>>>>> Plot Optimizations" << endl;
	//Optimize();

	cout << "\n>>>>>>>> Finalize" << endl;
	Finalize();

	return 0;
}


