#include "Driver.cc"
#include "TTL/TMVAEvaluator.h"

#define Nidra_cxx
using namespace std;


int main(int argc, char **argv){

	Initialize(argc,argv);

	ReadConfig(string(argv[1]));
	BuildProPack(string(argv[1]));
	
	if (IsArgumentThere("-a")) { 
      ReMakeDir(GetParam("webDir"));
      ReMakeDir(GetParam("bigDir"));
      // fist copy config, then analyze
      BackUpConfigFile(argv[1], GetParam("webDir"));
      Analyze();
   } else {
      // copy current config to output directory
      BackUpConfigFile(argv[1], GetParam("webDir"));
   }

    DistributeProcesses();

    if (IsArgumentThere("-t")) {
        MakeTMVATrainingSample();
    }

    if (IsArgumentThere("-T")) {
        TTL_TMVAEvaluator trainer(params);
        trainer.TrainMVA();
    }

	if (IsArgumentThere("-p")) {
      PreparePlots();
      CombineProcesses();
		CrunchNumbers();
	}

	if(IsArgumentThere("-k")){ PlotStacks();	}
	if(IsArgumentThere("-m")){ PlotStamps();	}
	if (IsArgumentThere("-n")) { CrunchNumbers(); }
	if(IsArgumentThere("-o")){ Optimize();		}

	Finalize();

	return 0;
}


