#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "rk.h"

/**
  Using the 4th order Adaptive Runge Kutta Method(Step - halving) to solve question 6.1.

Author: Rajat Vadiraj Dwaraknath
Date: 28th September 2016

 */

// Function which returns the derivative according to the differential equation
void f1(double x, double *y, double *m){
	m[0] = 4*exp(0.8*x)-0.5*y[0];
}

void f2(double x, double *y, double *m){
	m[0] = 10*exp(-pow(x-2,2)/2.0/pow(0.075,2)) - 0.6*y[0];
}

int main(){
	printf("# 6.1 Step halving method\n# Using one step:\n# x\t\ty\n");
	double y0[1] = {2};
	rk4(f1,y0,0,1,2,1);
	double oneStep = y0[0];

	printf("# Using two half steps:\n# x\t\ty\n");
	y0[0] = 2;
	rk4(f1,y0,0,2,1,1);
	double twoHalfSteps = y0[0];

	double error = twoHalfSteps - oneStep;
	twoHalfSteps += error/15.0;

	printf("# Corrected prediction = %lf\n\n# 6.2 Using Cash-Karp Method:\n# x\t\ty\n",twoHalfSteps);

	y0[0] = 2;
	rk45(f1,y0,0,1,1,0.00005,1);
	return 0;
}
