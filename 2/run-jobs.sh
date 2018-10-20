#!/usr/bin/env bash

for ((I=0;$I<10;I=$I+1)) do
 echo "seq $(./4clique-seq input/350.txt)" >> output/seq.out
 echo "mp-2t $(./4clique-mp-2t input/350.txt)" >> output/mp-2t.out 
 echo "mp-3t $(./4clique-mp-3t input/350.txt)" >> output/mp-3t.out 
 echo "mp-4t $(./4clique-mp input/350.txt)" >> output/mp-4t.out 
 echo "mpi-2t $(mpirun -np 2 ./4clique-mpi input/350.txt)" >> output/mpi-2t.out 
 echo "mpi-3t $(mpirun -np 3 ./4clique-mpi input/350.txt)" >> output/mpi-3t.out 
 echo "mpi-4t $(mpirun -np 4 ./4clique-mpi input/350.txt)" >> output/mpi-4t.out 
 echo "hybrid-2t $(mpirun -np 2 ./4clique-hybrid input/350.txt)" >> output/hybrid-2t.out 
 echo "hybrid-3t $(mpirun -np 3 ./4clique-hybrid input/350.txt)" >> output/hybrid-3t.out 
 echo "hybrid-4t $(mpirun -np 4 ./4clique-hybrid input/350.txt)" >> output/hybrid-4t.out 
done
  
