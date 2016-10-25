#include <stdio.h>
#include <shmem.h>
#include <math.h>
#include <stdlib.h>
#include "libgemm.h"

int main(int argc, char **argv){
	int N;

	if (argc !=2){
		printf("Usage: oshrun -np #_processes matrix_multiply N\n");
		exit(1);
	}
	
	N = atoi(argv[1]);

	/*
	 * Initialize openshemm
	 */
	start_pes(0);


	return 0;
}
