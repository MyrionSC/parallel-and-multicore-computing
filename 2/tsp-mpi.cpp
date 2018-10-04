#include <stdio.h>
#include <iostream>
#include <vector>
#include "mpi.h"

/// A utility function that returns maximum of two integers.
int max(int a, int b) { return (a > b)? a : b; }

/// Returns the maximum value that can be put in a knapsack of capacity W.
int knapSack(int W, int wt[], int val[], int n)
{
    int i, w;
    int K[n+1][W+1];

    // Build table K[][] in bottom up manner
    for (i = 0; i <= n; i++) {
        for (w = 0; w <= W; w++) {
            if (i==0 || w==0)
                K[i][w] = 0;
            else if (wt[i-1] <= w)
                K[i][w] = max(val[i-1] + K[i-1][w-wt[i-1]],  K[i-1][w]);
            else
                K[i][w] = K[i-1][w];
        }
    }

    return K[n][W];
}

/// Basic knapsack example from: https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/+-
/// Slightly modified.
int main(int argc, char *argv[])
{
    /// OpenMPI
    int root = 0;
    int nrProcesses, idProcces;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &nrProcesses);
    MPI_Comm_rank(MPI_COMM_WORLD, &idProcces);
    printf("num processes: %d\n", nrProcesses);
    printf("Process Id: %d\n\n", idProcces);

    int  W = -1;
    std::vector<int> values;
    std::vector<int> weights;

    if(argc != 2){
        printf("The path to the input file is not specified as a parameter.\n");
        return -1;
    }

    FILE *in_file  = fopen(argv[1], "r");
    if (in_file  == NULL) {
        printf("Can't open file for reading.\n");
        return -1;
    }

    /// Read input file.
    fscanf(in_file,"%d", &W);
    int value, weight;

    while(fscanf(in_file,"%d %d", &value, &weight) != EOF) {
        values.push_back(value);
        weights.push_back(weight);
    }

    /// Execute algorithm.
    printf("%d", knapSack(W, &weights.at(0), &values.at(0), values.size()));

    MPI_Finalize();
    return 0;
}
