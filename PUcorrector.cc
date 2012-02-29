
#define PUcorrector_cxx
#include "PUcorrector.h"

using namespace std;



// Default constructor
PUcorrector::PUcorrector(){
	generated.clear();
	weight.clear();
	for(int pv=0; pv<25; pv++){ weight[pv] = 1.0; }
}

// Constructor taking integrated lumi as argument
PUcorrector::PUcorrector(string const iFile){
	generated.clear();
	weight.clear();

	for(int pv=0; pv<25; pv++){ weight[pv] = 1.0; }

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

	/*			const long double npu_probs[25] = {  0.069286816, // 0  
				0.069286816, // 1  
				0.069286816, // 2  
				0.069286816, // 3  
				0.069286816, // 4  
				0.069286816, // 5  
				0.069286816, // 6  
				0.069286816, // 7  
				0.069286816, // 8  
				0.069286816, // 9  
				0.069286816, // 10 
				0.06518604 , // 11 
				0.053861878, // 12 
				0.040782032, // 13 
				0.030135062, // 14 
				0.019550796, // 15 
				0.012264707, // 16 
				0.007449117, // 17 
				0.004502075, // 18 
				0.002194605, // 19 
				0.001166276, // 20 
				0.000476543, // 21 
				0.000188109, // 22 
				7.52436E-05, // 23 
				1.25406E-05  // 24 
				}; //*/


	vector<double> result(25);

	double s = 0.0;
	for(int npu=0; npu<25; ++npu){
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
	for(int npu=0; npu<25; ++npu){ weight[npu] /= s; }
	
}



// Copy constructor
PUcorrector::PUcorrector(PUcorrector const & iPUcorrector){
}

// Default destructor
PUcorrector::~PUcorrector(){}

// Return the trigger weight given the pT
float const PUcorrector::GetWeight(float const iNumPV) const{

	float result = 1.0;

	if((iNumPV==0) || (iNumPV>=24)){ result = 0; }
	else{ result = weight.find(iNumPV)->second; }

	return result;
}

