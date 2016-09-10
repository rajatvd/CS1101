import numpy as np
import matplotlib.pyplot as plt

fo = open("numbers.txt", 'r')
nums = fo.read().split("\n")
nums = [float(i) for i in nums[:-1] if i[0]!='#']
numbuckets = 100
buckets = [0 for i in range(numbuckets)]
for i in nums:
	buckets[int(i*numbuckets)]+=1

print(sum(buckets))
plt.hist(nums,numbuckets)
plt.show()
fo.close()


