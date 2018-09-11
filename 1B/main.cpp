#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include <list>
#include <array>
#include <vector>
#include <string>
#include "omp.h"
#include "mpi.h"

#define DEBUG

// return 1 if in set, 0 otherwise
int inset(double real, double img, int maxiter){
	double z_real = real;
	double z_img = img;
	for(int iters = 0; iters < maxiter; iters++){
		double z2_real = z_real*z_real-z_img*z_img;
		double z2_img = 2.0*z_real*z_img;
		z_real = z2_real + real;
		z_img = z2_img + img;
		if(z_real*z_real + z_img*z_img > 4.0) return 0;
	}
	return 1;
}

void mandelbrotSetCount(double real_lower, double real_upper, double img_lower, double img_upper, int num, int maxiter, int idProcces, int nrProccesses){
    double real_step = (real_upper-real_lower)/num;
    double img_step = (img_upper-img_lower)/num;
    int count[1] = {0};

    int chunkSize = num / nrProccesses;
    if (chunkSize == 0) { // if there are more processors than number of loop iterations
        chunkSize = 1;
    }

    int real = idProcces * chunkSize;
    int real_end = idProcces * chunkSize + chunkSize;
    if (idProcces == nrProccesses-1) { // to make pretty sure that nothing has been missed
        real_end = num;
    }

//    if (idProcces == 0) {
//        printf("chunksize: %d\n", chunkSize);
//        printf("nrOfProcs: %d\n", nrProccesses);
//    }
//    printf("procid: %d, count: %d\n", idProcces, count[0]);


    for(; real < real_end; ++real){
        for(int img = 0; img < num; ++img){
            count[0] += inset(real_lower + real * real_step, img_lower + img * img_step, maxiter);
        }
    }

    /// MPI Gather all the counts to proc 0
    int* resultsbuffer = NULL;
    if (idProcces == 0) {
        resultsbuffer = (int*)malloc(sizeof(int) * nrProccesses);
    }
    MPI_Gather( count, 1, MPI_INT, resultsbuffer, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (idProcces == 0) {
        int result = 0;
        for (int i = 0; i < nrProccesses; i++) {
//            printf("count: %d\n", resultsbuffer[i]);
            result += resultsbuffer[i];
        }
        printf("result: %d\n", result);
        free(resultsbuffer);
    }
}

// main
int main(int argc, char *argv[]){
	double real_lower;
	double real_upper;
	double img_lower;
	double img_upper;
	int num;
	int maxiter;
	int nrRegions = (argc-1)/6;
//	printf("Number of regions: %d\n", nrRegions);

    /// OpenMPI
    int nrProccesses, idProcces;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &nrProccesses);
    MPI_Comm_rank(MPI_COMM_WORLD, &idProcces);

    for(int region=0;region<nrRegions;region++) {
        sscanf(argv[region*6+1],"%lf",&real_lower);
        sscanf(argv[region*6+2],"%lf",&real_upper);
        sscanf(argv[region*6+3],"%lf",&img_lower);
        sscanf(argv[region*6+4],"%lf",&img_upper);
        sscanf(argv[region*6+5],"%i",&num);
        sscanf(argv[region*6+6],"%i",&maxiter);
        mandelbrotSetCount(real_lower,real_upper,img_lower,img_upper,num,maxiter, idProcces, nrProccesses);
    }

	MPI_Finalize();

	return EXIT_SUCCESS;
}
