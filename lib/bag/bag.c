/*
 * bag.c- module for the data structure "bag"
 *
 * a bag  is a collection of indistinguishable items; it starts empty,
 * grows as the caller adds one item at a time, and shrinks as the caller
 * extracts one item at a time. It could be empty, or could contain hundreds
 * of items. Since items are indistinguishable, the module is free to
 * return any item from the bag.
 * Larissa Chen, July 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include "bag.h"

/**** local bagitem and global bag *****/
typedef struct bagitem {
  void *data;
  struct bagitem *next;
} bagitem_t;

typedef struct bag {
  struct bagitem *head;
  void (*deleteitem)(void *Data);
} bag_t;

/**** local bag_item functions ****/
static bagitem_t *bagitem_new(void *data);

/**** bag functions ****/
/*
* bag_new allocates a new empty bag
* args: void
* returns: a new bag or null if bag cannot be allocated
*/
bag_t *bag_new(void (*delete)(void*)) {
  //before malloc check if delete is valid argument function
  if (delete == NULL) {
    printf("Delete function cannot be NULL \n");
    return NULL;
  }
  bag_t *bag= malloc(sizeof(bag_t));
  if (bag == NULL)
    return NULL;
  else {
    bag->head = NULL;
    bag->deleteitem = delete;
  }
  return bag;
}

/*
* bag_insert inserts a new item in the bag
* args: bag to insert a new item in, and the data to be associated with
* the new item
* return: void
*/
void bag_insert(bag_t *bag, void *data) {
  //if bag exists
  if (bag != NULL && data != NULL) {
    //create new bag item
    bagitem_t *new_bagitem = bagitem_new(data);
    if(new_bagitem != NULL)  {
    //insert before head and update head
      new_bagitem->next = bag->head;
      bag->head = new_bagitem;
    }
  }
}

/*
* bag_extract remove item at the head and returns it
* arg: bag to remove an item from
* returns: pointer to data of removed bag item, or null if no items
*/
void *bag_extract(bag_t *bag) {
  void* data_extract;
  bagitem_t *next;

  if (bag == NULL) {
    return NULL; //bag doesn't exist
  }
  if (bag->head == NULL) {
    printf("Can't extract more bag is empty\n"); 
    return NULL;  //bag is empty
  } else {
    next = bag->head->next;
    data_extract = bag->head->data;
    free(bag->head);
    bag->head = next;
    return data_extract;
  }
}

/*
* bag_delete deletes the entire bag
* arg: bag to delete
*/
void bag_delete(bag_t *bag) {
  if (bag != NULL) {
    bagitem_t* next;
    while(bag->head != NULL) {
      next = bag->head->next;
      (*bag->deleteitem)(bag->head->data); //delete data
      free(bag->head);//delete item
      bag->head = next;
    }
    free(bag);
  }
}

/*
* create a new bag_item
* input: data to be stored in the new bag item
* output: new bag item, or null if bag item can't be allocated
*/
static bagitem_t *bagitem_new(void *data) {
  bagitem_t *new = malloc(sizeof(bagitem_t));
  if (new == NULL)
    return NULL;
  else {
    new->data = data;
    new->next = NULL;
  }
  return new;
}
