"""
Author: Rajat Vadiraj Dwaraknath EE16B033
Date 5th October 2016

Python code to plot the data in a text file assuming it contains the solution to a system of differential equations.
The first column is assumed to contain the time instants and the successive columns are assumed to contain the values
of the states at those time instants. Any number of states can be present.
"""
import matplotlib.pyplot as plt
from numpy import *
import sys

# Command line argument for file name
s = sys.argv[1]


def plotData(s):
	
	# Open the file
	fo = open(s, 'r')

	# Read lines ignoring those that begin with '#'
	lines = fo.read().split("\n")[:-1]
	lines = [x.strip() for x in lines if x[0] != '#']

	# Close the file
	fo.close()

	# List of time instants
	t = []

	# List of state vectors
	states = []

	for i in lines[:-1]:
		
		# Separate the columns
		values = i.split("\t")

		# First column contains time instants
		t.append(float(values[0]))

		# Add each successive column as a new state in the state vector
		states.append([float(i) for i in values[1:]])


	x0 = t[1]
	x1 = t[2]
	y0 = states[1][1]
	y1 = states[2][1]
	
	a1 = (y1-y0)/(x1-x0)
	a0 = y0 - a1*x0


	# Plot the data
	plt.scatter(t,[i[0] for i in states])
	line = plt.plot(t,[i[1] for i in states])
	plt.setp(line, color = 'r', linewidth = 2);
	
	plt.legend(["$y = $"+str(a1)+"*$x + $"+str(a0)+"\n$R^{2} = $"+lines[-1]], loc = 2);
	plt.xlabel("X")
	plt.ylabel("Y")
	plt.title(s+" Y vs X")
	plt.show()


plotData(s)
