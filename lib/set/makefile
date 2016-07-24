# Makefile for 'counters module
#
# Larissa Chen, July 2016
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb

settest: set.o settest.o
	$(CC) $(CFLAGS) set.o settest.o -o settest

set.o: set.h
settest.o: set.h

clean:
	rm -f *~
	rm -f *.o
	rm settest
