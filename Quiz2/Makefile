# Makefile 
# Author: Rajat Vadiraj Dwaraknath
# Date: 18th October 2016 
# The default target complies and runs all executables and automatically pipes output into text files, and finally plots the data.

CC = gcc
LIBS = -lm
OBJS = convolve.o quiz2.o 

all : quiz2.out
	

.PHONY : all, clean

clean:
	rm -f *.o *.out *.txt 

%.o : %.c convolve.h 
	$(CC) -c $< -o $@ $(LIBS)


quiz2.out : convolve.o quiz2.o
	$(CC) -o $@ convolve.o quiz2.o $(LIBS)
