#include <unistd.h>

#include "Driver.cc"
#include "Helper.h"
#include "TTL/Analyzer.h"
#include "TTL/TMVAEvaluator.h"

#define Nidra_cxx
using namespace std;

void
setup_mva(const string& prefix, const string& dir, const Config& cfg,
        ProPack *proPack, bool make_trees, bool train)
{
    string method = cfg.pString(prefix + "method");
    if (method.length() == 0)
        return;

    string basedir = cfg.pString(prefix + "dir");
    if (basedir.length() == 0)
        basedir = cfg.pString("bigDir") + "/" + dir;

    ReMakeDir(basedir + "/");

    map<string, string> setup;
    for (const auto& m: Helper::SplitString(cfg.pString(prefix + "method")))
        setup[m] = cfg.pString(prefix + "options" + m);

    string signal = cfg.pString(prefix + "signal");
    string background = cfg.pString(prefix + "background");
    vector<string> vars = Helper::SplitString(cfg.pString(prefix + "variables"));

    int rank = signal == background ? 0 : 1;
    TTL_TMVAEvaluator *mva = new TTL_TMVAEvaluator(basedir, vars, rank);

    if (make_trees) {
        if (rank == 0)
            mva->CreateTrainingSample(signal, proPack);
        else
            mva->CreateTrainingSample(signal, background, proPack);
    }

    if (train)
        mva->TrainMVA(setup);

    delete mva;

    for (const auto& m: setup) {
        mva = new TTL_TMVAEvaluator(basedir, vars, rank);
        if (!mva->BookMVA(m.first)) {
            delete mva;
            mva = 0;
        }

        if (rank == 0)
            TTL_TMVAEvaluator::gComboMVA[m.first] = mva;
        else
            TTL_TMVAEvaluator::gMVA[m.first] = mva;
    }
}

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

    ReMakeDir(GetParam("webDir"));
    ReMakeDir(GetParam("bigDir"));
    // fist copy config, then analyze
    BackUpConfigFile(argv[0], GetParam("webDir"));

    if (analyze or all) {
        Analyze();
    } else {
        // copy current config to output directory
        BackUpConfigFile(argv[0], GetParam("webDir"));
    }

    DistributeProcesses();

    if (proPack)
        delete proPack;

    // FIXME the proPack should be up to date at all times!
    TFile file((params["process_file"]).c_str(), "UPDATE");
    file.GetObject((params["propack_name"]).c_str(), proPack);
    file.Close();

    setup_mva("comboSelectorMVA", "combos", cfg, proPack, train_combo_mva || all, train_combo_mva || all);
    setup_mva("MVA", "tmva", cfg, proPack, prep_train || all, train || all);

    if (prep_plots or all) {
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


