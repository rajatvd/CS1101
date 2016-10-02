#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "rk.h"

/**
  Using the 4th order  Cash-Karp Adaptive Runge Kutta Method to solve question 6.3.

Author: Rajat Vadiraj Dwaraknath
Date: 28th September 2016

 */

// Function which returns the derivative according to the differential equation
void f2(double x, double *y, double *m){
	m[0] = 10*exp(-pow(x-2,2)/2.0/pow(0.075,2)) - 0.6*y[0];
}

int main(){
	// Answer displayed:
	printf("# 6.3 Using Cash-Karp Method:\n# x\t\ty\n");
	double y0[1] = {0.5};
	rk45(f2,y0,0,4,0.5,0.0000001,1); // Using tolerance of 10^-7

	return 0;
}
