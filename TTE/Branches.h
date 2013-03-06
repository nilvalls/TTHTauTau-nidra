#ifndef TTEBranches_h
#define TTEBranches_h

#include "../Branches.h"

using namespace std;

class TTEBranches : public Branches {

	public:

	private:
		void	Null();
		void	Delete();
		void	Clear();
		void	SetBranchAddresses();

	public:
		TTEBranches();
		TTEBranches(map<string,string> const &, vector<string> const &);
		~TTEBranches();

		unsigned int	GetTau1IsolationIndex(const unsigned int) const;
		unsigned int	GetTau2IsolationIndex(const unsigned int) const;
		unsigned int	GetTau1AntiElectronIndex(const unsigned int) const;
		unsigned int	GetTau2AntiElectronIndex(const unsigned int) const;
		unsigned int	GetTau1AntiMuonIndex(const unsigned int) const;
		unsigned int	GetTau2AntiMuonIndex(const unsigned int) const;

	public:
		#include "Branches_declarations.h"

};

#endif










