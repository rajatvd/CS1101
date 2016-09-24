#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "rk.h"

/**
  Using the 4th order Runge Kutta Method to solve question 1(a).

Author: Rajat Vadiraj Dwaraknath
Date: 21st September 2016
 */

// Function which returns the derivative according to the differential equation
void f1(double x, double *y, double *m){
	m[0] = (-2*pow(x,3) + 12*pow(x,2) - 20*x + 8.5);
}


int main(){
	printf("# First function\n# x\t\ty\n");
	double y0[1] = {1};
	rk4(f1,y0,0,10,0.05,1);
}
