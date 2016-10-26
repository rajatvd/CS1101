"""
Author: Rajat Vadiraj Dwaraknath EE16B033
Date 26th October 2016

Python code to plot the data in a text file as histograms.
Each column is treated independently and plotted.
The first two lines of input can be optionally used to determine the title and labels of each plot.
"""
import matplotlib.pyplot as plt
from numpy import *
import sys

# Command line argument for file name
s = sys.argv[1]


def plotHists(s):
	
	# Open the file
	fo = open(s, 'r')

	rawlines = fo.read().split("\n")
	
	# Extract the lines with data
	lines = [x.strip() for x in rawlines if len(x) != 0 and x[0] != '#']
	
	n = len(lines[0].split(" "))

	# Extract labels and titles if possible
	title = []
	labels = []

	if rawlines[0][0] == '#' and rawlines[1][0] == '#': 
		title = rawlines[0][1:].strip().split(";")
		labels = [[j.strip() for j in i.strip().split(',')] for i in rawlines[1][1:].strip().split(";")]

	if len(labels) != n or len(title) !=n:
		title = [s+" X vs Y"]*n
		labels = [['X','Y']]*n

	

	# Close the file
	fo.close()

	# List of data
	states = []

	for i in lines:
		
		# Separate the columns
		values = i.split(" ")

		# Add each successive column as a new state in the state vector
		states.append([float(i) for i in values])


	# Plot the data
	for i in range(n):
		plt.figure()
		plt.xlabel(labels[i][0])
		plt.ylabel(labels[i][1])
		plt.title(title[i])
		plt.hist([k[i] for k in states])
		plt.show()



plotHists(s)
