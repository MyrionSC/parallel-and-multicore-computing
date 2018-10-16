#!/bin/bash

###SBATCH --partition=physical
#SBATCH --output=output/1n-8c.out
#SBATCH --job-name="1n-8c"
#SBATCH --time=0-12:00:00
#SBATCH --nodes=1
#SBATCH --ntasks=8
###SBATCH --cpus-per-task=1

###SBATCH --array=0-10
###SBATCH --output=output/32c-run-%a.out

module load OpenMPI/2.1.2-GCC-6.4.0-2.28

echo " "
echo " *** 1 Nodes, 8 Cores ***"
echo " "

# compile files
g++ ../knapsack-sequential.cpp -o knapsack-sequential
g++ -fopenmp ../knapsack-mp.cpp -o knapsack-mp
#mpic++ -std=c++11 ../knapsack-mpi.cpp -o knapsack-mpi
mpic++ ../knapsack-mpi.cpp -o knapsack-mpi
#mpic++ -fopenmp -std=c++11 ../knapsack-hybrid.cpp -o knapsack-hybrid
mpic++ -fopenmp ../knapsack-hybrid.cpp -o knapsack-hybrid


echo "Sequential output:"
time ./knapsack-sequential ../input/400.txt
echo " "

echo "MP output:"
time ./knapsack-mpi ../input/400.txt
echo " "

echo "MPI output:"
time mpirun ./knapsack-mpi ../input/400.txt
echo " "

echo "Hybrid output:"
time mpirun ./knapsack-hybrid ../input/400.txt
echo " "




