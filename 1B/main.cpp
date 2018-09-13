#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include <list>
#include <array>
#include <vector>
#include <string>
#include "mpi.h"


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
int mandelbrotSetCount(double real_lower, double real_upper, double img_lower, double img_upper, int num, int maxiter, int idProcess, int nrProcesses){
	double real_step = (real_upper - real_lower) / num;
	double img_step = (img_upper - img_lower) / num;

    int local_count = 0;
    int chunkSize = num / nrProcesses;
    if (chunkSize == 0) { // if there are more processors than number of loop iterations
        chunkSize = 1;
    }

    int real = idProcess * chunkSize;
    int real_end = idProcess * chunkSize + chunkSize;
    if (idProcess == nrProcesses-1) { // to make pretty sure that nothing has been missed
        real_end = num;
    }

    for(; real < real_end; ++real){
        for (int img = 0; img < num; ++img) {
            double tmp_img = img_lower + img * img_step;
            double tmp_real = real_lower + real * real_step;
            double z_real = tmp_real;
            double z_img = tmp_img;
            for(int iters = 0; iters < maxiter; iters++){
                double z2_real = z_real*z_real-z_img*z_img;
                double z2_img = 2.0*z_real*z_img;
                z_real = z2_real + tmp_real;
                z_img = z2_img + tmp_img;
                if(z_real*z_real + z_img*z_img > 4.0)
                    goto break1;
            }
            local_count++;
            break1:;
        }
    }

    int global_count = 0;
    MPI_Reduce(&local_count, &global_count,1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    /// print result
    if (idProcess == 0) {
        printf("%d\n", global_count);
    }
}

// main
int main(int argc, char *argv[]){
	double real_lower;
	double real_upper;
	double img_lower;
	double img_upper;
	int num;
	int maxIter;
	int nrRegions = (argc-1)/6;

    /// OpenMPI
    int root = 0;
    int nrProcesses, idProcess;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &nrProcesses);
    MPI_Comm_rank(MPI_COMM_WORLD, &idProcess);

    for(int region=0; region<nrRegions; region++) {
        sscanf(argv[region * 6 + 1], "%lf", &real_lower);
        sscanf(argv[region * 6 + 2], "%lf", &real_upper);
        sscanf(argv[region * 6 + 3], "%lf", &img_lower);
        sscanf(argv[region * 6 + 4], "%lf", &img_upper);
        sscanf(argv[region * 6 + 5], "%i", &num);
        sscanf(argv[region * 6 + 6], "%i", &maxIter);

        mandelbrotSetCount(real_lower, real_upper, img_lower, img_upper, num, maxIter, idProcess, nrProcesses);
    }

	///
	MPI_Finalize();

	return EXIT_SUCCESS;
}
