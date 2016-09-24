# Makefile 
# Author: Rajat Vadiraj Dwaraknath
# Date: 24th September 2016 
# The default target complies and runs all executables and automatically pipes output into text files, and finally plots the data.

CC = gcc
LIBS = -lm
OBJS = assignment6F1a.o assignment6F1b.o assignment6F2.o rk.o

all : F1a.out F1b.out F2.out
	./F1a.out > F1a.txt
	./F1b.out > F1b.txt
	./F2.out > F2.txt
	python plotSolns.py F1a.txt
	python plotSolns.py F1b.txt
	python plotSolns.py F2.txt

.PHONY : all

clean:
	rm -f *.o *.out *.txt

%.o : %.c rk.h 
	$(CC) -c $< -o $@ $(LIBS)

F1a.out : assignment6F1a.o rk.o
	$(CC) -o $@ assignment6F1a.o rk.o $(LIBS)

F1b.out : assignment6F1b.o rk.o
	$(CC) -o $@ assignment6F1b.o rk.o $(LIBS)

F2.out : assignment6F2.o rk.o
	$(CC) -o $@ assignment6F2.o rk.o $(LIBS)



