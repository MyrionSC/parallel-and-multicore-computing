#!/bin/bash

#SBATCH --partition=physical
#SBATCH --output=output/sequential.out
#SBATCH --job-name="sequential"
#SBATCH --time=0-12:00:00
#SBATCH --ntasks=1

echo " "
echo " *** Sequential ***"
echo " "

g++ -std=c++11 ../mandelbrot-sequential.cpp -o seq 

echo "Program output:"
time ./seq -2.0 1.0 -1.0 1.0 100 10000 -1 1.0 0.0 1.0 100 10000 -1 1.0 -1.0 0.0 500 10000 -1 0.0 -2.0 -1.0 100 10000 -1 0.0 0.0 2.0 100 10000 0 2.0 0.0 2.0 100 10000 1 2.0 -1.0 1.0 200 10000 -2.0 2.0 -2.0 2.0 200 10000 -1.0 2.0 -1.0 1.0 200 10000 0.0 2.0 0.0 1.0 300 10000 0.0 2.0 -2.0 1.0 200 10000 -1 0.0 -1.0 1.0 500 10000 -1 1.0 -1.0 2.0 700 10000
echo " "

