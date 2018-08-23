#!/bin/bash

#SBATCH --output=output/seq-alg.out
#SBATCH --job-name="seq-alg"
#SBATCH --time=0-12:00:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1

echo " "
echo " *** Sequential algorithm ***"
echo " "
echo "dataset: example-input"
time ./seq-alg input-files/example-input.txt

echo " "
echo "dataset: 1000e-10000v"
time ./seq-alg input-files/1000v-10000e.txt

echo " "
echo "dataset: 2000e-50000v"
time ./seq-alg input-files/2000v-50000e.txt

echo " "





