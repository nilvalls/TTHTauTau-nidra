#!/bin/bash

# Make sure we have a valid root file to read
input="$1"
if [ -z "$input" ]; then echo "ERROR: no input file provided."; exit 1; fi
if [ ! -e "$input" ]; then echo "ERROR: Could not read input file '$input'."; exit 1; fi

src="$2"
interface="$3"
if [ -z "$src" ]; then src="../../src/"; fi
if [ -z "$interface" ]; then interface="../../interface/"; fi

if [ ! -e "$src" ]; then echo "ERROR: src directory '$src' does not exist."; exit 1; fi
if [ ! -e "$interface" ]; then echo "ERROR: interface directory '$interface' does not exist."; exit 1; fi


function getFile(){
	branch="$1"
	file=`grep "\"$branch\"" "$src/"*.cc | cut -d: -f1 | sed 's/\/\+/\//g'`
	if [ -z "$file" ]; then
		echo "WARNING: branch '$branch' could not be found in source code. Please check code." >&2; 
		kill -SIGPIPE $$
	else
		file="${file##*\/}"
		file="${file%.cc}"
	fi
	echo $file
}

function getType(){
	branch="$1"
	file=`getFile "$branch"`
	if [ ! -z "$file" ]; then
		var=`grep "\"$branch\"" "$src$file.cc" | sed 's/.*&\(.*\)).*/\1/g'`
		grep "$var;" "$interface$file.h" | sed -e "s/$var.*//g" -e "s/^\s\+//g" -e "s/\s\+$//g"
	fi
}

function declaring(){
	while read branch; do 
		typeOfBranch=`getType "$branch"`
		vector=`echo $typeOfBranch | grep "vector<"`
		if [ ! -z "$vector" ]; then
			echo "	$typeOfBranch* $branch;"
		else
			echo "	$typeOfBranch $branch;"
		fi
	done < "$branches"
}

function nulling(){
	while read branch; do 
		vector=`getType "$branch" | grep "vector<"`
		if [ ! -z "$vector" ]; then
			echo "	$branch = NULL;"	
		else
			echo "	$branch = 0;"	
		fi
	done < "$branches"
}

function deleting(){
	while read branch; do 
		vector=`getType "$branch" | grep "vector<"`
		if [ ! -z "$vector" ]; then
			echo "	delete $branch;"	
		fi
	done < "$branches"
}

function clearing(){
	while read branch; do 
		vector=`getType "$branch" | grep "vector<"`
		if [ ! -z "$vector" ]; then
			echo "	$branch->clear();"	
		else
			echo "	$branch = 0;"	
		fi
	done < "$branches"
}

function addressing(){
	while read branch; do 
		echo "	fChain->SetBranchAddress(\"$branch\", &$branch);"
	done < "$branches"
}

# Get list of branches
tree="makeNtuple/TTbarHTauTau"
#tree="makeNtuple/tree"
macro="{ TFile *_file0 = TFile::Open(\"$input\");  TTree* tree = (TTree*)_file0->Get(\"$tree\"); tree->Print(); }"
tempMacro=".tempMacro.C"
branches=".branches"
echo "$macro" > "$tempMacro"
echo "Wrote temp macro... executing it to get list of branches..."
root -l -b -q "$tempMacro" | grep "*Br" | awk '{print $3}' | sed 's/://g' &> "$branches"
echo "Got list of branches."
rm -f "$tempMacro"

# Write stuff to the appropriate files
if [ "$2" == "-b" ]; then
	declaring
else
	echo "Preparing declarations..."
	declaring > "Branches_declarations.h"
	echo "done."

	echo "Preparing branch addressing..."
	addressing > "Branches_setBranchAddress.h"
	echo "done."

	echo "Preparing pointer deletion..."
	deleting > "Branches_delete.h"
	echo "done."

	echo "Preparing pointer nulling..."
	nulling > "Branches_null.h"
	echo "done."

	echo "Preparing variable nulling..."
	clearing > "Branches_clear.h"
	echo "done."
fi


# Clean up
rm -f "$branches"


