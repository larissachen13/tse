/*
 * bagtest.c - test program for bag module
 *
 *
 * Larissa Chen, July 2016
 */
#include <stdio.h>
#include <stdlib.h>
#include "bag.h"

int main() {
  bag_t *bag;
  char *extract_string;
  int *extract_int;

  bag = bag_new(&free);
  if (bag == NULL) {
    printf("Error in allocating enough memory for bag data structure");
    exit(1);
  }
  //insert items into bag
  printf("Insert and Extract strings [one, two, three, three] into and out of bag\n");
  char one[] = "One";
  char two[] = "Two";
  char three[] = "Three";
  bag_insert(bag, one);
  bag_insert(bag, two);
  bag_insert(bag, three);
  bag_insert(bag, three);
  bag_insert(NULL, one); // should be ignored
  bag_insert(bag, NULL); // this should also be ignored

  //extract the bag's items
  do {
    //should extract bag's in reverse order they are put in
    extract_string = bag_extract(bag);
    if (extract_string != NULL)
      printf("Extracted String: %s\n", extract_string);
  } while (extract_string != NULL);

  //Read new items into the now empty bag
  printf("\nNow adding and extracting integers [1, 2] into the empty bag\n");
  int first = 1;
  int second = 2;
  bag_insert(bag, &first);
  bag_insert(bag, &second);
  do {
    extract_int = bag_extract(bag);
    if (extract_int != NULL)
      printf("Extracted int: %d\n", *extract_int);
  } while (extract_int != NULL);

  //delete bag
  bag_delete(bag);
  bag = bag_new(NULL); //will create
  if (bag != NULL)
    bag_delete(bag); //this second deletion should succeed
  exit(0);
}
