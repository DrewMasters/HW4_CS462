#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(int argc, char **argv){
	double *A;
	FILE *fr,*fb;
	int i,j,n;
	n = atoi(argv[1]);
	if (argc != 4){
		printf("./matrix_maker size byte_file_name human_file_name\n");
		exit(1);
	}
	A=(double *)malloc(sizeof(double)*n*n);
	srand(time(NULL));
	for (i=0;i<n*n;i++){
		A[i]=((double)rand()/(double)RAND_MAX)*100;
		printf("i: %d A: %f\n",i,A[i]);
	}
	for (i=0;i<n*n;i++) printf("A[%d]: %f\n",i,A[i]);
	
	for (i=0;i<n*n;i++){
		if (i%n==0&&i!=0) printf("\n");
		printf("%f ",A[i]);
	}	
	printf("\n");
	int tmpi;
	fb = fopen(argv[2],"wb");
	fwrite(A,sizeof(double),n*n,fb);
	fclose(fb);
	fr = fopen(argv[3],"w");
	for (i=0; i<n*n;i++){
		if (i%n==0)fprintf(fr,"\n");
		fprintf(fr, "%f ", A[i]);
	}
	fclose(fr);
}
