#!/bin/bash

#SBATCH --array=0-10
#SBATCH --partition=physical
#SBATCH --output=output/2n-1c.out
#SBATCH --job-name="2n-1c"
#SBATCH --time=0-12:00:00
#SBATCH --nodes=2 
#SBATCH --ntasks=5 
#SBATCH --cpus-per-task=1

# we use this version because it is the one that is installed on linux when using apt
# If we just run module load OpenMPI we get version 3
module load OpenMPI/2.1.2-GCC-6.4.0-2.28

echo " "
echo " *** Two Nodes, 5 Cores, run $SLURM_ARRAY_TASK_ID ***"
echo " "

mpic++  -std=c++11 ../main.cpp -o main

echo "Program output:"
#mpirun ./main -2.0 1.0 -1.0 1.0 100 10000 -1 1.0 0.0 1.0 100 10000
time mpirun ./main -2.0 1.0 -1.0 1.0 100 10000 -1 1.0 0.0 1.0 100 10000 -1 1.0 -1.0 0.0 500 10000 -1 0.0 -2.0 -1.0 100 10000 -1 0.0 0.0 2.0 100 10000 0 2.0 0.0 2.0 100 10000 1 2.0 -1.0 1.0 200 10000 -2.0 2.0 -2.0 2.0 200 10000 -1.0 2.0 -1.0 1.0 200 10000 0.0 2.0 0.0 1.0 300 10000 0.0 2.0 -2.0 1.0 200 10000 -1 0.0 -1.0 1.0 500 10000 -1 1.0 -1.0 2.0 700 10000
echo " "

