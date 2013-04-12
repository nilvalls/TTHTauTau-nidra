#ifndef TTL_ComboSelector_h
#define TTL_ComboSelector_h

#include "TMVAEvaluator.h"

class TTL_ComboSelector : public TTL_TMVAEvaluator {
    public:
        static TTL_ComboSelector *gComboMVA;

        TTL_ComboSelector(const std::string&, const std::string&, const std::string&, const std::vector<std::string>&);
        virtual ~TTL_ComboSelector();

        void InitiateTrainingSample();
        void FinalizeTrainingSample();
        void FillTrees(TTLBranches*);
        multimap<double, unsigned int> GetSortedCombosByPt(Branches*);
        multimap<double, unsigned int> GetSortedCombos(Branches*);
        virtual void TrainMVA();

    private:
        TFile *ofile;
        TTree *sig;
        TTree *bkg;
};

#endif
