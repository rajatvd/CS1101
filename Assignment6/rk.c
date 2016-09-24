#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "rk.h"

/**
Implementation of the 4th order Runge Kutta Method 

Author: Rajat Vadiraj Dwaraknath
Date: 21st September 2016
 */

// Generalized RK4 ode solver where sizeOfY is the order of the ode and f is the function which returns the derivative.
// y and x are initial conditions, n is the number of intervals and h is the stepsize.
void rk4(void (*f)(double, double*, double*), double *y, double x, int n, double h, int sizeOfY){
	// Dynamically allocate the arrays for each slope and a temporary array based on order of ode
	double *yTemp = (double*)malloc(sizeof(double)*sizeOfY);
	double *k1 = (double*)malloc(sizeof(double)*sizeOfY);
	double *k2 = (double*)malloc(sizeof(double)*sizeOfY);
	double *k3 = (double*)malloc(sizeof(double)*sizeOfY);
	double *k4 = (double*)malloc(sizeof(double)*sizeOfY);
	double m = 0; // Weighted average of slopes
	int i = 0, j = 0; // Iterators


	for(i = 0;i<=n;i++){
		// Print the value of x
		printf("%lf\t",x);

		// Print the value of each y
		for(j = 0;j<sizeOfY;j++){
			printf("%lf\t",y[j]);
		}
		printf("\n");
		
		// Find k1
		f(x,y,k1);

		// Find k2
		for(j = 0;j<sizeOfY;j++){
			yTemp[j] = y[j]+k1[j]*h*0.5;
		}
		f(x+h/2,yTemp,k2);

		// Find k3
		for(j = 0;j<sizeOfY;j++){
			yTemp[j] = y[j]+k2[j]*h*0.5;
		}

		// Find k4
		f(x+h/2,yTemp,k3);

		for(j = 0;j<sizeOfY;j++){
			yTemp[j] = y[j]+k3[j]*h;
		}
		f(x+h,yTemp,k4);
		
		// Find y_i+1
		for(j = 0;j<sizeOfY;j++){

			m = (k1[j]+2*k2[j]+2*k3[j]+k4[j])/6; // Weighted average of slopes
			y[j] = y[j]+m*h;
		}
		
		// Increment x
		x+=h;
	}
	
	// Free allocated memory
	free(k1);
	free(k2);
	free(k3);
	free(k4);
	free(yTemp);
}
