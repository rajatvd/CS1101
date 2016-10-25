#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "peakAnalyze.h"

/**

Author: Rajat Vadiraj Dwaraknath EE16B033

 */


// Derivative at a point
double deriv(double *a, int i, double dt){
	return (a[i+1]-a[i-1])/(2*dt);
}

// Finds the height and index of highest point of peak
void findHeight(struct Peak *p){
	double maxH = 0;
	for(int i = (*p).start;i<(*p).end;i++){
		if(maxH<(*p).data[i]){
			maxH = (*p).data[i];
			(*p).maxi = i;
		}
	}
}

// Find start and end indices of the peak
void findEnds(struct Peak *p, double tol){
	int i, ontop;
	double slope, tolerance, oldSlope = 0, f = 0.65;

	ontop = 1;
	i = (*p).maxi-1;
	tolerance = fabs(deriv((*p).data,i,(*p).dt)*tol);

	while(1){
		slope = deriv((*p).data, i, (*p).dt);
		if(ontop && fabs(slope)>tolerance){
			ontop = 0;
		}
		if(!ontop && (fabs(slope)<tolerance || slope*oldSlope<0) && (*p).data[i]<(*p).height*f){
			break;
		}
		if(i==0){
			break;
		}
		i--;
		oldSlope = slope;
	}
	(*p).start = i;
	
	ontop = 1;
	i = (*p).maxi+1;
	oldSlope = 0;
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
		i++;
		oldSlope = slope;
	}
	(*p).end = i;
//	printf("%lf %lf\n",p.dt*p.start, p.dt*p.end);
}

// Find the halfwidth of the peak
void findHalfwidth(struct Peak *p){
	int inhalf = 0;
	double start=(*p).start,end=(*p).end,thres = (*p).height/2;
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

	(*p).halfstart = start;
	(*p).halfend = end;
	(*p).halfwidth = (end-start)*(*p).dt;
}

// Find the area of the peak
void findArea(struct Peak *p){
	double area=0;
	for(int i=(*p).start;i<(*p).end-1;i++){
		area += ((*p).data[i]+(*p).data[i+1])*(*p).dt/2;
	}
	(*p).area = area;
}


