#!/bin/bash

#SBATCH --partition=bigmem
#SBATCH --array=0-10
#SBATCH --output=output/mp-24c-run-%a.out
#SBATCH --job-name="mp-24c"
#SBATCH --time=0-00:30:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=24

#echo " "
#echo " *** MP 1 Nodes, 24 Cores ***"
#echo " "

module load GCC/6.2.0

# compile files
g++ -fopenmp ../4clique-mp.cpp -o 4clique-mp

echo "mp-24c $(./4clique-mp ../input/350.txt)"



