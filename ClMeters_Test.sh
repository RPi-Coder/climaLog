#!/bin/bash
file="ClMeters_Test.exe"
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

sudo gcc -o $file ClMeters_Test.c ClMeters.c ClTimeH.c ClFileH.c ClStrH.c -lwiringPi -Wall

if [ -f "$file" ]
then
    echo "Executing new version of ClimaLog 2000 - [$file] ..."
    sudo ./$file -li 3
else
    echo "New version [$file] can not be executed!"
fi

