#include<stdio.h>
#include<stdlib.h>
#include<math.h>
/*
EE1103 - Assignment 5
Author: Rajat Vadiraj Dwaraknath
Date: 14th September 2016

Program to solve a system of two first order differential equations using the euler method and the central difference method.
It also successively reduces h until the consecutive error is less than a given tolerance.

The differential equation in vector form is:

Y' = f(t,Y)

which when discretized yields

Y_n+1 = Y_n + h*f(t_n, Y_n)

Recommened to use endTime of 10 so that computation time does not take too long.
*/

// This is the function which returns the derivatives of each dependent variable as a vector of size 2.
void f(double t, double *y, double *yPrime){

	double g = 9.8, k = 1,m = 1,b = 0.0; // constants


        
        // Evaluating derivatives using the differential equation
	yPrime[0] = y[1];
	yPrime[1] = -k/m*y[0] + g - b*y[1];
}


void forward(double *y, double t, double h, int n){
        // Solving the differential equation using forward difference method as in assignment5Forward.c
	int i;
	double yPrime[2];
	for(i=0;i<n;i++){

		f(t,y,yPrime);
		y[0] = y[0] + h*yPrime[0];
		y[1] = y[1] + h*yPrime[1];
		t += h;
	}

}


void central(double *yOld, double t, double h, int n){
	// Solving the differential using the central difference method, as in assignment5Central.c
	int i;
	double yPrime[2], y[2], yNew[2];
	
	f(t,yOld,yPrime);
	y[0] = yOld[0] + h*yPrime[0];
	y[1] = yOld[1] + h*yPrime[1];
	
	for(i=0;i<n;i++){

		f(t,y,yPrime);
		yNew[0] = 2*h*yPrime[0] + yOld[0];
		yNew[1] = 2*h*yPrime[1] + yOld[1];
		
		yOld[0] = y[0];
		yOld[1] = y[1];
		
		y[0] = yNew[0];
		y[1] = yNew[1];
		
		t += h;
		
	}
	
}

int main(int argc, char **argv){
	if(argc != 3){
		printf("Invalid input. Usage: %s endtime tolerance\n",argv[0]);
		return(0);
	}

	double tEnd = atof(argv[1]); // Time upto which the solution must be found
	double tolerance = atof(argv[2]); // Tolerance
	
	double y[2]; // The solution
	double t, oldY = 0,error = tolerance+1;
	
        // Error for central difference
	double h = 0.1;
	printf("# Central Difference\n# Stepsize\tError\n");
	while(error>tolerance){
		y[0] = 0;y[1] = 0;t = 0;
		central(y,t,h,(int)tEnd/h); // Solve the differential equation and use the final value to compare for error	
		error = fabs((y[0]-oldY)/y[0]); // Calculate error
		oldY = y[0];
		h*=0.1; // Decrease step size
		printf("%.9f\t%.9f\n",h,error); // Print data
	}	

        // Error for forward difference
        error = tolerance+1;
	printf("# Forward Difference\n# Stepsize\tError\n");
        h = 0.1;
	while(error>tolerance){
        	y[0] = 0;y[1] = 0;t = 0;
		forward(y,t,h,(int)tEnd/h); // Solve the differential equation and use the final value to compare for error	
		error = fabs((y[0]-oldY)/y[0]); // Calculate error
		oldY = y[0];
		h*=0.1;
		printf("%.9f\t%.9f\n",h,error);
	}	
        
        return(0);

}

