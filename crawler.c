/*
 * crawler.c - crawler program, see README.md for more details
 *
 * Larissa Chen July 28, 2016
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include "./lib/set/set.h"
#include "./lib/bag/bag.h"
#include "./lib/counters/counters.h"
#include "./lib/hashtable/hashtable.h"
#include "./lib/memory/memory.h"
#include "web.h"

#define DEBUG

bool isWriteableDirectory(char* dir);
int isInteger(char* integer);
void crawler(WebPage* seed, char* dirName, int max);
bool pageFetcher(WebPage* target);
bool pageSaver(char* dir, WebPage* target, int id);
void pageScanner(WebPage* target, bag_t* bag, hashtable_t* pages);
inline static void logr(const char *word, const int depth, const char *url);
void deletePage(void* data);

/*
 * main- controller function that validates arguments and calls crawler-- the
 * function that handles the whole crawling process
 */
int main(int argc, char* argv[]) {
  char* dir;
  int maxDepth;
  WebPage* seedPage;

//check arguments
  //check # of arguments
  if (argc != 4) {
    printf("Usage Error: Invalid number of arguments. ./crawler [seedURL]");
      printf("[pageDirectory] [maxDepth]\n");
    exit(1);
  }

  //check pageDirectory
  if (!isWriteableDirectory(argv[2])) {
    printf("Invalid Argument: Cannot write to directory %s\n", argv[2]);
    exit(1);
  } else {
    dir = argv[2];
  }

  //check maxDepth
  if ((maxDepth = isInteger(argv[3])) == -1) {
    printf("Invalid Argument: %s is not a valid integer between 0 and 10\n",
      argv[3]);
    exit(1);
  }

  //check seedURL
  if (!IsInternalURL(argv[1])) {
    printf("Invalid Argument: %s is not an internal URL that", argv[1]);
    printf(" begins \nwith http://old-www.cs.dartmouth.edu/\n");
    exit(1);
  } else {
    seedPage = assertp(malloc(sizeof(WebPage)), "WebPage");
    seedPage->url = malloc(strlen(argv[1]) + 1);
    strcpy(seedPage->url, argv[1]);
    seedPage->depth = 0;
  }

  //start the crawler starting from the seed page until maxDepth
  crawler(seedPage, dir, maxDepth);

}

/*
 * crawler- controller function that handles the crawling process
 *
 * Assumptions:
 *  1. seed is the already allocated root URL
 *  2. seed->url contains a valid internal URL
 *  3. dirName is the name or an existing writeable directory
 *  4. max is a valid integer of the depth to be crawled
 * Pseudocode:
 *  1. allocate a new bag to store pages to explore and a hashtable of
 *      urls added to bag
 *  2. fetch HTML of seed page
 *  3. save page contents in the directory
 *  4. scan page if page->depth < max & add new URLS at new depth
 *  5. loop steps 2-4 until bag of pages to explore is empty
 *  6. clean up
 * Returns:
 *  1. void; if a certain file cannot be written because of file errors, or
 *      if a certain page's html cannot be fetched, no error is produced,
 *      program simply continues
 */
void crawler(WebPage* seed, char* dirName, int max) {
  bag_t* bagPages; //bag of pages to crawl
  hashtable_t* hashPages; //hashtable of added pages to the bag
  WebPage* targetPage; //page currently being crawled
  int id = 1; //document id
  int *dummyData = malloc(sizeof(int)); //malloc dummyData to associate w/
  *dummyData = 1;                         //each key in hte hashtable

  bagPages = assertp(bag_new(&deletePage), "bag");
  hashPages =assertp(hashtable_new(1000, &free), "hashtable");

  //insert seed
  bag_insert(bagPages, seed);
  hashtable_insert(hashPages, seed->url, dummyData);

  //loop through all the pages in the bag
  while((targetPage = bag_extract(bagPages)) != NULL) {
    //try to fetch page
    if (pageFetcher(targetPage)) {
      //save page if successfully fetched
      pageSaver(dirName, targetPage, id);
      id++; //increment id for next saved page
      //explore page if it doesn't exceed max depth
      if (targetPage->depth < max){
        pageScanner(targetPage, bagPages, hashPages);
      }
    }
    deletePage(targetPage);
  }
  bag_delete(bagPages);
  hashtable_delete(hashPages);
}

/*
 * pageFetcher - attempts to fetch page's html
 *
 * Assumptions:
 *  1. target page has been allocated
 *  2. target->url contains internal and valid URL to fetch
 *  3. target->html is NULL at call time
 * Pseudocode:
 *  1. call GetWebPage, which takes a struct page and stores html in
 *     its html member.
 *  2. Sleep after fetching the page to ensure 1 sec delay between
 *     successive fetches
 * Returns:
 *  1. True: success; page->html to be freed later
 *  2. False: error in fetching
 */
bool pageFetcher(WebPage* target) {
   if(!GetWebPage(target)) {
     return false;
   }
   #ifdef DEBUG
     logr("Fetched", target->depth, target->url);
   #endif
   sleep(1); //assure one second sleep between calls of pageFetcher()
   return true;
}

