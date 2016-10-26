# Makefile 
# Author: Rajat Vadiraj Dwaraknath
# Date: 26th October 2016 
# The default target complies and runs all executables and automatically pipes output into text files, and finally plots the data.

CC = gcc -std=c99
LIBS = -lm
OBJS = convolve.o noiseRemove.o peakFind.o peakAnalyze.o stat.o

all:
	@echo
	make noiseRemove
	@echo
	make peakFind
	@echo
	make histograms
	@echo
	make stat
	@echo

noiseRemove: noiseRemove.out
	./noiseRemove.out FL1.dat > cleanFL1.txt
	python plotSolns.py cleanFL1.txt
	./noiseRemove.out FS1.dat > cleanFS1.txt
	python plotSolns.py cleanFS1.txt
	./noiseRemove.out SS1.dat > cleanSS1.txt
	python plotSolns.py cleanSS1.txt
	
peakFind: peakFind.out
	./peakFind.out cleanFL1.txt > peaksFL1.txt
	./peakFind.out cleanFS1.txt > peaksFS1.txt
	./peakFind.out cleanSS1.txt > peaksSS1.txt

histograms: 
	python plotHists.py peaksFL1.txt
	python plotHists.py peaksFS1.txt
	python plotHists.py peaksSS1.txt

stat: stat.out
	@echo "\nStatistics of FL1"
	./stat.out < peaksFL1.txt
	@echo "Statistics of FS1"
	./stat.out < peaksFS1.txt
	@echo "Statistics of SS1"
	./stat.out < peaksSS1.txt


clean:
	rm -f *.o *.out *.txt 

%.o : %.c convolve.h peakAnalyze.h 
	$(CC) -c $< -o $@ $(LIBS)


noiseRemove.out : convolve.o noiseRemove.o
	$(CC) -o $@ convolve.o noiseRemove.o $(LIBS)

peakFind.out: peakFind.o peakAnalyze.o
	$(CC) -o $@ peakFind.o peakAnalyze.o $(LIBS)

stat.out: stat.o
	$(CC) -o $@ stat.o $(LIBS)

.PHONY : all, clean, noiseRemove, peakFind, histograms, stat
