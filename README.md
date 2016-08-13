# Tiny Search Engine
## Build: `make`
  * recursively builds all libraries and modules
  * clean: `make clean`

## Libraries and Modules
  1. common - library of common modules
    * build: `make` builds common.a library
    * file.h, index.h, web.h, webpage.h, word.h
  2. crawler - contains crawler module
    * build  `make` builds crawler standalone program
  3. data
    * holds the crawler output data used by indexer
  4. indexer - contains indexer module
    * build `make` builds indexer program that takes in output from crawler program
      as input
  5. querier - contains querier module
    * build `make` builds querier program that takes in output from crawler program and indexer program 
  5. lib - library of data structures
    * build `make` builds cs50ds.a library
    * bag.h, counters.h, hashtable.h, memory.h, set.h
