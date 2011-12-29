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
Cruncher::Cruncher(){}

Cruncher::Cruncher(map<string,string>const & iParams){
	params = iParams;
	Long_t *id,*size,*flags,*mt; id=NULL; size=NULL;flags=NULL;mt=NULL;
	bool badFile = gSystem->GetPathInfo((params["process_file"]).c_str(),id,size,flags,mt);
	if(badFile){ cerr << "ERROR: trying to fill plots but proPack file does not exist. Please run the event analysis first" << endl; exit(1); }

	TFile* file = new TFile((params["process_file"]).c_str(), "UPDATE");
	file->cd();

	ProPack proPack = *((ProPack*)file->Get((params["propack_name"]).c_str()));

	processes = ((ProPack*)file->Get((params["propack_name"]).c_str()))->GetProcesses();

	file->Close();
}

// Default destructor
Cruncher::~Cruncher(){}

string Cruncher::GetDocumentHeader(string const iFormat){
	stringstream result; result.str("");

	if(iFormat.compare("HTML")==0){
		result << "<HTML>";
	}else if(iFormat.compare("TEX")==0){

	}else if(iFormat.compare("TXT")==0){

	}else if(iFormat.compare("CSV")==0){

	}else{ cerr << "ERROR: Format for efficiency table \"" << iFormat << "\" invalid." << endl; exit(1); }

	return result.str();
}

string Cruncher::GetDocumentFooter(string const iFormat){
	stringstream result; result.str("");

	if(iFormat.compare("HTML")==0){
		result << "</HTML>";
	}else if(iFormat.compare("TEX")==0){

	}else if(iFormat.compare("TXT")==0){

	}else if(iFormat.compare("CSV")==0){

	}else{ cerr << "ERROR: Format for efficiency table \"" << iFormat << "\" invalid." << endl; exit(1); }

	return result.str();
}

string Cruncher::GetTableHeader(string const iFormat, string const iOptions){
	stringstream result; result.str("");

	if(iFormat.compare("HTML")==0){
		result << "<TABLE border=1 cellspacing=0>" << endl;
		result << "<TR><TH rowspan=2>Cut</TH>";
		for(unsigned int p = 0; p < processes.size(); p++){
			result << "<TH colspan=" << GetNumberOfOptions(iOptions) << ">"
			<< processes.at(p).GetNiceName()
			<< "</TH>";
		}
		result << "</TR>";
	}else if(iFormat.compare("TEX")==0){

	}else if(iFormat.compare("TXT")==0){

	}else if(iFormat.compare("CSV")==0){

	}else{ cerr << "ERROR: Format for efficiency table \"" << iFormat << "\" invalid." << endl; exit(1); }

	return result.str();
}

string Cruncher::GetTableSubHeader(string const iFormat, string const iOptions){
	stringstream result; result.str("");
	for(unsigned int p = 0; p < processes.size(); p++){ result << GetOptionsHeader(iFormat, iOptions); }
	return result.str();
}

string Cruncher::GetTableFooter(string const iFormat){
	stringstream result; result.str("");

	if(iFormat.compare("HTML")==0){
		result << "</TABLE>";
	}else if(iFormat.compare("TEX")==0){

	}else if(iFormat.compare("TXT")==0){

	}else if(iFormat.compare("CSV")==0){

	}else{ cerr << "ERROR: Format for efficiency table \"" << iFormat << "\" invalid." << endl; exit(1); }

	return result.str();
}

string Cruncher::GetOptionsHeader(string const iFormat, string const iOptions){
	stringstream result; result.str("");

	if(iFormat.compare("HTML")==0){
		if(IsOptionThere("e",iOptions)){ result << "<TH>Events</TH>"; }
		if(IsOptionThere("r",iOptions)){ result << "<TH>Rel.</TH>"; }
		if(IsOptionThere("c",iOptions)){ result << "<TH>Cum.</TH>"; }
	}else if(iFormat.compare("TEX")==0){

	}else if(iFormat.compare("TXT")==0){

	}else if(iFormat.compare("CSV")==0){

	}else{ cerr << "ERROR: Format for efficiency table \"" << iFormat << "\" invalid." << endl; exit(1); }

	return result.str();

}

