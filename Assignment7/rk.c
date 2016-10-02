#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "rk.h"

/**
  Implementation of the 4th order adaptive Runge Kutta Method with 5th order predictor-corrector.

Author: Rajat Vadiraj Dwaraknath
Date: 28th September 2016
 */

// Generalized RK4 ode solver where sizeOfY is the order of the ode and f is the function which returns the derivative.
// y and x are initial conditions, n is the number of intervals and h is the stepsize. The input pointer y will contain the final value
// of integration after completion of the function evaluation.
void rk4(void (*f)(double, double*, double*), double *y, double x, int n, double h, int sizeOfY){
	// Dynamically allocate the arrays for each slope and a temporary array based on order of ode
	double *yTemp = (double*)malloc(sizeof(double)*sizeOfY);
	double *k1 = (double*)malloc(sizeof(double)*sizeOfY);
	double *k2 = (double*)malloc(sizeof(double)*sizeOfY);
	double *k3 = (double*)malloc(sizeof(double)*sizeOfY);
	double *k4 = (double*)malloc(sizeof(double)*sizeOfY);
	double m = 0; // Weighted average of slopes
	int i = 0, j = 0; // Iterators

	// Printing initial conditions:
	// Print the value of x
	printf("%lf\t",x);

	// Print the value of each y
	for(j = 0;j<sizeOfY;j++){
		printf("%lf\t",y[j]);
	}
	printf("\n");

	for(i = 0;i<n;i++){

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
		f(x+h/2,yTemp,k3);

		// Find k4
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

		// Print the value of x
		printf("%lf\t",x);

		// Print the value of each y
		for(j = 0;j<sizeOfY;j++){
			printf("%lf\t",y[j]);
		}
		printf("\n");
	}

	// Free allocated memory
	free(k1);
	free(k2);
	free(k3);
	free(k4);
	free(yTemp);
}


double rk45Step(void (*f)(double, double*, double*), double *y, double x, double h, int sizeOfY){
	// Dynamically allocate the arrays for each slope and a temporary array based on order of ode
	double *yTemp = (double*)malloc(sizeof(double)*sizeOfY);
	double *k1 = (double*)malloc(sizeof(double)*sizeOfY);
	double *k2 = (double*)malloc(sizeof(double)*sizeOfY);
	double *k3 = (double*)malloc(sizeof(double)*sizeOfY);
	double *k4 = (double*)malloc(sizeof(double)*sizeOfY);
	double *k5 = (double*)malloc(sizeof(double)*sizeOfY);
	double *k6 = (double*)malloc(sizeof(double)*sizeOfY);
	double m4 = 0, m5 = 0, error = 0; // Weighted average of slopes for different order methods
	int j = 0;

	// Find k1
	f(x,y,k1);

	// Find k2
	for(j = 0;j<sizeOfY;j++){
		yTemp[j] = y[j] + k1[j]*h*1.0/5;
	}
	f(x+h*1.0/5,yTemp,k2);

	// Find k3
	for(j = 0;j<sizeOfY;j++){
		yTemp[j] = y[j] + k1[j]*h*3.0/40 + k2[j]*h*9.0/40;
	}
	f(x+3.0/10*h,yTemp,k3);

	// Find k4
	for(j = 0;j<sizeOfY;j++){
		yTemp[j] = y[j] + k1[j]*h*3.0/10 + k2[j]*h*-9.0/10 + k3[j]*h*6.0/5;
	}
	f(x+h*3.0/5,yTemp,k4);

	// Find k5
	for(j = 0;j<sizeOfY;j++){
		yTemp[j] = y[j] + k1[j]*h*-11.0/54 + k2[j]*h*5.0/2 + k3[j]*h*-70.0/27 + k4[j]*h*35.0/27;
	}
	f(x+h,yTemp,k5);

	// Find k6
	for(j = 0;j<sizeOfY;j++){
		yTemp[j] = y[j] + k1[j]*h*1631.0/55296 + k2[j]*h*175.0/512 + k3[j]*h*575.0/13824 + k4[j]*h*44275.0/110592 + k5[j]*h*253.0/4096;
	}
	f(x+h*7.0/8,yTemp,k6);

	// Find y_i+1
	for(j = 0;j<sizeOfY;j++){

		m4 = k1[j]*37.0/378 + k3[j]*250.0/621 + k4[j]*125.0/594 + k6[j]*512.0/1771; // Weighted average of slopes for fourth order
		m5 =  k1[j]*2825.0/27648 + k3[j]*18575.0/48384 + k4[j]*13525.0/55296 + k5[j]*277.0/14336 + k6[j]*1.0/4; // Weighted average of slopes for fifth order
		y[j] = y[j]+m4*h; // Update state variable
		error += fabs(m4*h - m5*h); // Calculate truncation error using fifth order method
	}

	error /= sizeOfY;
	free(k1);
	free(k2);
	free(k3);
	free(k4);
	free(k5);
	free(k6);
	free(yTemp);
	return error;
}

// Generalized RK45 ode solver where sizeOfY is the order of the ode and f is the function which returns the derivative.
// y and x are initial conditions, xEnd is final value of x to which integration should be done, h is the initial stepsize, and tolerance is the desired relative error.
// The input pointer y will contain the final value of integration after completion of the function evaluation.
void rk45(void (*f)(double, double*, double*), double *y, double x, double xEnd, double h, double tolerance, int sizeOfY){
	double error = 0, errorDesired = 0;
	int j = 0;
	double *m = (double*)malloc(sizeof(double)*sizeOfY);

	// Print initial values
	// Print the value of x
	printf("%lf\t",x);

	// Print the value of each y
	for(j = 0;j<sizeOfY;j++){
		printf("%lf\t",y[j]);
	}
	printf("\n");


	// Driver loop
	while(x<xEnd){
		if(xEnd-x<h){
			// Checking if this should be the last step or not
			h = xEnd-x;
		}
		error = rk45Step(f,y,x,h,sizeOfY);
		// Move by the stepsize

		// Choosing y_scale based on number of dependent variables
		if(sizeOfY == 1){
			f(x,y,m);
			errorDesired = tolerance*(fabs(y[0]) + fabs(m[0]*h));
		}else{
			errorDesired = tolerance;
		}
		// Adapting step size based on lesser or more error than that which is desired
		x+=h;
		if(error <= errorDesired){
			h *= pow(errorDesired/error, 0.2);
		}else{
			h *= pow(errorDesired/error, 0.25);
		}
		// Print the value of x
		printf("%lf\t",x);

		// Print the value of each y
		for(j = 0;j<sizeOfY;j++){
			printf("%lf\t",y[j]);
		}
		printf("\n");
	}
}
