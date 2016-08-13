# Makefile TEMPLATE for 'indexer' module
#
# David Kotz, April 2016
# updated by Xia Zhou, July 2016
# updated by Larissa Chen, August 2016
PROG = querier
OBJS = querier.o
LIBS = -lcurl -lm
LLIBS = ../common/common.a ../lib/cs50ds.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb
CC = gcc
MAKE = make

# build the querier
$(PROG): $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

querier.o: ../lib/set/set.h ../lib/counters/counters.h ../lib/hashtable/hashtable.h ../lib/memory/memory.h ../common/index.h ../common/file.h

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
