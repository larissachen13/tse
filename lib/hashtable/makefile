# Makefile for 'hashtabletest' program
#
#
# Larissa Chen, July 2016

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb
PROG = hashtable
OBJS = ../set/set.o hashtable.o jhash.o
LIBS = -lm

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

hashtable.o: hashtable.h ../set/set.h jhash.h
../set/set.o: ../set/set.h
jhash.o: jhash.h
clean:
	rm -f *~
	rm -f *.o
	rm -f hashtable
