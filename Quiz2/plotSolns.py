"""
Author: Rajat Vadiraj Dwaraknath EE16B033
Date 20th October 2016

Python code to plot the data in a text file.
The first column is assumed to contain the X values and the successive columns are assumed to contain the values
of different data sets at the corresponding X values. These data sets are plotted individually. If the first three lines
of the file being with #, they are assumed to contain the title, the x and y labels(comma separated) and legend(comma separated)
respectively.
"""
import matplotlib.pyplot as plt
from numpy import *
import sys

# Command line argument for file name
s = sys.argv[1]


def plotData(s):
	
	# Open the file
	fo = open(s, 'r')

	lines = fo.read().split("\n")
	
	title = s+" X vs Y"
	labels = ['X','Y']
	legend = []

	if lines[0][0] == '#' and lines[1][0] == '#' and lines[2][0] == '#':
		title = lines[0][1:].strip()
		labels = [i.strip() for i in lines[1][1:].strip().split(',')]
		legend = [i.strip() for i in lines[2][1:].strip().split(',')]

	if len(labels) != 2:
		labels = ['X','Y']
		

	lines = [x.strip() for x in lines if len(x) != 0 and x[0] != '#']

	# Close the file
	fo.close()

	# List of time instants
	t = []

	# List of state vectors
	states = []

	for i in lines:
		
		# Separate the columns
		values = i.split(" ")

		# First column contains time instants
		t.append(float(values[0]))

		# Add each successive column as a new state in the state vector
		states.append([float(i) for i in values[1:]])

	# Plot the data
	plt.plot(t,states)
	plt.xlabel(labels[0])
	plt.ylabel(labels[1])
	plt.title(title)
	plt.legend(legend)
	plt.show()


plotData(s)
