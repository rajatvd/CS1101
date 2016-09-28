# Makefile 
# Author: Rajat Vadiraj Dwaraknath
# Date: 28th September 2016 
# The default target complies and runs all executables and automatically pipes output into text files, and finally plots the data.

CC = gcc
LIBS = -lm
OBJS = assignment7Q6_12.o assignment7Q6_12.o rk.o

all : Q6_12.out Q6_3.out
	./Q6_12.out
	./Q6_3.out
	./Q6_3.out > Q6_3.txt
	python plotSolns.py Q6_3.txt	

.PHONY : all

clean:
	rm -f *.o *.out *.txt

%.o : %.c rk.h 
	$(CC) -c $< -o $@ $(LIBS)


Q6_12.out : assignment7Q6_12.o rk.o
	$(CC) -o $@ assignment7Q6_12.o rk.o $(LIBS)
Q6_3.out : assignment7Q6_3.o rk.o
	$(CC) -o $@ assignment7Q6_3.o rk.o $(LIBS)
