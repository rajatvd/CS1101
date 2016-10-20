#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "convolve.h"

/**

Author: Rajat Vadiraj Dwaraknath

 */


// Find the dentral difference of f with respect to x and put it into fPrime.
void centralDiff(double* f, double *x, double* fPrime, int n){
	
	int i;
	fPrime[0] = (f[1]-f[0])/(x[1]-x[0]);
	fPrime[n-1] = (f[n-1]-f[n-2])/(x[n-1]-x[n-2]);
	for(i=1;i<n-1;i++){
		fPrime[i] = (f[i+1] - f[i-1])/(x[i+1] - x[i-1]);
	}

}

int main(int argc, char **argv){
	
	if(argc!=2){
		printf("Invalid input. Usage: %s <input file path>\n", argv[0]);
		return 0;
	}

	// Reading a file
	char buff[255];
	int n = 0;

	FILE *infile;
	infile = fopen(argv[1],"r");

	// Get the number of lines
	while(fgets(buff,255,infile)){
		if(buff[0] == '#') continue;
		n++;
	}

	// Create arrays for x and y values
	double *x = (double*)malloc(sizeof(double)*n),
		*y = (double*)malloc(sizeof(double)*n),
		*z = (double*)malloc(sizeof(double)*n);

	fclose(infile);
	infile = fopen(argv[1],"r");

	// Get the values from each line
	int i=0;
	while(fgets(buff,255,infile)){
		if(buff[0] == '#') continue;
		sscanf(buff,"%lf %lf %lf",&x[i],&y[i],&z[i]);
		i++;
	}


	double halfwidth = 15;

	int gaussLength = 100;
	double gaussian[100];
	getGaussian(gaussian,halfwidth,gaussLength);

	double *noiseless = (double*)malloc(sizeof(double)*n);
	double *noiseless2 = (double*)malloc(sizeof(double)*n);

	double *zPrime = (double*)malloc(sizeof(double)*n);
	double *yPrime = (double*)malloc(sizeof(double)*n);

	convolve(y,gaussian,noiseless,n,gaussLength);
	convolve(z,gaussian,noiseless2,n,gaussLength);

	convolve(noiseless,noiseless,y,n,n);
	convolve(noiseless2,noiseless2,z,n,n);

	centralDiff(y,x,yPrime,n);
	centralDiff(z,x,zPrime,n);

	//centralDiff(yPrime,x,y,n);
	//centralDiff(zPrime,x,z,n);

	printf("# Scattering vs Time\n# Time,Scatter amount\n# Forward scatter, Side scatter, Zero\n");
	for(i=0;i<n;i++){
		//printf("%lf %lf %lf\n",x[i],y[i],z[i]);
		//printf("%lf %lf %lf\n",x[i],noiseless[i],noiseless2[i]);
		printf("%lf %lf %lf 0\n",x[i],yPrime[i], zPrime[i]);
	}
	
	return 0;
}

