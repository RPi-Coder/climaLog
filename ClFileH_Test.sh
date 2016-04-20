#!/bin/bash
file="ClFileH_Test.exe"
clear

if [ -f "$file" ]
then
	echo "[$file] found!"
	echo "Deleting old version ..."
	sudo rm $file 
else
	echo "[$file] not found!"
fi

echo "Compiling new version [$file] ..." 

sudo gcc -o $file ClFileH_Test.c ClFileH.c -lwiringPi -Wall

if [ -f "$file" ]
then
    echo "Running new version [$file]. Press [Ctrl]/[C] to stop ..."
    sudo ./$file
else
    echo "New version [$file] can not be executed!"
fi
