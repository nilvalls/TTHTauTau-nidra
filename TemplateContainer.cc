/*
    Author:			Jeff Kolb <jkolb@cern.ch>
    Date:			1 April, 2013
    Description:	Container class for histograms representing systematic shifts.
    Notes:

*/

#include <cmath>
#include <stdlib.h>

// #include "boost/filesystem/operations.hpp"

#include "TemplateContainer.h"

using namespace std;

// Default constructor
TemplateContainer::TemplateContainer(): storageFile(0) {
    cout << "WARNING: Using default constructor of TemplateContainer." << endl;
}

// Default destructor
TemplateContainer::~TemplateContainer()
{
    if( storageFile != NULL ) {
        //cout << "Closing storage file" << endl;
        storageFile->Close();
    }

    TString removeCmd = "rm -f ";
    removeCmd += storageFile->GetName();
    system(removeCmd);
}

TemplateContainer::TemplateContainer(map<string,string>const & iParams): storageFile(0)
{
    params = iParams;
    TString fn = ".storage_" + params["analysisTag"] + ".root";
    storageFile = new TFile(fn.ReplaceAll("/", "_"), "RECREATE");

    // parse systematics configuration
    map<string,Config*> sysConfigs;
    Config* sysCfg = NULL;
    if (params.find("systematicsFile") != params.end()) {
        string systematicsFile = params.find("systematicsFile")->second;

        // using namespace boost::filesystem;

        // If additional systematics are not defined locally, look in nidra's
        // directory
        //path lpath(systematicsFile);
        //if (not exists(lpath) or is_directory(lpath)) {
        //    path epath = system_complete(lpath);
        //    systematicsFile = epath.string();
        //}

        //cout << "Using systematics file at: " << endl << systematicsFile << endl;

        sysCfg = new Config(systematicsFile);
        sysConfigs = sysCfg->getGroups();
    } else {
        cout << "Configuration parameter 'systematicsFile' is not found! No shape systematic uncertainties will be plotted." << endl;
    }

    //cout << "Adding shape uncertainties from..." << endl;
    
    // loop over entries in systematics cfg file
    for(map<string,Config*>::const_iterator cfgIterator = sysConfigs.begin(); cfgIterator != sysConfigs.end(); ++cfgIterator) {
        string fileName = cfgIterator->second->pString("fullFilePath");
        string sysName = cfgIterator->first;
        cout << fileName << endl; 
        if( fileName == "" ) {
            cout << "Missing 'fullFilePath' parameter for systematic " << sysName << "...skipping!" << endl; 
            continue;
        }

        TFile file(fileName.c_str());
        if (!file.IsOpen()) {
            cout << "File " << fileName << " can not be opened! Skipping '" << sysName << "' systematic..." << endl;
            continue;
        }

        ProPack* proPack = 0;
        file.GetObject((params["propack_name"]).c_str(), proPack);
        if (!proPack) {
            cout << "Can't get ProPack from file " << fileName << " for '" << sysName << "' systematic...skipping!" << endl;
            continue;
        }

        // Get map of shifted templates
        vector<string> plotNames = proPack->GetAvailableProcess().GetHContainerForSignal()->GetNames();
        map<string,TH1*> backgroundSums;
        for( vector<string>::const_iterator plotNameIt = plotNames.begin(); plotNameIt != plotNames.end(); ++plotNameIt) {
            backgroundSums.insert(pair<string,TH1*>(*plotNameIt,GetSumOfBackgroundTemplates(*plotNameIt,proPack)));
        }

        // Fill and store struct
        if ((sysName.find("up") != string::npos) || (sysName.find("Up") != string::npos)) {
            string sysNameStripped = sysName.substr(0,sysName.size()-2);
            shifts[sysNameStripped].bgSumsUp = backgroundSums;
        } else if((sysName.find("down") != string::npos) || (sysName.find("Down") != string::npos)) {
            string sysNameStripped = sysName.substr(0,sysName.size()-4);
            shifts[sysNameStripped].bgSumsDown = backgroundSums;
        } else {
            cerr << "Can't determine systematics in file " << fileName << endl;
        }
    }

    if (!sysCfg)
        delete sysCfg;
}

float TemplateContainer::GetAbsoluteErrorUp(string variableName, int iBin, float centralBinContent) {
    return GetAbsoluteError(variableName,iBin,centralBinContent,true);
}
float TemplateContainer::GetAbsoluteErrorDown(string variableName, int iBin, float centralBinContent) {
    return GetAbsoluteError(variableName,iBin,centralBinContent,false);
}
float TemplateContainer::GetAbsoluteError(string variableName, int iBin, float centralBinContent, bool shiftUp) {

    TH1* shiftedTemplate;
    float absError = 0;
  
    for( map<string,Shift>::iterator shiftIterator = shifts.begin(); shiftIterator != shifts.end(); ++shiftIterator) {
        
        if(shiftUp && shiftIterator->second.bgSumsUp.find(variableName) != shiftIterator->second.bgSumsUp.end()) 
            shiftedTemplate = shiftIterator->second.bgSumsUp[variableName];
        else if(!shiftUp && shiftIterator->second.bgSumsDown.find(variableName) != shiftIterator->second.bgSumsDown.end()) 
            shiftedTemplate = shiftIterator->second.bgSumsUp[variableName];
        else 
            continue;
        
        float binContent = shiftedTemplate->GetBinContent(iBin);
        float binDiff = fabs(binContent - centralBinContent);
        absError = sqrt(absError*absError + binDiff*binDiff);
        //cout << "var = " << variableName << "; bin = " << iBin << "; sys = " << shiftIterator->first << (shiftUp ? "Up" : "Down") << "; binContent = " << binContent << "; centralBinContent = " << centralBinContent << "; abs error = " << binDiff << "; total abs error = " << absError << endl;
    }
    return absError;
}

// code adapted from Plotter::GetBackgroundSum
TH1* TemplateContainer::GetSumOfBackgroundTemplates(string variableName, ProPack* proPack) {
    
    // Put new histograms in storage file
    storageFile->cd();

    // Get sum of MC backgrounds
	TH1* buffer = NULL;
    
	// Add each MC background if we have them
    //cout << proPack->GetMCbackgrounds()->size() << " backgrounds in propack" << endl;
	if(proPack->HaveMCbackgrounds()){
		for(unsigned int b = 0; b < proPack->GetMCbackgrounds()->size(); b++){
			//if(!proPack->GetMCbackgrounds()->at(b).Plot())
            //    continue; 
			if(buffer == NULL) {
                buffer = (TH1*)proPack->GetMCbackgrounds()->at(b).GetHistoForSignal(variableName)->GetHisto()->Clone(); 
            } else {
                buffer->Add(proPack->GetMCbackgrounds()->at(b).GetHistoForSignal(variableName)->GetHisto()); 
            }
		}
	} else {
        cout << "proPack->HaveMCbackgrounds() is false for " << variableName << endl;
    }

	if(buffer == NULL){ cerr << "ERROR --> [TemplateContainer::GetSumOfBackgroundTemplates]: requested sum of backgrounds for " << variableName << " but result came out NULL" << endl; exit(1); }

    return buffer;
}
