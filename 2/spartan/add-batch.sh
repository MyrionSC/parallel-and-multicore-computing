#!/bin/bash
FILES=slurm-files/*
for F in $FILES
do
  sbatch $F
  #echo "Processing $F file..."
  #cat $F
done
