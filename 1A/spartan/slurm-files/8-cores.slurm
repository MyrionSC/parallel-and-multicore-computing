#!/bin/bash

#SBATCH --output=output/08-cores.out
#SBATCH --job-name="M&M-1A-eight-cpu"
#SBATCH --time=0-12:00:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=8

echo " "
echo " *** Eight cores *** "
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





