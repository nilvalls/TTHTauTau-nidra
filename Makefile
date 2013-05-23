ROOTCFLAGS    = $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS      = $(shell $(ROOTSYS)/bin/root-config --libs)
ROOTGLIBS     = $(shell $(ROOTSYS)/bin/root-config --glibs)

#######################################
# -- DEFINE ARCH to something sensible!
#######################################

#  CXXFLAGS      = -g -fPIC -std=c++0x -Wall -pedantic -pg
#  CXXFLAGS      = -g -fPIC -std=c++0x -Wall -pedantic
CXXFLAGS      = -O2 -fPIC -std=c++0x -Wall -pedantic
#  LDFLAGS       = -g -lboost_filesystem -pg
#  LDFLAGS       = -g -lboost_filesystem
LDFLAGS       = -O2 -lboost_filesystem
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
		.Branches.o .Plotter.o \
		.MVABase.o \
		.TTLBranches.o .TTLBranches_cuts.o .TTLPlotter.o .TTLMVABase.o \
		.Combiner.o \
		.Stacker.o .Stamper.o .Optimizer.o \
		.Trigger.o .Cruncher.o \
		.RootFileMaker.o .RawHistoSaver.o \
		.TemplateContainer.o

.%.o: %.cc %.h
	$(CXX) $(CXXFLAGS) -c $*.cc -o $@

all: .nidra.exe

.nidra.exe: $(NOBJS) linkdefs.h 
	$(LD) $(LDFLAGS) -o $@ $(GLIBS) $(NOBJS)

.NidraDict.cc: HWrapper.h HContainer.h PContainer.h CutFlow.h Process.h ProPack.h Helper.h TemplateContainer.h linkdefs.h
	rootcint -f $@ -c -g -fPIC -p $^

libNidra.so: .NidraDict.cc 
	g++ -shared -o$@ `root-config --ldflags` $(CXXFLAGS) -I$(ROOTSYS)/include $^ 

configParser/libconfigParser.so: configParser/config.h
	cd configParser && make && cd -	

.Driver.o: Driver.cc Driver.h Nidra.cc style-CMSTDR.h
	$(CXX) $(CXXFLAGS) -c Nidra.cc -o $@

########################
### Channel-specific ###
########################

### TTL
.TTLBranches.o: TTL/Branches.cc TTL/Branches.h TTL/Branches_*.h Helper.h
	$(CXX) $(CXXFLAGS) -c TTL/Branches.cc -o $@

.TTLBranches_cuts.o: TTL/Branches.cc TTL/Branches.h TTL/Branches_*.h Helper.h
	$(CXX) $(CXXFLAGS) -c TTL/Branches_cuts.cc -o $@

.TTLPlotter.o: TTL/Plotter.cc TTL/Plotter.h TTL/FillHistos.h TTL/Branches_*.h Helper.h
	$(CXX) $(CXXFLAGS) -c TTL/Plotter.cc -o $@

.TTLMVABase.o: TTL/MVABase.cc TTL/MVABase.h TTL/Branches_*.h Helper.h
	$(CXX) $(CXXFLAGS) -c TTL/MVABase.cc -o $@

########################
###      Global      ###
########################

cleanDicts:
	rm -f .*Dict.cc && rm -f *.so

clean:
	rm -rf .*.o && rm -f .nidra.exe && make cleanDicts

make ca:
	make clean && make all

