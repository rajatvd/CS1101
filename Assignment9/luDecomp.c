#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "luDecomp.h"

/**
  Implementation of LU Decomposition.

Author: Rajat Vadiraj Dwaraknath
Date: 20th October 2016
 */

// Performs backward substition assuming a is a upper triangular matrix, and does the same operation on b.
void backwardSub(double **a, double **b, int n){
	double pivot, mult;

	// Eliminate off-diagonal elements
	for(int i=n-1;i>=0;i--){
		pivot = a[i][i];
		for(int j=i-1;j>=0;j--){
			mult = -a[j][i]/pivot;
			for(int k=0;k<n;k++){
				a[j][k] += mult*a[i][k];
				b[j][k] += mult*b[i][k];
			}
		}
	}

	// Normalize diagonal elements to 1
	for(int i=0;i<n;i++){
		for(int k=0;k<n;k++){
			b[i][k] /= a[i][i];
		}
		a[i][i] = 1;
	}
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

// Free a matrix.
void freeMatrix(double **a, int n){
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
int invert(double **a, double **aInv, int n, double th){

	// Initializations
	setIdentity(aInv,n);
	double **u;
	makeMatrix(u,n);
	copyMatrix(a,u,n);
	double pivot, mult;	
	int k=0;

	for(int i=0;i<n;i++){
		
		// FInd pivot and do row swap if needed
		k=i;
		do{
			pivot = u[k][i];
			k++;
		}while(pivot < th && k<n);
		if(pivot < th){
			// If no non-zero element in the pivot column is found, the matrix is singular
			return 0;
		}
		if(i!=k-1){
			rowSwap(u,i,k,n);
			rowSwap(aInv,i,k,n);
		}

		// Elimination of lower triangular elements
		for(int j = i+1;j<n;j++){
			mult = -u[j][i]/pivot;
			for(k=0;k<n;k++){
				u[j][k] += mult*u[i][k];
				aInv[j][k] += mult*aInv[i][k];
			}
			
		}
	

	}

	// Backward substition to eliminate upper triangle elements, and normalize diagonal elements.
	backwardSub(u,aInv,n);

	freeMatrix(u,n);
	return 1;
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


// Put the LU decomposition of a(assuming it is nxn) into l and u
int luDecomp(double **a, double **l, double **u, int n, double th){

	// Initializations
	int i=0,j=0,k=0;
	double pivot, mult;	

	copyMatrix(a,u,n);
	setIdentity(l,n);

	for(i=0;i<n;i++){

		// find the pivot
		k=i;
		do{
			pivot = u[k][i];
			k++;
		}while(fabs(pivot) < th && k<n);
		if(fabs(pivot)<th){
			return 0;
		}
		if(i!=k-1){
			rowSwap(u,i,k,n);
			rowSwap(l,i,k,n);
		}

		// Do forward substition to find U
		for(j = i+1;j<n;j++){
			mult = -u[j][i]/pivot;
			for(k=0;k<n;k++){
				u[j][k] += mult*u[i][k];
			}
			l[j][i] = -mult; // Find L
		}


	}

	return 1;

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

// Performs forward substition assuming a is a lower triangular matrix, and does the same operation on b.
void forwardSub(double **a, double **b, int n){
	double pivot, mult;
	for(int i=0;i<n;i++){
		pivot = a[i][i];
		for(int j=i+1;j<n;j++){
			mult = -a[j][i]/pivot;
			for(int k=0;k<n;k++){
				a[j][k] += mult*a[i][k];
				b[j][k] += mult*b[i][k];
			}
		}
	}
}

// Inverts a using the LU decomposition and forward and backward substitution.
int invert2(double **a, double **aInv, int n, double th){
	double **l, **u;
	makeMatrix(l,n);
	makeMatrix(u,n);

	setIdentity(aInv,n);

	if(!luDecomp(a,l,u,n,th))return 0;
	// Inverting L using forward substitution and inverting U using backward substition.
	// Using A_inverse = U_inverse * L_inverse * IDENTITY
	forwardSub(l,aInv,n);
	backwardSub(u,aInv,n);
	
	return 1;

}

// Print a column vector of size n
void printVector(double *x, int n){
	for(int i=0;i<n;i++){
		printf("%lf\n", x[i]);
	}
	printf("\n");
}

// Multiplies a matrix a and a vector n
void vectorMultiply(double **a, double *x, double *b, int n){
	for(int i=0;i<n;i++){
		b[i]=0;
		for(int j=0;j<n;j++){
			b[i] += a[i][j]*x[j];
		}
	}
}
