#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "omp.h"

#define MAX 10000
#define NOT_CONNECTED 9999
#define MIN(a,b) ((a) < (b) ? a : b)

// TODO Add multiple small test dataset with known solution that can be used to verify the functionality of the algorithm.
// TODO Write a test script who compates the results of th algorithm with the test datasets.

int distance[MAX][MAX];
int nodesCount;

void Initialize(){
    for (int i=0;i<MAX;++i){
        for (int j=0;j<MAX;++j){
            distance[i][j]=NOT_CONNECTED;

        }
        distance[i][i]=0;
    }
}

/// Prototypes.

int main(int argc, char *argv[]) {

    int maxNrThreads = omp_get_max_threads();
    printf("Max threads: %d\n", maxNrThreads);

    /// Set number of threads.
    omp_set_num_threads(maxNrThreads);

    /// Timing scope.
    double startTime = omp_get_wtime();


    if(argc!=2){
        printf("The path to the input file is not specified as a parameter.\n");
        return -1;
    }
    FILE *in_file  = fopen(argv[1], "r");
    if (in_file  == NULL)
    {
        printf("Can't open file for reading.\n");
        return -1;
    }

    /// Section 1: scan file into memory
    Initialize();
    fscanf(in_file,"%d", &nodesCount);
    int a, b, c;
    while(fscanf(in_file,"%d %d %d", &a, &b, &c)!= EOF){
        if ( a > nodesCount || b > nodesCount){
            printf("Vertex index out of boundary.");
            return -1;
        }
        distance[a][b]=c;
    }
    printf("Section 1: %f sec\n", omp_get_wtime()-startTime);


    /// Section 2: Floyd-Warshall
    #pragma omp parallel for
    for (int k = 1; k <= nodesCount; ++k) {
        for (int i = 1; i <= nodesCount; ++i) {
                for (int j = 1; j <= nodesCount; ++j) {
                        distance[i][j] = MIN(distance[i][j], distance[i][k] + distance[k][j]);
                }
        }
    }
    printf("Section 2: %f sec\n", omp_get_wtime()-startTime);


    int diameter=-1;

    /// Section 3: look for the most distant pair
    for (int i=1; i <= nodesCount; ++i){
        for (int j=1; j <= nodesCount; ++j){
            if (diameter < distance[i][j]){
                diameter = distance[i][j];
                printf("%d-%d-%d\n", i, diameter, j);
            }
        }
    }

    /// Print execution time.
    printf("Scope execution time: %f sec\n", omp_get_wtime()-startTime);

    printf("%d\n", diameter);

    return 0;
}
