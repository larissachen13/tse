/*
 * indextest - load an index, and save it, to test those functions
 * See README.md for more usage details.
 *
 * Larissa Chen, July 2016
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


 /*
  * main driver test program that first validates arguments then loads
  * index data structure from one file and resaves it to a new file
  *
  * index_load, index_save, and deleteCounter function are defined in
  * ../common/index.c part of the common library
  */
 int main(int argc, char*argv[]) {
   FILE *oldfile;
   FILE *newfile;
   index_t *index = assertp(hashtable_new(100000, &deleteCounter), "hashtable");

   //validate arguments
   if (argc != 3) {
   printf("Usage Error: Invalid number of arguments. ./indextest [oldFileName]");
   printf("[newFileName]\n");
   exit(1);
   }

   // validate that oldfile can be read
   oldfile = fopen(argv[1], "r");
   if(oldfile == NULL) {
     printf("Invalid Argument: Cannot read file %s\n", argv[1]);
     exit(1);
   }  else {
     fclose(oldfile);
   }

   // validate that newfile can be written to
   newfile = fopen(argv[2], "w");
   if (newfile == NULL) {
     printf("Invalid Argument: Cannot write file %s\n", argv[2]);
     exit(1);
   } else {
     fclose(newfile);
   }

   // load index from oldfile
   oldfile = fopen(argv[1], "r");
   index_load(index, oldfile);
   fclose(oldfile);

   // save index to newfile
   newfile = fopen(argv[2], "w");
   index_save(index, newfile);

   hashtable_delete(index);

 }
