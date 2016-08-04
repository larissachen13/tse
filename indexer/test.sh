#!/bin/bash
# validate command-line arguments for indexer
# more than 2 args
echo -en "\nindexer foo foo foo\n"
indexer foo foo foo

# invalid crawler output directory
echo -en "\nindexer foo indexfile\n"
rm -rf foo
mkdir foo
indexer foo indexfile

# validate command-line arguments for indextest
echo -en "\nindextest foo foo foo\n"
indextest foo foo foo

# test on page directory due to max depth of 0
rm -rf ../data/dep0
mkdir ../data/dep0
echo -en "\nmaking crawler output directory w/ depth 0...\n"
../crawler/crawler http://old-www.cs.dartmouth.edu/~cs50/index.html ../data/dep0 0
echo -en "storing indexfile in 0index\n"
indexer ../data/dep0 0index
echo -en "reloading into 0newindex\n"
indextest 0index 0newindex
echo -en "comparing 0newindex and 0newindex...\n"
./compare.sh 0index 0newindex

# test on page directory of max depth of 1
rm -rf ../data/dep1
mkdir ../data/dep1
echo -en "\n\nmaking crawler output directory w/ depth 1...\n"
../crawler/crawler http://old-www.cs.dartmouth.edu/~cs50/index.html ../data/dep1 1
echo -en "storing indexfile in 1index\n"
indexer ../data/dep1 1index
echo -en "comparing 0newindex and 0newindex...\n"
indextest 1index 1newindex
./compare.sh 1index 1newindex
