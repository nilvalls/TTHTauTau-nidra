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
	backgrounds.push_back("ZjetsM10-50");
	backgrounds.push_back("ZjetsM50");
	iProPack->CombineAndRemoveMCbackgrounds(backgrounds,"Zjets", "Z + jets", "Z + jets", 5);	

	backgrounds.clear();
	backgrounds.push_back("WW");
	backgrounds.push_back("WZ");
	backgrounds.push_back("ZZ");
	iProPack->CombineAndRemoveMCbackgrounds(backgrounds,"DiBoson", "DiBoson", "DiBoson", 3);	

	backgrounds.clear();
	backgrounds.push_back("sT-sCh");
	backgrounds.push_back("sTW");
	backgrounds.push_back("sT-tCh");
	backgrounds.push_back("sTbarW");
	backgrounds.push_back("sTbar-sCh");
	backgrounds.push_back("sTbar-tCh");
	iProPack->CombineAndRemoveMCbackgrounds(backgrounds,"SingleTop", "Single t/tbar", "single t/#bar{t}", 4);	

	backgrounds.clear();
	backgrounds.push_back("ttPlusW");
	backgrounds.push_back("ttPlusZ");
	iProPack->CombineAndRemoveMCbackgrounds(backgrounds,"ttWZ", "ttbar + W/Z", "t#bar{t} + W/Z", 800);	

}

