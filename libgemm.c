#include <shmem.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "libgemm.h"

int dgemm_(int N, double alpha, char* A_filename, char *B_filename, double beta, char *C_filename){
	int peid, P, NB, dP, i, j, x=0;
	double *A, *B, *C;
	long pSync[_SHMEM_BCAST_SYNC_SIZE];

	for (i=0; i < _SHMEM_BCAST_SYNC_SIZE; i++){
		pSync[i]=_SHMEM_SYNC_VALUE;
	}

	if (peid==0) printf("N: %d A: %s B: %s C: %s\n",N,A_filename,B_filename,C_filename);
	
	shmem_barrier_all();
	A = (double *)shmalloc(sizeof(double)*N*N);
	B = (double *)shmalloc(sizeof(double)*N*N);
	C = (double *)shmalloc(sizeof(double)*N*N);
	shmem_barrier_all();

	//total number of processes
	P = shmem_n_pes();
	//dimensions of processor grid
	dP = (int)sqrt(P);
	//dimensions of data elements per process
	NB = N/dP;

	//get processing element id
	peid = shmem_my_pe();

	//printf("peid: %d np: %d P: %d NB: %d N: %d\n",peid,P, dP, NB, N);

	if (peid == 0){
		//read in matrix A, B, and C
		read_matrix(A,A_filename,N);
		read_matrix(B,B_filename,N);
		read_matrix(C,C_filename,N);
	}

	shmem_barrier_all();
	shmem_broadcast64(A,A,N*N,0,0,0,P, pSync);
	shmem_broadcast64(B,B,N*N,0,0,0,P, pSync);
	shmem_broadcast64(C,C,N*N,0,0,0,P, pSync);
	shmem_barrier_all();

	for (i=0; i < N*N; i++){
		if ((i/N)/NB!=0) x=1;
		//printf("i: %d row: %d col: %d pr: %d pc: %d process: %d\n",i,i/N,i%N,(i/N)/NB,(i%N)%NB,(i/N)/NB+(i%N)/NB+x);
		if (peid == (i/N)/NB+(i%N)/NB+x){
			//printf("peid: %d i: %d\n",peid, i);
			dot_product(A,B,C,alpha,beta,N,i/N,i%N);
			shmem_double_put(C+i,C+i,1,0);
		}
	}

	if (peid==0){
		write_matrix(C, C_filename, N);
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

void write_matrix(double *X, char *n, int N){
	FILE *f;
	f=fopen(n,"wb");
	fwrite(X,sizeof(double),N*N,f);
	fclose(f);
	return;
}

void print_array(double *t, int N, char *name){
	int i;
	printf("%s\n",name);
	for (i=0; i<N*N; i++){
		printf("i: %d val: %f\n",i,t[i]);
	}
	return;
}

void dot_product(double *A, double *B, double *C, double alpha, double beta, int N, int r, int c){
	int i;
	double sum=0;
	for (i=0; i < N; i++){
		//printf("r: %d c: %d i: %d A: %f B: %f\n",r,c,i,A[r*N+i],B[i*N+c]);
		sum=A[r*N+i]*B[i*N+c]+sum;
	}
	sum = sum*alpha;
	//printf("r: %d c: %d sum: %f prevC: %f updatedC: %f\n",r,c,sum,C[r*N+c],sum+(beta*C[r*N+c]));
	C[r*N+c]=sum+(beta*C[r*N+c]);
}
