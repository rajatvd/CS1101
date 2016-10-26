#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "convolve.h"

/**

  Removes the noise in the data provided in the input file, using a gaussian convolution filter.

Author: Rajat Vadiraj Dwaraknath
Date: 25th October 2016

 */
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
		if(buff[0] == '#')continue;
		n++;
	}

	// Create arrays for x and y values
	double *x = (double*)malloc(sizeof(double)*n);
	double *y = (double*)malloc(sizeof(double)*n);

	fclose(infile);
	infile = fopen(argv[1],"r");

	// Get the values from each line
	int i=0;
	while(fgets(buff,255,infile)){
		// Ignore comments
		if(buff[0] == '#'){
			printf("%s",buff);
		}
		else{
			sscanf(buff,"%lf %lf",&x[i],&y[i]);
			i++;
		}
	}


	// Create the gaussian kernel based on some parameters like width and number of points.
	double halfwidth = 3;
	int gaussLength = 21;
	double gaussian[21];
	getGaussian(gaussian,halfwidth,gaussLength);

	// Create array to store noise removed data
	double *noiseless = (double*)malloc(sizeof(double)*n);

	// Remove the noise
	convolve(y,gaussian,noiseless,n,gaussLength);

	// Output the results
	for(i=0;i<n;i++){
		printf("%lf %lf %lf\n",x[i],y[i],noiseless[i]);
	}

	return 0;
}
