#ifndef TTLBranches_h
#define TTLBranches_h

#include "../Branches.h"

using namespace std;

class TTLBranches : public Branches {

	public:

	private:
		void	Null();
		void	Delete();
		void	Clear();
		void	SetBranchAddresses();

	public:
		TTLBranches();
		TTLBranches(map<string,string> const &, vector<string> const &);
		~TTLBranches();

		unsigned int	GetTau1IsolationIndex(const unsigned int) const;
		unsigned int	GetTau2IsolationIndex(const unsigned int) const;
		unsigned int	GetTau1AntiElectronIndex(const unsigned int) const;
		unsigned int	GetTau2AntiElectronIndex(const unsigned int) const;
		unsigned int	GetTau1AntiMuonIndex(const unsigned int) const;
		unsigned int	GetTau2AntiMuonIndex(const unsigned int) const;
        unsigned int    GetTau1MatchIndex(const unsigned int) const;
        unsigned int    GetTau2MatchIndex(const unsigned int) const;

	public:
		#include "Branches_declarations.h"

};

#endif










