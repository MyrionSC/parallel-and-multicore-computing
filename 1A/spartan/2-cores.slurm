#!/bin/bash

#SBATCH --output=2-cores.out
#SBATCH --job-name="M&M-1A-two-cpu"
#SBATCH --time=0-12:00:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=2

echo " "
echo "dataset: example-input\n"
time ./main example-input.txt

echo " "
echo "dataset: 1000e-10000v"
time ./main 1000v-10000e.txt

echo " "
echo "dataset: 2000e-50000v"
time ./main 2000v-50000e.txt

echo " "
echo "all done"





