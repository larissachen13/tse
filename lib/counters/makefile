# Makefile for 'counters module
#
# Larissa Chen, July 2016
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb

counters: counters.o
	$(CC) $(CFLAGS) counters.o  -o counters

counters.o: counters.h

clean:
	rm -f *~
	rm -f *.o
	rm counters
