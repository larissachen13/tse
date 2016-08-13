# Requirement's Spec

1. execute from a command line with usage syntax
  * ./querier pageDirectory indexFilename
  * where pageDirectory is a directory produced by the crawler, and
  * where indexFilename is an index file produced by the indexer.
2. load the index from indexFilename into an internal data structure.
3. read search queries from stdin, one per line, until EOF.
  * clean and parse each query according to the syntax described below.
  * print the ‘clean’ query for user to see.
  * use the index to identify the set of documents that satisfy the query, as described below.
  * if no documents satisfy the query, print No documents match.
  * otherwise, rank the resulting set of documents according to its score, as described below, and print the set of      documents in decreasing rank order; for each, list the score, document ID and URL. (Obtain the URL by reading the first line of the relevant document file from the pageDirectory.)
4. The querier shall validate its command-line arguments:
  * pageDirectory is a directory produced by the crawler, and
  * indexFilename is the name of a readable file.
5. The querier may assume that the input directory and files follow the designated formats.
  * pageDirectory has files named 1, 2, 3, …, without gaps.
  * The content of document files in pageDirectory follow the format as defined in the crawler specs; thus your code (to read a document file) need not have extensive error checking.
  * The content of the file named by indexFilename follows our Index file format; thus your code (to recreate an index structure by reading a file) need not have extensive error checking.

# Design Spec
#### Data Structures
  * `char *queries[]`- array of query strings from stdin
  * `char *tokenized[]` - array of each string in query
  *  `index_t *index` - hashtable that holds index of words to docs
  * `counters_t *docs` - returned counterset for all matches of query
    * `counters_t *sum` - accumulator for the "or" queries
    * `counters_t *prod` - accumulator for the "and" queries
  * `doc_t sortedDocs[]` - array of sorted doc_t structs
#### Pseudocode:
  1. Validate Arguments
  2. Store all queries in `queries[]`
  3. Loop through each query
  4. Parse each query into individual word tokens and store in `tokenized`
      * while tokenizing check for bad characters in query
  5. Print a clean version of the query
      * while printing check for "and/or" syntax errors
  6. If query is acceptable, continue
  7. Identify the documents that satisfy the query
      * Loop through the query, evaluating each "andSequence", result of each
        andSequence is stored in accumulator `counters_t *prod`
      * Evaluate each andSequence with `ctrsMultiply` and `ctrMultiplyEach`, which
        iterate over one counter searching for each key in second and adjusting the first
      * After each andSequence, evaluate the or sum using `sum` as accumulator
      * Evaluate each or sum with `ctrsPlus` and `ctrsAddEach`, iterate over one counter
        searching and incrementing or adding to the second
  8. sort the final docs counterset into a sorted array of doc structs
  9. loop over the sorted array of docs and print each one
  10. cleanup

Testing Plan
  1. Test command-line arguments
    * Enter w/ more than 2 command-line arguments
    * Check w/ directory not from crawler output
  2. Check for error for non-letter queries
  3. Check for error for queries w/ wrong syntax
    * and/or at beginning or end of query
    * and/or adjacent
  4. Check for basic queries
    * simple or queries
    * simple and queries
  5. Combine for more complex queries
    * xx or xxxx and xxx or xxx and xxx and xxxx
    * xx or xxxx xxxx or xxx xxx xxxx (implicit and)
  6. Check empty queries
  7. check that queries with more whitespace should be the same than queries w/ less whitespace
  8. Check for memory leaks 
