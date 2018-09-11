#!/bin/bash

#SBATCH --output=output/4n-8c.out
#SBATCH --job-name="4n-8c"
#SBATCH --time=0-12:00:00
#SBATCH --nodes=4
#SBATCH --ntasks=8 
#SBATCH --cpus-per-task=1

# we use this version because it is the one that is installed on linux when using apt
# If we just run module load OpenMPI we get version 3
module load OpenMPI/1.10.2-GCC-6.2.0

echo " "
echo " *** 4 Nodes, 8 Cores ***"
echo " "

mpic++ -fopenmp ../main.cpp -o main

echo "Program output:"
mpirun ./main -2.0 1.0 -1.0 1.0 100 10000 -1 1.0 0.0 1.0 100 10000

echo " "





