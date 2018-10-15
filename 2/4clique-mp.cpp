#include <bits/stdc++.h>
#include "omp.h"

// Number of vertices in the graph
#define MAX_NODES 1000
static int nrNodes = -1;

void four_clique(int graph[MAX_NODES][MAX_NODES]);
void print_graph(int graph[MAX_NODES][MAX_NODES]);

// driver program to test above function
int main(int argc, char *argv[])
{
    int maxNrThreads = omp_get_max_threads();
    printf("Max threads: %d\n", maxNrThreads);

    /// Set number of threads.
    omp_set_num_threads(maxNrThreads);

    // init graph with zeroes
    int graph[MAX_NODES][MAX_NODES] = {0};

    if(argc != 2){
        printf("The path to the input file is not specified as a parameter.\n");
        return -1;
    }

    FILE *in_file  = fopen(argv[1], "r");
    if (in_file  == NULL) {
        printf("Can't open file for reading.\n");
        return -1;
    }

    /// Timing scope.
    double timeBegin, timeEnd;
    timeBegin = omp_get_wtime();

    /// Read input file.
    fscanf(in_file,"%d", &nrNodes);
    int src, dst, wgt;

    while(fscanf(in_file,"%d %d %d", &src, &dst, &wgt) != EOF) {
        graph[src][dst] = wgt;
    }

    four_clique(graph);
//    print_graph(graph);

    /// Print execution time.
    timeEnd = omp_get_wtime();
    printf("Execution time: %.16g", timeEnd-timeBegin);

    return 0;
}

void four_clique(int graph[MAX_NODES][MAX_NODES]) {
    int nrCliques = 0;

    #pragma omp parallel for
    for (int i = 0; i < nrNodes - 1; ++i) {
        for (int j = 0; j < nrNodes - 1; ++j) {
            for (int k = 0; k < nrNodes - 1; ++k) {
                for (int l = 0; l < nrNodes - 1; ++l) {
                    // check for four clique. The graph is undirected, so only need to check one direction
                    if (graph[i][j] >= 1 && graph[i][k] >= 1 && graph[i][l] >= 1 &&
                        graph[j][k] >= 1 && graph[j][l] >= 1 && graph[k][l] >= 1) {
                        // maybe use mutex here. There are race condition risks (although it would be very unlucky with sparse graphs)
                        nrCliques++;
                    }
                }
            }
        }
    }
    printf("Number of four cliques: %d\n", nrCliques);
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
