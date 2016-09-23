import matplotlib.pyplot as plt
import sys
s = sys.argv[1]
fo = open(s, 'r')
lines = fo.read().split("\n")[:-1]
lines = [x.strip() for x in lines if x[0] != '#']
fo.close()
t = []
states = []

for i in lines:

	values = i.split("\t")
	t.append(float(values[0]))
	states.append([float(i) for i in values[1:]])

plt.plot(t,states)
#plt.figure()
#plt.plot(x,v);
plt.show()
