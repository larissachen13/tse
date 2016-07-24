/*
 * set.c - module for the data structure "bag"
 *
 * set is a collection of (string, data) pairs implemented as a linked list
 * the string serves as the key for each entry
 *
 * Larissa Chen, July 2016
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "set.h"


/**** structs ******/
typedef struct setitem {
 char *key;
 void *data;
 struct setitem *next;
} setitem_t;

typedef struct set {
 struct setitem *head;
 void (*deleteitem)(void *Data);
} set_t;

/**** static function declaration *****/
static setitem_t *setitem_new(char *key, void *data);
static void *set_find_helper(setitem_t *start, char *key);

/*
*set_new creates a new empty set data structure and sets its head to NULL
*returns: the newly allocated set or null if malloc fails
*/
set_t *set_new(void (*delete)(void*)) {
  //before malloc, check if delete is valid argument
  if (delete==NULL) {
    printf("Invalid delete item pointer\n");
    return NULL;
  }
 set_t *new = malloc(sizeof(set_t));
 if (new == NULL) {
   return NULL;
 }  else {
   new->head = NULL;
   new->deleteitem = delete;
 }
 return new;
}

/*
*set_find finds the data for the given key or NULL if key isn't found
*args: set to look in, key to look for
*returns: data or NULL
*/
void *set_find(set_t *set, char *key) {
  //if set is NULL or key is NULL don't insert
  if (set == NULL || key == NULL) {
    return NULL;
  } else {
    return set_find_helper(set->head, key);
  }
}

/*
*set_find_helper assists in finding a given key in a set that starts w/ start
*simple recursive function whose base case is when node is NULL or node's
*key matches key
*args: setitem to begin looking at, key to look for
*returns: data or NULL
*/
static void *set_find_helper(setitem_t *start, char *key) {
  if (start == NULL) {
    return NULL;
  } else if(strcmp(start->key, key) == 0) {
    return start->data;
  } else {
    return set_find_helper(start->next, key);
  }
}

/*
*set_insert inserts a (key, data) pair into the set at the head if key
*doesn't exist already
*args: set to insert it, key and data pair to insert
*returns: false if key already exists, and true if new item was inserted.
*If set is NULL, or you encounter other error, return false.
*/
bool set_insert(set_t *set, char *key, void *data) {
  //first check if key or data is not NULL or empty
  if (key == NULL || data == NULL || set == NULL)
    return false;

  setitem_t *found = set_find(set, key);
  //key is not found, insert
  if (found == NULL) {
    found = setitem_new(key, data);
    if (found == NULL) {
      return false;
    } else {
      //insert new node "found" at the set's head
      found->next = set->head;
      set->head = found;
      return true;
    }
  //key does exist, return false
  } else {
    return false;
  }
}

/*
*setitem_new creates a new setitem node with the (key, data) pair
*args: key, data pair
*return: newly created setitem or NULL if mallloc fails
*/
static setitem_t *setitem_new(char *key, void *data) {
  setitem_t* new = malloc(sizeof(setitem_t));
  if (new == NULL) {
    return NULL;
  } else {
    new->key = malloc(strlen(key)+1);
    if (new->key == NULL) {
      free(new);
      return NULL;
    } else {
      strcpy(new->key, key);
      new->data = data;
      new->next = NULL;
    }
  }
  return new;
}

void set_delete(set_t* set) {
  if (set != NULL) {
    setitem_t* next;
    while(set->head != NULL) {
      next = set->head->next;
      (*set->deleteitem)(set->head->data); //free data
      free(set->head->key); //free key
      free(set->head);  //free node
      set->head = next;
    }
    free(set);
  }
}
