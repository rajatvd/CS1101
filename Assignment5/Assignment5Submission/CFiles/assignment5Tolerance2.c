#include<stdio.h>
#include<stdlib.h>
#include<math.h>
/*
   EE1103 - Assignment 5
Author: Rajat Vadiraj Dwaraknath
Date: 14th September 2016

Program to solve a system of two first order differential equations using the euler method and the central difference method.
It also successively reduces h until the consecutive error is less than a given tolerance.
This program finds the error using all the points.

The differential equation in vector form is:

Y' = f(t,Y)

which when discretized yields

Y_n+1 = Y_n + h*f(t_n, Y_n)


 */

// This is the function which returns the derivatives of each dependent variable as a vector of size 2.
void f(double t, double *y, double *yPrime){

    double g = 9.8, k = 1,m = 1,b = 0.0; // constants

    // Evaluating derivatives using the differential equation
    yPrime[0] = y[1];
    yPrime[1] = -k/m*y[0] + g - b*y[1];
}


double forward(double *y, double t, double h, int n){
    // Solving the differential equation using forward difference method as in assignment5Forward.c and then finding the relative error
    int i, j;
    double yPrime[2], yOldH[2], error = 0.0, sum = 0.0;
    yOldH[0] = y[0]; // States for old stepsize
    yOldH[1] = y[1];
    for(i=0;i<n;i++){

        f(t,y,yPrime);
        y[0] = y[0] + h*yPrime[0];
        y[1] = y[1] + h*yPrime[1];
        if(i%10==0){ // Find the states for the old stepsize every ten of the new steps
            f(t-10*h,yOldH,yPrime);
            yOldH[0] = yOldH[0] + 10*h*yPrime[0];
            yOldH[1] = yOldH[1] + 10*h*yPrime[1];

            // Find the square distance at each point and the sum of the squares of the new states at each point
            error += (pow(yOldH[0]-y[0],2)+pow(yOldH[1]-y[1],2))/2; // Averaging the error of each state into one error
            sum += (pow(y[0],2)+pow(y[1],2))/2;
        }
        t += h;
    }
    return error/sum; // Return the relative error

}


double central(double *yOld, double t, double h, int n){
    // Solving the differential using the central difference method, as in assignment5Central.c and then finding the relative error
    int i;
    double yPrime[2], y[2], yNew[2], yH[2], yHNew[2], yHOld[2], sum = 0.0, error = 0.0;
    
    yHOld[0] = yOld[0]; // States for old stepsize as in the method for forward
    yHOld[1] = yOld[1];

    f(t,yOld,yPrime);
    y[0] = yOld[0] + h*yPrime[0];
    y[1] = yOld[1] + h*yPrime[1];

    f(t,yHOld,yPrime);
    yH[0] = yHOld[0] + 10*h*yPrime[0];
    yH[1] = yHOld[1] + 10*h*yPrime[1];
    t+=h;
    for(i=1;i<n;i++){

        f(t,y,yPrime);
        yNew[0] = 2*h*yPrime[0] + yOld[0];
        yNew[1] = 2*h*yPrime[1] + yOld[1];

        yOld[0] = y[0];
        yOld[1] = y[1];

        y[0] = yNew[0];
        y[1] = yNew[1];

        if(i%10==0 && i!=10){ // Again, evaluating states for old stepsize every 10 ten steps of new stepsize

            f(t-10*h,yHOld,yPrime);
            
            yHNew[0] = 2*10*h*yPrime[0] + yHOld[0];
            yHNew[1] = 2*10*h*yPrime[1] + yHOld[1];

            yHOld[0] = yH[0];
            yHOld[1] = yH[1];

            yH[0] = yHNew[0];
            yH[1] = yHNew[1];
            
            // Finding the error and sum similar to what is done in the forward method
            error += (pow(yH[0]-y[0],2)+pow(yH[1]-y[1],2))/2;
            sum += (pow(y[0],2)+pow(y[1],2))/2;
        }	
        t += h;

    }

    return error/sum; // Return the relative error
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
        
        error = central(y,t,h,(int)tEnd/h);
        
        h*=0.1; // Decrease step size to one tenth of old value
        printf("%.9f\t%.9f\n",h,error); // Print data
    }	

    // Error for forward difference
    error = tolerance+1;
    printf("# Forward Difference\n# Stepsize\tError\n");
    h = 0.1;
    while(error>tolerance){
        y[0] = 0;y[1] = 0;t = 0;

        error = forward(y,t,h,(int)tEnd/h);

        h*=0.1; // Decrease step size to one tenth of old value
        printf("%.15f\t%.15f\n",h,error);
    }	

    return(0);

}

