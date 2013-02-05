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


function echoErr {     echo -e $RED"[  ERROR  ]  $1$NOCOLOR"; exit 1; }
function echoWar {  echo -e $PURPLE"[ WARNING ]  $1$NOCOLOR"; }
function echoInf {    echo -e $BLUE"[  INFO   ]  $1$NOCOLOR"; }
function echoSuc {   echo -e $GREEN"[ SUCCESS ]  $1$NOCOLOR"; }

execFile=".nidra.exe"

config="$PWD/$1"
options="$*"
options="${options##$1} "

# Check that an input config file is passed and exists
if [ -z "$1" ]; then echoErr "Must provide a configuration file";
elif [ ! -e "$config" ]; then echoErr "Config file '$config' invalid";
elif [ -z "$2" ]; then echoErr "Must provide options";
fi

cd $(dirname $0)

function hasArgument(){
	arg=" -$1 "
	case "$options" in
		*$arg*) return 0;;
		*) return -1;;
	esac
}

function isOnlyArgument(){
	arg=" -$1 "
	case "$options" in
		*$arg) return 0;;
		*) return -1;;
	esac
}

if hasArgument "c"; then 
		echoInf "Cleaning nidra..."
		make clean &> /dev/null
		if [ $? -eq 0 ]; then echoSuc "done!"; fi
fi

if hasArgument "r"; then 
		echoInf "Compiling nidra..."
		make all
		if [ $? -ne 0 ]; then echoErr "Error while compiling nidra"; exit 1; fi
fi



# Set up paths to configParser library
LDLIBS=$(pwd):$(pwd)/configParser/
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$LDLIBS
export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:$LDLIBS

function checkExe(){
	# Check that $execFile exists and is accessible, otherwise try to compile it
	if [ ! -e "$execFile" ]; then
		echoWar "$execFile not found. Attempting to compile it."
			make $execFile
			exit_status=$?
		if [ $exit_status -ne 0 ]; then
			echoErr "Compilation of $execFile failed."
			exit 1;
		else
			echoSuc "$execFile compiled!"
		fi
	fi
}

if hasArgument "m"; then make all; fi

if hasArgument "f"; then 
	checkExe;
	./$execFile $config -a && ./$execFile $config -p -k
else
	checkExe;
	./$execFile $config $options
fi


# Notify of analysis end
echoSuc " Analysis finished!"
echo ""




