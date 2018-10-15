#include <bits/stdc++.h>
#include <limits.h>
#include <string.h>
#include "omp.h"
using namespace std;

// Number of vertices in the graph
#define MAX_NODES 1000
static int nrNodes = -1;

void three_clique(int pInt[1000][1000]);

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int dist[], bool sptSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < nrNodes; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// A utility function to print the constructed distance array
int printSolution(int dist[], int n)
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < nrNodes; i++)
        printf("%d tt %d\n", i, dist[i]);
}

// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void three_clique(int **graph, int src)
{
    int dist[nrNodes];     // The output array.  dist[i] will hold the shortest
    // distance from src to i

    bool sptSet[nrNodes]; // sptSet[i] will true if vertex i is included in shortest
    // path tree or shortest distance from src to i is finalized

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < nrNodes; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < nrNodes-1; count++)
    {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in the first iteration.
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < nrNodes; v++)

            // Update dist[v] only if is not in sptSet, there is an edge from
            // u to v, and total weight of path from src to  v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u]+graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    // print the constructed distance array
    printSolution(dist, nrNodes);
}

// driver program to test above function
int main(int argc, char *argv[])
{
    /* Let us create the example graph discussed above */
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

    three_clique(graph);

    /// Print execution time.
    timeEnd = omp_get_wtime();
    printf("%.16g", timeEnd-timeBegin);

    return 0;
}

void three_clique(int graph[MAX_NODES][MAX_NODES]) {
    for (int i = 0; i < nrNodes-1; ++i) {
        for (int j = 0; j < nrNodes - 1; ++j) {
            for (int k = 0; k < nrNodes - 1; ++k) {
                // check for three clique. The graph is undirected, so only need to check one direction
                if (graph[i][j] >= 1 && graph[i][k] >= 1 && graph[j][k] >= 1) {
                    // print nodes or add to set or something
                    // adding to set would be best since we don't get duplicates like that
                    printf("Three clique detected: %d %d %d\n", i, j, k);
                }
            }
        }
    }
}
