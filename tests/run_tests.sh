#!/bin/bash

# Path for the assembler executable
executable=../build/Assembler

# Checks if assembler was compiled
if [ ! -e "$executable" ]; then
    echo "Assembler does not exists! please compile the project first."
    exit 0 
fi

# Call for the assembler for each file in the directory
files=`ls ./*.as`
$executable $files
