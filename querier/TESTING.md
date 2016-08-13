# Testing
`test.sh`
####: Build:
  `chmod +x ./test.sh`
####: Run
  `./test.sh`

Keep in mind test will take a while because it also calls crawler and indexfile to generate the testing files
After building the crawler and index files in the data directory the first time, you can comment out the first
two lines of `test.sh` so it does not rebuild the testing files 

#### testing script that:
* Test command-line arguments
  * Enter w/ more than 2 command-line arguments: `./querier foo foo foo`
  * Check w/ directory not from crawler output: `./querier foo ../data/if1`
  * A non-readable file: `./querier ../data/dir1 foo`
* Test w/ stdin from `badinputs` a file w/ 'bad' queries
  * non-letter queries
  * queries w/ wrong syntax, ors and ands in inacceptable positions
* Test w/ basic queries reading stdin from  `goodinputs`
  * tests three words individually `indebted`, `cancel`, `skip`
* Test w/ complex queries still reading from `goodinputs`
  * test different combinations of ors and ands w/ these three words
  * compare w/ known good output
    * good output is stored in file called `good output`,  which contains more comments on how I calculated that
    * `good output` is printed to compare
* Random syntax cases reading from `randominputs`
  * queries of empty lines
  * similar queries but some w/ less whitespace and some w/ more whitespace
  * test leaving the and out in `andSequences`
  * test w/ nonexistent words such as `foo`
  * test w/ repeated query tokens to see if they sum up
* Along the way, check for memory leaks
