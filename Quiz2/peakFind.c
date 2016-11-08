#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "peakAnalyze.h"
#define MAXPEAKS 300
/**
  Finds peaks in the data using a threshold and analyzes them using the peakAnalyze header.

Authors: Rajat Vadiraj Dwaraknath EE16B033, Nithesh N Hariharan EE16B144
Date: 25th October 2016

 */

int main(int argc, char **argv){

	if(argc!=2){
		printf("Invalid input. Usage: %s <input file path>\n", argv[0]);
		return 0;
	}

	// Reading a file
	char buff[255];
	int n = 0;

	FILE *infile;
	infile = fopen(argv[1],"r");

	// Get the number of lines
	while(fgets(buff,255,infile)){
		if(buff[0] == '#')continue;
		n++;
	}

	// Create arrays for t and y values
	double *t = (double*)malloc(sizeof(double)*n);
	double *y = (double*)malloc(sizeof(double)*n);
	double *rawY = (double*)malloc(sizeof(double)*n);

	fclose(infile);
	infile = fopen(argv[1],"r");

	// Get the values from each line
	int i=0;
	while(fgets(buff,255,infile)){
		if(buff[0] == '#'){// Ignore comments in datafile
			//	printf("%s",buff);
		}
		else{
			sscanf(buff,"%lf %lf %lf",&t[i],&rawY[i],&y[i]);
			i++;
		}
	}

	// Time difference between samples
	double dt = t[3]-t[2];

	// Peak array
	struct Peak peaks[MAXPEAKS];

	// Initialise the peak array
	for(int j=0;j<MAXPEAKS;j++){
		peaks[j].maxi=-1;
		peaks[j].start=-1;
		peaks[j].end=-1;
		peaks[j].data = y;
		peaks[j].dt = dt;
		peaks[j].n = n;
		peaks[j].height = -1;
	}

	// Variables
	int peakCount=0, maxi=0;
	int inpeak=0; // Flag indicating whether we are in a peak
	double thres = 0, maxH = 0, // Threshold and local maximum data value
		   maxVal=0, // Maximum data value
		   f=0.325, // Relative threshold factor
		   minVal = 1e10; // Minimum data value

	// Find initial threshold
	for(int i=0;i<n;i++){
		if(maxVal<y[i])maxVal=y[i];
		if(minVal>y[i])minVal=y[i];
	}
	thres = f*(maxVal-minVal);

	// Re-centre data and find an iterated threshold to help mitigate the effects of outliers
	int count = 0;
	double sum = 0;
	for(int i=0;i<n;i++){
		// Data recentre
		y[i] = y[i]-minVal;
		rawY[i] = rawY[i]-minVal;

		if(y[i]>thres){
			sum+=y[i];
			count++;
		}
	}

	// Find final threshold
	thres = f*sum/count;

	// Find and store the peaks
	if(y[0]>thres)inpeak=1;
	for(int i=0;i<n;i++){
		if(inpeak){
			if(y[i]<thres){
				inpeak = 0;
				peaks[peakCount].maxi = maxi;
				peaks[peakCount].height = maxH;
				maxH = 0;
				peakCount++; // Peak was found, increment counter
			}
			else if(y[i]>maxH){
				maxH = y[i];
				maxi = i;
			}
		}
		else{
			if(y[i]>thres){
				inpeak = 1;
			}
		}
	}

	// Print data for convenient plotting in the future
	printf("# %s Height; %s Width; %s Area\n# Height,Frequency;Width ($sec$),Frequency;Area ($sec$),Frequency\n",argv[1],argv[1],argv[1]);

	// Choosing tolerance factor as 1e-4
	double tol = 1e-4 * deriv(y,2,dt);

	// Analyze the found peaks
	for(int j=0;j<peakCount;j++){
		findEnds(&peaks[j],tol);
		findArea(&peaks[j]);
		peaks[j].data = rawY; // Using the raw data itself to find the height of peak instead of noise removed data
		findHeight(&peaks[j]);
		peaks[j].data = y;
	}

	// Merge intersecting peaks into one peak
	int mergeWidth = 0;
	for(int j=0;j<peakCount-1;j++){
		if(peaks[j].height == -1)continue;

		// Condition for peak intersection
		if(peaks[j].end-peaks[j+1].start>mergeWidth){
			// Perform merge of endpoints
			peaks[j].start = (peaks[j].start<peaks[j+1].start)?peaks[j].start:peaks[j+1].start;
			peaks[j].end = (peaks[j].end>peaks[j+1].end)?peaks[j].end:peaks[j+1].end;

			// Update height values
			if(peaks[j+1].height>peaks[j].height){
				peaks[j].height = peaks[j+1].height;
				peaks[j].maxi = peaks[j+1].maxi;
			}

			// Discard the old peak
			peaks[j+1].height = -1;
		}
	}

	// Recount peaks after merging
	int newCount = 0;
	for(int j=0;j<peakCount;j++){
		if(peaks[j].height == -1)continue;
		newCount++;
		findHalfwidth(&peaks[j]); // Find the widths after merging

		// Output results
		printf("%lf %lf %lf\n", peaks[j].height, peaks[j].halfwidth, peaks[j].area);
	}

	printf("# %d\n", newCount);

	// Code used to check peak detection and analysis
/*	double val=0;
	for(int i=0;i<n;i++){
		val=0;
		for(int j=0;j<peakCount;j++){
			if(peaks[j].height == -1)continue;
			if(i==peaks[j].maxi || i==peaks[j].start || i==peaks[j].end ||i==peaks[j].halfstart || i==peaks[j].halfend){
				if(i==peaks[j].maxi){
					val = rawY[i];
				}else{
					val = y[i];
				}
			}
		}
		printf("%lf %lf %lf\n", t[i], y[i], val);
	}
*/

	return 0;
}