string Cruncher::GetCutLine(string const iFormat, string const iOptions, string const iCut){
	stringstream result; result.str("");

	if(iFormat.compare("HTML")==0){
		result << "<TR>"; 
		result << "<TD>" << iCut << "</TD>";
		for(unsigned int p = 0; p < processes.size(); p++){ result << GetCutTriplet(iFormat, iOptions, iCut, p); }
		result << "</TR>";	
	}else if(iFormat.compare("TEX")==0){

	}else if(iFormat.compare("TXT")==0){

	}else if(iFormat.compare("CSV")==0){

	}else{ cerr << "ERROR: Format for efficiency table \"" << iFormat << "\" invalid." << endl; exit(1); }

	return result.str();
}

string Cruncher::GetCutTriplet(string const iFormat, string const iOptions, string const iCut, int const iProcess){
	stringstream result; result.str("");

	CutFlow cutFlow = CutFlow(*(processes.at(iProcess).GetCutFlow()));

	if(iFormat.compare("HTML")==0){
		if(IsOptionThere("e", iOptions)){ result << "<TD>" << cutFlow.GetPassedEventsForSignal(iCut) << "</TD>"; }
		if(IsOptionThere("r", iOptions)){ result << "<TD>" << cutFlow.GetRelEffForSignal(iCut) << "</TD>"; }
		if(IsOptionThere("c", iOptions)){ result << "<TD>" << cutFlow.GetCumEffForSignal(iCut) << "</TD>"; }
	}else if(iFormat.compare("TEX")==0){

	}else if(iFormat.compare("TXT")==0){

	}else if(iFormat.compare("CSV")==0){

	}else{ cerr << "ERROR: Format for efficiency table \"" << iFormat << "\" invalid." << endl; exit(1); }

	return result.str();
}

string Cruncher::GetEfficiencies(string const iFormat, string const iOptions){
	stringstream result; result.str("");
	if(processes.size()==0){ cerr << "ERROR: Trying to get efficiencies but zero visible processes found" << endl; exit(1); }
	vector<string> cutNames = processes.at(0).GetCutFlow()->GetCutNames();

	result << GetDocumentHeader(iFormat) << endl;
	result << GetTableHeader(iFormat, iOptions) << endl;
	result << GetTableSubHeader(iFormat, iOptions) << endl;

	for(unsigned int c = 0; c < cutNames.size(); c++){ 
		result << GetCutLine(iFormat, iOptions, cutNames.at(c)) << endl; }

	result << GetTableFooter(iFormat) << endl;
	result << GetDocumentFooter(iFormat) << endl;

	return result.str();
}

void Cruncher::PrintEfficiencies(string const iFormat, string const iOptions){ 
	string output = "";
	if(iFormat.compare("HTML")==0){
		output = ((params["efficiency_output"])+ "efficiency_" + iOptions + ".html");
		cout << "\tCalculating and priting numbers in HTML to: " << output << endl;
	}else if(iFormat.compare("TEX")==0){
		output = ((params["efficiency_output"])+ "efficiency_" + iOptions + ".tex.txt");
		cout << "\tCalculating and priting numbers in TEX  to: " << output << endl;
	}else if(iFormat.compare("TXT")==0){
		output = ((params["efficiency_output"])+ "efficiency_" + iOptions + ".txt");
		cout << "\tCalculating and priting numbers in TXT  to: " << output << endl;
	}else if(iFormat.compare("CSV")==0){
		output = ((params["efficiency_output"])+ "efficiency_" + iOptions + ".csv.txt");
		cout << "\tCalculating and priting numbers in CSV to: " << output << endl;
	}else{
		cout << "WARNING: Trying to print numbers in \"" << iFormat << "\" but this format is not valid." << endl;
	}

	SaveToFile(GetEfficiencies(iFormat, iOptions), output);
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


