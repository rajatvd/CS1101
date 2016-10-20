#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "luDecomp.h"

/**
  Implementation of LU Decomposition.

Author: Rajat Vadiraj Dwaraknath
Date: 20th October 2016
 */


// Free a matrix.
void freeMarix(double **a, int n){
	int i;	
	for(i=0;i<n;i++){
		free(a[i]);
	}
	free(a);
}

// Copy the square nxn matrix a into b
void copyMatrix(double **a, double **b, int n){

	int i=0,j=0;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			b[i][j] = a[i][j];
		}
	}
}

// Make the square matrix a into an identity matrix
void setIdentity(double **a, int n){

	int i=0,j=0;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(i==j){
				a[i][j] = 1;
			}else{
				a[i][j] = 0;
			}
		}	
	}	
}

// Put the inverse matrix of a(assuming it is nxn) into aInv
void invert(double **a, double **aInv, int n){

}

// Print a square nxn matrix, with space-separated entries
void printMatrix(double **a, int n){

	int i=0,j=0;

	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("%lf ",a[i][j]);
		}	
		printf("\n");
	}	
	printf("\n");
}

// Swap the pth and qth rows of a square nxn matrix a.
void rowSwap(double **a, int p, int q, int n){
	double swap=0;
	int k;
	for(k=0;k<n;k++){
		swap = a[p][k];
		a[p][k] = a[q][k];
		a[q][k] = swap;
	}
}

// Put the LU decomposition of a(assuming it is nxn) into l and u
void luDecomp(double **a, double **l, double **u, int n){
	
	int i=0,j=0,k=0;
	double pivot, mult;	
	
	copyMatrix(a,u,n);
	setIdentity(l,n);

	for(i=0;i<n;i++){

		k=i;
		do{
			pivot = u[k][i];
			k++;
		}while(pivot == 0);
		if(i!=k-1){
			printf("ROWS WERE SWAPPED");
			rowSwap(u,i,k,n);
			rowSwap(l,i,k,n);
		}

		for(j = i+1;j<n;j++){
			mult = -u[j][i]/pivot;
			for(k=0;k<n;k++){
				u[j][k] += mult*u[i][k];
			}
			l[j][i] = -mult;
		}
	

	}	

}


// Multiply two square nxn matrices
void matrixMultiply(double **a, double **b, double **c, int n){

	double sum;

	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			sum = 0;
			for(int k=0;k<n;k++){
				sum+=a[i][k]*b[k][j];
			}
			c[i][j] = sum;
		}
	}

}
