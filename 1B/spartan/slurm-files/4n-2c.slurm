#!/bin/bash

#SBATCH --output=output/2n-1c.out
#SBATCH --job-name="2n-1c"
#SBATCH --time=0-12:00:00
#SBATCH --nodes=4
#SBATCH --ntasks=8 
#SBATCH --cpus-per-task=1

# we use this version because it is the one that is installed on linux when using apt
# If we just run module load OpenMPI we get version 3
module load OpenMPI/1.10.2-GCC-6.2.0

echo " "
echo " *** 4 Nodes, 2 Core Per Node ***"
echo " "

mpicc -fopenmp ../main.c -o main

echo "Program output:"
mpirun ./main -2.0 1.0 -1.0 1.0 100 10000 -1 1.0 0.0 1.0 100 10000

echo " "





