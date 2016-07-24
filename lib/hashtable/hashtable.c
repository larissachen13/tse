/*
* hashtable.c - module for the data structure hashtable
*
* hashtable is a collection of (string, data) pairs implemented
* as array of slots wiht a list for each slot
*
* Larissa Chen, July 2016
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hashtable.h"
#include "../set/set.h"
#include "jhash.h"

/***** declare structs ****/
typedef struct hashtable {
  set_t **slots;
  int size;
  void (*deleteitem)(void *Data);
} hashtable_t;

/***** static functions ****/
void delete(hashtable_t *to_delete);

/*
* hashtable_new creates a new empty hash table data structure
* args: number of slots for the keys in the hashtable, ptr to deleteitem
* function...ptr cannot point to null
* returns: hashtable data structure, null if malloc fails
*/
hashtable_t *hashtable_new(const int num_slots, void (*delete)(void*)) {
  if (delete == NULL) {
    printf("Invalid delete function as argument\n");
    return NULL;
  }

  //malloc new hashtable
  hashtable_t *new = malloc(sizeof(hashtable_t));
  if (new == NULL) {
    return NULL;
  } else {
    //malloc enough space for num_slots * size of set pointer
    //initialize array to have elements of NULL
      new->slots = malloc(num_slots * sizeof(set_t*));
      if (new->slots == NULL) { //if malloc fails, free new hash and return
        free(new);
        return NULL;
      }
      new->size = num_slots;
      new->deleteitem = delete;
    }
  return new;
}

/*
return data for the given key, or NULL if not found or invalid key is searched
for
*/
void *hashtable_find(hashtable_t *ht, char *key) {
  if (key == NULL) {
    printf("Invalid NULL key to search for\n");
    return NULL;
  }
  set_t* keys_set;
  unsigned long hash_code;

  if (ht == NULL) {
    return NULL;
  } else {
    //compute hash code
    hash_code = JenkinsHash(key, ht->size);
    keys_set = ht->slots[hash_code];
    if (keys_set==NULL) { // not found return NULL
      return NULL;
    }
  }
  return set_find(keys_set, key);  //found, return ptr to list
}

/*
return false if key already exists, and true if new item was inserted.
If ht is NULL, or you encounter other error, return false.
*/
bool hashtable_insert(hashtable_t *ht, char *key, void *data) {
  unsigned long hash_code;
  if (key == NULL || data == NULL) {
    printf("Cannot insert key or data of value NULL\n");
    return false;
  }
  //try looking for the key, if found return
  if(hashtable_find(ht, key)) {
    printf("Key \'%s\'' already exists in the hashtable\n", key);
    return false;
  } else {
    //insert into hashtable
    hash_code = JenkinsHash(key, ht->size);
    //create new set for slot if necessary
    if (ht->slots[hash_code] == NULL) {
      ht->slots[hash_code] = set_new(ht->deleteitem);
      //handle NULL malloc test in set_insert function
    }
  }
  return set_insert(ht->slots[hash_code], key, data);
}

void hashtable_delete(hashtable_t* ht) {
  if (ht != NULL) {
    //loop through and delete each set
    for (int i = 0; i < ht->size; i++) {
      if (ht->slots[i] != NULL)
        set_delete(ht->slots[i]);
    }
    free(ht->slots);
    free(ht);
  }
}
