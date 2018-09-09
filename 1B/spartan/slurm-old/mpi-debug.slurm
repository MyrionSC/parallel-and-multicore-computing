#!/bin/bash

#SBATCH --output=mpi-debug.out
#SBATCH --job-name="mpi-debug"
#SBATCH --time=0-12:00:00
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=1

# we use this version because it is the one that is installed on linux when using apt
# If we just run module load OpenMPI we get version 3
module load OpenMPI/1.10.2-GCC-6.2.0

echo " "
echo " *** mpi-debug ***"
echo " "

mpicc ../mpi-debug.c -o mpi-debug

echo "running 1:"
mpirun ./mpi-debug

echo "running 2:"
mpirun ./mpi-debug

echo " "





