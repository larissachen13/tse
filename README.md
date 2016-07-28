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
<<<<<<< HEAD
### output:
  html pages saved in the pageDirectory
=======
    
    
### output:
  HTML pages saved as separate files w/ unique ids in the pageDirectory 
  #### where: 
  * line 1 is the URL 
  * line 2 is the depth 
  * the rest is the content 
>>>>>>> c72287de08196d3724a40927fc796fdc3b9b6d5f

### Example Command Lines
  `crawler http://old-www.cs.dartmouth.edu/~cs50/index.html dir 0`
  `crawler http://old-www.cs.dartmouth.edu/~cs50/index.html dir 1`

## Exit Status
* 1- Invalid arguments

## Assumptions
  * Arguments follow previously described standards
  * 
  
## Limitations
  * If a URL is invalid and points to a non-existing page,
    program continues without crashing or notifying the user. That is, if a
    non-existing URL is found on a page, it is found, but not added, therefore
    it is not fetched or saved. 
  * Same case w/ repeated URLs. Found but not added 
  * However, if the seedURL  is not internal and not valid, program throws an 
    argument error. 
