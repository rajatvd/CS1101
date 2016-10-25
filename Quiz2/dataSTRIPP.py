s = "cleanFS_SS1.dat"
# Open the file
fo = open(s, 'r')

lines = fo.read().split("\n")

for i in lines:
	if len(i) == 0:
		continue
	if i[0] != '#':
		values = i.split(" ")
		print(values[0]+" "+values[1])
