#!/bin/bash

#SBATCH --array=0-10
#SBATCH --partition=physical
#SBATCH --output=output/mpi-4c-%a.out
#SBATCH --job-name="mpi-4c"
#SBATCH --time=0-00:30:00
#SBATCH --ntasks=4

module load OpenMPI/2.1.2-GCC-6.4.0-2.28

echo " "
echo " *** MPI 4 tasks ***"
echo " "

# compile files
#mpic++ --fopenmpi std=c++11 ../knapsack-mpi.cpp -o knapsack-mpi
mpic++ -fopenmpi ../4clique-mpi.cpp -o 4clique-mpi

mpirun ./4clique-mpi ../input/350.txt
echo " "



