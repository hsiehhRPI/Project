#!/bin/bash

echo "This is the start of the program, lets see if it works"

make 
inputs=("input.txt" "input2.txt" "input3.txt" "input4.txt" "input5.txt", "input6.txt" "input7.txt")
echo "Start of program execution: "
for ((i = 0; i < 7; i += 1))
do
	echo "Testing files ${inputs[$i]} and ${inputs[$i+1]}"
	echo ${inputs[$i]}
	echo ${inputs[$i+1]}
	valgrind ./all  < filenames.txt


done
make clean