#######################################
# -- DEFINE ARCH to something sensible!
#######################################

#
CXX           = g++
CXXFLAGS      = -g -Wall -fPIC
LD            = g++
LDFLAGS       = -g
SOFLAGS       = -shared

libconfigParser: config.o log.o
	$(CXX) $(SOFLAGS) -o libconfigParser.so config.o log.o

config.o: config.cpp config.h
	$(CXX) $(CXXFLAGS) -c config.cpp

log.o: log.cpp log.h
	$(CXX) $(CXXFLAGS) -c log.cpp

all: config.o log.o libconfigParser

clean: 
	rm -rf *.o *.so

