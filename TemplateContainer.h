#ifndef TemplateContainer_h
#define TemplateContainer_h

#include <map>
#include <string>

#include "TFile.h"
#include "TH1.h"

#include "ProPack.h"

class TemplateContainer {
    public:
        TemplateContainer();
        TemplateContainer(std::map<std::string,std::string> const & );
        virtual ~TemplateContainer();
        float GetAbsoluteError(std::string s, int i, float f, bool up = true);
        float GetAbsoluteErrorUp(std::string, int, float);
        float GetAbsoluteErrorDown(std::string, int, float);

    private:
        struct Shift {
            std::map<std::string,TH1*> bgSumsUp;
            std::map<std::string,TH1*> bgSumsDown;
        };

        std::map<std::string,std::string> params;
        std::map<std::string,Shift> shifts;

        TFile* storageFile;
        TH1* GetSumOfBackgroundTemplates(std::string, ProPack*);
};

#endif
