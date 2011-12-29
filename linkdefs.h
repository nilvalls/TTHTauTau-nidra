#include "HWrapper.h"
#include "HContainer.h"
#include "PContainer.h"
#include "CutFlow.h"
#include "Process.h"
#include "ProPack.h"

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all structs;
#pragma link off all functions;

#pragma link C++ class HWrapper+;
#pragma link C++ class HContainer+;
#pragma link C++ class PContainer+;
#pragma link C++ class std::map<std::string, HWrapper>+;
#pragma link C++ class CutFlow+;
#pragma link C++ class Process+;
#pragma link C++ class ProPack+;



//#pragma read source="runNumber" sourceClass="DitauBranches" target="runNumber" targetClass="DitauBranches" attributes="Owner";

//*/
#endif
