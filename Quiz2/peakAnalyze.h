#ifndef PEAKANALYZE_H 
#define PEAKANALYZE_H
#include<stdlib.h>
#include<math.h>

/**

Author: Rajat Vadiraj Dwaraknath EE16B033
Date: 25th October 2016

Interface for analysis of peaks

 */

// Peak structure
struct Peak{
	// Indices in data array:
	int maxi, start, end, halfstart, halfend;

	// Values
	double height;
	double halfwidth;
	double area;

	// Pointer to data array
	double *data;
	int n; // Length of data array

	// Time difference between data points
	double dt;
};

// Find start and end indices of the peak
void findHeight(struct Peak *p);

// Find start and end indices of the peak
void findEnds(struct Peak *p, double tolerance);

// Find the halfwidth of the peak
void findHalfwidth(struct Peak *p);

// Find the area of the peak
void findArea(struct Peak *p);

// Derivative at a point
double deriv(double *a, int i, double dt);
#endif
