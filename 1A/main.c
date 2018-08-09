#include <stdio.h>
#include "omp.h"

int main() {
    printf("Hello, World!\n");
    printf("Max available threads: %d\n", omp_get_max_threads());
    return 0;
}