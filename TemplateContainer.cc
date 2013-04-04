/*
    Author:			Jeff Kolb <jkolb@cern.ch>
    Date:			1 April, 2013
    Description:	Container class for histograms representing systematic shifts.
    Notes:

*/

#include "TemplateContainer.h"

#include "math.h"
#include "TH1F.h"
#include "ProPack.h"

#include "boost/filesystem/operations.hpp"

using namespace std;

#define AT __LINE__

// Default constructor
TemplateContainer::TemplateContainer(){
	cout << "WARNING: Using default constructor of TemplateContainer." << endl;
}

// Default destructor
TemplateContainer::~TemplateContainer(){
    
    // clean up ROOT files
    for( vector<Shift>::iterator shiftIterator = shifts.begin(); shiftIterator != shifts.end(); ++shiftIterator) {
        shiftIterator->file->Close();
        delete shiftIterator->file;
        shiftIterator->file = NULL;
        shiftIterator->proPack = NULL;
    }

}

TemplateContainer::TemplateContainer(map<string,string>const & iParams) {
	
    params = iParams;
    
    // parse systematics configuration
    map<string,Config*> sysConfigs;
    //vector<pair<string,Config*> > sysConfigs;
    Config* sysCfg = NULL;
    if (params.find("systematicsFile") != params.end()) {
        
        string systematicsFile = params.find("systematicsFile")->second;
        
        using namespace boost::filesystem;

        // If additional systematics are not defined locally, look in nidra's
        // directory
        //path lpath(systematicsFile);
        //if (not exists(lpath) or is_directory(lpath)) {
        //    path epath = system_complete(lpath);
        //    systematicsFile = epath.string();
        //}
        cout << "Using systematics file at: " << endl << systematicsFile << endl;

        sysCfg = new Config(systematicsFile);
        sysConfigs = sysCfg->getGroups();
    } else {
        cout << "Configuration parameter 'systematicsFile' is not found! No shape systematic uncertainties will be plotted." << endl;
    }

    cout << "Adding shape uncertainties from..." << endl;
    
    // loop over entries in systematics cfg file
    for(map<string,Config*>::const_iterator cfgIterator = sysConfigs.begin(); cfgIterator != sysConfigs.end(); ++cfgIterator) {
        string fileName = cfgIterator->second->pString("fullFilePath");
        cout << fileName;
        if( fileName == "" ) {
            cout << "Missing 'fullFilePath' parameter for systematic " << cfgIterator->first << "...skipping!" << endl; 
            continue;
        }
        TFile* file = NULL;
        file = new TFile(fileName.c_str());
        if( file == NULL ) {
            cout << "File " << fileName << " can not be opened! Skipping '" << cfgIterator->first << "' systematic..." << endl;
            continue;
        }
        ProPack* proPack = NULL;
        proPack = (ProPack*)file->Get((params["propack_name"]).c_str());
        if( proPack == NULL ) {
            cout << "Can't get ProPack from file " << fileName << " for '" << cfgIterator->first << "' systematic...skipping!" << endl;
            continue;
        }

        cout << " / " << cfgIterator->first << endl;

        // Fill and store struct
        Shift shift;
        shift.file = file;
        shift.name = cfgIterator->first;
        shift.proPack = proPack;
        shifts.push_back(shift);
    }

    if( sysCfg!=NULL ) {
        delete sysCfg;
    }
}

// assume symmetric errors for now
float TemplateContainer::GetAbsoluteError(string variableName, int iBin, float centralBinContent) {
    TH1F* shiftedTemplate;
    float absError = 0;
    // loop over systematics
    for( vector<Shift>::const_iterator shiftIterator = shifts.begin(); shiftIterator != shifts.end(); ++shiftIterator) {
        // only consider "Up" shifts
        if( shiftIterator->name.find("Up") ==  string::npos ) continue;
        shiftedTemplate = (TH1F*)((GetSumOfBackgroundTemplates(variableName,shiftIterator->proPack)).GetHisto());
        float binContent = shiftedTemplate->GetBinContent(iBin);
        float binDiff = fabs(binContent - centralBinContent);
        absError = sqrt(absError*absError + binDiff*binDiff);
    }
    return absError;
}

float TemplateContainer::GetRelativeError(string variableName, int iBin, float centralBinContent) {
    if( abs(centralBinContent) > 0.00001 ) 
        return (GetAbsoluteError(variableName,iBin,centralBinContent)/centralBinContent);
    else
        return 0;
}

HWrapper TemplateContainer::GetSumOfBackgroundTemplates(string variableName, ProPack* proPack) {

    // Get sum of MC backgrounds
	HWrapper* buffer = NULL;

	// Add each MC background if we have them
	if(proPack->HaveMCbackgrounds()){
		for(unsigned int b = 0; b < proPack->GetMCbackgrounds()->size(); b++){
			if(!proPack->GetMCbackgrounds()->at(b).Plot()){ continue; }
			if(buffer == NULL){	buffer = new HWrapper(*(proPack->GetMCbackgrounds()->at(b).GetHistoForSignal(variableName))); }
			else{ buffer->Add(*(proPack->GetMCbackgrounds()->at(b).GetHistoForSignal(variableName))); }
		}
	}

	if(buffer == NULL){ cerr << "ERROR: requested sum of backgrounds for " << variableName << " but result came out NULL" << endl; exit(1); }
	HWrapper result = HWrapper(*buffer);
	delete buffer;

    return result;
}
