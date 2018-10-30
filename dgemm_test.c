/* C source code is found in dgemm_example.c */

#define min(x,y) (((x) < (y)) ? (x) : (y))

#include <stdio.h>
#include <stdlib.h>
#include "mkl.h"

int main(int argc,char *argv[])
{
	if(argc<2)return 1;
	double *A, *B, *C;
	int m, n, k, i, j,a,b;
	double alpha, beta;
	double time_st,time_end,time_avg,gflop,gflops,sum = 0;
	int num = atoi(argv[1]);
	m = 12000, k = 12000, n = 12000;
	printf (" Initializing data for matrix multiplication C=A*B for matrix \n"
			" A(%ix%i) and matrix B(%ix%i)\n\n", m, k, k, n);
	alpha = 1.0; beta = 0.0;
	A = (double *)mkl_malloc( m*k*sizeof( double ), 64 );
	B = (double *)mkl_malloc( k*n*sizeof( double ), 64 );
	C = (double *)mkl_malloc( m*n*sizeof( double ), 64 );
	if (A == NULL || B == NULL || C == NULL) {
		printf( "\n ERROR: Can't allocate memory for matrices. Aborting... \n\n");
		mkl_free(A);
		mkl_free(B);
		mkl_free(C);
		return 1;
	}

	for (i = 0; i < (m*k); i++) {
		A[i] = (double)(i+1);
	}

	for (i = 0; i < (k*n); i++) {
		B[i] = (double)(-i-1);
	}

	for (i = 0; i < (m*n); i++) {
		C[i] = 0.0;
	}
	printf (" Computing matrix product using Intel(R) MKL dgemm function via CBLAS interface \n\n");
	gflop = (2.0*m*n*k)*1E-9;
	for(b=0;b<num;b++){
		time_st = dsecnd();
		cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m, n, k, alpha, A, k, B, n, beta, C, n);
		time_end = dsecnd();
		time_avg = time_end - time_st;
		gflops = gflop/time_avg;
		sum += gflops;
		printf("time_avg: %.8f secs       GFlops: %.5f\n",time_avg,gflops);
	}
	printf("age_gflops:%.5f\n",sum/num);
	mkl_free(A);
	mkl_free(B);
	mkl_free(C); 
	return 0;
}
