# Makefile for 'hashtabletest' program
#
#
# Larissa Chen, July 2016

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb
PROG = hashtabletest
OBJS = ../set/set.o hashtable.o hashtabletest.o jhash.o
LIBS = -lm

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

hashtabletest.o: hashtable.h ../set/set.h jhash.h
hashtable.o: hashtable.h ../set/set.h jhash.h
../set/set.o: ../set/set.h
jhash.o: jhash.h
clean:
	rm -f *~
	rm -f *.o
	rm -f hashtabletest
