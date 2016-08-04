/*
* set.h - header file for set module
*
*
* Larissa Chen, July 2016
*/
#ifndef __SET_H
#define __SET_H

typedef struct set set_t;

/*
create a new empty set data structure initialized with delete function
*/
set_t *set_new(void (*delete)(void*));

/*
return data for the given key, or NULL if key is not found
*/
void *set_find(set_t *set, char *key);

/*
return false if key already exists, and true if new item was inserted.
If set is NULL, or you encounter other error, return false.
*/
bool set_insert(set_t *set, char *key, void *data);

void set_delete(set_t* toDestroy);

/* Iterate over all items in set (in undefined order):
 * call itemfunc for each item, passing (arg, key, data).
 */
void set_iterate(set_t *set,
		  void (*itemfunc)(void *arg, const char *key, void *data),
		  void *arg);

#endif
