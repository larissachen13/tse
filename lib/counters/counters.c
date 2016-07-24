/*
 * counters.c - module for the data structure "counters"
 *
 * counter is a collection of items that have a key and counter associated
 * with each item. Whenever a key is initially added, its counter starts
 * at 1 and incremenets with every successive add of that key.
 *
 * Larissa Chen, July 2016
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include "counters.h"

/********** structs *********/
typedef struct ctritem {
  int key;
  int ctr;
  struct ctritem *next;
} ctritem_t;

typedef struct counters {
  struct ctritem *head;
} counters_t;

/******** static functions and  helper functions *****/
static ctritem_t* ctritem_new(int key);
static ctritem_t *find_key(ctritem_t *curr, int key);


/******* counters functions ****/
/*
*counters_new allocates a new counters data structure
*args: void
*returns: a newly allocated counter, null if it fails to allocate memory
*/
counters_t *counters_new(void) {
  counters_t *ctrs = malloc(sizeof(counters_t));
  if (ctrs == NULL)
    return NULL;
  else {
    ctrs->head = NULL;
  }
  return ctrs;
}

/*
*counters_add adds a new ctritem with the input key into the data structure
*or updates the counter of the existing key, keys are >= 0
*args: ctrs data structure, key to add or whose counter to
*incremeent
*/
void counters_add(counters_t *ctrs, int key) {
  if (key < 0) {
    printf("Key has to be positive or zero\n");
    return;
  }
  if (ctrs != NULL) {
    ctritem_t *found;
    found = find_key(ctrs->head, key);
    if (found == NULL) {//key was not found, insert new at head
      found = ctritem_new(key);
      if (found != NULL) {
        found->next = ctrs->head;
        ctrs->head = found;
      }
    } else { //else increment
      found->ctr++;
    }
  }
}

/*
*find_key finds the ctritem with the input key in a ctr data structure that
*starts at the ctritem curr
*args: ctr data structure to look in, and key to look for
*returns: returns the ctritem with the key, or NULL if not found
*
*/
static ctritem_t *find_key(ctritem_t *curr, int key) {
  //if key is not valid return immediately
  if (key < 0) {
    printf("Key has to be positive or zero\n");
    return NULL;
  }
  //loop through ctr data structure starting at curr and break when key is found
  while(curr != NULL) {
    if (curr->key == key)
      break;
    curr = curr->next;
  }
  if (curr == NULL) { //if not found return NULL
    return NULL;
  }
  return curr;  //if found return curr ptr
}

/*
*counters_get gets the counter for the key in the data structure or returns
*0 if the keys exist
*args: counter data structure, key to retrieve
*returns: current value of the counter for the key, if none or invalid ctrs
* return 0
*/
int counters_get(counters_t *ctrs, int key) {
  if (key < 0) {
    printf("Key has to be positive or zero\n");
    return 0;
  }
  if (ctrs != NULL) {
    ctritem_t *found;
    found = find_key(ctrs->head, key);
    if (found == NULL) {
      return 0;
    } else {
      return found->ctr;
    }
  }
  return 0;
}

/*
*counters_delete deletes the whole ctr data structure
*args: counter data structure to delete
*/
void counters_delete(counters_t *ctrs) {
  if (ctrs != NULL) {
    ctritem_t* curr;
    curr = ctrs->head;
    while(curr != NULL) {
      ctritem_t *temp = curr->next;
      free(curr);
      curr = temp;
    }
    free(ctrs);
  }
}

/*ctritem_new allocates a new ctritem with key of int key and counter of 1
*returns: newly allocated ctritem with key or null if failed to allocate memory
*/
static ctritem_t *ctritem_new(int key) {
  ctritem_t *new = malloc(sizeof(ctritem_t));
  if (new == NULL) {
    return NULL;
  } else {
    new->key = key;
    new->ctr = 1;
  }
  return new;
}
