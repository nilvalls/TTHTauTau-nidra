#include <unistd.h>

#include "Driver.cc"
#include "Helper.h"
#include "TTL/Analyzer.h"
#include "TTL/TMVAEvaluator.h"

#define Nidra_cxx
using namespace std;

void
usage()
{
    cerr << "usage: nidra [-acAkmnopPtT] configfile" << endl;
    exit(1);
}

int
main(int argc, char **argv) {
    bool all = false;
    bool train_combo_mva = false;
    bool analyze = false;
    bool crunch = false;
    bool prep_train = false;
    bool prep_plots = false;
    bool train = false;
    bool stack = false;
    bool stackWithSys = false;
    bool stamp = false;
    bool optim = false;

    int opt;
    while ((opt = getopt(argc, argv, "aAcksmnopPtT")) != -1) {
        switch (opt) {
            case 'c':
                train_combo_mva = true;
                break;
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
            case 's':
                stackWithSys = true;
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

    const Config cfg = ReadConfig(string(argv[0]));
    BuildProPack(string(argv[0]));

    if (analyze or train_combo_mva or all) {
        ReMakeDir(GetParam("webDir"));
        ReMakeDir(GetParam("bigDir"));
        // fist copy config, then analyze
        BackUpConfigFile(argv[0], GetParam("webDir"));

        std::string method = cfg.pString("comboSelectorMVAmethod");
        if (method.length() > 0) {
            std::string basedir = cfg.pString("comboSelectorMVAdir");
            // FIXME this ugliness should disappear
            if (basedir.length() == 0) {
                basedir = cfg.pString("bigDir") + "/combos/";
            }
            // FIXME the trailing slash is a safety measure to _really_ create
            // a directory
            ReMakeDir(basedir + "/");

            std::string method = cfg.pString("comboSelectorMVAmethod");
            std::string options = cfg.pString("comboSelectorMVAoptions");
            std::vector<std::string> vars = Helper::SplitString(cfg.pString("comboSelectorMVAvariables"));

            TTL_ComboSelector::gComboMVA = new TTL_ComboSelector(basedir, method, options, vars);

            if (train_combo_mva or all) {
                TTLAnalyzer analyzr(params);
                TTL_ComboSelector::gComboMVA->InitiateTrainingSample();
                analyzr.SampleComboSelectorSampler(*proPack->GetPContainer()->Get(cfg.pString("comboSelectorProcess")));
                cout << "Finalizing" << endl;
                TTL_ComboSelector::gComboMVA->FinalizeTrainingSample();
                cout << "Training" << endl;
                TTL_ComboSelector::gComboMVA->TrainMVA();
            }

            cout << "Booking" << endl;
            TTL_ComboSelector::gComboMVA->BookMVA();
        }

        if (analyze or all) {
            Analyze();
            DistributeProcesses();
        }
    } else {
        // copy current config to output directory
        BackUpConfigFile(argv[0], GetParam("webDir"));
    }

    if (proPack)
        delete proPack;

    // FIXME the proPack should be up date at all times!
    TFile file((params["process_file"]).c_str(), "UPDATE");
    file.GetObject((params["propack_name"]).c_str(), proPack);
    file.Close();

    std::string method = cfg.pString("MVAmethod");
    if (method.length() > 0) {
        std::string basedir = cfg.pString("MVAdir");
        // FIXME this ugliness should disappear
        if (basedir.length() == 0) {
            basedir = cfg.pString("bigDir") + "/tmva/";
        }
        // FIXME the trailing slash is a safety measure to _really_ create
        // a directory
        ReMakeDir(basedir + "/");

        std::string method = cfg.pString("MVAmethod");
        std::string options = cfg.pString("MVAoptions");
        std::string signal = cfg.pString("MVAsignal");
        std::string background = cfg.pString("MVAbackground");
        std::vector<std::string> vars = Helper::SplitString(cfg.pString("MVAvariables"));
        // SetParam(theConfig, "MVAsignal");

        TTL_TMVAEvaluator::gMVA = new TTL_TMVAEvaluator(basedir, method, options, vars);

        if (prep_train or all)
            TTL_TMVAEvaluator::gMVA->CreateTrainingSample(signal, background, proPack);

        if (train or all)
            TTL_TMVAEvaluator::gMVA->TrainMVA(background, proPack);

        TTL_TMVAEvaluator::gMVA->BookMVA();
    }

    if (prep_plots or all) {
        DistributeProcesses();
        PreparePlots();
        CombineProcesses();
    }

    if (stack or all)
        PlotStacks();
    if (stackWithSys)
        PlotStacksWithShapeSystematics();
    if (stamp or all)
        PlotStamps();
    if (crunch or prep_plots or all)
        CrunchNumbers();
    if (optim or all)
        Optimize();

    Finalize();

    return 0;
}


