#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "rk.h"

/**
  Using the 4th order Runge Kutta Method to solve question 2.

Author: Rajat Vadiraj Dwaraknath
Date: 21st September 2016
 */

// Function which returns the derivative according to the differential equation
void f3(double x, double *y, double *m){
	m[0] = -0.5*y[0];
	m[1] = 4 - 0.3*y[1] - 0.1*y[0];
}


int main(){
	printf("# Third function\n# x\t\ty1\t\ty2\n");
	double y1[2] = {4,6};
	rk4(f3,y1,0,4,0.5,2);
}
