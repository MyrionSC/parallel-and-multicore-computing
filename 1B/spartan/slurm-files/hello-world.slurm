#!/bin/bash

#SBATCH --output=output/hello-world.out
#SBATCH --job-name="hello-world"
#SBATCH --time=0-12:00:00
#SBATCH --nodes=2 
#SBATCH --ntasks=5 
#SBATCH --cpus-per-task=1

##SBATCH --nodes=4
##SBATCH --ntasks-per-node=8

# we use this version because it is the one that is installed on linux when using apt
# If we just run module load OpenMPI we get version 3
module load OpenMPI/1.10.2-GCC-6.2.0

echo " "
echo " *** Hello World - 2 nodes, 5 tasks, 1 cpus per task ***"
echo " "

mpicc ../mpi-helloworld.c -o mpi-hw

echo "running 1:"
mpirun ./mpi-hw

