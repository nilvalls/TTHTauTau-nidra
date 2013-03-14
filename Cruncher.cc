/*
    Author:			Nil Valls <nil.valls@cern.ch>
    Date:			11 Jun 2011
    Description:	Plot stacking class.
    Notes:

*/

#include "Cruncher.h"

#define Cruncher_cxx
using namespace std;

#define AT __LINE__

// Default constructor
Cruncher::Cruncher(){
	file = NULL;
	proPack = NULL;
}

Cruncher::Cruncher(map<string,string>const & iParams){
	params = iParams;
	Long_t *id,*size,*flags,*mt; id=NULL; size=NULL;flags=NULL;mt=NULL;
	bool badFile = gSystem->GetPathInfo((params["process_file"]).c_str(),id,size,flags,mt);
	if(badFile){ cerr << "ERROR: trying to fill plots but proPack file does not exist. Please run the event analysis first" << endl; exit(1); }

	file = new TFile((params["process_file"]).c_str(), "UPDATE");
	file->cd();

	proPack = ((ProPack*)file->Get((params["propack_name"]).c_str()));
	processes = proPack->GetProcesses();

}

// Default destructor
Cruncher::~Cruncher(){
	delete proPack; proPack = NULL;
	file->Close();
}

void Cruncher::PrintEfficiencies(string const iFormat, string const iOptions, bool qcd){ 

	string output = "";
	if(iFormat.compare("HTML")==0){
		output = ((params["efficiency_output"])+ "efficiency" + (qcd ? "QCD" : "") + "_" + iOptions + ".html");
		cout << "\tCalculating and printing numbers in HTML to: " << output << endl;
	}else if(iFormat.compare("TEX")==0){
		output = ((params["efficiency_output"])+ "efficiency" + (qcd ? "QCD" : "") + "_" + iOptions + ".tex.txt");
		cout << "\tCalculating and printing numbers in TEX  to: " << output << endl;
	}else if(iFormat.compare("TXT")==0){
		output = ((params["efficiency_output"])+ "efficiency" + (qcd ? "QCD" : "") + "_" + iOptions + ".txt");
		cout << "\tCalculating and printing numbers in TXT  to: " << output << endl;
	}else if(iFormat.compare("CSV")==0){
		output = ((params["efficiency_output"])+ "efficiency" + (qcd ? "QCD" : "") + "_" + iOptions + ".csv.txt");
		cout << "\tCalculating and printing numbers in CSV to: " << output << endl;
	}else{
		cout << "WARNING: Trying to print numbers in \"" << iFormat << "\" but this format is not valid." << endl;
	}

    bool has_colspan = false;
    string start = "";
    string header_start = "";
    string header_middle = "";
    string header_end = "";
    string subheader_start = "";
    string subheader_elem_start = "";
    string subheader_elem_end = "";
    string subheader_end = "";
    string line_start = "";
    string line_middle = "";
    string line_middle_e = "";
    string line_middle_c = "";
    string line_middle_r = "";
    string line_end = "";
    string end = "";

    ostringstream contents;

    if (iFormat == "CSV") {
        header_middle        = ",";
        subheader_elem_start = ",";
        line_middle          = ",";
    } else if (iFormat == "HTML") {
        stringstream colsp;
        colsp << " colspan=\"" << GetNumberOfOptions(iOptions) << "\">";

        contents << setprecision(7);

        has_colspan          = true;
        start                = "<HTML>\n<BODY>\n<TABLE border=1 cellspacing=0>";
        header_start         = "<TR><TH rowspan=\"2\">Cut";
        header_middle        = "</TH><TH" + colsp.str();
        header_end           = "</TH></TR>";
        subheader_start      = "<TR>";
        subheader_elem_start = "<TH>";
        subheader_elem_end   = "</TH>";
        subheader_end        = "</TH></TR>";
        line_start           = "<TR><TD>";
        line_middle          = "</TD><TD ";
        line_middle_e        = " bgcolor=\"#F0FFF0\">";
        line_middle_c        = " bgcolor=\"#FFDAB9\">";
        line_middle_r        = " bgcolor=\"#E0FFFF\">";
        line_end             = "</TD></TR>";
        end                  = "</TABLE></BODY>\n</HTML>";
    }

    contents << start << header_start;
    vector<Process*>::const_iterator p;
    for (p = processes.begin(); p != processes.end(); ++p) {
        if (!(*p)->Plot())
            continue;
        if (has_colspan)
            contents << header_middle << (*p)->GetNiceName();
        else
            for (int i = 0; i < GetNumberOfOptions(iOptions); ++i)
                contents << header_middle << (*p)->GetNiceName();
    }
    contents << header_end << endl << subheader_start;
    for (p = processes.begin(); p != processes.end(); ++p) {
        if (!(*p)->Plot())
            continue;
        if (iOptions.find("e") != string::npos)
            contents << subheader_elem_start << "Events" << subheader_elem_end;
        if (iOptions.find("r") != string::npos)
            contents << subheader_elem_start << "Rel." << subheader_elem_end;
        if (iOptions.find("c") != string::npos)
            contents << subheader_elem_start << "Cum." << subheader_elem_end;
    }
    contents << subheader_end << endl;
    vector<string>::const_iterator c;
    vector<string> cuts = processes.at(0)->GetCutFlow()->GetCutNames();
    if (iOptions.find("n") != string::npos)
        cuts = processes.at(0)->GetNormalizedCutFlow()->GetCutNames();
    for (c = cuts.begin(); c != cuts.end(); ++c) {
        contents << line_start << *c;
        for (p = processes.begin(); p != processes.end(); ++p) {
            if (!(*p)->Plot())
                continue;
            CutFlow *cutflow = (*p)->GetCutFlow();
            if (iOptions.find("n") != string::npos)
                cutflow = (*p)->GetNormalizedCutFlow();
            if (iOptions.find("e") != string::npos)
                contents << line_middle << line_middle_e <<
                    (qcd ? cutflow->GetPassedEventsForQCD(*c) : cutflow->GetPassedEventsForSignal(*c));
            if (iOptions.find("r") != string::npos)
                contents << line_middle << line_middle_r << 100 * 
                    (qcd ? cutflow->GetRelEffForQCD(*c) : cutflow->GetRelEffForSignal(*c));
            if (iOptions.find("c") != string::npos)
                contents << line_middle << line_middle_c << 100 * 
                    (qcd ? cutflow->GetCumEffForQCD(*c) : cutflow->GetCumEffForSignal(*c));
        }
        contents << line_end << endl;
    }
    contents << end;
    SaveToFile(contents.str(), output);
}

void Cruncher::PrintEfficienciesForQCD(string const iFormat, string const iOptions){ 
    PrintEfficiencies(iFormat, iOptions, true);
}

bool Cruncher::IsOptionThere(string const iOption, string const iOptions){ return ((0 <= iOptions.find(iOption)) && (iOptions.find(iOption) < iOptions.length())); }
int Cruncher::GetNumberOfOptions(string const iOptions){
	int result = 0;
	if(IsOptionThere("e", iOptions)){ result++; }
	if(IsOptionThere("r", iOptions)){ result++; }
	if(IsOptionThere("c", iOptions)){ result++; }
	return result;
}

void Cruncher::SaveToFile(stringstream const iOutput, string const iFile){ SaveToFile(iOutput.str(), iFile); }
void Cruncher::SaveToFile(string const iOutput, string const iFile){
	ofstream fout;
	fout.open(iFile.c_str());
	if (fout.is_open()){
		fout << iOutput;
		fout.close();
	}else{
		cerr << "ERROR: Could not open file \"" << iFile << "\" for writing." << endl;
		exit(1);
	}
}


