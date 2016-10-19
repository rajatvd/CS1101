#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "convolve.h"

int main(){

	double f[1000],g[1000], fcg[1000];
	int i;

	for(i=0;i<1000;i++){
		f[i] = exp(i/100.0);
		g[i] = (i/100.0);
	}
	//g[500] = 1;
	convolve(f,g,fcg,1000,1000);

	for(i=0;i<1000;i++){
		printf("%lf\t%lf\t%lf\n",i/10.0,f[i],fcg[i]);
	}



}

