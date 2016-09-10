"""
Program to plot the random numbers generated using the C program, which are now in the file named "numbers.txt".

Author: Rajat Vadiraj Dwaraknath EE16B033
Date: 10th September 2016
"""

import matplotlib.pyplot as plt # Importing matplotlib.pyplot

fo = open("numbers.txt", 'r') # File opened in read only mode.
nums = fo.read().split("\n") # Each line of the file is extracted.

# Each line(except the last EOF line) is parsed to a float unless the line begins with a #(comment).
nums = [float(i) for i in nums[:-1] if i[0]!='#'] 

intervals = 100 # Number of intervals in the histogram.
 
# Plotting the histogram.
plt.hist(nums,intervals)
plt.xlabel("Random number intervals")
plt.ylabel("Frequency of occurence of the numbers in the intervals")
plt.show()

fo.close() # Closing the opened file.


