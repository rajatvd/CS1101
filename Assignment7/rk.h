#ifndef RK_H
#define RK_h
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

/**
Interface or header for the 4th order Runge Kutta Method 

Author: Rajat Vadiraj Dwaraknath
Date: 21st September 2016
 */

// Generalized RK4 ode solver where sizeOfY is the order of the ode and f is the function which returns the derivative.
// y and x are initial conditions, n is the number of intervals and h is the stepsize.
void rk4(void (*f)(double, double*, double*), double *y, double x, int n, double h, int sizeOfY);
double rk45Step(void (*f)(double, double*, double*), double *y, double x, double h, int sizeOfY);
void rk45(void (*f)(double, double*, double*), double *y, double x, double xEnd, double h, double tolerance, int sizeOfY);
#endif
