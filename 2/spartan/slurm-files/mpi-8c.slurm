#!/bin/bash

#SBATCH --array=0-10
#SBATCH --partition=cloud
#SBATCH --output=output/mpi-8c-%a.out
#SBATCH --job-name="mpi-8c"
#SBATCH --time=0-00:30:00
#SBATCH --ntasks=8

module load OpenMPI/2.1.2-GCC-6.4.0-2.28

#echo " "
#echo " *** MPI 8 tasks ***"
#echo " "

# compile files
#mpic++ --fopenmp std=c++11 ../knapsack-mpi.cpp -o knapsack-mpi
mpic++ -fopenmp ../4clique-mpi.cpp -o 4clique-mpi

echo "mpi-8c $(mpirun ./4clique-mpi ../input/350.txt)"



