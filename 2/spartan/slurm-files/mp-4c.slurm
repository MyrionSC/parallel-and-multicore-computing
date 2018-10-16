#!/bin/bash

#SBATCH --partition=physical
#SBATCH --array=0-10
#SBATCH --output=output/mp-4c-run-%a.out
#SBATCH --job-name="mp-4c"
#SBATCH --time=0-00:30:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=4

echo " "
echo " *** MP 1 Nodes, 4 Cores ***"
echo " "

# compile files
g++ -fopenmp 4clique-mp.cpp -o 4clique-mp

./4clique-mp ../input/350.txt
echo " "



