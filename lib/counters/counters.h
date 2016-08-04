/*
 * counters.h - header file for counters module
 *
 *
 * Larissa Chen, July 2016
 */

#ifndef __COUNTERS_H
#define __COUNTERS_H

/********* global counters type **********/
typedef struct counters counters_t;

/*
create a new empty counters data structure
*/
counters_t *counters_new(void);

/*
if key exists, increment its counter; otherwise add key and set
its counter to 1, keys are all positive integers >=0
*/
void counters_add(counters_t *ctrs, int key);

/*
return the current value of the counter for key, or 0 if key is not found
keys are all positive integers >=0
*/
int counters_get(counters_t *ctrs, int key);

/*
delete the whole data structure, and its contents
*/
void counters_delete(counters_t *ctrs);

/* Set value of the counter indicated by key.
 * If the key does not yet exist, create a counter for it
 * and initialize its counter value to 'count', adding it to the head of counter
 * NULL counters is ignored.
 */
void counters_set(counters_t *ctrs, int key, int count);

/* Iterate over all counters in the set (in undefined order):
 * call itemfunc for each item, with (arg, key, count).
 */
void counters_iterate(counters_t *ctrs,
		      void (*itemfunc)(void *arg, const int key, int count),
		      void *arg);

#endif
