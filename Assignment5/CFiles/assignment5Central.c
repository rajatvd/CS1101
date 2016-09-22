#include<stdio.h>
#include<stdlib.h>
#include<math.h>
/*
EE1103 - Assignment 5
Author: Rajat Vadiraj Dwaraknath
Date: 14th September 2016

Program to solve a system of two first order differential equations using the central difference method.

The differential equation in vector form is:

Y' = f(t,Y)

which when discretized yields

Y_n+1 = Y_n + h*f(t_n, Y_n)


*/

// This is the function which returns the derivatives of each dependent variable as a vector of size 2.
void f(double t, double *y, double *yPrime){

	double g = 9.8, k = 2.5,m = 1.5,b = 0.0; // constants


        // Evaluated using the differential equation
	yPrime[0] = y[1];
	yPrime[1] = -k/m*y[0] + g - b*y[1];
}

void central(double *yOld, double t, double h, int n){
        // Solve the differential equation using central difference approximation
	int i;
	double yPrime[2], y[2], yNew[2]; // yNew is y_n+1, y is y_n and yOld is y_n-1
	
	f(t,yOld,yPrime); // Get derivative

        // First iteration has to be done using forward difference
	y[0] = yOld[0] + h*yPrime[0]; 
	y[1] = yOld[1] + h*yPrime[1];
	
	for(i=0;i<n;i++){

		printf("%lf\t%lf\t%lf\n", t, y[0], y[1]);		
		f(t,y,yPrime); // Get derivative

                // Central difference approximation
		yNew[0] = 2*h*yPrime[0] + yOld[0];
		yNew[1] = 2*h*yPrime[1] + yOld[1];
		
                // Update y_n-1
		yOld[0] = y[0];
		yOld[1] = y[1];
		
                // Update y_n
		y[0] = yNew[0];
		y[1] = yNew[1];
		
		t += h; // Next iteration
		
	}
	
}

int main(int argc, char **argv){
	if(argc != 3){
		printf("Invalid input. Usage: %s stepsize (number of iterations)\n",argv[0]);
		return(0);
	}

	double h = atof(argv[1]);
	int n = atoi(argv[2]);
	
        // Initial conditions x = 0, v = 0 at t = 0
	double y[2] = {0,0};
	double t = 0;

        // Call appropriate function
	central(y,t,h,n);
}

