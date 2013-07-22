#include <unistd.h>

#include "TTL/Branches.h"
#include "TTL/Branches.h"
#include "TLL/MVABase.h"
#include "TLL/MVABase.h"
#include "Driver.cc"
#include "Helper.h"

#include "Nidra.h"

using namespace std;

void
Nidra::Combine(ProPack& pack)
{
    pack.CombineAndRemoveMCbackgrounds(
            {"TTbar_Hadronic", "TTbar_SemiLept", "TTbar_FullLept"},
            "TTbar", "t + tbar", "t #bar{t}", 870);
    pack.CombineAndRemoveMCbackgrounds(
            {"ZplusJets_LowMass", "ZplusOneJet", "ZplusTwoJets", "ZplusThreeJets", "ZplusFourJets"},
            "Zjets", "Z + jets", "Z + jets", 5);
    pack.CombineAndRemoveMCbackgrounds(
            {"WW", "WZ", "ZZ"},
            "DiBoson", "DiBoson", "DiBoson", 3);
    pack.CombineAndRemoveMCbackgrounds(
            {"singleTopSch", "singleTopBarSch", "singleTopTch", "singleTopBarTch", "singleTopPlusW", "singleTopBarPlusW"},
            "SingleTop", "Single t/tbar", "single t/#bar{t}", 4);
    pack.CombineAndRemoveMCbackgrounds(
            {"ttPlusW", "ttPlusZ"},
            "ttWZ", "ttbar + W/Z", "t#bar{t} + W/Z", 880);
    pack.CombineAndRemoveMCbackgrounds(
            {"WplusOneJet", "WplusTwoJets", "WplusThreeJets", "WplusFourJets"},
            "Wjets", "W + jets", "W + jets", 810);
}

template<typename T>
void
setup_mva(const string& prefix, const string& dir, const Config& cfg,
        ProPack *proPack, bool make_trees, bool train, int rank)
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

    MVABase *mva = new T(basedir, vars, rank);

    if (make_trees) {
        if (rank == 0) {
            mva->CreateTrainingSample(signal, proPack);
        } else {
            mva->CreateTrainingSample(signal, background, proPack);
        }
    }

    if (train) {
        cout << "Training " << prefix << endl;
        mva->TrainMVA(setup);
    }

    delete mva;

    for (const auto& m: setup) {
        cout << "reading MVA: " << m.first << " from " << basedir << endl;
        mva = new T(basedir, vars, rank);
        if (!mva->BookMVA(m.first)) {
            cout << "Couln't find MVA: " << m.first << " in " << basedir << endl; 
            delete mva;
            mva = 0;
        }

        if (rank == 0)
            MVABase::gComboMVA[m.first] = mva;
        else
            MVABase::gMVA[m.first] = mva;
    }
}

void
usage()
{
    cerr << "usage: nidra [-acArkmnopPtT] configfile" << endl;
    exit(1);
}

int
main(int argc, char **argv) {
    bool all = false;
    bool train_combo_mva = false;
    bool do_analyze = false;
    bool crunch = false;
    bool prep_train = false;
    bool create_corr = false;
    bool prep_plots = false;
    bool train = false;
    bool stack = false;
    bool stackWithSys = false;
    bool stamp = false;
    bool optim = false;

    int opt;
    while ((opt = getopt(argc, argv, "aAcrksmnopPtT")) != -1) {
        switch (opt) {
            case 'c':
                train_combo_mva = true;
                break;
            case 'a':
                do_analyze = true;
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
            case 'r':
                create_corr = true;
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

	string channel = GetParam("channel");
    if (do_analyze or all) {
        for (auto& p: *(proPack->GetPContainer()->GetContainer())) {

			if(channel == "TTL"){
					Nidra::Analyze<TTLBranches>(p.second, cfg.pString("cutsToApply"),
							cfg.pString("treeName"), atoi(cfg.pString("maxEvents").c_str()));
			}else if(channel == "TLL"){
					Nidra::Analyze<TLLBranches>(p.second, cfg.pString("cutsToApply"),
							cfg.pString("treeName"), atoi(cfg.pString("maxEvents").c_str()));
			}else{	assert(GetParam("channel") == "TTL or TLL");		}

        }
        rootFileMaker.MakeFile(proPack, params["process_file"]);
        DistributeProcesses();
    } else {
        // copy current config to output directory
        BackUpConfigFile(argv[0], GetParam("webDir"));
    }


    if (proPack)
        delete proPack;

    // FIXME the proPack should be up to date at all times!
    TFile file((params["process_file"]).c_str(), "UPDATE");
    file.GetObject((params["propack_name"]).c_str(), proPack);
    file.Close();

	if(channel == "TTL"){
		setup_mva<TTL::MVABase>("comboSelectorMVA", "combos", cfg, proPack, train_combo_mva || all, train_combo_mva || all, 0);
		setup_mva<TTL::MVABase>("MVA", "tmva", cfg, proPack, prep_train || all, train || all, 1);
	}else if(channel == "TLL"){
		setup_mva<TLL::MVABase>("comboSelectorMVA", "combos", cfg, proPack, train_combo_mva || all, train_combo_mva || all, 0);
		setup_mva<TLL::MVABase>("MVA", "tmva", cfg, proPack, prep_train || all, train || all, 1);
	}else{	assert(GetParam("channel") == "TTL or TLL");		}
    proPack->DistributeProcesses();


    if (prep_plots or create_corr or all) {
        DistributeProcesses();

        if (create_corr or all) {
            MakeTreeForCorrelations();
        }

        if (prep_plots or all) {
            PreparePlots();
            CombineProcesses();
        }
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


