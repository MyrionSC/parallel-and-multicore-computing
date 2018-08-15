#!/bin/bash

#SBATCH --output=4-cores.out
#SBATCH --job-name="M&M-1A-four-cpu"
#SBATCH --time=0-12:00:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=4

echo " "
echo " *** Four cores ***"
echo " "
echo "dataset: example-input"
time ./main example-input.txt

echo " "
echo "dataset: 1000e-10000v"
time ./main 1000v-10000e.txt

echo " "
echo "dataset: 2000e-50000v"
time ./main 2000v-50000e.txt

echo " "





