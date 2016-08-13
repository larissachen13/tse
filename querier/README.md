# Querier
### Usage:
  `querier.c` is a standalone program that reads the index file produced by the
  TSE indexer, and answers search queries submitted via stdin.

### compiling: `make`
### usage: `./querier pageDirectory indexFilename`
### where:
  * pageDirectory is a directory produced by the crawler, and
  * indexFilename is the name of a file into where the index is written
  * documents from the pageDirectory has..
    * a unique document ID which starts at 1 and increments for each new document,
    * a filename of form pageDirectory/id,
    * a first line representing the URL,
    * a second line of the depth,
    * its remaining lines representing the pages content
  * the indexfile follows the appropriate format indicated by the `indexer` module
  * the stdin provides the queries

### output:
  printed summary of the query results in the format:
  * header - displays number of documents matched: `Matched: # documents`
  * list of satisfied documents in decreasing rank of score
  * each doc summary displays score, docid, url: `score  39 doc   6: http://old-www.cs.dartmouth.edu/~cs50/Resources/`

  score is calculated by adding one for any doc that satifies a certain andsequence
  and by adding one for any doc that satifies any element in an or sequence

  if no documents satisfy, header will indicate no documents matched

### Example Command Lines


## Exit Status
* 1- Invalid arguments

## Assumptions
  * pageDirectory is created from the crawler program
  * files in the pageDirectory are formatted according to the crawler program
    standards
  * no gaps exist in the document ids
  * instances of words can only be positive

## Limitations
  * content will not be parsed correctly if it isnt in the correct html format



# Indextest
## Usage:
  `indextest.c` is a testing program for `indexer.c` It loads the index from the
  new file outputted by `indexer` and resaves it to another new file. Output
  from commands `indextest` and `indexer` should be identical.

### compiling: `make`
### usage: `indexetest oldIndexFilename newIndexFilename`
### where:
  * oldIndexFilename is the name of a file produced by the indexer, and
  * newIndexFilename is the name of a file into which the index should be written.

### output:
  new file holding the resaved word to document index where:
  * format matches the format specifications for indexer.c

### Example Command Lines


## Exit Status
 * 1- Invalid arguments

## Assumptions
The querier may assume that the input directory and files follow the designated formats.

pageDirectory has files named 1, 2, 3, …, without gaps.
The content of document files in pageDirectory follow the format as defined in the crawler specs; thus your code (to read a document file) need not have extensive error checking.
The content of the file named by indexFilename follows our Index file format; thus your code (to recreate an index structure by reading a file) need not have extensive error checking.


### ../common/index.c
* holds shared functions such as `index_load` and `index_save`
* also holds functions pertinent to deleting the index_t structure and iterating
  through it

## Exit Status
* 1: Invalid arguments
* 2: Bad Query
