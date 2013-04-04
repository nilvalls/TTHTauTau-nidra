
#ifndef TemplateContainer_h
#define TemplateContainer_h

#include <string>
#include <map>
#include "ProPack.h"
#include "HWrapper.h"
#include "TFile.h"

class TemplateContainer {

    public:
    
    TemplateContainer();
    TemplateContainer(std::map<std::string,std::string> const & );
    virtual ~TemplateContainer();
    float GetRelativeError(std::string, int, float);
    float GetAbsoluteError(std::string, int, float);

    private: 
    
    struct Shift {
        std::string name;
        TFile* file;
        ProPack* proPack;
    };
    
    std::map<std::string,std::string>	params;
    std::vector<Shift> shifts;
    HWrapper GetSumOfBackgroundTemplates(std::string, ProPack*);
    

};

#endif










