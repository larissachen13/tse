
# HASHTABLE Module
#### Larissa Chen July 18, 2016

## Compiling
compiling: `make`

## Usage
running the test program: `hashtabletest`

## About the Hashtable Module
A hashtable is a collection of unique (string, data) pairs stored in an array.
Collisions for the same slot in the array are handled using a linked list
for each slot in the array. A new hashtable can be allocated by calling
`hashtable_new(const int num_slots, void (*delete)(void*))` where num_slots
is the maximum number of slots in the hash table, and delete is the delete item
function pointer. Delete cannot point to a null function. Use `hashtable_insert`
to add a new string, data pair to the hashtable. A string key is converted
to a slot in the hashtable using the Jenkins Hash function provided to us.
The modulus for the hash function, is the size of the hashtable provided as
an argument in the hashtable constructor. One can search for a certain key
using the hashtable_find function.

## Limitations
  - Cannot insert an item with a NULL key or a NULL piece of data 
  - Cannot create a set module with a delete function that points to NULL
  - The delete function need to be able to handle the data passed into
    the module by the data, checking if the deleteitem ptr actually points to
    a valid function is beyond the scope of this module

## Implementation
The set `set_t`data structure is maintained as a linked list. The members
of the set struct consist of a pointer to the head of the linked list
which contains all of the setitems `setitem_t` and also a pointer to a function
that should be used within the module to deallocate the data item in
each setitem. An empty list is denoted when a sets head pointer `set->head`
is NULL.


## Test Program
Exit Codes:
  0 - Success
  1 - Malloc Fail
