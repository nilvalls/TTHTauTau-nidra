//#include "CutFlow.h"
#include "HistoWrapper.h"
#include "Topology.h"
#include "TopoPack.h"

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all structs;
#pragma link off all functions;

//#pragma link C++ class CutFlow+;
#pragma link C++ class HistoWrapper+;
#pragma link C++ class std::vector<HistoWrapper*>+;
#pragma link C++ class Topology+;
#pragma link C++ class TopoPack+;

#pragma read source="histosForSignal" sourceClass="Topology" target="histosForSignal" targetClass="Topology" attributes="Owner";
#pragma read source="histosForQCD" sourceClass="Topology" target="histosForQCD" targetClass="Topology" attributes="Owner";


#endif
