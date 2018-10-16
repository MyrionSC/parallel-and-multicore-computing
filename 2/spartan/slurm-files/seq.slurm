#!/bin/bash

#SBATCH --partition=physical
#SBATCH --output=output/seq.out
#SBATCH --job-name="4n-8c"
#SBATCH --time=0-0:10:00
#SBATCH --ntasks=1

echo " "
echo " *** Sequential ***"
echo " "

# compile files
g++ -fopenmp 4clique-sequential.cpp -o 4clique-seq

./4clique-seq ../input/350.txt
echo " "




