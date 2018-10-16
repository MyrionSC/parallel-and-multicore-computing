#!/bin/bash

#SBATCH --array=0-10
#SBATCH --partition=physical
#SBATCH --output=output/seq-%a.out
#SBATCH --job-name="seq"
#SBATCH --time=0-0:30:00
#SBATCH --ntasks=1

#echo " "
#echo " *** Sequential ***"
#echo " "

module load GCC/6.2.0

# compile files
g++ -fopenmp ../4clique-sequential.cpp -o 4clique-seq

echo "sec $(./4clique-seq ../input/350.txt)"
#echo " "




