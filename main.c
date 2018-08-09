#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "omp.h"

#define inputBufferSize 1000000


char *readFile(char *const *argv, const FILE *fp, char *buf, char string[1000000]);

int main(int argc, char *argv[] ) {
//    printf("Hello, World!\n");
//    printf("Max available threads: %d\n", omp_get_max_threads());

    // if argv[1] not given, exit
    if (argc != 2)
    {
        fprintf(stderr,
                "Usage: %s <input-file>\n", argv[0]);
        return 1;
    }


    FILE* fp;
    char buf[inputBufferSize];

    readFile(argc, argv, fp, buf);



    return 0;
}




char *readFile(char *const *argv, const FILE *fp, char *buf, char string[1000000]) {
    if ((fp = fopen(argv[1], "r")) == NULL)
    { /* Open source file. */
        perror("fopen source-file");
        return 1;
    }

    while (fgets(buf, sizeof(buf), fp) != NULL)
    {
        buf[strlen(buf) - 1] = '\0'; // eat the newline fgets() stores
        printf("%s\n", buf);
    }
    fclose(fp);

    return buf;
}