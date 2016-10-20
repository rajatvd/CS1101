#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include "convolve.h"

/**

Implements the convolution operation in C.
AUthor: Rajat Vadiraj Dwaraknath EE16B033.

*/

// Puts the output of f convolved with g into fcg. 
void convolve(double *f, double *g, double *fcg, int lenF, int lenG){
	
	// If f is smaller than g, call g convolve f instead.
	if(lenF<lenG){
		convolve(g,f,fcg,lenG,lenF);
		return;
	}
	
	int i,j;
	double sum = 0, denom = 0, gSum = 0;

	// For normalizing purpose
	for(i=0;i<lenG;i++){
		gSum+=fabs(g[i]);
	}
	
	for(i=0;i<lenF;i++){
		
		sum = 0;
		denom = 0;

		// Partially convolving the starting part of f
		if(i<lenG/2){
			for(j=0;j<i+lenG/2;j++){
				sum += f[j]*g[j-i+lenG/2];
				denom += g[j-i+lenG/2];
			}

		}
		//Partially convolving the ending part of f
		else if(i>lenF-lenG/2){
			for(j=0;j<lenF-i+lenG/2;j++){
				sum += g[j]*f[i-lenG/2+j]; 
				denom += g[j]; 
			}
		}
		//Fully convolve the central part of f
		else{
			denom = gSum;
			for(j = 0;j<lenG;j++){
				sum += g[j]*f[i-lenG/2+j];
			}
		}

		//Normalize the sum if required
		fcg[i] = sum/denom*gSum;

	}
	
	return;

}


// Puts a normalized gaussian from -halfWdith to halfWidth into out with n points. 
void getGaussian(double *out, double halfwidth, int n){
	
	int i;
	double x, step = 2*halfwidth/(n-1), sum=0;

	// Get gaussian
	for(i=0;i<n;i++){
		x = -halfwidth + i*step;
		out[i] = exp(-x*x/2);
		sum += out[i];
	}

	// Normalize
	for(i=0;i<n;i++){
		out[i]/=sum;
	}

}
