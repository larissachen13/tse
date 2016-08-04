# Makefile TEMPLATE for 'common' library
#   Builds and compiles all the data structures into a library.
#
# David Kotz, April 2016
# updated by Xia Zhou, July 2016
# updated by Larissa Chen July 2016

OBJS = file.o index.o webpage.o word.o web.o
LIB = common.a
LLIBS = ../lib/cs50ds.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb
CC = gcc
MAKE = make

$(LIB): $(OBJS)
	ar cr $@ $^

# add other targets for the other .o files
file.o: file.h file.c
index.o: index.c index.h ../lib/set/set.h ../lib/counters/counters.h ../lib/hashtable/hashtable.h ../lib/memory/memory.h
web.o: web.h web.c
word.o: word.h word.c
webpage.o: file.h webpage.h ../lib/memory/memory.h

# add cleanup commands for other subdirectories
.PHONY: clean

clean:
	rm -f *~
	rm -f *.o
	rm -f $(LIB)
	cd ../lib/memory; $(MAKE) clean
