# Makefile for 'bag' module
#
# Larissa Chen, July 2016
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb

bag: bag.o
	$(CC) $(CFLAGS) bag.o -o bag

bag.o: bag.h 

clean:
	rm -f *~
	rm -f *.o
	rm bag
