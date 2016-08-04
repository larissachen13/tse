/*
 * indexer - a simple web indexer
 * See README.md for more usage details
 *
 * Larissa, July 2016
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include "../lib/set/set.h"
#include "../lib/bag/bag.h"
#include "../lib/counters/counters.h"
#include "../lib/hashtable/hashtable.h"
#include "../lib/memory/memory.h"
#include "../common/index.h"
#include "../common/web.h"
#include "../common/word.h"
#include "../common/webpage.h"

void index_build(char *dir, index_t *index);
void scan_page(char *page, index_t *index, int id);
void index_save(index_t *index, FILE *writefile);
void ctr_iter_func(void *arg, int key, int count);
void hash_iter_func (void *arg, const char *key, void *data);

/*
 * main driver program that first validates arguments then initializes index
 * data structure to pass into index_build and then into index_save
 *
 * index_save and deleteCounter function is defined in ../common/index.c part
 * of the common library
 */
int main(int argc, char* argv[]) {
  char *dir;
  FILE *indexFile;
  index_t *index;

//validate arguments
  //validate # of arguments
  if (argc != 3) {
  printf("Usage Error: Invalid number of arguments. ./indexer [pageDirectory]");
  printf("[indexFilename]\n");
  exit(1);
  }

  //validate pageDirectory
  if (!is_pageDirectory(argv[1])) {
    printf("Invalid Argument: Directory %s wasn't produced by crawler program\n", argv[1]);
    exit(1);
  } else {
    dir = argv[1];
  }

  //validate filename
  indexFile = fopen(argv[2], "w");
  if(indexFile == NULL) {
    printf("Invalid Argument: Cannot write to file %s\n", argv[2]);
    exit(1);
  } else {
    fclose(indexFile);
  }

   // initialize index data structure with deleteCounter function found in
   //  ../common/index.c
  index = assertp(hashtable_new(100000, &deleteCounter), "hashtable");

  //build index
  index_build(dir, index);

  //write index to indexfile
  indexFile = fopen(argv[2], "w");
  index_save(index, indexFile);

  //clean up
  hashtable_delete(index);
}

/*
* index_build- helper function that builds the word to <document, frequency>
* mapping
*
* Assumptions:
*  1. index is initialize and empty
*  2. dir is a valid direcory written to in the crawler program
*  3. dir holds pages w/ id's incrementing from 1
*
* Pseudocode:
*  1. loop through all readable files in the dir using webpage_load
*  2. call scan_page to scan each file stored in pageToRead->html for word frequency
*  3. close each file
*/
void index_build(char *dir, index_t *index) {
  WebPage *pageToRead;
  int id = 0;

  //  loop through all the readable files storing the HTML in pageToRead
  while(1) {
    pageToRead = webpage_load(dir, ++id);
    if (pageToRead == NULL) {
      break;
    }
    //scan each page for word frequency
    scan_page(pageToRead->html, index, id);
    //clean up
    webpage_delete(pageToRead);
  }
}

/*
* scan_page- helper function that scans each page's file for word frequency
* mapping
*
* Assumptions:
*  1. readfile is a readable file that is already open
*  2. ht holds the index to build
*  3. id corresponds to the id of the readablefile
*
* Pseudocode:
*  1. scan a word from the file using GetNextWord
*  2. if word is longer than three, normalize and insert into the hashtable
*  3. loop through every word in file
*/
void scan_page(char *page, index_t *ht, int id){
  int pos = 0;
  char *word;
  counters_t *wordctrs;

  //loop through all the words on the page
  while ((pos = GetNextWord(page, pos, &word)) > 0) {
    //ignore strings w length less than 3
    if (strlen(word) > 3) {
      NormalizeWord(word);
      if((wordctrs = hashtable_find(ht, word))) {
        //word exists in ht, add to ctr for this id
        counters_add(wordctrs, id);
      } else {
        //if word doesn't exist in ht, insert into hashtable with new
        // counterset for this word
        wordctrs = assertp(counters_new(), "counters");
        counters_add(wordctrs,id);
        hashtable_insert(ht, word, wordctrs);
      }
    }
    free(word);
  }
}
