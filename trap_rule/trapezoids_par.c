// Ernesto Ulate Ramirez - 2014092260
// COMPILE: gcc trapezoids_par.c -o trap_rule_par -fopenmp
// EXECUTE: ./trap_rule_par

#include <stdio.h>
#include <omp.h>

const double pi = 3.141592653589793238462643383079;

/* FUCTION TO INTEGRATE */
double f(double x) {
   double val = 100/(100+x+2*x*x);
   return val;
}

/* TRAPEZOID RULE */
double Trap(double a, double b, int n, double h) {
   double result;
   int i;

   result = (f(a) + f(b))/2.0;
   
   #pragma omp parallel for reduction(+:result)
   for (i = 1; i <= n-1; i++) {
     result += f(a+i*h);
   }
   result = result*h;

   return result;
}

int main(int argc, char* argv[]) {
    double start_time, run_time;
    double  integral;   /* Store result in integral   */
    double  a, b;       /* Left and right endpoints   */
    int     n;          /* Number of trapezoids       */
    double  h;          /* Height of trapezoids       */

    a = 0;
    b = 10;
    n = 900000000;

    h = (b-a)/n;

    start_time = omp_get_wtime();
    integral = Trap(a, b, n, h);
    run_time = omp_get_wtime() - start_time;

    printf("Integral from %f to %f = %.15f\n", a, b, integral);
    printf("in %f seconds \n", run_time);

    return 0;
}