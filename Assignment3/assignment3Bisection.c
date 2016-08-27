#include<stdlib.h>
#include<stdio.h>
#include<math.h>

/*
To find the roots of x - tan(x) in the interval (0, 20) using the bisection method.
Author: Rajat Vadiraj Dwaraknath
Date: 24th August 2016

Inputs: tolerance
Outputs: The value of the roots obtained using the bisection method.
*/

// The given function.
double f(double x){
	double y = x - tan(x);
	return(y);
}

// Find a root of f using the bisection method. 
double bisectionMethod(double a, double b, double tolerance){
	if(f(a)*f(b)>0){ // In case the value of f at the limits have the same sign(their product is positive), return -1.
		printf("Invalid interval limits %g %g, both function values (%g,%g) are same sign.\n",a,b,f(a),f(b));
		return(-1);
	}

	double x = 0;
	double left = a, right = b;
	do{
		x = (left+right)/2.0; // Find the midpoint
		if(f(x)*f(left)>0){ // Change the interval based on sign of f at the midpoint
			left = x; // In case f(x) and f(left) have the same sign(their product is positive), use x as new left limit.	
		}else{
			right = x; // Reverse in case they are of different sign.
		}
	}while(fabs(f(x))>tolerance); // Tolerence check in the while condition

	return(x);
}

int main(int argc, char **argv){
	// Accepting the inputs
	if(argc != 2){
		printf("Wrong input format, usage: %s tolerance \n", argv[0]);
		return(0);
	}
	double tolerance =  (double)atof(argv[1]);
	double PI = 3.14159265;		
	
	// We observe from the plot of the function that it has 5 roots in the open interval (0,20). 
	// Find the 5 roots:
	double root[5];
	root[0] = bisectionMethod(4.2,4.5, tolerance);
	root[1] = bisectionMethod(7.6,7.8, tolerance);
	root[2] = bisectionMethod(10.8,10.95, tolerance);
	root[3] = bisectionMethod(14,14.1, tolerance);
	root[4] = bisectionMethod(16.8,17.25, tolerance);
	
	// Display the output.
	int i;
	for(i=0;i<5;i++){
		printf("Root %d = %.7f\n",(i+1),root[i]);	
	}
	
	return(0);
}

