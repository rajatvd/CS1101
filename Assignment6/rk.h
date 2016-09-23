#include<stdio.h>
#include<stdlib.h>
#include<math.h>

/**
Implementation of the 4th order Runge Kutta Method 

Author: Rajat Vadiraj Dwaraknath
Date: 21st September 2016
 */

// Generalized RK4 ode solver where sizeOfY is the order of the ode and f is the function which returns the derivative.
// y and x are initial conditions, n is the number of intervals and h is the stepsize.
void rk4(void (*f)(double, double*, double*), double *y, double x, int n, double h, int sizeOfY){
	// Dynamically allocate the arrays for each slope and a temporary array based of order of ode
	double *yTemp = (double*)malloc(sizeof(double)*sizeOfY);
	double *k1 = (double*)malloc(sizeof(double)*sizeOfY);
	double *k2 = (double*)malloc(sizeof(double)*sizeOfY);
	double *k3 = (double*)malloc(sizeof(double)*sizeOfY);
	double *k4 = (double*)malloc(sizeof(double)*sizeOfY);
	double m = 0; // Weighted average of slopes
	int i = 0, j = 0; // Iterators


	for(i = 0;i<=n;i++){
		// Print the value of x
		printf("%lf\t",x);

		// Print the value of each y
		for(j = 0;j<sizeOfY;j++){
			printf("%lf\t",y[j]);
		}
		printf("\n");
		
		// 
		f(x,y,k1);

		for(j = 0;j<sizeOfY;j++){
			yTemp[j] = y[j]+k1[j]*h*0.5;
		}
		f(x+h/2,yTemp,k2);

		for(j = 0;j<sizeOfY;j++){
			yTemp[j] = y[j]+k2[j]*h*0.5;
		}
		f(x+h/2,yTemp,k3);

		for(j = 0;j<sizeOfY;j++){
			yTemp[j] = y[j]+k3[j]*h;
		}
		f(x+h,yTemp,k4);

		for(j = 0;j<sizeOfY;j++){

			m = (k1[j]+2*k2[j]+2*k3[j]+k4[j])/6;
			y[j] = y[j]+m*h;
		}
		x+=h;
	}


}

void f1(double x, double *y, double *m){
	m[0] = (-2*pow(x,3) + 12*pow(x,2) - 20*x + 8.5);
}

void f2(double x, double *y, double *m){
	m[0] = (4*exp(0.8*x) - 0.5*y[0]);
}

void f3(double x, double *y, double *m){
	m[0] = -0.5*y[0];
	m[1] = 4 - 0.3*y[1] - 0.1*y[0];
}


int main(int argc, char **argv){
	if(argc != 2){
		printf("Usage:%s function number(1,2,or,3)",argv[0]);
		return(0);
	}

	int fn = atoi(argv[1]);
	switch(fn){
		case 1:
			printf("# First function\n# x\t\ty\n");
			double y0[1] = {1};
			rk4(f1,y0,0,10,0.05,1);
			break;
		case 2: 
			printf("# Second function\n# x\t\ty\n");
			y0[0] = 2;
			rk4(f2,y0,0,10,0.05,1);
			break;
		case 3:
			printf("# Third function\n# x\t\ty1\t\ty2\n");
			double y1[2] = {4,6};
			rk4(f3,y1,0,4,0.5,2);
			break;
		default:
			printf("Usage:%s function number(1,2,or,3)",argv[0]);
			return(0);
	}
	return(0);
}
