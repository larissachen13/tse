/*
 * index - a set of functions for creating, saving, loading the index
 *
 * See index.h for interface descriptions.
 *
 * Larissa Chen, July 2016
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <stdbool.h>
 #include <errno.h>
 #include <unistd.h>
 #include "index.h"
 #include "../lib/set/set.h"
 #include "../lib/bag/bag.h"
 #include "../lib/counters/counters.h"
 #include "../lib/hashtable/hashtable.h"
 #include "../lib/memory/memory.h"

 // void index_load(FILE *readfile, index_t *index) {
 //
 // }

 /*
 * index_load- helper function that loads the index represented in the file
 * into an index data structure
 *
 * See header file for more
 */
 void index_load(index_t *index, FILE *readfile) {
   const int len = 200;
   char word[len];
   int doc_id, count;
   counters_t *ctr;
   ctr = NULL;

   while((fscanf(readfile, "%s", word)) == 1) {
     counters_t *ctr = assertp(counters_new(), "counters");
     if(!hashtable_insert(index, word, ctr)) {
       counters_delete(ctr);
     } else {
       while((fscanf(readfile,"%d %d", &doc_id, &count)) == 2){
        counters_set(ctr, doc_id, count);
       }
     }
  }
 }

 /*
 * index_save- helper function that saves a complete index to a file
 *
 * See header file for more
 */
 void index_save(index_t *index, FILE *writefile) {
   hashtable_iterate(index, &hash_iter_func, writefile);
   fclose(writefile);
 }

 /*
 * hash_iter_func- function to be called by hashtable_iterate AND also
 * set_iterate
 *
 * See header file for more
 */
 void hash_iter_func (void *arg, const char *key, void *data) {
   FILE *writefile = (FILE *)arg;
   counters_t *wordctr = (counters_t *)data; //set's data is a counter

   //for each set item which represents a single word write the word to the file
   fputs(key, writefile);
   //now iterate through each <docid, count> pairings for each word
   counters_iterate(wordctr, &ctr_iter_func , writefile);
   fputc('\n', writefile);
 }


 /*
 * ctr_iter_fun- function to be called by counters_iterate, iterates through
 * counter printing each <docid, count> pairing
 *
 * See header file for more
 */
 void ctr_iter_func(void *arg, int key, int count) {
   FILE *writefile = (FILE *)arg;
   fprintf(writefile, " %d %d", key, count);
 }

 /*
 * deleteCounter- function to deleting each counter data item for the hashtable
 */
 void deleteCounter(void* data) {
   counters_t *ctr;
   ctr = (counters_t *)data;
   counters_delete(ctr);
 }

 void ctr_iter_print(void *arg, int key, int count) {
   printf(" %d %d\n", key, count);
 }
