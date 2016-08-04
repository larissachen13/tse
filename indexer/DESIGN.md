# Requirements spec:
## Indexer:
  1. execute from a command line with usage syntax
    `/indexer pageDirectory indexFilename`
    * where pageDirectory is a directory produced by the crawler, and
    * where indexFilename is the name of a file into which the index should be written.
  2. read documents from the pageDirectory, each of which has a unique document ID,
    * wherein the document id starts at 1 and increments for each new document,
    * and the filename is of form pageDirectory/id,
    * and the first line of the file is the URL,
    * and the second line of the file is the depth,
    * and the rest of the file is the page content.
  3. build an inverted-index data structure mapping from words to (documentID, count) pairs,
    * wherein each count represents the number of occurrences of the given word in the given document.  * Ignore words with fewer than three characters, and NormalizeWord before indexing.
  4. create a file indexFilename and write the index to that file

### The indexer shall validate its command-line arguments:

* pageDirectory is a directory produced by the crawler (see below), and
* indexFilename is the name of a writeable file.

### The indexer may assume that:

* pageDirectory has files named 1, 2, 3, …, without gaps.
* The content of files in pageDirectory follow the format as defined in the crawler specs; thus your code (to create a WebPage by reading a file) need not have extensive error checking.

## Indextester shall:

1. execute from a command line with usage syntax
  `./indextest oldIndexFilename newIndexFilename`
  * where oldIndexFilename is the name of a file produced by the indexer, and
  * where newIndexFilename is the name of a file into which the index should be written.
2. load the index from the oldIndexFilename into an inverted-index data structure.
3. create a file newIndexFilename and write the index to that file, in the format described below
4. It need not validate its command-line arguments other than to ensure that it receives precisely two            arguments; it may simply try to open the oldIndexFilename for reading and, later, try to open the newIndexFilename for writing. You may use indextest.sh (provided) to verify that the output is identical to (or equivalent to) the input.

### The index tester may assume that:

The content of the index file follows the format specified below; thus your code (to recreate an index structure by reading a file) need not have extensive error checking.

# Design Spec
## Indexer:
Indexer makes use of an inverted index which:
  * is a `hashtable_t` or `index_t`that maps documents to words where:
    * `char *key` is the word
    * and `void *data` `counters_t` of <doc_id, count> pairs
      count being the amount of times the word appears on the document w/ doc_id
  * each array slot in `index_t *index` is represented by a set of <key, data> or
    <word, document-counterset> pairs that hash to the same slot

### Indexer Pseudocode:
1. Process and validate command-line parameters
2. Initialize data structure `index_t *index`
3. `index_build(directory, index)`
  * loop through all readable files in the directory
  * scan each page in the file with `scan_page`to figure out frequency of words
4. Each time coming across a new word greater than 3 characters, insert it into
   the hashtable, updating the counter for the appropriate doc
5. Once finished building the index, save the index to the file
  * Do this by iterating through the hashtable
  * For each slot's set iterate through the set
  * For each set's data iterate through the counter struct
6. Clean up data structures

## Indextester
Loads the index from a file and writes it back to another file. If the load/save
functions are correct, the two files should be identical (or at least, equivalent)

### Indextester Pseudocode
  1. Process and validate command-line parameters
  2. Initialize data structure index
  3. index_load(file1, index)
  4. index_save(file2, index)
  5. clean up data structures

### ../common/index.c
* holds shared functions such as `index_load` and `index_save`
* also holds functions pertinent to deleting the index_t structure and iterating
  through it

# Testing plan
  * Test indexer.c
    * Test invalid command-line arguments
      * Directories not made by crawler.c
      * Can open and write to indexFilename
      * exactly two arguments are provided
    * Start by just testing indexer in a one-page directory
    * I tested on the cs50 home page and looked at the output page matching
      word counts on the indexfile to the word counts on the page by using cmd+f
      on the website to count word occurences
    * Test w/ multiple-page directories
    * Check for memory leaks
  * Use indextest.c
    * Test invalid command-line arguments
      * exactly two arguments are provided
    * indextest on the one-page directory indexfile
      * call compare.sh on indexfile and newindexfile to check they're identical
      * assure no differences arising from diff are printed to stdout
    * Check for memory leaks 

## `compare.sh`
