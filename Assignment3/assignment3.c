#include<stdlib.h>
#include<stdio.h>
#include<math.h>

/*
To find the root of x^3 - 10x^2 + 5 in the interval (0.6,0.8) using iteration and the Newton-Raphson method.
Author: Rajat Vadiraj Dwaraknath
Date: 24th August 2016

Inputs: Stepsize for iteration method, tolerance for both methods, first guess for Newton-Raphson method.
Outputs: The value of the root obtained using the two methods.
*/

// The polynomial function.
double f(double x){
	double y = pow(x,3) - 10*pow(x,2) + 5;
	return(y);
}

// Numerically evaluates the derivative of f.
double fPrime(double x, double h){
	double yPrime = (f(x+h)-f(x-h))/(2*h);
	return(yPrime);
}

// Finds the root using the brute force iteration method.
double iterationMethod(double stepsize, double tolerance){
	
	double x = 0.6; // Initial point of interval
	double y = tolerance+1; // This is done so that the while condition is not satisfied before the first iteration.

	while(fabs(y)>tolerance && x<0.8){ // The tolerance is checked in the while condition itself
		x += stepsize;
		y = f(x);
	}
	
	if(fabs(x-0.8) < tolerance){
		return(-1); // In case no root was found, a value outside the interval is returned(-1).
	}
	
	return(x);	
}

// Finds the root using the Newton-Raphson method.
double newtonsMethod(double firstGuess, double tolerance, double h){
	double xn = firstGuess; // Initialise the initial guess.
	double xnPlusOne = firstGuess+tolerance+1; // This is initialised in this way so that the while condition 
						   // is not satisfied before the first tieration.
	while(fabs(f(xnPlusOne))>tolerance){ // The tolerance is checked in the while condition itself.
		xn = xnPlusOne;
		xnPlusOne = xn - f(xn)/fPrime(xn, h); // Newton-Raphson formula for the next guess.
	}
	return(xnPlusOne);	
}

int main(int argc, char **argv){
	// Accepting the inputs
	if(argc != 4){
		printf("Wrong input format, usage: %s stepsize tolerance firstGuess(for Newton's method)\n", argv[0]);
		return(0);
	}
	double stepsize = (double)atof(argv[1]);
	double tolerance =  (double)atof(argv[2]);
	double firstGuess =  (double)atof(argv[3]);
	

	// Finding the roots using the two different methods.
	double rootIter = iterationMethod(stepsize, tolerance);
	double rootNewt = newtonsMethod(firstGuess, tolerance, stepsize);
	
	// Print results based on whether a root was found or not.
	if(rootIter == -1){
		printf("No root was found using the iteration method, and %.7f was found using Newton-Raphson method.\n", rootNewt);
	}else{	
		printf("The root was found to be %.7f using the iteration method, and %.7f using Newton-Raphson method.\n", rootIter, rootNewt);
	}
	return(0);
}

