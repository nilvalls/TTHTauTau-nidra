ROOTCFLAGS    = $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS      = $(shell $(ROOTSYS)/bin/root-config --libs)
ROOTGLIBS     = $(shell $(ROOTSYS)/bin/root-config --glibs)
MYINC         = ./
MYLIBS        = ./

#######################################
# -- DEFINE ARCH to something sensible!
#######################################

#
CXX           = g++
#CXXFLAGS      = -g -Wall -fPIC
CXXFLAGS      = -g -fPIC
LD            = g++
LDFLAGS       = -g
SOFLAGS       = -shared


#CXXFLAGS      += $(ROOTCFLAGS) -I$(MYINC2) -I.
CXXFLAGS      += $(ROOTCFLAGS) -I$(MYINC)
#CXXFLAGS	  += -I$(CMSSW_BASE)/src/ -I$(CMSSW_RELEASE_BASE)/src/
LIBS           = $(ROOTLIBS) 

NGLIBS         = $(ROOTGLIBS) -lMinuit
NGLIBS		  += -L./ -lNidra
NGLIBS		  += -L./configParser/ -lconfigParser
NGLIBS		  += -lTMVA
#NGLIBS		  += -L$(shell $(CMSSW_BASE))/lib/slc5_amd64_gcc462/ -lNtupleMakerBEANmaker

GLIBS          = $(filter-out -lNew, $(NGLIBS))


.nidra.exe: .Driver.o linkdefs.h libNidra.so libConfigParser.so \
			.HWrapper.o .HContainer.o .HMath.o .CutFlow.o \
			.Process.o .PContainer.o .ProPack.o \
			.Branches.o .Analyzer.o .Plotter.o \
			.TTMBranches.o .TTMAnalyzer.o .TTMPlotter.o \
			.TTEBranches.o .TTEAnalyzer.o .TTEPlotter.o \
			.DILBranches.o .DILAnalyzer.o .DILPlotter.o \
			.Combiner.o \
			.Stacker.o .Stamper.o .Optimizer.o \
			.Trigger.o .Cruncher.o \
			.RootFileMaker.o .RawHistoSaver.o
			$(LD) $(LDFLAGS) -o .nidra.exe .Driver.o libNidra.so configParser/libconfigParser.so \
			.HWrapper.o .HContainer.o .HMath.o .CutFlow.o .Process.o .PContainer.o .ProPack.o \
			.Branches.o .Analyzer.o .Plotter.o \
			.TTMBranches.o .TTMAnalyzer.o .TTMPlotter.o \
			.TTEBranches.o .TTEAnalyzer.o .TTEPlotter.o \
			.DILBranches.o .DILAnalyzer.o .DILPlotter.o \
			.Combiner.o \
			.Stacker.o .Stamper.o .Optimizer.o \
			.Trigger.o .Cruncher.o \
			.RootFileMaker.o .RawHistoSaver.o $(GLIBS)

.NidraDict.cc: HWrapper.h HContainer.h PContainer.h CutFlow.h Process.h ProPack.h linkdefs.h
	rootcint -f $@ -c $(CXXFLAGS) -p $^

libNidra.so: .NidraDict.cc 
	g++ -shared -o$@ `root-config --ldflags` $(CXXFLAGS) -I$(ROOTSYS)/include $^ 

libConfigParser.so: configParser/config.h
	cd configParser && make && cd -	

.HWrapper.o: HWrapper.cc HWrapper.h 
	$(CXX) $(CXXFLAGS) -c HWrapper.cc -o $@

.HContainer.o: HContainer.cc HContainer.h 
	$(CXX) $(CXXFLAGS) -c HContainer.cc -o $@

.PContainer.o: PContainer.cc PContainer.h 
	$(CXX) $(CXXFLAGS) -c PContainer.cc -o $@

.CutFlow.o: CutFlow.cc CutFlow.h
	$(CXX) $(CXXFLAGS) -c CutFlow.cc -o $@

.Process.o: Process.cc Process.h 
	$(CXX) $(CXXFLAGS) -c Process.cc -o $@

.Branches.o: Branches.cc Branches.h
	$(CXX) $(CXXFLAGS) -c Branches.cc -o $@

.ProPack.o: ProPack.cc ProPack.h 
	$(CXX) $(CXXFLAGS) -c ProPack.cc -o $@

.Analyzer.o: Analyzer.cc Analyzer.h
	$(CXX) $(CXXFLAGS) -c Analyzer.cc -o  $@

