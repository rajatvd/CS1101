#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "luDecomp.h"

/**
  Solvnig assignment 9.

Author: Rajat Vadiraj Dwaraknath
Date: 27th October 2016

 */

int main(int argc, char **argv){
	// Accepting filename
	if(argc!=2){
		printf("Invalid input. Usage: %s <input file path>\n", argv[0]);
		return 0;
	}

	char *buff;
	buff = (char*)malloc(sizeof(char)*255);
	int n = 0;

	FILE *infile;
	infile = fopen(argv[1],"r");

	// Get number of lines, and size of matrix
	while(fgets(buff,255,infile)){
		n++;
	}

	// Initialize matrices
	double **a, **l, **u, **aInv, **lu,  *b, *x;
	makeMatrix(a,n);
	makeMatrix(l,n);
	makeMatrix(u,n);
	makeMatrix(aInv,n);
	makeMatrix(lu,n);

	// Initialize vectors
	b = (double*)(malloc(sizeof(double)*n));
	x = (double*)(malloc(sizeof(double)*n));

	fclose(infile);
	infile = fopen(argv[1],"r");

	// Get data
	int i=0,j=0;
	while(fgets(buff,255,infile)){
		j=0;
		while(j<n && sscanf(buff,"%lf",&a[i][j]) == 1){
			while(buff[0]!=' ')buff++;
			buff++;
			j++;
		}
		// Last column is values of b
		sscanf(buff,"%lf",&b[i]); 
		i++;
	}

	// Tolerance for considering zero
	double t = 1e-4;

	// Use the functions defined in luDecomp.c to find all the required matrices, and perform the required verifications.
	printf("A\n");
	printMatrix(a,n);

	if(!luDecomp(a,l,u,n,t)){
		printf("Matrix is singular\n");
		return 0;
	}

	printf("L\n");
	printMatrix(l,n);

	printf("U\n");
	printMatrix(u,n);

	matrixMultiply(l,u,lu,n);
	printf("LU\n");
	printMatrix(lu,n);

	invert2(a,aInv,n,t);
	printf("A_inverse using LU decomposition\n");
	printMatrix(aInv,n);

	matrixMultiply(aInv,a,u,n);
	printf("A_inverse*A\n");
	printMatrix(u,n);

	invert(a,aInv,n,t);
	printf("A_inverse directly\n");
	printMatrix(aInv,n);

	matrixMultiply(aInv,a,u,n);
	printf("A_inverse*A\n");
	printMatrix(u,n);

	printf("Column vector b\n");
	printVector(b,n);

	vectorMultiply(aInv,b,x,n);	
	printf("The solution x =  A_inverse * b\n");
	printVector(x,n);

	freeMatrix(a,n);
	freeMatrix(l,n);
	freeMatrix(u,n);

	return 0;
}	
