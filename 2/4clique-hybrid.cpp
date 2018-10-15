#include <bits/stdc++.h>
#include "omp.h"
#include "mpi.h"

// Number of vertices in the graph
#define MAX_NODES 1000
static int nrNodes = -1;

void four_clique(int graph[MAX_NODES][MAX_NODES], int idProcess, int nrProcesses);
void print_graph(int graph[MAX_NODES][MAX_NODES]);

int graph[MAX_NODES][MAX_NODES] = {0};

// driver program to test above function
int main(int argc, char *argv[])
{
    /// OpenMP
    int maxNrThreads = omp_get_max_threads();
    printf("Max threads: %d\n", maxNrThreads);
    omp_set_num_threads(maxNrThreads);

    /// OpenMPI
    int root = 0;
    int nrProcesses, idProcces;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &nrProcesses);
    MPI_Comm_rank(MPI_COMM_WORLD, &idProcces);
//    printf("num processes: %d\n", nrProcesses);
//    printf("Process Id: %d\n", idProcces);

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
    int nrNodes = -1;
    fscanf(in_file,"%d", &nrNodes);
    int src, dst, wgt;

    while(fscanf(in_file,"%d %d %d", &src, &dst, &wgt) != EOF) {
        graph[src][dst] = wgt;
    }

    four_clique(graph, idProcces, nrProcesses);

    MPI_Finalize();
    return 0;
}

void four_clique(int graph[MAX_NODES][MAX_NODES], int idProcess, int nrProcesses) {
    int nrCliques = 0;
    for (int i = 0; (i + idProcess) < nrNodes - 1; i += nrProcesses) {
        int para_i = i + idProcess;

        #pragma omp parallel for
        for (int j = 0; j < nrNodes - 1; ++j) {
            for (int k = 0; k < nrNodes - 1; ++k) {
                for (int l = 0; l < nrNodes - 1; ++l) {
                    // check for four clique. The graph is undirected, so only need to check one direction
                    if (graph[para_i][j] >= 1 && graph[para_i][k] >= 1 && graph[para_i][l] >= 1 &&
                        graph[j][k] >= 1 && graph[j][l] >= 1 && graph[k][l] >= 1) {
                        nrCliques++;
                    }
                }
            }
        }
    }

    int globalCount = 0;
//    printf("procId: %d, cliques num: %d\n", idProcess, nrCliques);
    MPI_Reduce(&nrCliques, &globalCount,1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (idProcess == 0) {
        printf("Number of four cliques: %d\n", globalCount);
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