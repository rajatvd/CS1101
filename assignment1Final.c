#include<stdio.h>
#include<stdlib.h>
#include<math.h>

/*
   Numerical integration using trapeziodal method and Simpson's method of the functions:
   function1: e^-x * cos^2(x) from 0 to pi
   function2: cos(2*acos(x)) from -1 to 1
   Author: Rajat Vadiraj Dwaraknath, EE16B033
   Date: 14th August 2016

   Input: Limits of integration x1 and x2 for both functions and the required percent error threshold.
   Output: Table containing the area and the respective errors for the trapezoidal and Simpson's methods.
   Format:
   Actual area = <value obtained using antiderivative>
   Table:
   # N(number of intervals)\tTrapezoidal Area\tSimpson's Area\tTrap Consecutive Error %\tSimp Consecutive Error %\tActual Trap Error %\tActual Simp Error %
   <table entries>
   Number of intervals at which the error falls below given threshold for Trapezoidal and Simpsons's methods.
 */

// get the value of function1 at x
float function1(float x){
	float y = exp(-x)*pow(cos(x),2);
	return(y);
}

// get value of the antiderivative of function1 at x
float inty1(float x){
	float y = exp(-x)*(-0.5 + 0.1*(2*sin(2*x) - cos(2*x)));
	return(y);
}

// get the value of funtion2 at x
float function2(float x){
	float y = cos(2*acos(x));
	return(y);
}

// get value of the antiderivative of function2 at x
float inty2(float x){
	float y = 2.0/3*pow(x,3) - x;
	return(y);
}
/*
   This function numerically integrates the passed function(funcy) from x1 to x2 using both the trapezoidal
   method and Simpson's rule until the percent error between successive values is less than errorThreshold. 
   It also displays the percent error with respect to the actual area calculated using the antiderivative(inty).
 */
void numIntegrate(float (*funcy)(float), float (*inty)(float), float x1, float x2, float errorThreshold){

	float N = 2.0; // Initial number of intervals is 2 as it must be even for Simpson's method
	float dx = (x2-x1)/N; // Stepsize
	float y1, y2, trapArea = 0.0, oldTArea = 0.0, simpArea = 0.0, oldSArea = 0.0, x, trapError = 1, simpError = 1; // Errors initialised to 1 so that inital iteration can occur	
	float trapN = 1, simpN = 1; // Number of intervals at which error falls below given threshold
	int i = 0; // Iterator used for Simpson's method
	float actualArea = inty(x2) - inty(x1); // Area calculated using antiderivative
	float actualTrapError = 0, actualSimpError = 0; // Errors with respect to actual area

	printf("Actual area = %.4f\n", actualArea);
	printf("# N\tArea(Trapezoidal)\tArea(Simpson\'s)\tPercent Error(Trapezoidal)\tPercent Error(Simpson\'s)\tPercent Error Actual(Trapezoidal)\tPercent Error Actual(Simpson\'s)\n");
	// Table header printed
		
	while(trapError>errorThreshold){ // Using trapError to compare as simpError will always be less than trapError
		dx = (x2-x1)/N;
		
		// Trapezoidal Method Start
		oldTArea = trapArea;
		trapArea = 0.0;
		// Using x as the iterator itself
		for(x = x1;x <= x2-dx; x+=dx){
			y1 = funcy(x);
			y2 = funcy(x+dx);
			trapArea += 0.5*(y1+y2)*dx; // Area of a single trapezoid
		}
		// Error calculated
		if(trapArea == 0){
			trapError = 100;
			actualTrapError = 100;
		}else{
			trapError = fabs(100*(1 - oldTArea/trapArea));
			actualTrapError = fabs(100*(1 - trapArea/actualArea)); 
		}
		// Trapezoidal Method End


		// Simpson's Method Start
		if(simpError != 0){ // Condition to prevent unecessary calculations if Simpson's method is exact(if the function is a cubic polynomial)
			oldSArea = simpArea;
			simpArea = 0;
			for(i = 0;i < N/2;i++){
				// Simpson's rule formula
				simpArea += funcy(x1 + 2*i*dx) + 4*funcy(x1+(2*i+1)*dx) + funcy(x1+(2*i+2)*dx);
			}
			simpArea*=dx/3.0;
			// Error Calculation
			if(simpArea == 0){
				simpError = 100;
				actualSimpError = 100;
			}else{
				simpError = fabs(100*(1 - oldSArea/simpArea));
				actualSimpError = fabs(100*(1 - simpArea/actualArea)); 
			}
			// To find the point at which error falls below given threshold
			if(simpError < errorThreshold && simpN == 1){
				simpN = N;
			}
		}
		// Simpson's Method End
		
		// Print table entires
		printf("%.0f\t%.4f\t\t\t%.4f\t\t%.3f\t\t\t\t%.3f\t\t\t\t%.3f\t\t\t\t\t%.3f\n", N, trapArea, simpArea, trapError, simpError, actualTrapError, actualSimpError);
		N+=2.0; // Increment by 2 to keep N even
	}
	trapN = N-2; // Threshold for Trapezoidal method crossed just before ending of loop, so trapN = N-2
	printf("N for trapezoidal = %.0f, N for Simpson\'s = %.0f\n", trapN, simpN); // Display of threshold points
}

int main(int argc, char **argv){

	if(argc != 6){
		printf("Usage:%s x1 x2(limits for function1) x1 x2(limits for function 2) percentErrorThreshold\n",argv[0]);
		return(0);
	}

	float x1 = atof(argv[1]);
	float x2 = atof(argv[2]);
	float xx1 = atof(argv[3]);
	float xx2 = atof(argv[4]);
	float errorThreshold = atof(argv[5]);

	// Integrating using the given arguments
	printf("Function 1:\n");
	numIntegrate(function1, inty1, x1, x2, errorThreshold);
	printf("Function 2:\n");
	numIntegrate(function2, inty2, xx1, xx2, errorThreshold);

	return(0);

}

