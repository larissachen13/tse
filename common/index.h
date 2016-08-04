/*
 * index - a set of functions for creating, saving, loading the index
 *
 * The index is keyed by words (strings) and stores counter sets;
 * each counter set represents the set of documents where that word
 * appeared, and the number of occurrences of that word in each document.
 *
 * Name, Summer 2016
 */

#ifndef __INDEX_H
#define __INDEX_H

#include <stdio.h>
#include <stdbool.h>
#include "../lib/hashtable/hashtable.h"
#include "../lib/counters/counters.h"
#include "../lib/memory/memory.h"

/**************** global types ****************/

// The index is actually a hashtable.
typedef hashtable_t index_t;

/********** add function prototypes here *********/

 void index_load(index_t *index, FILE *readfile);
/*
* index_save- helper function that saves a complete index to a file
*
* Assumptions:
*  1. index has already been instantiated and built
*  2. writefile is a writeable file that is already open
*
* Pseudocode:
*  1. iterate through the hashtable and write each words <docid, count>
*     pairings to writefile
*  2. close writefile
*/
void index_save(index_t *index, FILE *writefile);

/*
* hash_iter_func- function to be called by hashtable_iterate AND also
* set_iterate
*
* Args:
*  1. arg = writefile passed into the iteration function
*  2. key = key of each set item, that is the word
*  3. data = counter for each set item, that is the words counters list
*
* Pseudocode:
*  1. iterate through the hashtable and write each words <docid, count>
*     pairings to writefile
*  2. close writefile
*/
void hash_iter_func (void *arg, const char *key, void *data);


/*
* ctr_iter_fun- function to be called by counters_iterate, iterates through
* counter printing each <docid, count> pairing
*
* Args:
*  1. arg = writefile passed into the iteration function
*  2. key = key of each ctrs item, that is the docid
*  3. data = count for each ctrs item, that is the words frequency in that doc
*
* Pseudocode:
*  1. iterate through the counters list writing each counter item to the file
*     pairings to writefile
*/
void ctr_iter_func(void *arg, int key, int count);

 /*
 * deleteCounter- function to deleting each counter data item for the hashtable
 */
 void deleteCounter(void* data); 



#endif // __INDEX_H
