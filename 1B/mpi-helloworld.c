#include <stdio.h>
#include "mpi.h"

int main( argc, argv )
int  argc;
char **argv;
{
    int rank, size, nameLenght = 0;
    MPI_Init( &argc, &argv );
    char procName[MPI_MAX_PROCESSOR_NAME];

    MPI_Comm_size( MPI_COMM_WORLD, &size );
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Get_processor_name(procName, &nameLenght);

    printf( "%s: Hello world from process %d of %d\n", procName, rank, size );
    MPI_Finalize();
    return 0;
}

