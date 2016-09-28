#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "rk.h"

/**
  Using the 4th order Runge Kutta Method to solve question 1(b).

Author: Rajat Vadiraj Dwaraknath
Date: 21st September 2016
 */

// Function which returns the derivative according to the differential equation
void f2(double x, double *y, double *m){
	m[0] = (4*exp(0.8*x) - 0.5*y[0]);
}


int main(){
	printf("# Second function\n# x\t\ty\n");
	double  y0[1] = {2};
	rk4(f2,y0,0,10,0.05,1);
	return 0;
}
