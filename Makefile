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
		.TTMBranches.o .TTMAnalyzer.o .TTMPlotter.o .TTM_TMVASampler.o .TTM_TMVAEvaluator.o \
		.TTEBranches.o .TTEAnalyzer.o .TTEPlotter.o .TTE_TMVASampler.o .TTE_TMVAEvaluator.o \
		.TTLBranches.o .TTLAnalyzer.o .TTLPlotter.o .TTL_TMVASampler.o .TTL_TMVAEvaluator.o \
		.Combiner.o \
		.Stacker.o .Stamper.o .Optimizer.o \
		.Trigger.o .Cruncher.o \
		.RootFileMaker.o .RawHistoSaver.o

.%.o: %.cc %.h
	$(CXX) -std=c++0x $(CXXFLAGS) -c $*.cc -o $@

all: .nidra.exe

.nidra.exe: $(NOBJS) linkdefs.h 
	$(LD) $(LDFLAGS) -o $@ $(GLIBS) $(NOBJS)

.NidraDict.cc: HWrapper.h HContainer.h PContainer.h CutFlow.h Process.h ProPack.h Helper.h linkdefs.h
	rootcint -f $@ -c $(CXXFLAGS) -p $^

libNidra.so: .NidraDict.cc 
	g++ -shared -o$@ `root-config --ldflags` $(CXXFLAGS) -I$(ROOTSYS)/include $^ 

configParser/libconfigParser.so: configParser/config.h
	cd configParser && make && cd -	

.Driver.o: Driver.cc Driver.h Nidra.cc style-CMSTDR.h
	$(CXX) $(CXXFLAGS) -c Nidra.cc -o $@

########################
### Channel-specific ###
########################

### TTM
.TTMBranches.o: TTM/Branches.cc TTM/Branches.h TTM/Branches_*.h Helper.h
	$(CXX) $(CXXFLAGS) -c TTM/Branches.cc -o $@

.TTMAnalyzer.o: TTM/Analyzer.cc TTM/Analyzer.h TTM/Branches_*.h TTM/Cuts_*.h Analyzer.cc Analyzer.h Helper.h
	$(CXX) $(CXXFLAGS) -c TTM/Analyzer.cc -o  $@

.TTMPlotter.o: TTM/Plotter.cc TTM/Plotter.h TTM/FillHistos.h TTM/Branches_*.h Helper.h
	$(CXX) $(CXXFLAGS) -c TTM/Plotter.cc -o $@

.TTM_TMVASampler.o: TTM/TMVASampler.cc TTM/TMVASampler.h TTM/Branches_*.h Helper.h
	$(CXX) $(CXXFLAGS) -c TTM/TMVASampler.cc -o $@

.TTM_TMVAEvaluator.o: TTM/TMVAEvaluator.cc TTM/TMVAEvaluator.h TTM/Branches_*.h Helper.h
	$(CXX) $(CXXFLAGS) -c TTM/TMVAEvaluator.cc -o $@

### TTE
.TTEBranches.o: TTE/Branches.cc TTE/Branches.h TTE/Branches_*.h Helper.h
	$(CXX) $(CXXFLAGS) -c TTE/Branches.cc -o $@

.TTEAnalyzer.o: TTE/Analyzer.cc TTE/Analyzer.h TTE/Branches_*.h TTE/Cuts_*.h Analyzer.cc Analyzer.h Helper.h
	$(CXX) $(CXXFLAGS) -c TTE/Analyzer.cc -o  $@

.TTEPlotter.o: TTE/Plotter.cc TTE/Plotter.h TTE/FillHistos.h TTE/Branches_*.h Helper.h
	$(CXX) $(CXXFLAGS) -c TTE/Plotter.cc -o $@

.TTE_TMVASampler.o: TTE/TMVASampler.cc TTE/TMVASampler.h TTE/Branches_*.h Helper.h
	$(CXX) $(CXXFLAGS) -c TTE/TMVASampler.cc -o $@

.TTE_TMVAEvaluator.o: TTE/TMVAEvaluator.cc TTE/TMVAEvaluator.h TTE/Branches_*.h Helper.h
	$(CXX) $(CXXFLAGS) -c TTE/TMVAEvaluator.cc -o $@

### TTL
.TTLBranches.o: TTL/Branches.cc TTL/Branches.h TTL/Branches_*.h Helper.h
	$(CXX) $(CXXFLAGS) -c TTL/Branches.cc -o $@

.TTLAnalyzer.o: TTL/Analyzer.cc TTL/Analyzer.h TTL/Branches_*.h TTL/Cuts_*.h Analyzer.cc Analyzer.h Helper.h
	$(CXX) $(CXXFLAGS) -c TTL/Analyzer.cc -o  $@

.TTLPlotter.o: TTL/Plotter.cc TTL/Plotter.h TTL/FillHistos.h TTL/Branches_*.h Helper.h
	$(CXX) $(CXXFLAGS) -c TTL/Plotter.cc -o $@

.TTL_TMVASampler.o: TTL/TMVASampler.cc TTL/TMVASampler.h TTL/Branches_*.h Helper.h
	$(CXX) $(CXXFLAGS) -c TTL/TMVASampler.cc -o $@

.TTL_TMVAEvaluator.o: TTL/TMVAEvaluator.cc TTL/TMVAEvaluator.h TTL/Branches_*.h Helper.h
	$(CXX) $(CXXFLAGS) -c TTL/TMVAEvaluator.cc -o $@


########################
###      Global      ###
########################

cleanDicts:
	rm -f .*Dict.cc && rm -f *.so

clean: 
	rm -rf .*.o && rm -f .nidra.exe && make cleanDicts

make ca:
	make clean && make all

