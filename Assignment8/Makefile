# Makefile 
# Author: Rajat Vadiraj Dwaraknath
# Date: 5th October 2016 
# The default target complies and runs all executables and automatically pipes output into text files, and finally plots the data.

CC = gcc
LIBS = -lm
OBJS = assignment8.o leastSquares.o 

all : leastSquares.out
	./leastSquares.out Q4.dat > Q4out.txt
	./leastSquares.out Q5.dat > Q5out.txt
	python plotSolns.py Q4out.txt	
	python plotSolns.py Q5out.txt	

.PHONY : all, clean

clean:
	rm -f *.o *.out *.txt 

%.o : %.c leastSquares.h 
	$(CC) -c $< -o $@ $(LIBS)


leastSquares.out : assignment8.o leastSquares.o
	$(CC) -o $@ assignment8.o leastSquares.o $(LIBS)
