#ifndef PEAKANALYZE_H 
#define PEAKANALYZE_H
#include<stdlib.h>
#include<math.h>

// Peak structure
struct Peak{
	int maxi, start, end, halfstart, halfend;
	double height;
	double halfwidth;
	double area;
	double *data;
	int n;
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
