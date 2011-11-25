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
LIBS           = $(ROOTLIBS) 

NGLIBS         = $(ROOTGLIBS) -lMinuit
NGLIBS		  += -L./ -lNidra
NGLIBS		  += -L./configParser/ -lconfigParser

GLIBS          = $(filter-out -lNew, $(NGLIBS))


.nidra.exe: linkdefs.h libNidra.so libConfigParser.so \
			.HistoWrapper.o .Topology.o .TopoPack.o .Driver.o .RootFileMaker.o \
			.Analyzer.o .Trigger.o .CutFlow.o .Stacker.o .Plotter.o
			$(LD) $(LDFLAGS) -o .nidra.exe libNidra.so configParser/libconfigParser.so \
			.HistoWrapper.o .Topology.o .TopoPack.o .Driver.o .RootFileMaker.o \
			.Analyzer.o .Trigger.o .CutFlow.o .Plotter.o .Stacker.o $(GLIBS)

.NidraDict.cc: HistoWrapper.h Topology.h TopoPack.h linkdefs.h
	rootcint -f $@ -c $(CXXFLAGS) -p $^

libNidra.so: .NidraDict.cc 
	g++ -shared -o$@ `root-config --ldflags` $(CXXFLAGS) -I$(ROOTSYS)/include $^ 

libConfigParser.so: configParser/config.h
	cd configParser && make && cd -	

.HistoWrapper.o: HistoWrapper.cc HistoWrapper.h 
	$(CXX) $(CXXFLAGS) -c HistoWrapper.cc -o $@

.Topology.o: Topology.cc Topology.h 
	$(CXX) $(CXXFLAGS) -c Topology.cc -o $@

.TopoPack.o: TopoPack.cc TopoPack.h 
	$(CXX) $(CXXFLAGS) -c TopoPack.cc -o $@

.RootFileMaker.o: RootFileMaker.cc RootFileMaker.h 
	$(CXX) $(CXXFLAGS) -c RootFileMaker.cc -o $@

.Analyzer.o: Analyzer.cc Analyzer.h clarity/*.h PUcorrector.h
	$(CXX) $(CXXFLAGS) -c Analyzer.cc -o  $@

.Trigger.o: Trigger.cc Trigger.h
	$(CXX) $(CXXFLAGS) -c Trigger.cc -o $@

.CutFlow.o: CutFlow.cc CutFlow.h
	$(CXX) $(CXXFLAGS) -c CutFlow.cc -o $@

.Plotter.o: Plotter.cc Plotter.h
	$(CXX) $(CXXFLAGS) -c Plotter.cc -o $@

.Stacker.o: Stacker.cc Stacker.h
	$(CXX) $(CXXFLAGS) -c Stacker.cc -o $@

.Driver.o: Driver.cc Driver.h Nidra.cc style-CMSTDR.h
	$(CXX) $(CXXFLAGS) -c Nidra.cc -o $@

.CommonDefs.o: CommonDefs.cc
	$(CXX) $(CXXFLAGS) -c CommonDefs.cc -o CommonDefs.o

all: .nidra.exe libNidra.so libConfigParser.so .CommonDefs.o \
	.HistoWrapper.o .Topology.o .TopoPack.o .Driver.o .RootFileMaker.o \
	.Analyzer.o .Trigger.o .CutFlow.o .Stacker.o .Plotter.o


clean: 
	rm -rf .*.o && rm -f *.so && rm -f .nidra.exe

make ca:
	make clean && make all

