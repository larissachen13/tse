/*
 * settest.c-test program for the set module
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "set.h"

void call_set_insert(set_t *set, char *key, void *data);

int main () {
  set_t* set1 = set_new(&free);
  //malloc the data so the user-passed function 'free()' will work 
  int *one = malloc(sizeof(int));
  int *two = malloc(sizeof(int));
  *one = 1;
  *two = 2;
  char* first = "first";
  char* second = "second";
  char* foo = "foo";
  if (set1 != NULL) {
    call_set_insert(set1, first, one);
    call_set_insert(set1, second, two);
    call_set_insert(set1, foo, NULL);
    call_set_insert(set1, NULL, two);
    call_set_insert(set1, second, two);

    void *data = set_find(set1, first);
    printf("Data for %s is: %d\n",first, *(int*)data);

    set_delete(set1);
  }
}

/*
*tester function that directly calls the set_insert function with the arguments
*passed, displays a success or error message depending on outcome of
*the set_insert function
*args: same args to pass into set_insert
*/
void call_set_insert(set_t *set, char *key, void *data) {
  //null check arguments of key and data so they do not trigger a
  //segfault while printing, in doing so, the original versions
  //can be safely passed to the set_insert function to test how set
  //handles these NULL pieces of data
  int *data_int = data;
  if (set_insert(set, key, data)) {
    printf("Successfully inserted %s w/ data of %d \n", key, *data_int);
  } else {
    //print which argument was first to trigger the error or default error
    //message that key already exists
    if (key == NULL)
      printf("Not successful in inserting NULL key ");
    else if (data == NULL)
      printf("Not successful in inserting NULL data");
    else
      printf("Key \'%s\' already exists\n", key);
    printf("\n");
  }
}
