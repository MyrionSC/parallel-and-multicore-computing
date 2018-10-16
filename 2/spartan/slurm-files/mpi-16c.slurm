#!/bin/bash

#SBATCH --array=0-10
#SBATCH --partition=physical
#SBATCH --output=output/mpi-16c-%a.out
#SBATCH --job-name="mpi-16c"
#SBATCH --time=0-00:30:00
#SBATCH --ntasks=16

module load OpenMPI/2.1.2-GCC-6.4.0-2.28

#echo " "
#echo " *** MPI 16 tasks ***"
#echo " "

# compile files
#mpic++ --fopenmp std=c++11 ../knapsack-mpi.cpp -o knapsack-mpi
mpic++ -fopenmp ../4clique-mpi.cpp -o 4clique-mpi

echo "mpi-16c $(mpirun ./4clique-mpi ../input/350.txt)"



