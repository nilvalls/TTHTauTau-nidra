#ifndef __TLL_MVABase_h
#define __TLL_MVABase_h

#include "TMVA/Factory.h"
#include "TMVA/Reader.h"

#include "../MVABase.h"
#include "../ProPack.h"
#include "Branches.h"

namespace TLL {
    class MVABase : public ::MVABase {
        public:
            MVABase(const std::string&, const std::vector<std::string>&, const int rnk=1);

            virtual void FillVariables(Branches*, const int);
            virtual void FillCorrelationsVariables(Branches*, const int, const Process*, ::MVABase*);

        protected:
            virtual Branches* GetBranches(const Process*);
            virtual void SetupVariables(TMVA::Factory*);
            virtual void SetupVariables(TMVA::Reader*);
            virtual void SetupVariables(TTree*);
            virtual void SetupCorrelationsVariables(TTree*);
            template<typename T> void SetupVariablesT(T*);

            float csr;
            float HT;
            float TauPt;
            float TauEta;
            float TauDecayMode;
            float TauIsolationIndex;
            float TauIsolationIndexMVA2;
            float TauIsolationMVA2Raw;
            float TauLTPt;
            float TauNProngs;
            float DeltaRTauLepton1;
            float DeltaRTauLepton2;
            float DeltaRLepton1Lepton2;
            float DeltaRTauLeadingJet;
            float DeltaRTauSubleadingJet;
            float DeltaRLepton1LeadingJet;
            float DeltaRLepton1SubleadingJet;
            float DeltaRLepton2LeadingJet;
            float DeltaRLepton2SubleadingJet;
            float LeadingJetSubleadingJetMass;
            float LeadingJetPt;
            float SubLeadingJetPt;

			float Xsec;
			unsigned int nGen;
			float weight;
			float topPtWgt;
			float lep1TotalSF;
			float lep2TotalSF;
			float triggerSF;
			float csvWgtlf;
			float csvWgthf;
            float MVAoutput;
    };
}

#endif
