int dgemm_(int N, double alpha, char *A_filename, char *B_filename, double beta, char *C_filename);
void read_matrix(double *X, char *n, int N);
void write_matrix(double *X, char *n, int N);
void print_array(double *t,int N, char *name);
void dot_product(double *A, double *B, double *C, double alpha, double beta, int N, int r, int c);
