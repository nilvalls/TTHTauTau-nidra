#!/bin/bash

LDLIBS=$(pwd):$(pwd)/configParser/
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$LDLIBS
export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:$LDLIBS

exec ./.nidra.exe $@
