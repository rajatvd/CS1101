#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "peakAnalyze.h"
#define MAXPEAKS 300

/**

Author: Rajat Vadiraj Dwaraknath EE16B033

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
		if(buff[0] == '#'){
			printf("%s",buff);
		}
		else{
			sscanf(buff,"%lf %lf %lf",&t[i],&rawY[i],&y[i]);
			i++;
		}
	}

	double dt = t[3]-t[2];
	struct Peak peaks[MAXPEAKS];

	for(int j=0;j<MAXPEAKS;j++){
		peaks[j].maxi=-1;
		peaks[j].start=-1;
		peaks[j].end=-1;
		peaks[j].data = y;
		peaks[j].dt = dt;
		peaks[j].n = n;
		peaks[j].height = -1;
	}

	int peakCount=0, maxi=0;
	int inpeak=0;
	double thres = 0, maxH = 0, maxVal=0, f=0.325, minVal = 1e10;

	for(int i=0;i<n;i++){
		if(maxVal<y[i])maxVal=y[i];
		if(minVal>y[i])minVal=y[i];
	}
	thres = f*(maxVal-minVal);

	int count = 0;
	double sum = 0;
	for(int i=0;i<n;i++){
		y[i] = y[i]-minVal;
		rawY[i] = rawY[i]-minVal;
		if(y[i]>thres){
			sum+=y[i];
			count++;
		}
	}

	thres = f*sum/count;

	if(y[0]>thres)inpeak=1;
	for(int i=0;i<n;i++){
		if(inpeak){
			if(y[i]<thres){
				inpeak = 0;
				peaks[peakCount].maxi = maxi;
				peaks[peakCount].height = maxH;
				maxH = 0;
				peakCount++;
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

	printf("# Height\tFull-Width at Half Max\tArea\n");
	double tol = deriv(y,2,dt);
	for(int j=0;j<peakCount;j++){
		findEnds(&peaks[j],tol);
		findArea(&peaks[j]);
		peaks[j].data = rawY;
		findHeight(&peaks[j]);
		peaks[j].data = y;
	}

	//Merging:
	int mergeWidth = 0;
	for(int j=0;j<peakCount-1;j++){
		if(peaks[j].height == -1)continue;
		if(peaks[j].end-peaks[j+1].start>mergeWidth){
			peaks[j].start = (peaks[j].start<peaks[j+1].start)?peaks[j].start:peaks[j+1].start;
			peaks[j].end = (peaks[j].end>peaks[j+1].end)?peaks[j].end:peaks[j+1].end;
			if(peaks[j+1].height>peaks[j].height){
				peaks[j].height = peaks[j+1].height;
				peaks[j].maxi = peaks[j+1].maxi;
			}
			peaks[j+1].height = -1;
		}
	}

	int newCount = 0;
	for(int j=0;j<peakCount;j++){
		if(peaks[j].height == -1)continue;
		newCount++;
		findHalfwidth(&peaks[j]);
		printf("%lf %lf %lf\n", peaks[j].height, peaks[j].halfwidth, peaks[j].area);
	}
	printf("# %d\n", newCount);

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
	


}
