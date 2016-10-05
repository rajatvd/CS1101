#ifndef LEASTSQUARES_H
#define LEASTSQUARES_H
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

/**
  Interface or header for Least Squares linear regression 

Author: Rajat Vadiraj Dwaraknath
Date: 5th October 2016
 */

// Perform linear least squares regression on the data points given by x and y, and output the slope, intercept, and correlation coefficient into a.
void leastSquares(double *x, double *y, int n, double *a);

// Predict the value of y for some x given a regression line described using 'a'.
double predict(double x, double*a);

#endif
