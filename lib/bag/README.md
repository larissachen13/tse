# BAG Module
#### Larissa Chen July 18, 2016

## Compiling
compiling: `make`

## Usage
running the test program: `bagtest`

## About the Bag Module
A bag is a collection of indistinguishable items. Upon calling
`bag_new(void (*delete)(void*)) `, a new empty bag is allocated. After
successfully creating a bag, the bag can grow
to an indefinite size depending on the number of
`bag_insert(bag_t *bag, void *data)` calls. `bag_insert` does not execute
anything when trying to insert into a non-existing bag or insert a NULL
piece of data. Inserting into a bag will always insert at the head of the
bag. And extracting from the bag with `bag_extract(bag_t *bag)` will
always extract the item located at the tail of the bag.In other words,
this bag operates like a queue. First in First out. `bag_extract` should
not delete the bag data structure. That is what`bag_delete(bag_t* bag)` is
for. `bag_delete` should only be used if there was a previous `bag_new`
call or the program will crash.

## Limitations
  - Cannot insert a bagitem with a NULL piece of data
  - Cannot create a new bag with a delete function that points to NULL
  - The delete function need to be able to handle the data passed into
    the module by the data, checking if the deleteitem ptr actually points to
    a valid function is beyond the scope of this module
  - If an item is extracted, the bagitem's node will be freed
    but user must free the extracted data.

## Implementation
The bag `bag_t`data structure is maintained as a linked list. The members
of the bag struct consist of a pointer to the head of the linked list
which contains all of the bagitems `bagitem_t` and also a pointer to a function
that should be used within the module to deallocate the data item in
each bagitem. An empty list is denoted when a bags head pointer `bag->head`
is NULL.


## Test Program
Exit Codes:
  0 - Success
  1 - Malloc Fail