/*
 * pageSaver - saves page's html to a file
 *
 * Assumptions:
 *  1. target page has been allocated and successfully fetched
 *  2. target->url contains internal and valid URL to fetch
 *  3. target->html contains HTML from curl call
 *  4. target->depth contains depth
 *  5. dir is writeable and exists
 *  6. id holds the id of file
 * Pseudocode:
 *  1. form filename and open file to write to
 *  2. write to file where: line 1 -> url, line 2-> depth, line 3 -> html
 * Returns:
 *  1. True: success; dir/id file has been written to
 *  2. False: error in writing to dir/id
 */
bool pageSaver(char* dir, WebPage* target, int id) {
  const int len = 200;
  char filename[len]; // filename = pageDirectory/id
  char depthStr[len]; // string version of the depth of page
  FILE* pagefile; //file to write page content to

//create filename and open and write to it
  snprintf(filename, len, "%s/%d", dir, id);
  pagefile = fopen(filename, "w");
  if (pagefile == NULL){
    #ifdef DEBUG
      logr("Error Saving", target->depth, target->url);
    #endif
    return false;
  }
  //write to file
  fputs(target->url, pagefile);                  //line 1 = url
  fputc('\n', pagefile);
  snprintf(depthStr, len, "%d", target->depth); // line 2 = depth
  fputs(depthStr, pagefile);
  fputc('\n', pagefile);
  fputs(target->html, pagefile);                // line 3... = html
  fclose(pagefile);
  #ifdef DEBUG
    logr("Saved", target->depth, target->url);
  #endif

  return true;
}

/*
 * pageScanner - scans the target page for urls and adds the urls into the bag
 * of pages to be explored
 *
 * Assumptions:
 *  1. target page has been allocated and successfully fetched w/ valid
 *      url, html, and depth members
 *  2. bag is allocated
 *  3. hashtable pages contains URL's already visited
 *  4. target->depth contains depth
 *  5.
 *  6. hashtable pages contains URL's already visited
 * Pseudocode:
 *  1. scan target page for urls
 *  2. for each url check if it's valid and internal per web.c standards
 *  3. then check if URL hasn't already been added to bag
 *  4. If it hasn't, add the url to the bag of pages to be explored
 */
void pageScanner(WebPage* target, bag_t* bag, hashtable_t* pages) {
  int pos = 0;
  char* result;
  WebPage* addPage;

  #ifdef DEBUG
    logr("Scanning", target->depth, target->url);
  #endif
   while ((pos = GetNextURL(target->html, pos, target->url, &result)) > 0) {
     #ifdef DEBUG
       logr("Found", target->depth, result);
     #endif
     //validate URL result
     if (NormalizeURL(result)) {
       if(IsInternalURL(result)) {
        int* dummyData = assertp(calloc(1, sizeof(int)), "int");
         //if normalized URL is internal try adding to hashtable
         if(hashtable_insert(pages, result, dummyData)) {
           //only add page if page doesn't already exist in hashtable
           addPage = assertp(malloc(sizeof(WebPage)), "WebPage");
           addPage->url = result;
           addPage->depth = target->depth+1;
           bag_insert(bag, addPage);
           #ifdef DEBUG
             logr("Added", target->depth, result);
           #endif
         }  else {
           free(result); 
           free(dummyData);
         }
       }  else {
         //not internal
         #ifdef DEBUG
         logr("IgnExtern", target->depth, result);
         #endif
         free(result);
       }
     }  else {
       //unable to normalize
       #ifdef DEBUG
       logr("IgnExtern", target->depth, result);
       #endif
       free(result);
     }
    }

    return;
}

/*
*isWriteableDirectory- helper function that checks if a directory
* is writeable and exists
*
*args:
* 1. name of directory to test
*returns:
* 1. false if there was any problem writing a file to the directory,
* 2. true otherwise
*/
bool isWriteableDirectory(char* dir) {
  const int len = 200;
  char filename[len];
  FILE* testFile;

  snprintf(filename, len, "%s/.crawler", dir);
  testFile = fopen(filename, "w");
  if (testFile == NULL) {
    return false;
  } else {
    fclose(testFile);
    return true;
  }

}

/*
* isInteger- helper function that uses strtol to see if integer is a
*valid integer with no extra non-numerical chars and lies between 0 and 10.
*
*args:
* 1. string of integer to parse
*returns:
* 1. -1 if integer contains any non-numerical characters, is an empty string,
*      or a decimal number
* 2. else, returns the successfully parsed integer
*/
int isInteger(char* integer) {
  long maxDepth;
  char* endptr;

  maxDepth = strtol(integer, &endptr, 10);
  if (endptr == integer || *endptr || errno == ERANGE)
    return -1;
  if (maxDepth < 0 || maxDepth > 10) {
    return -1;
  }
  return maxDepth;
}

// log one word (1-9 chars) about a given url
inline static void logr(const char *word, const int depth, const char *url)
{
  printf("%2d %*s%9s: %s\n", depth, depth, "", word, url);
}

/*
 * deletePage- frees page contents
 */
void deletePage(void* data) {
  WebPage* page;
  page = (WebPage*)data;
  if (page->html)
    free(page->html);
  if (page->url)
    free(page->url);
  if (page)
    free(page);
}
