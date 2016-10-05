#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "leastSquares.h"

/**
  Using Least-Squares linear regression to solve questions 4 and 5. 

Author: Rajat Vadiraj Dwaraknath
Date: 5th October 2016

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
		n++;
	}

	// Create arrays for x and y values
	double *x = (double*)malloc(sizeof(double)*n),
		   *y = (double*)malloc(sizeof(double)*n);

	fclose(infile);
	infile = fopen(argv[1],"r");

	// Get the values from each line
	int i=0;
	while(fgets(buff,255,infile)){
		sscanf(buff,"%lf\t%lf",&x[i],&y[i]);
		i++;
	}

	// Linear regression
	double a[3] = {0.0, 0.0, 0.0};
	leastSquares(x,y,n,a);

	// Output data
	for(i=0;i<n;i++){
		printf("%.4f\t%.13f\t%.13f\n",x[i],y[i],predict(x[i],a));
	}
	printf("%.10f\n",a[2]);

	// Free dynamically allocated space
	free(x);
	free(y);
	return 0;
}

