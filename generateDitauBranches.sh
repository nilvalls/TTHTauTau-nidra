#!/bin/bash


input="$1"

if [ -z "$input" ]; then
	echo "ERROR: must provide an input file."
	exit 1;
elif [ ! -f "$input" ]; then
	echo "ERROR: input file \"$input\" could not be opened."
	exit 1;
fi

tempDir=".ditauBranches_temp"
mkdir "$tempDir"

declarations="clarity/ditauBranches_declarations.h"
nullPointers="clarity/ditauBranches_nullPointers.h"
deletePointers="clarity/ditauBranches_deletePointers.h"
setBranchAddresses="clarity/ditauBranches_setBranchAddresses.h"


### Clean up input file
startLine=`grep -n "=== START ===" "$input" | awk 'BEGIN {FS = ":"};{print $1}'`
tail --lines=+$(( $startLine + 1 )) "$input" > "$tempDir/input"
endLine=`grep -n "=== END ===" "$tempDir/input" | awk 'BEGIN {FS = ":"};{print $1}'`
head -n $(( $endLine - 1 )) "$tempDir/input" | sed -e '/^$/d' -e 's/^\s\+//g' -e 's/\s_/\ /g' -e 's/\s\+/\ /g'  > "$declarations"


### Generate NULL POINTERS
rm -f "$nullPointers"
while read line; do
	if [[ "$line" == *\** ]]; then
		echo "$line" | sed -e "s/^.*\*//g" -e "s/\s\+//g" -e "s/\(.*\);/\1\ =\ NULL;/g" >> "$nullPointers"
	else
		echo "$line" | sed -e "s/^.*\s//g" -e "s/\s\+//g" -e "s/\(.*\);/\1\ =\ 0;/g" >> "$nullPointers" 
	fi
done < "$declarations"

### Generate DELETE POINTERS
rm -f "$deletePointers"
while read line; do
	if [[ "$line" == *\** ]]; then
		echo "$line" | sed -e "s/^.*\*//g" -e "s/\s\+//g" -e "s/\(.*\);/delete\ \1;/g" >> "$deletePointers" 
	fi
done < "$declarations"


### Generate SET BRANCH ADDRESSES
cp "$declarations" "$setBranchAddresses"
sed -i 's/^.*\*//g' "$setBranchAddresses"
sed -i 's/.*\s\+//g' "$setBranchAddresses"
sed -i 's/\(.*\);/fChain->SetBranchAddress("\1",\ \&\1);/g' "$setBranchAddresses"


rm -rf "$tempDir"
