/*

This program will numerically compute the integral of

                  4/(1+x*x) 
				  
from 0 to 1. 
				 
History: Written by Tim Mattson, 11/99.

#-----------------------------------------------------

Modified by JGG 

#--------------------------------------------------------

*/

#include <stdio.h>
#include <omp.h>

static long num_steps = 800000000;
double step;
int main()
{
	int i, nprocs;
	double pi, sum = 0.0;
	double start_time, run_time;

	step = 1.0/(double) num_steps;

	/*start timer */
	start_time = omp_get_wtime();
	
	// Se establece este pragma para paralelizar el loop
	#pragma omp parallel for reduction(+:sum)
	for (i=1;i<= num_steps; i++){
		double x = (i-0.5)*step;  // Variable local del hilo
		double tmp = 4.0/(1.0+x*x); // Variable local del hilo
		sum += tmp; // Variable compartida entre hilos
	}
	
	pi = step * sum;
	run_time = omp_get_wtime() - start_time;
	printf("\n pi is %f in %f seconds \n",pi,run_time);
	
}


