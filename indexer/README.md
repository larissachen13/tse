# Indexer
## Usage:
  `indexer.c` is a standalone program that builds a word to document->word_count
  mapping from contents of the files in a given directory and writes the mapping
  to a new file. This program is meant to be called on a directory built from
  the `crawler` program, scanning each HTML page saved by `crawler` to build the
  index.

### compiling: `make`
### usage: `indexer pageDirectory indexFilename`
### where:
 * pageDirectory is a directory produced by the crawler, and
 * indexFilename is the name of a file into which the index should be written.
 * documents from the pageDirectory has..
   * a unique document ID which starts at 1 and increments for each new document,
   * a filename of form pageDirectory/id, 
   * a first line representing the URL,
   * a second line of the depth,
   * its remaining lines representing the pages content

### output:
  new file holding the word to document index where:
    * one line per word, one word per line
    * each line provides the word and one or more (docID, count) pairs, in the format
      word docID count [docID count]…
    * word is a string of lower-case letters,
    * docID is a positive non-zero integer,
    * count is a positive non-zero integer,
    * the word and integers are separated by spaces.

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
  * oldIndexFilename is a file produced by `indexer`
  * file of oldIndexFilename matches exactly the specfications detailed in
    `indexer`'s output assumptions.


### ../common/index.c
* holds shared functions such as `index_load` and `index_save`
* also holds functions pertinent to deleting the index_t structure and iterating
  through it
