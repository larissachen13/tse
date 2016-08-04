# Testing

* `compare.sh` is a small shell script to be compiled as:
    `chmod +x compare.sh`
    and run as:
    `./compare oldIndexFilename newIndexFilename`
    where `oldIndexFilename` and `newIndexFilename` should be the same arguments
    to `indextest`. `compare.sh` simply sorts both files and runs diff on the sorted
    files to indeed see if index_load and index_save functions are exact inverses
    of each other. If they're nothing should be printed to stdout from the `diff`
    command. The two new sorted files created in the process are `oldIndexFilename.sorted`
    && `newIndexFilename.sorted`.

* `test.sh` is a testing script to be compiled as:
    `chmod +x test.sh`
    and run as (compile compare.sh first):
    `./test.sh`
    all directories will be produced by calls to crawler in the test.sh script

    Procedure:
    1. check argument-validation for indexer
    2. call indexer on a one-page directory - dep0 created by crawler call to
       http://old-www.cs.dartmouth.edu/~cs50/index.html w/ depth of 0
       * assure that indexfile produced by the indexer call only contains doc_ids
         of 1
       * manually checked words such as 'computer' and 'crash' to see how many times
         they actually occured on the site's html source
    3. call again on directory dep1 created by crawler call to the same CS50 home
       site but this time w/ depth of 1
       * assure that doc_ids in indexfile don't exceed 10
       * doc_id counts are formatted correctly
    4. use indextest
       * call on indexfile holding pages of depth 0 `indextest 0index 0newindex`
          * compare w/ `compare.sh 0indexfile 0newindexfile`
       * call on indexfile holding pages of depth 1 `indextest 1index 1newindex`
          * compare the two files
       * If the two files match `compare.sh` should NOT output anything, indicating
         index_load and index_save work correctly
