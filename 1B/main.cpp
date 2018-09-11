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

// count the number of points in the set, within the region
int mandelbrotSetCount(double real_lower, double real_upper, double img_lower, double img_upper, int num, int maxiter){
	int count=0;
	double real_step = (real_upper-real_lower)/num;
	double img_step = (img_upper-img_lower)/num;

	/// OpenMP
//    int maxNrThreads = omp_get_max_threads();
//    printf("Max cores: %d\n", maxNrThreads);

    /// Set number of threads.
//    omp_set_num_threads(maxNrThreads);

//    #pragma omp parallel for collapse(2)
	for(int real = 0; real < num; ++real){
		for(int img = 0; img < num; ++img){
			count += inset(real_lower + real * real_step, img_lower + img * img_step, maxiter);
		}
	}
	return count;
}

void mandelbrotSetCount(double real_lower, double real_upper, double img_lower, double img_upper, int num, int maxiter, int idProcces, int nrProccesses){
    double real_step = (real_upper-real_lower)/num;
    double img_step = (img_upper-img_lower)/num;
    int result = 0, count = 0;
    int chunkSize = num / nrProccesses;

    printf("procid: %d, nrOfProcs: %d\n", idProcces, nrProccesses);


    //    int nrProccesses, idProcces, nameLenght = 0;


    /// MPI Scatter realStart and realEnd such that each processor has about the same number

//    int count=0;
//    for(int real = 0; real < num; ++real){
//        for(int img = 0; img < num; ++img){
//            count += inset(real_lower + real * real_step, img_lower + img * img_step, maxiter);
//        }
//    }

    /// MPI Gather the all the counts into result



    /// have processor with id 0 print the result
    if (idProcces == 0) {
        printf("result: %d\n", result);
    }


    return;
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

        MPI_Barrier(MPI_COMM_WORLD); // todo: remove later
        if (idProcces == 0) {
            printf("Barrier!\n");
        }
    }

	///
	MPI_Finalize();

	/// Destruct dynamically allocated memory.
//	free(allProcessIds);
//    free(allNodeNames);

	return EXIT_SUCCESS;
}
