//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun  7 03:28:02 2011 by ROOT version 5.27/06b
// from TTree HMTTree/TauTauTree
// found on file: ditau_nTuple.root
//////////////////////////////////////////////////////////

#ifndef TTMBranches_h
#define TTMBranches_h

#include "../Branches.h"

using namespace std;

class TTMBranches : public Branches {

	public:

	private:
		void	Null();
		void	Delete();
		void	Clear();
		void	SetBranchAddresses();

	public:
		TTMBranches();
		TTMBranches(map<string,string> const &, string const);
		~TTMBranches();


		unsigned int	GetTau1IsolationIndex(const unsigned int);
		unsigned int	GetTau2IsolationIndex(const unsigned int);
		unsigned int	GetTau1AntiElectronIndex(const unsigned int);
		unsigned int	GetTau2AntiElectronIndex(const unsigned int);
		unsigned int	GetTau1AntiMuonIndex(const unsigned int);
		unsigned int	GetTau2AntiMuonIndex(const unsigned int);

	public:
		#include "Branches_declarations.h"

};

#endif










