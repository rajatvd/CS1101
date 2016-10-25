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
	
	xyz = """	title = s+" X vs Y"
	labels = ['X','Y']
	legend = []

	if lines[0][0] == '#' and lines[1][0] == '#' and lines[2][0] == '#':
		title = lines[0][1:].strip()
		labels = [i.strip() for i in lines[1][1:].strip().split(',')]
		legend = [i.strip() for i in lines[2][1:].strip().split(',')]

	if len(labels) != 2:
		labels = ['X','Y']
"""	
	lines = [x.strip() for x in lines if len(x) != 0 and x[0] != '#']

	# Close the file
	fo.close()

	# List of state vectors
	states = []

	for i in lines:
		
		# Separate the columns
		values = i.split(" ")

		# Add each successive column as a new state in the state vector
		states.append([float(i) for i in values])

	# Plot the data
	yzx = """	plt.xlabel(labels[0])
	plt.ylabel(labels[1])
	plt.title(title)
	plt.legend(legend)
	"""	
	for i in range(len(states[0])):
		plt.figure()
		plt.hist([k[i] for k in states])
		plt.show()
	


plotData(s)
