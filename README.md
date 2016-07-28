# CS50 Labs 4-5-6: Tiny Search Engine


## Usage:
`crawler.c` a standalone program that crawls the web and retrieves webpages
 starting from a “seed” URL. It parses the seed webpage, extracts any
 embedded URLs, then retrieves each of those pages, recursively,
 but limiting its exploration to a given “depth”.

### usage: `crawler seedURL pageDirectory maxDepth`
### where:
  * seedURL is a valid internalURL meaning that it's a URL that can be
    normalized according to the web module and begins w/ the prefix
    http://old-www.cs.dartmouth.edu/
  * pageDirectory is an existing writeable directory to store the saved
    pages of the crawling process
  * maxDepth represents a valid integer between 0 and 10 inclusive indicating
    the depth of the recursion


### output:
  HTML pages saved as separate files w/ unique ids in the pageDirectory
  #### where:
  * line 1 is the URL
  * line 2 is the depth
  * the rest is the content

### Example Command Lines
  `crawler http://old-www.cs.dartmouth.edu/~cs50/index.html dir 0`
  `crawler http://old-www.cs.dartmouth.edu/~cs50/index.html dir 1`

## Exit Status
* 1- Invalid arguments

## Assumptions
  * Arguments follow previously described standards
  * 
  
## Limitations
  * If a URL besides the seedURL is invalid and points to a non-existing page,
    program continues without crashing or notifying the user. That is, if a
    non-existing URL is found on a page, it is found, but not added, fetched
    or saved. Same case w/ repeated URLs.
  * Therefore, a an internal seed url that points to a non-existing page, such 
    as: http://old-www.cs.dartmouth.edu/foo will pass parameter validation 
    but will not be able to fetch the site and consequently no files will be 
    written 
