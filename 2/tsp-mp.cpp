#include <bits/stdc++.h>
#include <limits.h>
#include "omp.h"

#define MAX_NODES 10000

int graph[MAX_NODES][MAX_NODES] = {0};

// implementation of traveling Salesman Problem
int travllingSalesmanProblem(int nrNodes) {
    // store all vertex apart from source vertex
    std::vector<int> vertex;

    for (int i = 0; i < nrNodes; i++)
        if (i != 0)
            vertex.push_back(i);

    // store minimum weight Hamiltonian Cycle.
    int min_path = INT_MAX;

<<<<<<< Updated upstream
    #pragma omp parallel
    for (int i = 0; i < nrNodes; i++) {

        auto vertexprime = vertex;
        std::rotate(vertexprime.begin(), vertexprime.begin() + i, vertexprime.begin() + i + 1);

        do {
            int currentPathweight = 0;
            int k = 0;

            for (int j = 0; j < vertexprime.size(); j++) {
                currentPathweight += graph[k][vertexprime[j]];
                k = vertexprime[j];
            }

            min_path = std::min(min_path, currentPathweight);

        } while(next_permutation(vertexprime.begin(), vertexprime.end()));

        // update minimum
=======

    for (int i = 0; i < vertex.size(); ++i) {
        auto perm = vertex;
        std::rotate(perm.begin(), perm.begin() + i, perm.begin() + i + 1);

        do {
            int currentPathweight = 0;
            int k = 0;

            for (int i = 0; i < vertex.size(); i++) {
                currentPathweight += graph[k][vertex.at(i)];
                k = vertex.at(i);
            }

            currentPathweight += graph[k][0];

            // update minimum
            min_path = std::min(min_path, currentPathweight);
        }
        while (std::next_permutation(perm.begin() + 1, perm.end()));

>>>>>>> Stashed changes
    }
//    #pragma omp parallel
//    for ( ; next_permutation(vertex.begin(), vertex.end()); ) {
//        int currentPathweight = 0;
//        int k = 0;
//
//        for (int i = 0; i < vertex.size(); i++) {
//            currentPathweight += graph[k][vertex.at(i)];
//            k = vertex.at(i);
//        }
//
//        currentPathweight += graph[k][0];
//
//        // update minimum
//        min_path = std::min(min_path, currentPathweight);
//    }
<<<<<<< Updated upstream

=======
>>>>>>> Stashed changes

    return min_path;
}

// driver program to test above function
int main(int argc, char *argv[])
{
    int maxNrThreads = omp_get_max_threads();
    printf("Max threads: %d\n", maxNrThreads);

    /// Set number of threads.
    omp_set_num_threads(maxNrThreads);

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

    std::cout << travllingSalesmanProblem(nrNodes) << std::endl;
    return 0;
}