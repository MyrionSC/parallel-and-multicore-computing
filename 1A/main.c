#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "omp.h"

char *readFile(char *const *argv);

int main(int argc, char *argv[]) {
    // if argv[1] not given, exit
    if (argc != 2) {
        fprintf(stderr,
                "Usage: %s <input-file>\n", argv[0]);
        return 1;
    }

    // read file into buffer
    char *inputBuffer = readFile(argv);
    printf("%s", inputBuffer);

    // create adjacancy matrix from input




    // run floyd-warshall algorithm




    // extract diameter


    free(inputBuffer);

    return 0;
}


char *readFile(char *const *argv) {

    FILE *infile;
    char* buffer;
    long numbytes;

    infile = fopen(argv[1], "r");

    if (infile == NULL)
        return 1;

    fseek(infile, 0L, SEEK_END);
    numbytes = ftell(infile);
    fseek(infile, 0L, SEEK_SET);

    buffer = (char *) calloc(numbytes, sizeof(char));
    if (buffer == NULL)
        return 1;

    fread(buffer, sizeof(char), numbytes, infile);
    fclose(infile);

    return buffer;
}