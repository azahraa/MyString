#!/bin/bash

#	Authors:  Anirudh Manohar Chellani 	(achellan@purdue.edu)
#						Joshua Michael Chambers 	(chambe41@purdue.edu)
#
#	Description : Checks memory leak for program specified in the argument stack

printUsage() {
	echo "Usage : checkMemory.sh <path-to-executable> <command line parameters for executable>..."	
	exit 1
}

# check if path to executable is supplied

if [ $# -eq 0 ] 
	then
    printUsage
fi

valout="valLog.txt" #log file for valgrind to use
commandString="valgrind --log-file=$valout"

#Append All parameters passed

for var in "$@"
do
	commandString=$commandString" "$var
done

$commandString; #execute command

valOutput=`cat $valout | grep "All heap blocks were freed"` #check if 'all blocks were freed' exists in valgrind output
deflost=$(cat $valout | grep "definitely lost:")
indlost=$(cat $valout | grep "indirectly lost:")

if [ -z "$valOutput" ] #return 1, i.e. failed if all blocks were not freeed
	then
		echo $deflost
		echo $indlost
		exit 1
fi

rm $valout #remove temp file

exit 0 #return 0, i.e. passed
