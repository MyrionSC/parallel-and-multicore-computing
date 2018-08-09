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
    printf("%d\n", numBytes);
    printf("%s", inputBuffer);

    // create adjacancy matrix from input




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