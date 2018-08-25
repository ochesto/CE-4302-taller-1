// Ernesto Ulate Ramirez - 2014092260
// COMPILE: gcc saxpy_par.c -o saxpy_par -fopenmp
// EXECUTE: ./saxpy_par

#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

#define SIZE_VECTOR_1 10
#define SIZE_VECTOR_2 1000
#define SIZE_VECTOR_3 100000

void saxpy( int n, float a, float* restrict x, float* restrict y )
{   
    #pragma omp parallel for
    for( int i=0; i<n; ++i ){
        y[i] = a*x[i] + y[i];
    }
}

int main()
{
	float start_time, run_time;
    omp_set_num_threads(64);

    float vector_1x[SIZE_VECTOR_1];
    float vector_2x[SIZE_VECTOR_2];
    float vector_3x[SIZE_VECTOR_3];

    float vector_1y[SIZE_VECTOR_1];
    float vector_2y[SIZE_VECTOR_2];
    float vector_3y[SIZE_VECTOR_3];

    /* FILL VECTORS */
    srand(time(NULL));
    
    for(int i=0; i<SIZE_VECTOR_2; ++i) {
        vector_2x[i] = rand();
        vector_2y[i] = rand();
    }
    for(int i=0; i<SIZE_VECTOR_3; ++i) {
        vector_3x[i] = rand();
        vector_3y[i] = rand();
    }
    for(int i=0; i<SIZE_VECTOR_1; ++i) {
        vector_1x[i] = rand();
        vector_1y[i] = rand();
    }

    /* PRIMER TAMANO DE VECTOR */
	/*start timer */
	start_time = omp_get_wtime();

    saxpy( SIZE_VECTOR_1, 150.0, vector_1x, vector_1y );

	run_time = omp_get_wtime() - start_time;
	printf("\n saxpy size %d in %f seconds \n", SIZE_VECTOR_1, run_time);

    /* SEGUNDO TAMANO DE VECTOR */
    /*start timer */
	start_time = omp_get_wtime();

    saxpy( SIZE_VECTOR_2, 150.0, vector_2x, vector_2y );

	run_time = omp_get_wtime() - start_time;
	printf("\n saxpy size %d in %f seconds \n", SIZE_VECTOR_2, run_time);

    /* TERCER TAMANO DE VECTOR */
    /*start timer */
	start_time = omp_get_wtime();

    saxpy( SIZE_VECTOR_3, 150.0, vector_3x, vector_3y );

	run_time = omp_get_wtime() - start_time;
	printf("\n saxpy size %d in %f seconds \n", SIZE_VECTOR_3, run_time);
	
}

