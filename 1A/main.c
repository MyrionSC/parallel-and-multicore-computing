#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "omp.h"

/// Prototypes.
unsigned readFile(char *const *argv, char **buffer);

int main(int argc, char *argv[]) {
    /// Timing scope.
    double startTime = omp_get_wtime();

    /// if argv[1] not given, exit.
    if (argc != 2) {
        fprintf(stderr,
                "Usage: %s <input-file>\n", argv[0]);
        return 1;
    }

    // read file into buffer
    char *inputBuffer = NULL;
    readFile(argv, &inputBuffer);


    // create adjacancy matrix from input
    int dim = (int)*inputBuffer - '0';
    int matrix[dim][dim];
    memset(matrix, 0, sizeof matrix);

    /// Parse input data.
    char *pch = strtok (inputBuffer,"\n\r");
    pch = strtok (NULL, "\n\r");
    while (pch != NULL)
    {
        int from, to, weight = 0;
        sscanf(pch, "%d %d %d", &from, &to, &weight);
        matrix[from-1][to-1] = weight;
        pch = strtok (NULL, "\n\r");
    }

    /// Create weighted matrix.
    for (int i = 0; i < dim ; ++i) {
        for (int j = 0; j < dim ; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    // run floyd-warshall algorithm
    // extract diameter

    /// Free dynamically allocated memory.
    free(inputBuffer);

    /// Print execution time.
    printf("Scope execution time: %f sec", omp_get_wtime()-startTime);

    return 0;
}


unsigned readFile(char *const *argv, char **buffer) {

    FILE *infile;
    size_t numbytes;

    infile = fopen(argv[1], "r");

    if (infile == NULL)
        return 0;

    fseek(infile, 0L, SEEK_END);
    numbytes = (size_t) ftell(infile);
    fseek(infile, 0L, SEEK_SET);

    *buffer = (char *) calloc(numbytes, sizeof(char));
    if (*buffer == NULL)
        return 0;

    fread(*buffer, sizeof(char), numbytes, infile);
    fclose(infile);

    return numbytes;
}