#!/bin/bash

#SBATCH --partition=cloud
#SBATCH --array=0-10
#SBATCH --output=output/mp-8c-run-%a.out
#SBATCH --job-name="mp-8c"
#SBATCH --time=0-00:30:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=8

#echo " "
#echo " *** MP 1 Nodes, 8 Cores ***"
#echo " "

module load GCC/6.2.0

# compile files
g++ -fopenmp ../4clique-mp.cpp -o 4clique-mp

echo "mp-8c $(./4clique-mp ../input/350.txt)"



