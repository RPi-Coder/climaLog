#!/bin/bash

file="ClGps_Test.exe"


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

sudo gcc -o $file ClGps_Test.c ClGps.c ClStrH.c -lwiringPi -Wall

if [ -f "$file" ]
then
    echo "Running new version [$file]. Press [Ctrl]/[C] to stop ..."
    sudo ./$file
else
    echo "New version [$file] can NOT be executed!"
fi
