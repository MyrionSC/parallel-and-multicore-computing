#include <bits/stdc++.h>
#include "mpi.h"
#include "omp.h"

#define MAX_NODES 1000
static int nrNodes = -1;

void four_clique(int graph[MAX_NODES][MAX_NODES], int idProcess, int nrProcesses);

void print_graph(int graph[MAX_NODES][MAX_NODES]);

// driver program to test above function
int main(int argc, char *argv[]) {
    /// OpenMPI.
    int root = 0;
    int nrProcesses, idProcces;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &idProcces);
    MPI_Comm_size(MPI_COMM_WORLD, &nrProcesses);
    printf("Process Id: %d\n\n", idProcces);
    printf("num processes: %d\n", nrProcesses);

    // init graph with zeroes
    int graph[MAX_NODES][MAX_NODES] = {0};

    if (argc != 2) {
        printf("The path to the input file is not specified as a parameter.\n");
        return -1;
    }

    FILE *in_file = fopen(argv[1], "r");
    if (in_file == NULL) {
        printf("Can't open file for reading.\n");
        return -1;
    }


    /// Read input file.
    fscanf(in_file, "%d", &nrNodes);
    int src, dst, wgt;

    while (fscanf(in_file, "%d %d %d", &src, &dst, &wgt) != EOF) {
        graph[src][dst] = wgt;
    }

    /// Timing scope.
    double timeBegin, timeEnd;
    timeBegin = omp_get_wtime();

    four_clique(graph, idProcces, nrProcesses);
//    print_graph(graph);

    /// Print execution time.
    timeEnd = omp_get_wtime();
    printf("Execution time: %.16g", timeEnd-timeBegin);

    MPI_Finalize();
    return 0;
}


void four_clique(int graph[MAX_NODES][MAX_NODES], int idProcess, int nrProcesses) {
    for (int i = 0; (i + idProcess) < nrNodes - 1; i += nrProcesses) {
        int para_i = i + idProcess;
        for (int j = 0; j < nrNodes - 1; ++j) {
            for (int k = 0; k < nrNodes - 1; ++k) {
                for (int l = 0; l < nrNodes - 1; ++l) {
                    // check for four clique. The graph is undirected, so only need to check one direction
                    if (graph[para_i][j] >= 1 && graph[para_i][k] >= 1 && graph[para_i][l] >= 1 &&
                        graph[j][k] >= 1 && graph[j][l] >= 1 && graph[k][l] >= 1) {
                        // print nodes or add to set or something
                        // adding to set would be best since we don't get duplicates like that
//                        printf("four clique detected: %d %d %d %d\n", para_i, j, k, l);
                    }
                }
            }
        }
    }
}

// for debugging
void print_graph(int graph[MAX_NODES][MAX_NODES]) {
    printf("\n");
    for (int i = 0; i < nrNodes - 1; ++i) {
        for (int j = 0; j < nrNodes - 1; ++j) {
            printf("%d\t", graph[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
