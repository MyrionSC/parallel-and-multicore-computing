#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "omp.h"

unsigned readFile(char *const *argv, char **buffer);

int main(int argc, char *argv[]) {
    // if argv[1] not given, exit
    if (argc != 2) {
        fprintf(stderr,
                "Usage: %s <input-file>\n", argv[0]);
        return 1;
    }

    // read file into buffer
    char *inputBuffer = NULL;
    int numBytes = readFile(argv, &inputBuffer);


    // create adjacancy matrix from input
    int dim = (int)*inputBuffer - '0';

    char *pch = strtok (inputBuffer,"\n\r");
    pch = strtok (NULL, "\n\r");
    while (pch != NULL)
    {
        int from, to, weight;
        sscanf(pch, "%d %d %d", &from, &to, &weight);

        printf("%d %d %d\n", from, to, weight);

//        printf ("%s\n",pch);
        pch = strtok (NULL, "\n\r");
    }


    // run floyd-warshall algorithm




    // extract diameter


    free(inputBuffer);

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