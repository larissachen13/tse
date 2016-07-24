/*
 * counters.h - header file for counters module
 *
 *
 * Larissa Chen, July 2016
 */

#ifndef __BAG_H
#define __BAG_H

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

#endif
