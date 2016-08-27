"""To plot the function f(x) = x - tan(x) to find how many roots it has in the interval (0,20)."""
import numpy as np
import matplotlib.pyplot as plt

x = np.arange(0,20,0.01)
y = [i - np.tan(i) for i in x]

threshold = 100 # To truncate very large values so the plot can clearly show the root points

for i in range(len(y)):
	if y[i]>threshold:
		y[i] = threshold
	elif y[i]<-threshold:
		y[i] = -threshold


plt.plot(x,y)
plt.plot(x,[0 for i in x]) # Plotting the x axis as well
plt.show()
