# Makefile TEMPLATE for 'indexer' module
#
# David Kotz, April 2016
# updated by Xia Zhou, July 2016
# updated by Larissa Chen, July 2016
LIBS = -lcurl
LLIBS = ../lib/cs50ds.a ../common/common.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb
CC = gcc
MAKE = make

all: indexer indextest

indexer: indexer.o $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@ $(LLIBS)

indextest: indextest.o $(LLIBS)
		$(CC) $(CFLAGS) $^ $(LIBS) -o $@ $(LLIBS)

indexer.o: indexer.c ../lib/set/set.h ../lib/counters/counters.h ../lib/hashtable/hashtable.h ../lib/memory/memory.h ../common/index.h
indextest.o: indextest.c ../common/index.h ../lib/set/set.h ../lib/counters/counters.h ../lib/hashtable/hashtable.h ../lib/memory/memory.h

# build the library
../lib/cs50ds.a:
	cd ../lib; $(MAKE)

../common/common.a:
	cd ../common; $(MAKE)

.PHONY: clean

clean:
	rm -f *~
	rm -f *.o
	rm -f $(PROG)
	cd ../lib; $(MAKE) clean
	cd ../common; $(MAKE) clean
