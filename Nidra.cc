#include "Driver.cc"

#define Nidra_cxx
using namespace std;


int main(int argc, char **argv){

	Initialize();

	ReadConfig(string(argv[1]));

	Analyze();

	PlotStacks();

	PlotStamps();

	Optimize();

	Finalize();

	return 0;
}


