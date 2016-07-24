# Makefile for 'counters module
#
# Larissa Chen, July 2016
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb

counterstest: counters.o counterstest.o
	$(CC) $(CFLAGS) counters.o counterstest.o -o counterstest

counters.o: counters.h
counterstest.o: counters.h

clean:
	rm -f *~
	rm -f *.o
	rm counterstest
