# Makefile for 'bag' module
#
# Larissa Chen, July 2016
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb

bagtest: bag.o bagtest.o
	$(CC) $(CFLAGS) bag.o bagtest.o -o bagtest

bag.o: bag.h
bagtest.o: bag.h

clean:
	rm -f *~
	rm -f *.o
	rm names
