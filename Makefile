ROOTCFLAGS    = $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS      = $(shell $(ROOTSYS)/bin/root-config --libs)
ROOTGLIBS     = $(shell $(ROOTSYS)/bin/root-config --glibs)

#######################################
# -- DEFINE ARCH to something sensible!
#######################################

CXXFLAGS      = -g -fPIC
LDFLAGS       = -g -lboost_filesystem
LD = $(CXX)


CXXFLAGS      += $(ROOTCFLAGS) -I.
LIBS           = $(ROOTLIBS) 

NGLIBS         = $(ROOTGLIBS) -lMinuit
NGLIBS		  += -L./ -lNidra
NGLIBS		  += -L./configParser/ -lconfigParser
NGLIBS		  += -lTMVA

GLIBS          = $(filter-out -lNew, $(NGLIBS))

NOBJS= .Driver.o libNidra.so configParser/libconfigParser.so \
		.HWrapper.o .HContainer.o .HMath.o .Helper.o .CutFlow.o \
		.Process.o .PContainer.o .ProPack.o \
		.Branches.o .Analyzer.o .Plotter.o \
		.TMVASampler.o \
		.TTLBranches.o .TTLAnalyzer.o .TTLPlotter.o .TTL_TMVASampler.o .TTL_TMVAEvaluator.o .TTL_ComboSelectorSampler.o .TTL_ComboSelector.o\
		.Combiner.o \
		.Stacker.o .Stamper.o .Optimizer.o \
		.Trigger.o .Cruncher.o \
		.RootFileMaker.o .RawHistoSaver.o \
		.TemplateContainer.o

.%.o: %.cc %.h
	$(CXX) -std=c++0x $(CXXFLAGS) -c $*.cc -o $@

all: .nidra.exe

.nidra.exe: $(NOBJS) linkdefs.h 
	$(LD) $(LDFLAGS) -o $@ $(GLIBS) $(NOBJS)

.NidraDict.cc: HWrapper.h HContainer.h PContainer.h CutFlow.h Process.h ProPack.h Helper.h TemplateContainer.h linkdefs.h
	rootcint -f $@ -c $(CXXFLAGS) -p $^

libNidra.so: .NidraDict.cc 
	g++ -shared -o$@ `root-config --ldflags` $(CXXFLAGS) -I$(ROOTSYS)/include $^ 

configParser/libconfigParser.so: configParser/config.h
	cd configParser && make && cd -	

.Driver.o: Driver.cc Driver.h Nidra.cc style-CMSTDR.h
	$(CXX) -std=c++0x $(CXXFLAGS) -c Nidra.cc -o $@

########################
### Channel-specific ###
########################

### TTL
.TTLBranches.o: TTL/Branches.cc TTL/Branches.h TTL/Branches_*.h Helper.h
	$(CXX) $(CXXFLAGS) -c TTL/Branches.cc -o $@

.TTLAnalyzer.o: TTL/Analyzer.cc TTL/Analyzer.h TTL/Branches_*.h TTL/Cuts_*.h Analyzer.cc Analyzer.h Helper.h
	$(CXX) $(CXXFLAGS) -c TTL/Analyzer.cc -o  $@

.TTLPlotter.o: TTL/Plotter.cc TTL/Plotter.h TTL/FillHistos.h TTL/Branches_*.h Helper.h
	$(CXX) $(CXXFLAGS) -c TTL/Plotter.cc -o $@

.TTL_TMVASampler.o: TTL/TMVASampler.cc TTL/TMVASampler.h TTL/Branches_*.h Helper.h
	$(CXX) -std=c++0x $(CXXFLAGS) -c TTL/TMVASampler.cc -o $@

.TTL_TMVAEvaluator.o: TTL/TMVAEvaluator.cc TTL/TMVAEvaluator.h TTL/Branches_*.h Helper.h
	$(CXX) -std=c++0x $(CXXFLAGS) -c TTL/TMVAEvaluator.cc -o $@

.TTL_ComboSelectorSampler.o: TTL/ComboSelectorSampler.cc TTL/ComboSelectorSampler.h TTL/Branches_*.h Helper.h
	$(CXX) -std=c++0x $(CXXFLAGS) -c TTL/ComboSelectorSampler.cc -o $@

.TTL_ComboSelector.o: TTL/ComboSelector.cc TTL/ComboSelector.h TTL/Branches_*.h Helper.h
	$(CXX) -std=c++0x $(CXXFLAGS) -c TTL/ComboSelector.cc -o $@

########################
###      Global      ###
########################

cleanDicts:
	rm -f .*Dict.cc && rm -f *.so

clean: 
	rm -rf .*.o && rm -f .nidra.exe && make cleanDicts

make ca:
	make clean && make all

