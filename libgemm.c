#include <shmem.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "libgemm.h"

int dgemm_(int N, double alpha, char* A_filename, char *B_filename, double beta, char *C_filename){
	int peid, P, NB, dP;
	double *A, *B, *C;

	printf("N: %d A: %s B: %s C: %s\n",N,A_filename,B_filename,C_filename);
	
	shmem_barrier_all();
	A = (double *)shmalloc(sizeof(double)*N*N);
	B = (double *)shmalloc(sizeof(double)*N*N);
	C = (double *)shmalloc(sizeof(double)*N*N);
	shmem_barrier_all();

	//total number of processes
	P = shmem_n_pes();
	dP = (int)sqrt(P);

	//get processing element id
	peid = shmem_my_pe();

	printf("peid: %d np: %d\n",peid,P);

	if (peid == 0){
		read_matrix(A,A_filename,N);
		read_matrix(B,B_filename,N);
		print_array(A,N,A_filename);
		print_array(B,N,B_filename);
	}

	return 1;
}

void read_matrix(double *X, char *n, int N){
	FILE *f;
	f = fopen(n,"rb");
	fread(X,sizeof(double),N*N,f);
	fclose(f);
	return;
}

void print_array(double *t, int N, char *name){
	int i;
	printf("%s\n",name);
	for (i=0; i<N*N; i++){
		printf("i: %d val: %f\n",i,t[i]);
	}
}
