#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
	FILE *f;
	int n, i, j;
	double *A;

	if (argc!=3){
		printf("Usage: ./matrix_reader size file_name\n");
		exit(1);
	}
	n=atoi(argv[1]);
	A=(double *)malloc(sizeof(double)*n*n);
	f = fopen(argv[2],"rb");
	
	fread(A,sizeof(double),n*n,f);
	fclose(f);

	int tmpi;
	for (i=0;i<n*n;i++){
		if(i%n==0&&i!=0)printf("\n");
		printf("%f ", A[i]);
	}
	printf("\n");
}
