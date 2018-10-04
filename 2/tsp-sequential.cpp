#include <bits/stdc++.h>

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

    for ( ; next_permutation(vertex.begin(), vertex.end()); ) {
            int currentPathweight = 0;
            int k = 0;

            for (int i = 0; i < vertex.size(); i++) {
                currentPathweight += graph[k][vertex[i]];
                k = vertex[i];
            }

            currentPathweight += graph[k][0];

            // update minimum
            min_path = std::min(min_path, currentPathweight);
    }

    return min_path;
}

// driver program to test above function
int main(int argc, char *argv[])
{
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