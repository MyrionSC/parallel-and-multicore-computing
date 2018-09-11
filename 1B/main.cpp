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

//#define DEBUG

// return 1 if in set, 0 otherwise
int inset(double real, double img, int maxiter){
	double z_real = real;
	double z_img = img;
    double z2_real;
    double z2_img;

	for(int iters = 0; iters < maxiter; iters++){
		z2_real = z_real * z_real - z_img * z_img;
        z2_img = 2.0 * z_real * z_img;
		z_real = z2_real + real;
		z_img = z2_img + img;
		if(z_real * z_real + z_img * z_img > 4.0) return 0;
	}
	return 1;
}

// count the number of points in the set, within the region
int mandelbrotSetCount(double real_lower, double real_upper, double img_lower, double img_upper, int num, int maxiter, int idProcess, int nrProcesses){
	int count=0;
	double real_step = (real_upper-real_lower)/num;
	double img_step = (img_upper-img_lower)/num;

    for (int real = 0; real < num; real += nrProcesses) {

        /// Precalculation.
        double tmpReal = real_lower + (real + idProcess) * real_step;

        /// Unrolling
        for (int img = 0; img < num; img += 4) {
            count += inset(tmpReal, img_lower + img * img_step, maxiter);
            count += inset(tmpReal, img_lower + (img + 1) * img_step, maxiter);
            count += inset(tmpReal, img_lower + (img + 2) * img_step, maxiter);
            count += inset(tmpReal, img_lower + (img + 3) * img_step, maxiter);
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
	int nrRegions = (argc-1)/6;

    /// OpenMPI
    int root = 0;
    int nrProcesses, idProcces, nameLenght = 0;
    char nameNode[MPI_MAX_PROCESSOR_NAME] = {0};
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &nrProcesses);
    MPI_Comm_rank(MPI_COMM_WORLD, &idProcces);
    MPI_Get_processor_name(nameNode, &nameLenght);

	int *allProcessIds = (int*)calloc(nrProcesses, sizeof(int));
	char *allNodeNames = (char*)calloc(nrProcesses, sizeof(nameNode));
	MPI_Gather(nameNode, MPI_MAX_PROCESSOR_NAME, MPI_CHAR, allNodeNames, MPI_MAX_PROCESSOR_NAME, MPI_CHAR, root, MPI_COMM_WORLD);
	MPI_Gather(&idProcces, 1, MPI_INT, allProcessIds, 1, MPI_INT, root, MPI_COMM_WORLD);

#ifdef DEBUG
    /// Index nodes and cores.
    std::vector<std::string> vNodeNames;
    std::vector<std::vector<int>> vNodeProcesses;
    std::vector<int> vNodeIds;

    /// Only executed by root process!
    if (idProcces == root) {
        std::vector<int> allProcesses;

		for (int i = 0; i < nrProcesses; ++i) {
			vNodeNames.push_back(std::string(&allNodeNames[i * MPI_MAX_PROCESSOR_NAME]));
			if (!vNodeNames.empty()) {
                allProcesses.push_back(allProcessIds[i]);
			}
		}

		auto tmp = vNodeNames;
		std::sort(vNodeNames.begin(), vNodeNames.end());
		auto lastIter = std::unique(vNodeNames.begin(), vNodeNames.end());
		vNodeNames.erase(lastIter, vNodeNames.end());

		for (int i = 0; i < vNodeNames.size(); ++i) {
            vNodeIds.push_back(i);
            vNodeProcesses.push_back(std::vector<int>());
            std::vector<int> setCores;
            for (int j = 0; j < tmp.size(); ++j) {
                if (vNodeNames.at(i).compare(tmp.at(j)) == 0) {
                    vNodeProcesses.at(i).push_back(allProcesses.at(j));
                }
            }
        }
    }

    if (idProcces == root) {
        for (int k = 0; k < vNodeIds.size(); ++k) {
            std::cout << "Node: " << vNodeIds.at(k) << "\t" << "Max thread: " << omp_get_max_threads() << "\t" << "Processes: ";
            for (int i = 0; i < vNodeProcesses.at(k).size(); ++i) {
                std::cout << " " << vNodeProcesses[k][i];
            }
            std::cout << std::endl;
        }
    }
#endif

    /// Wait for all processes.
    MPI_Barrier(MPI_COMM_WORLD);

    for(int region=0; region<nrRegions; region++) {
        sscanf(argv[region*6+1],"%lf",&real_lower);
        sscanf(argv[region*6+2],"%lf",&real_upper);
        sscanf(argv[region*6+3],"%lf",&img_lower);
        sscanf(argv[region*6+4],"%lf",&img_upper);
        sscanf(argv[region*6+5],"%i",&num);
        sscanf(argv[region*6+6],"%i",&maxiter);
        int localCount = mandelbrotSetCount(real_lower, real_upper, img_lower, img_upper, num, maxiter, idProcces, nrProcesses);
        int globalCount = 0;
        MPI_Reduce(&localCount, &globalCount,1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

        /// Root prints result.
        if (idProcces == root)
            printf("Result %d\n", globalCount);
	}

	///
	MPI_Finalize();

	/// Destruct dynamically allocated memory.
	free(allProcessIds);
    free(allNodeNames);

	return EXIT_SUCCESS;
}
