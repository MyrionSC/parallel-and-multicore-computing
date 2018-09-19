#!/bin/bash

#SBATCH --partition=gpu
#SBATCH --output=cuda-example.out
#SBATCH --job-name="cuda-example"
#SBATCH --time=0-12:00:00
#SBATCH --ntasks=1

module load CUDA/9.2.88-GCC-6.2.0

nvcc cuda-example.cu -o add

echo "*** cuda example ***"
echo ""

./add

echo ""

