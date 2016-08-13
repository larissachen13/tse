# Querier
### Usage:
  `querier.c` is a standalone program that reads the index file produced by the
  TSE indexer, and answers search queries submitted via stdin.
  `./querier pageDirectory indexFilename`

### compiling: `make`

### Example Command Lines
`querier ../data/directoryFromCrawler ../data/indexFileFromIndexer`

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
  * a query is considered bad if it contains any non-letter characters or...
  * if any string operators "or/and" are placed at the beginning, end, or are adjacent to each other
   

### output:
  printed summary of the query results in the format:
  * header - displays number of documents matched: `Matched: # documents`
  * list of satisfied documents in decreasing rank of score
  * each doc summary displays score, docid, url: `score  39 doc   6: http://old-www.cs.dartmouth.edu/~cs50/Resources/`

  score is calculated by adding one for any doc that satifies a certain andsequence
  and by adding one for any doc that satifies any element in an or sequence

  if no documents satisfy, header will indicate no documents matched

### Exit Status
* 1- Invalid arguments

### Assumptions
  * pageDirectory is created from the crawler program
  * files in the pageDirectory are formatted according to the crawler program
    standards
  * no gaps exist in the document ids
  * content of the file named by indexFilename follows our Index file format
  * instances of words can only be positive
  * and sequences take over precedence than or sequences
  * the indexfilename is an index built from the pageDirectory
  * scores are accumulated if any tokens in the query are repeated, that is, the query
    "dartmouth or dartmouth or dartmouth" will return the score for dartmouth * 3.

### Limitations
  * Does not process empty queries, that is program will not attempt to match
    the empty query w/ any documents and no summary will be printed
  * Does not process any queries with non-letters
  * scores are added even if tokens are repeated
  * Can process a limit of 500 queries 
