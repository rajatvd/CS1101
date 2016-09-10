#include<stdio.h>
#include<stdlib.h>
#include<math.h>
/*
EE1103 - Assignment 4
Program to generate random numbers using I_j+1 = a*I_j + c (mod m)

Author: Rajat Vadiraj Dwaraknath EE16B033
Date: 10th September 2016 

*/

// This function returns the next random number in the sequence after seed.
long long unsigned int getRand(long long unsigned int seed){
	long long unsigned int a = 1103515245, c = 12345, m = pow(2,32); // Constants
	return((seed*a + c)%m); // Calculating the next number in the sequence
}

int main(int argc, char **argv){
	// Input accepted
        if(argc!=3){
		printf("Wrong input. Usage:%s (number of random numbers) seed\n",argv[0]);
		return(0);
	}

	long long unsigned int seed = atoi(argv[2]); // The seed
        double  sumOfSquares = 0,sum = 0; // Intermediate variables for finding mean and standard deviation
        int  n = atoi(argv[1]); // Number of random numbers
	double num = 0, m = pow(2,32); // num is the normalized random number and m is the given contant
	int i; // Iterator
	for(i=0;i<n;i++){
		num = seed/m; // Normalize the random number
		printf("%lf\n",num); // Print the random number
		sum += num; // Increment sum
		sumOfSquares += num*num; // Increment sum of squares
		seed = getRand(seed); // Get the next random number in the sequence
	}

	double meanValue = (double)sum/n; // Find the mean
	double std = ((double)sumOfSquares/n - meanValue*meanValue); // Find the variance
	std = sqrt(std); // Standard deviation = sqrt(variance)
        
        // Display final output
	printf("# Mean\t\tStandard Deviation\n# %lf\t%lf\n",meanValue,std);
	
	return(0);
}
