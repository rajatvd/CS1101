#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "luDecomp.h"

/**
  Solvnig assignment 9.

Author: Rajat Vadiraj Dwaraknath
Date: 5th October 2016

 */

int main(int argc, char **argv){
	if(argc!=2){
		printf("Invalid input. Usage: %s <input file path>\n", argv[0]);
		return 0;
	}

	char *buff;
	buff = (char*)malloc(sizeof(char)*255);
	int n = 0;

	FILE *infile;
	infile = fopen(argv[1],"r");

	while(fgets(buff,255,infile)){
		n++;
	}

	double **a, **l, **u;
	makeMatrix(a,n);

	fclose(infile);
	infile = fopen(argv[1],"r");


	int i=0,j=0;
	while(fgets(buff,255,infile)){
		j=0;
		while(j<n && sscanf(buff,"%lf",&a[i][j]) == 1){
			while(buff[0]!=' ')buff++;
			buff++;
			j++;
		}
		i++;
	}

	printf("A\n");
	printMatrix(a,n);

	makeMatrix(l,n);
	makeMatrix(u,n);

	luDecomp(a,l,u,n);

	printf("L\n");
	printMatrix(l,n);

	printf("U\n");
	printMatrix(u,n);

	matrixMultiply(l,u,a,n);

	printf("LU\n");
	printMatrix(a,n);

	return 0;
}	
