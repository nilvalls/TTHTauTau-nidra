/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			11 Jun 2011
    Description:	Plot stacking class.
    Notes:

*/

#include "Combiner.h"

#define Combiner_cxx
using namespace std;

#define AT __LINE__

// Default constructor
Combiner::Combiner(){
}

// Default destructor
Combiner::~Combiner(){
}

Combiner::Combiner(map<string,string>const & iParams){
	params = iParams;
	Long_t *id,*size,*flags,*mt; id=NULL; size=NULL;flags=NULL;mt=NULL;
	bool badFile = gSystem->GetPathInfo((params["process_file"]).c_str(),id,size,flags,mt);
	if(badFile){ cerr << "ERROR: trying to fill plots but proPack file does not exist. Please run the event analysis first" << endl; exit(1); }

	TFile* file = new TFile((params["process_file"]).c_str(), "UPDATE");
	file->cd();
	ProPack* tempProPack = (ProPack*)file->Get((params["propack_name"]).c_str());

	Combine(tempProPack);
		

	file->cd();
	tempProPack->Write((params["propack_name"]).c_str(), TObject::kOverwrite);
	file->Close();
	delete file;


}

void Combiner::Combine(ProPack * iProPack){
	vector<string> backgrounds;

	backgrounds.clear();
	backgrounds.push_back("TTbar_Hadronic");
	backgrounds.push_back("TTbar_SemiLept");
	backgrounds.push_back("TTbar_Fulllept");
	iProPack->CombineAndRemoveMCbackgrounds(backgrounds, "TTbar", "t + tbar", "t #bar{t}", 870);	

	backgrounds.clear();
	backgrounds.push_back("ZplusJets_LowMass");
	backgrounds.push_back("ZplusOneJet");
	backgrounds.push_back("ZplusTwoJets");
	backgrounds.push_back("ZplusThreeJets");
	backgrounds.push_back("ZplusFourJets");
	iProPack->CombineAndRemoveMCbackgrounds(backgrounds,"Zjets", "Z + jets", "Z + jets", 5);	

	backgrounds.clear();
	backgrounds.push_back("WW");
	backgrounds.push_back("WZ");
	backgrounds.push_back("ZZ");
	iProPack->CombineAndRemoveMCbackgrounds(backgrounds,"DiBoson", "DiBoson", "DiBoson", 3);	

	backgrounds.clear();
	backgrounds.push_back("singleTopSch");
	backgrounds.push_back("singleTopBarSch");
	backgrounds.push_back("singleTopTch");
	backgrounds.push_back("singleTopBarTch");
	backgrounds.push_back("singleTopPlusW");
	backgrounds.push_back("singleTopBarPlusW");
	iProPack->CombineAndRemoveMCbackgrounds(backgrounds,"SingleTop", "Single t/tbar", "single t/#bar{t}", 4);	

	backgrounds.clear();
	backgrounds.push_back("ttPlusW");
	backgrounds.push_back("ttPlusZ");
	iProPack->CombineAndRemoveMCbackgrounds(backgrounds,"ttWZ", "ttbar + W/Z", "t#bar{t} + W/Z", 880);

	backgrounds.clear();
	backgrounds.push_back("WplusOneJet");
	backgrounds.push_back("WplusTwoJets");
	backgrounds.push_back("WplusThreeJets");
	backgrounds.push_back("WplusFourJets");
	iProPack->CombineAndRemoveMCbackgrounds(backgrounds,"Wjets", "W + jets", "W + jets", 810);
}

