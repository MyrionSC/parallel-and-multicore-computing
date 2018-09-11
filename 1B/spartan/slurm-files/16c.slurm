#!/bin/bash

#SBATCH --output=output/16c.out
#SBATCH --job-name="16c"
#SBATCH --time=0-12:00:00
#SBATCH --ntasks=16

# we use this version because it is the one that is installed on linux when using apt
# If we just run module load OpenMPI we get version 3
module load OpenMPI/1.10.2-GCC-6.2.0

echo " "
echo " *** 16 Tasks ***"
echo " "

mpic++ -std=c++11 ../main.cpp -o main

echo "Program output:"
#mpirun ./main -2.0 1.0 -1.0 1.0 100 10000 -1 1.0 0.0 1.0 100 10000
time mpirun ./main -2.0 1.0 -1.0 1.0 100 10000 -1 1.0 0.0 1.0 100 10000 -1 1.0 -1.0 0.0 500 10000 -1 0.0 -2.0 -1.0 100 10000 -1 0.0 0.0 2.0 100 10000 0 2.0 0.0 2.0 100 10000 1 2.0 -1.0 1.0 200 10000 -2.0 2.0 -2.0 2.0 200 10000 -1.0 2.0 -1.0 1.0 200 10000 0.0 2.0 0.0 1.0 300 10000 0.0 2.0 -2.0 1.0 200 10000 -1 0.0 -1.0 1.0 500 10000 -1 1.0 -1.0 2.0 700 10000
echo " "





