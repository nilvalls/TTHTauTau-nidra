#ifndef TLLBranches_h
#define TLLBranches_h

#include "../Branches.h"

class TLLBranches : public Branches {
	private:
        float conesize;
        std::vector<int> jetIndexCache;
        int jetIndexCacheCombo;

		void	Null();
		void	Delete();
		void	Clear();
		void	SetBranchAddresses();

	public:
        TLLBranches();
        TLLBranches(const std::string&, const std::vector<std::string>&);
        ~TLLBranches();

        virtual void GetEntry(double);
        inline virtual unsigned int GetNCombos() { return TLL_NumCombos; };
        virtual bool IsGoodGenMatch(const int&) const;
        virtual void RegisterCuts(CutFlow&);
        virtual unsigned int GetNumCombos();

        // Get index (excluding taus) of jet in J_ branches (which include taus)
        unsigned int	GetJetIndex(const int, const unsigned int);
		unsigned int	GetTauIsolationIndex(const unsigned int) const;
		unsigned int	GetTauIsolationIndexMVA(const unsigned int) const;
		unsigned int	GetTauIsolationIndexMVA2(const unsigned int) const;
		unsigned int	GetTauIsolationIndex3Hits(const unsigned int) const;
		unsigned int	GetTauAntiElectronIndex(const unsigned int) const;
		unsigned int	GetTauAntiElectronIndexMVA2(const unsigned int) const;
		unsigned int	GetTauAntiElectronIndexMVA3(const unsigned int) const;
		unsigned int	GetTauAntiMuonIndex(const unsigned int) const;
		unsigned int	GetTauAntiMuonIndex2(const unsigned int) const;
        unsigned int    GetTauMatchIndex(const unsigned int) const;
        // float GetMVAResponse(const unsigned int) const;

		#include "Branches_declarations.h"
};

#endif
