
#define PUcorrector_cxx
#include "PUcorrector.h"

using namespace std;

// Summer 11
// #define MAXPU 25

// Fall 11
#define MAXPU 50



// Default constructor
PUcorrector::PUcorrector(){
	generated.clear();
	weight.clear();
	for(int pv=0; pv<MAXPU; pv++){ weight[pv] = 1.0; }
}

// Constructor taking integrated lumi as argument
PUcorrector::PUcorrector(string const iFile){
	generated.clear();
	weight.clear();

	for(int pv=0; pv<MAXPU; pv++){ weight[pv] = 1.0; }

	TH1D* data_npu_estimated = NULL;

	string filename; string dir; dir = "";
	ifstream puList (iFile.c_str());
	if (puList.is_open()){
		while ( puList.good() ){
			getline (puList,filename);
			if(filename.length()==0){ continue; }
			if(dir.length() == 0){ dir = filename; }
			else{
				TFile file((string(dir+filename)).c_str());
				gROOT->cd(); // MUST HAVE THIS HERE!!!
				if(data_npu_estimated == NULL){
					data_npu_estimated = (TH1D*)((TH1D*)(file.Get("pileup")))->Clone();
				}else{
					data_npu_estimated->Add((TH1D*)file.Get("pileup")); 
				}

				file.Close();
			}
		}
		puList.close();
	}

	data_npu_estimated->Scale(1/(double)data_npu_estimated->Integral());

	/*
	const double npu_probs[25] = {
		0.0698146584,	  // 0  
		0.0698146584,	  // 1  
		0.0698146584,	  // 2  
		0.0698146584,	  // 3  
		0.0698146584,	  // 4  
		0.0698146584,	  // 5  
		0.0698146584,	  // 6  
		0.0698146584,	  // 7  
		0.0698146584,	  // 8  
		0.0698146584,	  // 9  
		0.0698146584,	  // 10 
		0.0630151648,	  // 11 
		0.0526654164,	  // 12 
		0.0402754482,	  // 13 
		0.0292988928,	  // 14 
		0.0194384503,	  // 15 
		0.0122016783,	  // 16 
		0.007207042,	  // 17 
		0.004003637,	  // 18 
		0.0020278322,	  // 19 
		0.0010739954,	  // 20 
		0.0004595759,	  // 21 

	}; //*/

	// Fall 2011
	const double npu_probs[50] = {
			0.003388501,
			0.010357558,
			0.024724258,
			0.042348605,
			0.058279812,
			0.068851751,
			0.072914824,
			0.071579609,
			0.066811668,
			0.060672356,
			0.054528356,
			0.04919354,
			0.044886042,
			0.041341896,
			0.0384679,
			0.035871463,
			0.03341952,
			0.030915649,
			0.028395374,
			0.025798107,
			0.023237445,
			0.020602754,
			0.0180688,
			0.015559693,
			0.013211063,
			0.010964293,
			0.008920993,
			0.007080504,
			0.005499239,
			0.004187022,
			0.003096474,
			0.002237361,
			0.001566428,
			0.001074149,
			0.000721755,
			0.000470838,
			0.00030268,
			0.000184665,
			0.000112883,
			6.74043E-05,
			3.82178E-05,
			2.22847E-05,
			1.20933E-05,
			6.96173E-06,
			3.4689E-06,
			1.96172E-06,
			8.49283E-07,
			5.02393E-07,
			2.15311E-07,
			9.56938E-08
		};


	vector<double> result(MAXPU);

	double s = 0.0;
	for(int npu=0; npu<MAXPU; ++npu){
		double npu_estimated = data_npu_estimated->GetBinContent(data_npu_estimated->GetXaxis()->FindBin(npu));                              
		if(npu_probs[npu] > 0){
			weight[npu] = npu_estimated / npu_probs[npu];
		}else{
			weight[npu] = 1.0;
		}
		//cout << npu << "  " << npu_estimated << "  " << npu_probs[npu] << "  " << weight[npu] << endl;
		s += npu_estimated;
		//cout << "SUM: " << s << endl;
	}

	// normalize weights such that the total sum of weights over thw whole sample is 1.0, i.e., sum_i  weight[i] * npu_probs[i] should be 1.0 (!)
	for(int npu=0; npu<MAXPU; ++npu){ weight[npu] /= s; }
	
}



// Copy constructor
PUcorrector::PUcorrector(PUcorrector const & iPUcorrector){
}

// Default destructor
PUcorrector::~PUcorrector(){}

// Return the trigger weight given the pT
float const PUcorrector::GetWeight(float const iNumPV) const{

	float result = 1.0;

	if((iNumPV==0) || (iNumPV>=(MAXPU-1))){ result = 1; }
	else{ result = weight.find(iNumPV)->second; }

	return result;
}

