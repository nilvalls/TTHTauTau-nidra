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
NGLIBS		  += -lTMVA

GLIBS          = $(filter-out -lNew, $(NGLIBS))


.nidra.exe: .Driver.o linkdefs.h libNidra.so libConfigParser.so \
			.HWrapper.o .HContainer.o .HMath.o .CutFlow.o .DitauBranches.o .Process.o .PContainer.o .ProPack.o \
			.Analyzer.o .Trigger.o .PUcorrector.o .Cruncher.o .Plotter.o .Stacker.o .Stamper.o .Optimizer.o \
			.RootFileMaker.o .RawHistoSaver.o .TMVASampler.o .TMVAEvaluator.o
			$(LD) $(LDFLAGS) -o .nidra.exe .Driver.o libNidra.so configParser/libconfigParser.so \
			.HWrapper.o .HContainer.o .HMath.o .CutFlow.o .DitauBranches.o .Process.o .PContainer.o .ProPack.o \
			.Analyzer.o .Trigger.o .PUcorrector.o .Cruncher.o .Plotter.o .Stacker.o .Stamper.o .Optimizer.o \
			.RootFileMaker.o .RawHistoSaver.o .TMVASampler.o .TMVAEvaluator.o $(GLIBS)

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

.PUcorrector.o: PUcorrector.cc PUcorrector.h 
	$(CXX) $(CXXFLAGS) -c PUcorrector.cc -o $@

.CutFlow.o: CutFlow.cc CutFlow.h
	$(CXX) $(CXXFLAGS) -c CutFlow.cc -o $@

.Process.o: Process.cc Process.h 
	$(CXX) $(CXXFLAGS) -c Process.cc -o $@

.DitauBranches.o: DitauBranches.cc DitauBranches.h clarity/ditauBranches_*
	$(CXX) $(CXXFLAGS) -c DitauBranches.cc -o $@

.ProPack.o: ProPack.cc ProPack.h 
	$(CXX) $(CXXFLAGS) -c ProPack.cc -o $@

.Analyzer.o: Analyzer.cc Analyzer.h clarity/*.h PUcorrector.h
	$(CXX) $(CXXFLAGS) -c Analyzer.cc -o  $@

.RootFileMaker.o: RootFileMaker.cc RootFileMaker.h 
	$(CXX) $(CXXFLAGS) -c RootFileMaker.cc -o $@

.RawHistoSaver.o: RawHistoSaver.cc RawHistoSaver.h
	$(CXX) $(CXXFLAGS) -c RawHistoSaver.cc -o $@

.Trigger.o: Trigger.cc Trigger.h
	$(CXX) $(CXXFLAGS) -c Trigger.cc -o $@

.Plotter.o: Plotter.cc Plotter.h clarity/fillHistos.h
	$(CXX) $(CXXFLAGS) -c Plotter.cc -o $@

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

.TMVASampler.o: TMVASampler.cc TMVASampler.h
	$(CXX) $(CXXFLAGS) -c TMVASampler.cc -o $@

.TMVAEvaluator.o: TMVAEvaluator.cc TMVAEvaluator.h
	$(CXX) $(CXXFLAGS) -c TMVAEvaluator.cc -o $@

all: .nidra.exe

cleanDicts:
	rm -f .*Dict.cc && rm -f *.so

clean: 
	rm -rf .*.o && rm -f .nidra.exe && make cleanDicts

make ca:
	make clean && make all

