#!/bin/bash
# setup input arguments
../crawler/crawler http://old-www.cs.dartmouth.edu/~cs50/index.html ../data/dir1 1
../indexer/indexer ../data/dir1 ../data/if1

# validate input
echo -en "\n\033[1mvalidating input arguments\033[0m\n"
./querier foo foo foo

./querier foo ../data/if1

./querier ../data/dir1 foo

# validate query string syntax
echo -en "\n\n\033[1mvalidating query strings\033[0m\n"
./querier ../data/dir1 ../data/if1 < badinputs

# validate basic and complex queries
echo -en "\n\n\033[1mvalidating basic and complex queries\033[0m\n"
./querier ../data/dir1 ../data/if1 < goodinputs
echo -en "\nGOOD OUTPUT:\n"
cat goodoutput

# validate queries w/ whitespace, empty queries, and case-different queries
echo -en "\n\n\033[1mvalidating queries w/ different (edge-case) syntax\033[0m\n"
./querier ../data/dir1 ../data/if1 < randominputs
