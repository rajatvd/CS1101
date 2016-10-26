#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "peakAnalyze.h"

/**

  Code to analyze a peak and find its end points, area, and width, given its height.

Author: Rajat Vadiraj Dwaraknath EE16B033
Date: 25th October 2016

 */


// Derivative at a point
double deriv(double *a, int i, double dt){
	return (a[i+1]-a[i-1])/(2*dt);
}

// Finds the height and index of highest point of peak assuming the end points are already found
void findHeight(struct Peak *p){
	double maxH = 0;
	for(int i = (*p).start;i<(*p).end;i++){
		// Simple max operation
		if(maxH<(*p).data[i]){
			maxH = (*p).data[i];
			(*p).maxi = i;
		}
	}
}

// Find start and end indices of the peak assuming the height and max index are found.
// These are found by moving through the data on either side from the max until the derivative reduces below a tolerance.
void findEnds(struct Peak *p, double tol){
	int i, ontop; // ontop is used to flag whether we are still in the top flat region of the peak

	// f is the factor of the peak height above which end points will not be considered
	// tolerance is used to determine when the slope is sufficiently small for it to be called an end point
	double slope, tolerance, oldSlope = 0, f = 0.65;

	ontop = 1; // We are on the flat top initially
	i = (*p).maxi-1; // Starting location to the left of the max
	tolerance = fabs(deriv((*p).data,i,(*p).dt)*tol); // Formula for the tolerance based on flatness of the peak top

	// Left endpoint
	while(1){
		// Get derivative
		slope = deriv((*p).data, i, (*p).dt);

		if(ontop && fabs(slope)>tolerance){
			// Indicates that we have left the top flat region of the peak
			ontop = 0;
		}
		if(!ontop && (fabs(slope)<tolerance || slope*oldSlope<0) && (*p).data[i]<(*p).height*f){
			// Indicates that we have hit an end point below the height threshold of f.
			break;
		}
		if(i==0){
			// If no more data points
			break;
		}

		i--; // Move left
		oldSlope = slope;
	}
	// Assign endpoint
	(*p).start = i;

	ontop = 1;
	i = (*p).maxi+1;
	oldSlope = 0;
	// Same as above but for the right endpoint
	while(1){
		slope = deriv((*p).data, i, (*p).dt);
		if(ontop && fabs(slope)>tolerance){
			ontop = 0;
		}
		if(!ontop && (fabs(slope)<tolerance || slope*oldSlope<0) && (*p).data[i]<(*p).height*f){
			break;
		}
		if(i==(*p).n-1){
			break;
		}
		i++; // Move right
		oldSlope = slope;
	}
	// Assign endpoint
	(*p).end = i;
}

// Find the halfwidth of the peak using a simple threshold, assuming the end points have already been found
void findHalfwidth(struct Peak *p){
	int inhalf = 0; // Flag which indicates whether we are in the top half of the peak

	// Initialize values
	double start=(*p).start, end=(*p).end, thres = (*p).height/2; // Finding the width at Half-Maximum

	for(int i=(*p).start;i<(*p).end;i++){
		if(inhalf){
			if((*p).data[i]<thres){
				end = i;
				break;
			}
		}else{
			if((*p).data[i]>thres){
				start = i;
				inhalf = 1;
			}
		}
	}

	// Assign the values to the peak
	(*p).halfstart = start;
	(*p).halfend = end;
	(*p).halfwidth = (end-start)*(*p).dt;
}

// Find the area of the peak using trapezoidal integration
void findArea(struct Peak *p){
	double area=0;
	for(int i=(*p).start;i<(*p).end-1;i++){
		area += ((*p).data[i]+(*p).data[i+1])*(*p).dt/2;
	}
	(*p).area = area;
}


