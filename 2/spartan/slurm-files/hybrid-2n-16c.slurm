#!/bin/bash

#SBATCH --array=0-10
#SBATCH --partition=physical
#SBATCH --output=output/hybrid-2n-16c-%a.out
#SBATCH --job-name="hybrid-2n-16c"
#SBATCH --time=0-00:30:00
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=8

module load OpenMPI/2.1.2-GCC-6.4.0-2.28

echo " "
echo " *** Hybrid 2 Node 16 Tasks ***"
echo " "

# compile files
#mpic++ --fopenmp std=c++11 ../knapsack-mpi.cpp -o knapsack-mpi
mpic++ -fopenmp ../4clique-hybrid.cpp -o 4clique-hybrid

mpirun ./4clique-hybrid ../input/350.txt
echo " "



