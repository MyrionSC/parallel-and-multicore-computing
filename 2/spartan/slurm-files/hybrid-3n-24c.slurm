#!/bin/bash

#SBATCH --array=0-10
#SBATCH --partition=cloud
#SBATCH --output=output/hybrid-3n-24c-%a.out
#SBATCH --job-name="hybrid-3n-24c"
#SBATCH --time=0-00:30:00
#SBATCH --nodes=3
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=8

module load OpenMPI/2.1.2-GCC-6.4.0-2.28

#echo " "
#echo " *** Hybrid 3 Node 24 Tasks ***"
#echo " "

# compile files
#mpic++ --fopenmp std=c++11 ../knapsack-mpi.cpp -o knapsack-mpi
mpic++ -fopenmp ../4clique-hybrid.cpp -o 4clique-hybrid

echo "hybrid-3n-24c $(mpirun ./4clique-hybrid ../input/350.txt)"



