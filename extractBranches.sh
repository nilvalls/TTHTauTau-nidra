#!/bin/bash

verbose=false;
src="../../src/";
interface="../../interface/";
tree="makeNtuple/TTbarHTauTau"
#tree="makeNtuple/tree"

### Output files
bdeclarations="Branches_declarations.h"
bsetBranchAddress="Branches_setBranchAddress.h"
bdelete="Branches_delete.h"
bnull="Branches_null.h"
bclear="Branches_clear.h"



while getopts ":i:c:h:v" opt; do
	case $opt in
		c) 
			src="$OPTARG"
		;;
		h) 
			interface="$OPTARG"
		;;
		v) 
			verbose=true;
		;;
		i) 
			input="$OPTARG"
		;;
		\?)
			echo "Invalid option: -$OPTARG" >&2
			exit 1
		;;
		:)
			echo "Option -$OPTARG requires an argument." >&2
			exit 1
		;;
	esac
done


#########################################################################################################################

### Terminate execution
function terminate(){
	echo "\n[ERROR]    $1" >&2
	echo "Terminating." >&2
	kill -s 2 $$;
}


# Make sure we have a valid paths
if [ -z "$input" ]; then terminate "No input file provided."; fi
if [ ! -e "$input" ]; then terminate "Could not read input file '$input'."; fi
if [ ! -e "$src" ]; then terminate "src directory '$src' does not exist."; fi
if [ ! -e "$interface" ]; then terminate "interface directory '$interface' does not exist."; fi


### Check if branch name in source code
function branchNotInSource(){
	branch="$1"
	there=`grep "\"$branch\"" "$src/"*.cc | cut -d: -f1 | sed 's/\/\+/\//g'`
	if [ -z "$there" ]; then
		if $verbose; then echo -e "\n[WARNING] Skipping branch '$branch' because it could not be found in source code.\n" >&2; fi
		return 0;
	else
		return 1;
	fi
}


### Get the name of the file that contains this branch
function getFile(){ grep "\"$1\"" "$src/"*.cc | cut -d: -f1 | sed 's/\/\+/\//g'; }


### Get datatype of this branch
function getType(){
	branch="$1"
	file=`getFile "$branch"`
	filler=`echo $file | sed 's/.*\/\(.*\)\...$/\1/'`
	var=`grep "\"$branch\"" "$file" | sed 's/.*&\(.*\)).*/\1/g'`
	branchType=`grep "$var;" "$interface$filler.h" | sed -e "s/$var.*//g" -e "s/^\s\+//g" -e "s/\s\+$//g"`
	if [ -z "$branchType" ]; then terminate "could not detect data type."; fi
	echo "$branchType"
}

### Function to output variable declaration
function getDeclare(){
	branch="$1";
	if $verbose; then echo -n "Declaring... " >&2; fi
	typeOfBranch=`getType "$branch"`
	vector=`echo $typeOfBranch | grep "vector<"`
	if [ ! -z "$vector" ]; then
		echo "	std::$typeOfBranch* $branch;"
	else
		echo "	$typeOfBranch $branch;"
	fi
}


### Function to output branch addressing
function getAddress(){
	branch="$1";
	if $verbose; then echo -n "Addressing... " >&2; fi
	echo "	fChain->SetBranchAddress(\"$branch\", &$branch);"
}


### Function to output pointer deletion
function getDelete(){
	branch="$1";
	if $verbose; then echo -n "Deleting... " >&2; fi
	vector=`getType "$branch" | grep "vector<"`
	if [ ! -z "$vector" ]; then
		echo "	delete $branch;"	
	fi
}


### Function to output pointer nulling
function getNull(){
	branch="$1";
	if $verbose; then echo -n "Nulling... " >&2; fi
	vector=`getType "$branch" | grep "vector<"`
	if [ ! -z "$vector" ]; then
		echo "	$branch = NULL;"	
	else
		echo "	$branch = 0;"	
	fi
}


### Function to output pointer clearing and variable zeroing
function getClear(){
	branch="$1";
	if $verbose; then echo -n "Clearing... " >&2; fi
	vector=`getType "$branch" | grep "vector<"`
	if [ ! -z "$vector" ]; then
		echo "	$branch->clear();"	
	else
		echo "	$branch = 0;"	
	fi
}

#########################################################################################################################

### Get list of branches
macro="{ TFile *_file0 = TFile::Open(\"$input\");  TTree* tree = (TTree*)_file0->Get(\"$tree\"); tree->Print(); }"
tempMacro=".tempMacro.C"
branches=".branches"
echo "$macro" > "$tempMacro"
echo -n "Wrote temp macro... executing it to get list of branches... "
root -l -b -q "$tempMacro" | grep "*Br" | awk '{print $3}' | sed 's/://g' &> "$branches"
echo "Got list of branches!"
rm -f "$tempMacro"


### Reset files
rm -rf "$bdeclarations" "$bsetBranchAddress" "$bdelete" "$bnull" "$bclear"


### Loop over branches
echo "Processing branches..."
while read branch; do
	if $verbose; then echo -n "Processing branch '$branch' "; fi

	if branchNotInSource "$branch"; then continue; fi
	getDeclare "$branch" >> "$bdeclarations";		
	getAddress "$branch" >> "$bsetBranchAddress";	
	getDelete "$branch" >> "$bdelete";			
	getNull "$branch" >> "$bnull";				
	getClear "$branch" >> "$bclear";				

	if $verbose; then echo ""; fi

done < "$branches"
echo "Complete!"


### Clean up
rm -f "$branches"

