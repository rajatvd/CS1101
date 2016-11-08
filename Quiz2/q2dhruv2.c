//Author: Dhruv Chopra EE16B107
//This code obtains the peak's max height using a different derivative method
//This is for FL1 data
#include <stdio.h>
int main()
{
	FILE *infile;
	char buff[255];
	infile=fopen("q2d2.txt","r");
	int n;
	float t[4900];
	float dat[4900];
	int i=0;
	float slope[4900];
	while(fgets(buff,255,infile))		//reading the file data
	{
		sscanf(buff,"%f %f",&t[i],&dat[i]);
		i++;
	}
	n=i;
	int u=0;		//peak variables
	int d=0;
	int r=0;
	float tim=0.0;		//time counter
	float time[100];	
	slope[0]=((dat[0+1]-dat[0])/2.0);
	if(slope[0]>=10)
	u++;
	if(slope[0]<=-5)
	d++;
	for(int i=1;i<(n-1);i++)		//calculating the derivative and thresholding it and checking it for peaks too 
	{
		slope[i]=((dat[i+1]-dat[i])/2.0);
		if(slope[i]>=10)		//peak counting
		{
			if(slope[i-1]>=10)
			{
			u--;
			}
			u++;
		}
		if(slope[i]<=-5)
		{
			if(slope[i-1]<=-5)
			{
			d--;
			}
			d++;
		}
		if(u>d && slope[i]>=-1.0 && slope[i]<=0.5 && (slope[i-1]>=0.5 || slope [i-1]<=-1.0))	//storing time instant at max height 
		{
			time[r]=tim;
			r++;
		}
		tim+=2.0;
	}
	for(int i=0;i<r;i++)
		printf("%f\n",time[i]);		//printing the time instants at max height 
	float maxh[100];
	for(int i,j=0;i<=4900;i++)		
	{
		if(t[i]==time[j])		//checking for time instant and hence storing the value of the max height by getting the corresponding data point at the relevant time interval obtained previously
		{
			maxh[j]=dat[i];
			printf("%f\n",maxh[j]);
			j++;
		}
		
	}
		
	printf("the number of peaks are %d\n",(u+d)/2);
	return 0;
}
			
		
