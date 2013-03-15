#include <unistd.h>

#include "Driver.cc"
#include "TTL/TMVAEvaluator.h"

#define Nidra_cxx
using namespace std;

void
usage()
{
    cerr << "usage: nidra [-aAkmnopPtT] configfile" << endl;
    exit(1);
}

int main(int argc, char **argv){
    bool all = false;
    bool analyze = false;
    bool crunch = false;
    bool prep_train = false;
    bool prep_plots = false;
    bool train = false;
    bool stack = false;
    bool stamp = false;
    bool optim = false;

    int opt;
    while ((opt = getopt(argc, argv, "aAkmnopPtT")) != -1) {
        switch (opt) {
            case 'a':
                analyze = true;
                break;
            case 'A':
                all = true;
                break;
            case 'k':
                stack = true;
                break;
            case 'm':
                stamp = true;
                break;
            case 'n':
                crunch = true;
                break;
            case 'o':
                optim = true;
                break;
            case 'p':
                prep_plots = true;
                break;
            case 'P':
                prep_plots = true;
                prep_train = true;
                break;
            case 't':
                prep_train = true;
                break;
            case 'T':
                train = true;
                break;
            default:
                usage();
                /* NOTREACHED */
        }
    }
    argc -= optind;
    argv += optind;

    if (argc != 1)
        usage();

	Initialize();

	ReadConfig(string(argv[0]));
	BuildProPack(string(argv[0]));
	
	if (analyze or all) {
      ReMakeDir(GetParam("webDir"));
      ReMakeDir(GetParam("bigDir"));
      // fist copy config, then analyze
      BackUpConfigFile(argv[0], GetParam("webDir"));
      Analyze();
   } else {
      // copy current config to output directory
      BackUpConfigFile(argv[0], GetParam("webDir"));
   }

    DistributeProcesses();

    if (prep_train or all)
        MakeTMVATrainingSample();

    if (train or all) {
        TTL_TMVAEvaluator trainer(params);
        trainer.TrainMVA();
    }

    if (prep_plots or all) {
        PreparePlots();
        CombineProcesses();
    }

    if (stack or all)
        PlotStacks();
    if (stamp or all)
        PlotStamps();
    if (crunch or prep_plots or all)
        CrunchNumbers();
    if (optim or all)
        Optimize();

	Finalize();

	return 0;
}


