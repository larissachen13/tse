/*
* hastable.h - header file for hashtable module
*
*
* Larissa Chen, July 2016
*/
#include "../set/set.h"
#ifndef __HASHTABLE_H
#define __HASHTABLE_H

typedef struct hashtable hashtable_t;

/*
create a new empty hash table data structure with delete function as argument
*/
hashtable_t *hashtable_new(const int num_slots, void (*delete)(void*));

/*
return data for the given key, or NULL if not found
*/
void *hashtable_find(hashtable_t *ht, char *key);

/*
return false if key already exists, and true if new item was inserted.
If ht is NULL, or you encounter other error, return false.
*/
bool hashtable_insert(hashtable_t *ht, char *key, void *data);

/* Iterate over all items in hashtable (in undefined order):
 * call itemfunc for each item, with (arg, key, data).
 */
void hashtable_iterate(hashtable_t *ht,
		       void (*itemfunc)(void *arg, const char *key,void *data),
		       void *arg);

void hashtable_delete(hashtable_t* ht);

#endif
