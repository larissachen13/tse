/*
 * bag.h - header file for bag module
 *
 *
 * Larissa Chen, July 2016
 */

#ifndef __BAG_H
#define __BAG_H

/********* global bag type **********/
typedef struct bag bag_t;

/******** functions ***************/
/*
create a new empty bag data structure
return null if error in allocating a new bag
*/
bag_t *bag_new(void (*delete)(void*)); 

/*
add a new item to the bag with associated data of data
*/
void bag_insert(bag_t *bag, void *data);

/*
remove any item from the bag & return it to the caller
return null if bag is empty
*/
void *bag_extract(bag_t *bag);

/*
*Remove the entire bag
*/
void bag_delete(bag_t *bag);

#endif
