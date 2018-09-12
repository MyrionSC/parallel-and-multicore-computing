#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include <list>
#include <array>
#include <vector>
#include <string>
//#include "omp.h"
#include "mpi.h"

//#define DEBUG

// count the number of points in the set, within the region
int mandelbrotSetCount(double real_lower, double real_upper, double img_lower, double img_upper, int num, int maxiter, int idProcess, int nrProcesses){
	int count=0;
	double real_step = (real_upper - real_lower) / num;
	double img_step = (img_upper - img_lower) / num;

    for (int real = 0; real < num; real += nrProcesses) {
        /// Precalculation.
        double tmpReal = real_lower + (real + idProcess) * real_step;
        for (int img = 0; img < num; ++img) {
            double tmpImg = img_lower + img * img_step;
            double z_real = tmpReal;
            double z_img = tmpImg;
            double z2_real, z2_img;

            for(int iters = 0; iters < maxiter; iters++){
                z2_real = z_real * z_real - z_img * z_img;
                z2_img = 2.0 * z_real * z_img;
                z_real = z2_real + tmpReal;
                z_img = z2_img + tmpImg;

                if(z_real * z_real + z_img * z_img > 4.0)
                    goto break1;
            }
            count++;
            break1:;
        }
    }

    return count;
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
    int nrProcesses, idProcces;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &nrProcesses);
    MPI_Comm_rank(MPI_COMM_WORLD, &idProcces);

    for(int region=0; region<nrRegions; region++) {
        sscanf(argv[region * 6 + 1], "%lf", &real_lower);
        sscanf(argv[region * 6 + 2], "%lf", &real_upper);
        sscanf(argv[region * 6 + 3], "%lf", &img_lower);
        sscanf(argv[region * 6 + 4], "%lf", &img_upper);
        sscanf(argv[region * 6 + 5], "%i", &num);
        sscanf(argv[region * 6 + 6], "%i", &maxIter);

        int localCount = mandelbrotSetCount(real_lower, real_upper, img_lower, img_upper, num, maxIter, idProcces, nrProcesses);
        int globalCount = 0;
        MPI_Reduce(&localCount, &globalCount,1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

        /// Root prints result.
        if (idProcces == root)
            printf("%d\n", globalCount);
	}

	///
	MPI_Finalize();

	return EXIT_SUCCESS;
}
