#!/bin/bash

## Nil Valls <nil.valls@cern.ch>
## 7 Jun 2011
## Helper script to run the TauTau analysis plotter

RED="\033[0;31m"
GRAY="\033[0;30m"
BLUE="\033[0;34m"
ORANGE="\033[0;33m"
PURPLE="\033[0;35m"
GREEN="\033[0;32m"
WHITE="\033[1;37m"
NOCOLOR="\e[0m"


function echoErr { 
	echo -e "$RED$1$NOCOLOR" 
}
function echoWar { 
	echo -e "$PURPLE$1$NOCOLOR"
}
function echoInf { 
	echo -e "$BLUE$1$NOCOLOR"
}
function echoSuc { 
	echo -e "$GREEN$1$NOCOLOR"
}

execFile=".nidra.exe"
allArgs="$*"

# Check that an input config file is passed and exits
if [ "$1" == "-r" ] || [ "$2" == "-r" ] || [ "$1" == "-c" ] || [ "$2" == "-c" ]; then

	if [ "$1" == "-r" ] || [ "$1" == "-c" ]; then
		iConfig="$2"; iOption="$1";
	elif [ "$2" == "-r" ] || [ "$2" == "-c" ]; then
		iConfig="$1"; iOption="$2";
	fi
	
	if [ "$iOption" == "-c" ]; then
		echoInf "Cleaning nidra..."
		make clean &> /dev/null
		if [ $? -eq 0 ]; then echoSuc "done!"; fi
	fi

	if [ "$iOption" == "-r" ] || [ "$iOption" == "-c" ]; then
		echoInf "Compiling nidra..."
		make all
		if [ $? -ne 0 ]; then echoErr "Error while compiling nidra"; exit 1; fi
	fi

else
	iConfig="$1"
fi

##iConfig="cfg/generic.cfg"

if [ -z "$iConfig" ]; then
	echoErr "ERROR: must provide a config file as argument."
	exit 1;
elif [ ! -e "$iConfig" ]; then
	echoErr "ERROR: file $iConfig does not exist or cannot be opened."
	exit 1;
fi

# CMS environment
#if [ -z "$CMSSW_BASE" ] || [ "$TERM" == "screen" ]; then
#	currentDir="$(pwd)"
#	cmsDir=${currentDir%%src/*}"src/"
#	cd $cmsDir;
#	eval `scramv1 runtime -sh`;
#	cd - &> /dev/null;
#fi

# Set up paths to configParser library
LDLIBS=$(pwd):$(pwd)/configParser/
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$LDLIBS
export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:$LDLIBS

# Check that $execFile exists and is accessible, otherwise try to compile it
if [ ! -e "$execFile" ]; then
	echoWar "WARNING: $execFile not found. Attempting to compile it."
		make $execFile
		exit_status=$?
	if [ $exit_status -ne 0 ]; then
		echoErr "ERROR: Compilation of $execFile failed."
		exit 1;
	else
		echoSuc "SUCCESS: $execFile compiled!"
	fi
fi

if [ "$1" == "-m" ]; then
	make all
fi

# If all the above check, run the plotter
echoInf "Running $execFile with config file $iConfig..."
./$execFile $iConfig $allArgs
#./$execFile $allArgs

# Notify of analysis end
echoSuc " Analysis finished!"
echo ""




