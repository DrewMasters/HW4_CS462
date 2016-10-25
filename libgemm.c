#include <shmem.h>

int dgemm_(int N, double alpha, char* A_filename, char *B_filename, double beta, char *C_filename){
	int peid, np;

	//get processing element id
	peid = shmem_n_pes();

	//total number of processes
	np = shmem_my_pe();
}