.RootFileMaker.o: RootFileMaker.cc RootFileMaker.h 
	$(CXX) $(CXXFLAGS) -c RootFileMaker.cc -o $@

.RawHistoSaver.o: RawHistoSaver.cc RawHistoSaver.h
	$(CXX) $(CXXFLAGS) -c RawHistoSaver.cc -o $@

.Trigger.o: Trigger.cc Trigger.h
	$(CXX) $(CXXFLAGS) -c Trigger.cc -o $@

.Plotter.o: Plotter.cc Plotter.h
	$(CXX) $(CXXFLAGS) -c Plotter.cc -o $@

.Combiner.o: Combiner.cc Combiner.h 
	$(CXX) $(CXXFLAGS) -c Combiner.cc -o $@

.Stacker.o: Stacker.cc Stacker.h
	$(CXX) $(CXXFLAGS) -c Stacker.cc -o $@

.Stamper.o: Stamper.cc Stamper.h
	$(CXX) $(CXXFLAGS) -c Stamper.cc -o $@

.Optimizer.o: Optimizer.cc Optimizer.h 
	$(CXX) $(CXXFLAGS) -c Optimizer.cc -o $@

.HMath.o: HMath.cc HMath.h 
	$(CXX) $(CXXFLAGS) -c HMath.cc -o $@

.Cruncher.o: Cruncher.cc Cruncher.h
	$(CXX) $(CXXFLAGS) -c Cruncher.cc -o $@

.Driver.o: Driver.cc Driver.h Nidra.cc style-CMSTDR.h
	$(CXX) $(CXXFLAGS) -c Nidra.cc -o $@

#.TMVASampler.o: TMVASampler.cc TMVASampler.h
#	$(CXX) $(CXXFLAGS) -c TMVASampler.cc -o $@
#
#.TMVAEvaluator.o: TMVAEvaluator.cc TMVAEvaluator.h
#	$(CXX) $(CXXFLAGS) -c TMVAEvaluator.cc -o $@

########################
### Channel-specific ###
########################

### TTM
.TTMBranches.o: TTM/Branches.cc TTM/Branches.h TTM/Branches_*.h
	$(CXX) $(CXXFLAGS) -c TTM/Branches.cc -o $@

.TTMAnalyzer.o: TTM/Analyzer.cc TTM/Analyzer.h TTM/Branches_*.h TTM/Cuts_*.h TTM/GenHelper.h Analyzer.cc Analyzer.h
	$(CXX) $(CXXFLAGS) -c TTM/Analyzer.cc -o  $@

.TTMPlotter.o: TTM/Plotter.cc TTM/Plotter.h TTM/FillHistos.h TTM/Branches_*.h
	$(CXX) $(CXXFLAGS) -c TTM/Plotter.cc -o $@

### TTE
.TTEBranches.o: TTE/Branches.cc TTE/Branches.h TTE/Branches_*.h
	$(CXX) $(CXXFLAGS) -c TTE/Branches.cc -o $@

.TTEAnalyzer.o: TTE/Analyzer.cc TTE/Analyzer.h TTE/Branches_*.h TTE/Cuts_*.h TTE/GenHelper.h Analyzer.cc Analyzer.h
	$(CXX) $(CXXFLAGS) -c TTE/Analyzer.cc -o  $@

.TTEPlotter.o: TTE/Plotter.cc TTE/Plotter.h TTE/FillHistos.h TTE/Branches_*.h
	$(CXX) $(CXXFLAGS) -c TTE/Plotter.cc -o $@

### DIL
.DILBranches.o: DIL/Branches.cc DIL/Branches.h DIL/Branches_*.h
	$(CXX) $(CXXFLAGS) -c DIL/Branches.cc -o $@

.DILAnalyzer.o: DIL/Analyzer.cc DIL/Analyzer.h DIL/Branches_*.h DIL/Cuts_*.h DIL/GenHelper.h Analyzer.cc Analyzer.h
	$(CXX) $(CXXFLAGS) -c DIL/Analyzer.cc -o  $@

.DILPlotter.o: DIL/Plotter.cc DIL/Plotter.h DIL/FillHistos.h DIL/Branches_*.h
	$(CXX) $(CXXFLAGS) -c DIL/Plotter.cc -o $@


########################
###      Global      ###
########################

all: .nidra.exe

cleanDicts:
	rm -f .*Dict.cc && rm -f *.so

clean: 
	rm -rf .*.o && rm -f .nidra.exe && make cleanDicts

make ca:
	make clean && make all

