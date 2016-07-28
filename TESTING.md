# TESTING w/ test.sh

## Test Command: `test.sh`

## Argument-checking
* Test w/ four arguments
* Test w/ seed url pointing to invalid server (http://foo.edu)
* Test w/ seed url pointing to valid server but invalid page (http://old-www.cs.dartmouth.edu/foo)
    (This does not produce a program error, program continues but just fails to fetch 
    this URL and does not write any files) 
* Test w/ non-existing directory
* Test w/ maxDepth not between 0-10
* Test w/ maxDepth that is a decimal (causes an parameter error)

## Custom testing file http://old-www.cs.dartmouth.edu/~larissachen13/tse **URL #1** 
### Urls tested in this file 
  * foo.html : A non-existing page 
    --> Should be found & added, but fails to fetch
  * http://old-www.cs.dartmouth.edu/~cs50/index.html: **URL #2**  
    --> Should be found, added, fetched, & saved
  * A repeat of **URL #2**
    --> Should be found & added, but fails to fetch
  * http://old-www.cs.dartmouth.edu/~larissachen13/tse2 **URL #3** 
      * holds the second given testing file http://old-www.cs.dartmouth.edu/~cs50/data/tse/index.html **URL #4** 
      * holds a repeat of **URL #2** 
      * A URL pointing back to seed URL **URL #1** 
    --> Should be found, added, fetched & saved (and also explored if
        maxDepth >2)
  6. A cyclical link that points back to this seed URL **URL #1**
    --> Should be found, but not added
    
## Crawling w/ depth = 0
Explore the contents of http://old-www.cs.dartmouth.edu/~larissachen13/tse **#1** 
& print it to pages/1

## Crawling w/ depth = 1
Additionally, explore the contents of  **#2, #3** 

## Crawling w/ depth = 2
Additionally, explore **#2 and #3** w/ depth of 1 and **#4** w/ depth of 0 
 

## Crawling w/ depth = 3
Additionally, explore **#2 and #3** w/ depth of 2 and **#4** w/ depth of 1 
In http://old-www.cs.dartmouth.edu/~larissachen13/tse2 the only non-repeated
 URL to explore is http://old-www.cs.dartmouth.edu/~cs50/data/tse/index.html.

 ## Starting w/ a different URL
 `crawler http://old-www.cs.dartmouth.edu/~larissachen13/tse2 pages3 2`
 I also tested if I started at **#3** as my Seed URL and a depth of 2.
 * explore **#4 #2 and #1** at depth of 1.  Also
 URLS that were treated as repeats before were added and explored as they have
 yet to have been added to the bag.
 


