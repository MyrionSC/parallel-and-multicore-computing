#!/bin/bash

#SBATCH --partition=bigmem
#SBATCH --output=output/12-cores.out
#SBATCH --job-name="twelve-cpu"
#SBATCH --time=0-12:00:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=12

echo " "
echo " *** Twelve cores ***"
echo " "
echo "dataset: example-input"
time ./main input-files/example-input.txt

echo " "
echo "dataset: 1000e-10000v"
time ./main input-files/1000v-10000e.txt

echo " "
echo "dataset: 2000e-50000v"
time ./main input-files/2000v-50000e.txt

echo " "





