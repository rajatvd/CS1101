# Makefile 
# Author: Rajat Vadiraj Dwaraknath
# Date: 25th October 2016 
# The default target complies and runs all executables and automatically pipes output into text files, and finally plots the data.

CC = gcc -std=c99
LIBS = -lm
OBJS = convolve.o noiseRemove.o peakFind.o peakAnalyze.o

all : noiseRemove.out peakFind.out
	./noiseRemove.out FL1.dat > cleanFL1.dat
	./noiseRemove.out FS1.dat > cleanFS1.dat
	./noiseRemove.out SS1.dat > cleanSS1.dat
	./peakFind.out cleanFL1.dat > peaks.txt
	python plotSolns.py peaks.txt
	./peakFind.out cleanFS1.dat > peaks.txt
	python plotSolns.py peaks.txt
	./peakFind.out cleanSS1.dat > peaks.txt
	python plotSolns.py peaks.txt

.PHONY : all, clean

clean:
	rm -f *.o *.out *.txt 

%.o : %.c convolve.h peakAnalyze.h 
	$(CC) -c $< -o $@ $(LIBS)


noiseRemove.out : convolve.o noiseRemove.o
	$(CC) -o $@ convolve.o noiseRemove.o $(LIBS)

quiz2part2.out : convolve.o quiz2part2.o
	$(CC) -o $@ convolve.o quiz2part2.o $(LIBS)

peakFind.out: peakFind.o peakAnalyze.o
	$(CC) -o $@ peakFind.o peakAnalyze.o $(LIBS)
