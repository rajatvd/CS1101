# Makefile 
# Author: Rajat Vadiraj Dwaraknath
# Date: 5th October 2016 
# The default target complies and runs all executables and automatically pipes output into text files, and finally plots the data.

CC = gcc -std=c99
LIBS = -lm
OBJS = assignment9.o luDecomp.o 

all : lu.out
	./lu.out matrix.dat

.PHONY : all, clean

clean:
	rm -f *.o *.out *.txt 

%.o : %.c luDecomp.h 
	$(CC) -c $< -o $@ $(LIBS)


lu.out : assignment9.o luDecomp.o
	$(CC) -o $@ assignment9.o luDecomp.o $(LIBS)
