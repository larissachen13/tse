/*
 * counterstest.c-test program for the counters module
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "counters.h"

int main () {
  counters_t* ctr1 = counters_new();
  if (ctr1 == NULL) {
    printf("Error in allocating memory for Counter");
    exit(1);
  }
  //add entries into ctr1
  printf("\nAdding each key, a key number of times\n");
  counters_add(ctr1, 1);
  counters_add(ctr1, 2);
  counters_add(ctr1, 2);
  counters_add(ctr1, 3);
  counters_add(ctr1, 3);
  counters_add(ctr1, 3);
  counters_add(NULL, 1); //ignore
  counters_add(ctr1, -1); //also ignore

  //get the counter for each
  int counter;
  for (int i = 0; i <= 3; i++) {
    counter = counters_get(ctr1, i);
    if (counter) {
      printf("Counter for key %d is: %d\n", i, counter);
    } else {
      printf("Key %d does not exist in this list\n", i);
    }
  }

  counters_delete(ctr1); 
}
