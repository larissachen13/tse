# TESTING w/ test.sh

## Test Command: `test.sh`

## Argument-checking
* Test w/ four arguments
* Test w/ url pointing to invalid server (http://foo.edu)
* Test w/url pointing to valid server but invalid page (http://old-www.cs.dartmouth.edu/foo)
* Test w/ non-existing directory
* Test w/ maxDepth not between 0-10
* Test w/ maxDepth that is a decimal

## http://old-www.cs.dartmouth.edu/~larissachen13/tse
### Urls tested in this custom testing file
  1. A non-existing page “foo.html”
    --> Should be found & added, but fails to fetch
  2. First given cs50 testing url
    --> Should be found, added, fetched, & saved
  3. A repeat of URL #2
    --> Should be found & added, but fails to fetch
  4. A custom file that...
      * holds the second given testing file
      * holds a repeat of URL #2
      * A URL pointing back to seed URL
    --> Should be found, added, fetched & saved (and also explored if
        maxDepth >2)
  5. A cyclical link that points back to this URL:
      http://old-www.cs.dartmouth.edu/~larissachen13/tsev
    --> Should be found, but not added
## Crawling w/ depth = 0
Explore the contents of http://old-www.cs.dartmouth.edu/~larissachen13/tse
& print it to pages/1

## Crawling w/ depth = 1
Additionally, explore the pages linked in
http://old-www.cs.dartmouth.edu/~larissachen13/tse

## Crawling w/ depth = 2
Additionally, explore the pages linked in http://old-www.cs.dartmouth.edu/~cs50/index.html
and http://old-www.cs.dartmouth.edu/~larissachen13/tse2

## Crawling w/ depth = 3
Go deeper and explore http://old-www.cs.dartmouth.edu/~cs50/index.html w/ depth
2 & explore http://old-www.cs.dartmouth.edu/~larissachen13/tse2 w/ depth 1.
In http://old-www.cs.dartmouth.edu/~larissachen13/tse2 the only non-repeated
 URL to explore is http://old-www.cs.dartmouth.edu/~cs50/data/tse/index.html.

 ## Starting w/ a different URL
 I also tested if I started at http://old-www.cs.dartmouth.edu/~larissachen13/tse2
 as my Seed URL and a depth of 2, it would then explore the contents of that page
 along w/ http://old-www.cs.dartmouth.edu/~cs50/index.html as expected. ALso
 URLS that were treated as repeats before were added and explored as they have
 yet to have been added to the bag.
