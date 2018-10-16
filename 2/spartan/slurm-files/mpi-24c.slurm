#!/bin/bash

#SBATCH --array=0-10
#SBATCH --partition=physical
#SBATCH --output=output/mpi-24c-%a.out
#SBATCH --job-name="mpi-24c"
#SBATCH --time=0-00:30:00
#SBATCH --ntasks=24

module load OpenMPI/2.1.2-GCC-6.4.0-2.28

echo " "
echo " *** MPI 24 tasks ***"
echo " "

# compile files
#mpic++ --fopenmp std=c++11 ../knapsack-mpi.cpp -o knapsack-mpi
mpic++ -fopenmp ../4clique-mpi.cpp -o 4clique-mpi

mpirun ./4clique-mpi ../input/350.txt
echo " "



