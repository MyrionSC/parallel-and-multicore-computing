#!/bin/bash

#SBATCH --output=output/hello-world.out
#SBATCH --job-name="hello-world"
#SBATCH --time=0-12:00:00
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=2

# we use this version because it is the one that is installed on linux when using apt
# If we just run module load OpenMPI we get version 3
module load OpenMPI/1.10.2-GCC-4.6.4

echo " "
echo " *** Hello World - 2 nodes, 2 cores each ***"
echo " "

mpicc ../mpi-helloworld.c -o mpi-hw

echo "running 1:"
mpirun ./mpi-hw

echo "running 2:"
mpirun ./mpi-hw

echo " "





