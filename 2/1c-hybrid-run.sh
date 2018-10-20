#!/usr/bin/env bash

for ((I=0;$I<10;I=$I+1)) do
 echo "mpi-8t $(mpirun -np 8 ./4clique-mpi input/350.txt)" >> output/mpi-8t.out 
done
  
