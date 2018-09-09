#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include <list>
#include <vector>
#include <string>
#include "omp.h"
#include "mpi.h"

#define MAX_CORES_PER_NODE 64

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
    int maxNrThreads = omp_get_max_threads();
//    printf("Max cores: %d\n", maxNrThreads);

    /// Set number of threads.
    omp_set_num_threads(maxNrThreads);

    #pragma parallel for collapse(2)
	for(int real = 0; real < num; ++real){
		for(int img = 0; img < num; ++img){
			count += inset(real_lower + real * real_step, img_lower + img * img_step, maxiter);
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
	int maxiter;
	int num_regions = (argc-1)/6;
//	printf("Number of regions: %d\n", num_regions);

    /// OpenMPI
    int nrProc, idProc, nameLenght = 0;
    char nameNode[MPI_MAX_PROCESSOR_NAME] = {0};
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &nrProc);
    MPI_Comm_rank(MPI_COMM_WORLD, &idProc);
    MPI_Get_processor_name(nameNode, &nameLenght);

	int *allIdProc = (int*)calloc(nrProc, sizeof(int));
	char *allNameNode = (char*)calloc(nrProc, sizeof(nameNode));
	MPI_Gather(nameNode, MPI_MAX_PROCESSOR_NAME, MPI_CHAR, allNameNode, MPI_MAX_PROCESSOR_NAME, MPI_CHAR, 0, MPI_COMM_WORLD);
	MPI_Gather(&idProc, 1, MPI_INT, allIdProc, 1, MPI_INT, 0, MPI_COMM_WORLD);

    /// Index nodes and cores.
    if (idProc == 0) {

		std::vector<std::string> nodeNames;
		std::vector<int> nodeCores;

		for (int i = 0; i < nrProc; ++i) {
			nodeNames.push_back(std::string(&allNameNode[i * MPI_MAX_PROCESSOR_NAME]));
			if (!nodeNames.empty()) {
				nodeCores.push_back(allIdProc[i]);
			}
		}

		auto tmp = nodeNames;
		std::sort(nodeNames.begin(), nodeNames.end());
		auto lastIter = std::unique(nodeNames.begin(), nodeNames.end());
		nodeNames.erase(lastIter, nodeNames.end());

		std::vector<std::vector<int>> setCores;
		for (int i = 0; i < nodeNames.size(); ++i) {
			std::cout << "Node: " << nodeNames.at(i) << "Cores:";
			setCores.push_back(std::vector<int>());
			for (int j = 0; j < tmp.size(); ++j) {
				if (nodeNames.at(i).compare(tmp.at(j)) == 0) {
					setCores.at(i).push_back(nodeCores.at(j));
					std::cout << " " << setCores[i][j];
				}
			}
			std::cout << std::endl;
		}
    }

    /// Timing scope.
	double timeBegin, timeEnd;
    if (idProc == 0) {
		timeBegin = omp_get_wtime();
	}

	for(int region=0;region<num_regions;region++){
		if (idProc == region) {
//			printf("Processor id: %d\t",idProc);
			sscanf(argv[region*6+1],"%lf",&real_lower);
			sscanf(argv[region*6+2],"%lf",&real_upper);
			sscanf(argv[region*6+3],"%lf",&img_lower);
			sscanf(argv[region*6+4],"%lf",&img_upper);
			sscanf(argv[region*6+5],"%i",&num);
			sscanf(argv[region*6+6],"%i",&maxiter);
			printf("%d\n",mandelbrotSetCount(real_lower,real_upper,img_lower,img_upper,num,maxiter));
		}
	}

	///
	MPI_Finalize();

	/// Destruct dynamically allocated memory.
	free(allIdProc);
    free(allNameNode);

    /// Print execution time.
	if (idProc == 0) {
		timeEnd = omp_get_wtime();
		printf("%.16g\n", (timeEnd - timeBegin));
	}

	return EXIT_SUCCESS;
}
