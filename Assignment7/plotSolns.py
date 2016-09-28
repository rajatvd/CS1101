"""
Author: Rajat Vadiraj Dwaraknath EE16B033
Date 24th September 2016

Python code to plot the data in a text file assuming it contains the solution to a system of differential equations.
The first column is assumed to contain the time instants and the successive columns are assumed to contain the values
of the states at those time instants. Any number of states can be present.
"""
import matplotlib.pyplot as plt
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

	for i in lines:
		
		# Separate the columns
		values = i.split("\t")

		# First column contains time instants
		t.append(float(values[0]))

		# Add each successive column as a new state in the state vector
		states.append([float(i) for i in values[1:]])

	# Plot the data
	plt.plot(t,states)
	plt.scatter(t,states)
	plt.xlabel("Time")
	plt.ylabel("States")
	plt.title(s+" States vs time")
	plt.legend(["State "+str(i) for i in range(1,len(states[0])+1,1)])
	plt.show()


plotData(s)
