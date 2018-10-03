#include <stdio.h>
#include <iostream>
#include <vector>
#include "mpi.h"

/// A utility function that returns maximum of two integers.
int max(int a, int b) { return (a > b)? a : b; }

/// Returns the maximum value that can be put in a knapsack of capacity W.
int knapSack(int W, int wt[], int val[], int n)
{
    // Base Case
    if (n == 0 || W == 0)
        return 0;

    // If weight of the nth item is more than Knapsack capacity W, then
    // this item cannot be included in the optimal solution
    if (wt[n-1] > W)
        return knapSack(W, wt, val, n-1);

        // Return the maximum of two cases:
        // (1) nth item included
        // (2) not included
    else return max( val[n-1] + knapSack(W-wt[n-1], wt, val, n-1),
                     knapSack(W, wt, val, n-1)
        );
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
