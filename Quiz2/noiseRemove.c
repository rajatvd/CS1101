#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "convolve.h"

/**

Author: Rajat Vadiraj Dwaraknath

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
		if(buff[0] == '#'){
			printf("%s",buff);
		}
		else{
			sscanf(buff,"%lf %lf",&x[i],&y[i]);
			i++;
		}
	}


	double halfwidth = 3;

	int gaussLength = 21;
	double gaussian[21];
	getGaussian(gaussian,halfwidth,gaussLength);

	int constLength = 10;
	double constant[10];

	for(i=0;i<constLength;i++){
		constant[i] = 1.0/constLength;
	}

	double *noiseless = (double*)malloc(sizeof(double)*n);

	convolve(y,gaussian,noiseless,n,gaussLength);

	//	printf("# Fluorescence vs Time\n# Time,Fluorescence\n# Autocorrelated data\n");
	for(i=0;i<n;i++){
		printf("%lf %lf %lf\n",x[i],y[i],noiseless[i]);
	}

	return 0;
}
