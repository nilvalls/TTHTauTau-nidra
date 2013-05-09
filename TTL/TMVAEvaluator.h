#ifndef TTL_TMVAEvaluator_h
#define TTL_TMVAEvaluator_h

#include "../ProPack.h"
#include "Branches.h"
#include "TMVA/Factory.h"
#include "TMVA/Reader.h"

class TTL_TMVAEvaluator {
    public:
        static TTL_TMVAEvaluator *gMVA;
        static TTL_TMVAEvaluator *gComboMVA;

        TTL_TMVAEvaluator(const std::string&, const std::string&, const std::string&, const std::vector<std::string>&, const int rnk=1);
        virtual ~TTL_TMVAEvaluator();

        void CreateTrainingSample(const std::string&, ProPack*);
        void CreateTrainingSample(const std::string&, const std::string&, ProPack*);
        float Evaluate(TTLBranches*, int);
        void FillTree(TTree*, const Process*);
        void FillTree(TTree*, TTree*, const Process*);
        void FillVariables(TTLBranches*, const int);
        virtual bool BookMVA();
        virtual void TrainMVA();

    protected:
        template<typename T> void SetupVariables(T*);
        template<typename W, typename T> void AddVariableConditionally(W*, const string&, const char&, T&);
        template<typename T> void AddVariable(TMVA::Factory*, const string&, const char&, T&);
        template<typename T> void AddVariable(TMVA::Reader*, const string&, const char&, T&);
        template<typename T> void AddVariable(TTree*, const string&, const char&, T&);

        TMVA::Reader* reader;

        std::string basedir;
        std::vector<std::string> variables;
        std::string method;
        std::string method_options;

        int rank;

        std::map<std::string, double> backgrounds;

        std::string log_filename;
        std::string output_filename;
        std::string sample_filename;
        std::string weight_filename;

        float csr;
        float HT;
        float Tau1Pt;
        float Tau1Eta;
        float Tau2Pt;
        float Tau1DecayMode;
        float Tau2DecayMode;
        float Tau1IsolationIndex;
        float Tau1IsolationIndexMVA2;
        float Tau1IsolationMVA2Raw;
        float Tau2IsolationIndex;
        float Tau2IsolationIndexMVA2;
        float Tau2IsolationMVA2Raw;
        float Tau1LTPt;
        float Tau2LTPt;
        float Tau1NProngs;
        float Tau2NProngs;
        float DitauVisibleMass;
        float DeltaRTau1Tau2;
        float DeltaRTau1Lepton;
        float DeltaRTau2Lepton;
        float DeltaRTau1LeadingJet;
        float DeltaRTau2LeadingJet;
        float DeltaRTau1SubleadingJet;
        float DeltaRTau2SubleadingJet;
        float DeltaRLeptonLeadingJet;
        float DeltaRLeptonSubleadingJet;
        float LeadingJetSubleadingJetMass;
        float LeadingJetPt;
        float SubLeadingJetPt;
};

#endif
