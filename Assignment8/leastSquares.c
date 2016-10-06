#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "leastSquares.h"

/**
  Implementation of Least-Squares Linear regression.

Author: Rajat Vadiraj Dwaraknath
Date: 5th October 2016
 */

// Perform linear least squares regression on the data points given by x and y, and output the slope, intercept, and correlation coefficient into a.
void leastSquares(double *x, double *y, int n, double *a){

	// variables for the sums
	double sumX = 0.0, sumY = 0.0, sumXY = 0.0, sumXSqr = 0.0, sumYSqr = 0.0;
	int i;

	// Calculate the sums
	for(i=0;i<n;i++){
		sumX += x[i];
		sumY += y[i];
		sumXY += x[i]*y[i];
		sumXSqr += x[i]*x[i];
		sumYSqr += y[i]*y[i];
	}

	// Calculate the slope, intercept, and correlation coefficient
	double a1 = (n*sumXY - sumX*sumY)/(n*sumXSqr - pow(sumX,2));
	double a0 = sumY/n - a1*sumX/n;
	double rsqr = (n*sumXY - sumX*sumY)/sqrt((n*sumXSqr - pow(sumX,2))*(n*sumYSqr - pow(sumY,2))); 	
	rsqr = pow(rsqr,2);

	// Put the values into the given pointer
	a[0] = a0;
	a[1] = a1;
	a[2] = rsqr;
}

// Predict the value of y for some x given a regression line described using 'a'.
double predict(double x, double *a){
	return a[0] + a[1]*x;
}
