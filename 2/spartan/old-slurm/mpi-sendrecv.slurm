#!/bin/bash

#SBATCH --output=sendrecv.out
#SBATCH --job-name="sendrecv"
#SBATCH --time=0-12:00:00
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=1

# we use this version because it is the one that is installed on linux when using apt
# If we just run module load OpenMPI we get version 3
module load OpenMPI/1.10.2-GCC-6.2.0

echo " "
echo " *** sendrecv ***"
echo " "

mpicc ../mpi-sendrecv.c -o mpi-sendrecv

echo "running 1:"
mpirun ./mpi-sendrecv

echo "running 2:"
mpirun ./mpi-sendrecv

echo " "





