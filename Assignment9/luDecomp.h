#ifndef LUDECOMP_H 
#define LUDECOMP_H
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define makeMatrix(a,n) a = (double**)malloc(sizeof(double*)*n);for(int i=0;i<n;i++){a[i] = (double*)malloc(sizeof(double)*n);}do{}while(0)

/**
Interface or header for LU Decomposition. 

Author: Rajat Vadiraj Dwaraknath
Date: 20th October 2016
 */

// Put the LU decomposition of a(assuming it is nxn) into l and u
void luDecomp(double **a, double **l, double **u, int n);

// Put the inverse matrix of a(assuming it is nxn) into aInv
void invert(double **a, double **aInv, int n);

// Print a nxn square matrix
void printMatrix(double **a, int n);

// Multiply two square nxn matrices
void matrixMultiply(double **a, double **b, double **c, int n);
#endif
