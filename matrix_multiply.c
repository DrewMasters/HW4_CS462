#include <stdio.h>
#include <shmem.h>
#include <math.h>
#include <stdlib.h>
#include "libgemm.h"

int main(int argc, char **argv){
	int N;
	char *A, *B, *C;

	if (argc !=5){
		printf("Usage: oshrun -np #_processes matrix_multiply N A_filename B_filename C_filename\n");
		exit(1);
	}
	
	N = atoi(argv[1]);
	A=argv[2];
	B=argv[3];
	C=argv[4];

	/*
	 * Initialize openshemm
	 */
	start_pes(0);
	dgemm_(N, 1.0, A, B, 0.0, C);

	return 0;
}
