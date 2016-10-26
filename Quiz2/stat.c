#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define BUF 255

/**

Author: Nithesh H

*/

double mean(double *a, int size){
	double result = 0;
	for(int i = 0; i < size; i++)
		result += a[i]/size;
	return result;
}
double std(double *a, int size){
	double m = mean(a, size);
	double result = 0;
	for(int i = 0; i < size; i++)
		result += a[i]*a[i];
	result = sqrt(result/size);
	return result;
}
int main(){
	char s[BUF];
	double *width = (double *)malloc(sizeof(double)*100);	
	double *height = (double *)malloc(sizeof(double)*100);
	double *area = (double *)malloc(sizeof(double)*100);		
	 
	int n = 0;
	
	//input from stdin(file)
	while(fgets(s, BUF, stdin)){
		if(s[0] != '#'){
			sscanf(s, "%lf %lf %lf", &height[n], &width[n], &area[n]);
			n++;
		}
	}

	printf("# Peak count = %d\n#\tMean\t\tSTD\nHeight\t%lf\t%lf\nWidth\t%lf\t%lf\nArea\t%lf\t%lf\n\n", n, mean(height, n), std(height, n), mean(width, n), std(width, n), mean(area, n), std(area, n));
}
