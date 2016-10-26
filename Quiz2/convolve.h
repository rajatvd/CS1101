#ifndef CONVOLVE_H
#define CONVOLVE_H
#include<stdlib.h>
#include<math.h>
/**
  Interface for convolution operation.

Author: Rajat Vadiraj Dwaraknath EE16B033
Date: 18th October 2016

 */

// Puts the output of f convolved with g into fcg. 
void convolve(double *f, double *g, double *fcg, int lenF, int lenG);

// Puts a normalized gaussian from -halfWdith to halfWidth into out with n points. 
void getGaussian(double* out, double halfWidth, int n);

#endif
