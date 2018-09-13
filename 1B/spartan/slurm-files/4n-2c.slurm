#!/bin/bash

#SBATCH --output=output/4n-8c.out
#SBATCH --job-name="4n-8c"
#SBATCH --time=0-12:00:00
#SBATCH --nodes=4
#SBATCH --ntasks=8 
#SBATCH --cpus-per-task=1

# we use this version because it is the one that is installed on linux when using apt
# If we just run module load OpenMPI we get version 3
#module load GCC/6.2.0
module load OpenMPI/2.1.2-GCC-6.4.0-2.28

echo " "
echo " *** 4 Nodes, 8 Cores ***"
echo " "

mpic++ -std=c++11 ../main.cpp -o main

echo "Program output:"
#mpirun ./main -2.0 1.0 -1.0 1.0 100 10000 -1 1.0 0.0 1.0 100 10000
time mpirun ./main -2.0 1.0 -1.0 1.0 100 10000 -1 1.0 0.0 1.0 100 10000 -1 1.0 -1.0 0.0 500 10000 -1 0.0 -2.0 -1.0 100 10000 -1 0.0 0.0 2.0 100 10000 0 2.0 0.0 2.0 100 10000 1 2.0 -1.0 1.0 200 10000 -2.0 2.0 -2.0 2.0 200 10000 -1.0 2.0 -1.0 1.0 200 10000 0.0 2.0 0.0 1.0 300 10000 0.0 2.0 -2.0 1.0 200 10000 -1 0.0 -1.0 1.0 500 10000 -1 1.0 -1.0 2.0 700 10000
echo " "

