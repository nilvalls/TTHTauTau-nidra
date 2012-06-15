#!/bin/bash

# Make sure we have a valid root file to read
input="$1"
if [ -z "$input" ]; then echo "ERROR: no input file provided."; exit 1; fi
if [ ! -e "$input" ]; then echo "ERROR: Could not read input file '$input'."; exit 1; fi

src="../src/"
interface="../interface/"


function getFile(){
	branch="$1"
	file=`grep "\"$branch\"" "$src/"*.cc | cut -d: -f1 | sed 's/\/\+/\//g'`
	file="${file##*\/}"
	file="${file%.cc}"
	echo $file
}

function getType(){
	branch="$1"
	file=`getFile "$branch"`
	var=`grep "\"$branch\"" "$src$file.cc" | sed 's/.*&\(.*\)).*/\1/g'`
	grep "$var;" "$interface$file.h" | sed -e "s/$var.*//g" -e "s/^\s\+//g" -e "s/\s\+$//g"
}

function declaring(){
	while read branch; do 
		typeOfBranch=`getType "$branch"`
		echo "	$typeOfBranch $branch;"
	done < "$branches"
}

function clearing(){
	while read branch; do 
		vector=`getType "$branch" | grep "vector<"`
		if [ ! -z "$vector" ]; then
			echo "	$branch.clear();"	
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
macro="{ TFile *_file0 = TFile::Open(\"$input\");  TTree* tree = (TTree*)_file0->Get(\"$tree\"); tree->Print(); }"
tempMacro=".tempMacro.C"
branches=".branches"
echo "$macro" > "$tempMacro"
root -l -b -q "$tempMacro" | grep "*Br" | awk '{print $3}' | sed 's/://g' &> "$branches"
rm -f "$tempMacro"

# Write stuff to the appropriate files
echo "Preparing declarations..."
declaring > "clarity/ditauBranches_declarations.h"

echo "Preparing branch addressing..."
addressing > "clarity/ditauBranches_setBranchAddresses.h"

echo "Preparing variable clearing..."
clearing > "clarity/ditauBranches_clear.h"
echo "done."

# Clean up
rm -f "$branches"


