#ifndef TTLBranches_h
#define TTLBranches_h

#include "../Branches.h"
// #include "TMVAEvaluator.h"

using namespace std;

class TTL_ComboSelector;

class TTLBranches : public Branches {
	private:
        TTL_ComboSelector *comboSelector;
        float conesize;
        vector<int> jetIndexCache;
        int jetIndexCacheCombo;

		void	Null();
		void	Delete();
		void	Clear();
		void	SetBranchAddresses();

	public:
		TTLBranches();
		TTLBranches(map<string,string> const &, vector<string> const &);
		~TTLBranches();

        virtual void GetEntry(double);

        // Get index (excluding taus) of jet in J_ branches (which include taus)
        unsigned int GetJetIndex(const int, const unsigned int);
		unsigned int	GetTau1IsolationIndex(const unsigned int) const;
		unsigned int	GetTau2IsolationIndex(const unsigned int) const;
		unsigned int	GetTau1AntiElectronIndex(const unsigned int) const;
		unsigned int	GetTau2AntiElectronIndex(const unsigned int) const;
		unsigned int	GetTau1AntiMuonIndex(const unsigned int) const;
		unsigned int	GetTau2AntiMuonIndex(const unsigned int) const;
        unsigned int    GetTau1MatchIndex(const unsigned int) const;
        unsigned int    GetTau2MatchIndex(const unsigned int) const;
        float GetComboSelectorResponse(const unsigned int) const;
        // float GetMVAResponse(const unsigned int) const;

		#include "Branches_declarations.h"
};

#endif
