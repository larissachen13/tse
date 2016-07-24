
# SET Module
#### Larissa Chen July 18, 2016

## Compiling
compiling: `make`

## Usage
running the test program: `settest`

## About the Set Module
A set is a collection of unique (string, data) pairs. A new set can be allocated
by calling `set_new(void (*delete)(void*))`. To add to the collection
`set_insert(set_t *set, char *key, void *data)` is called with a non-NULL
key and piece of data, which return true if it successfully entered the
new key, data pair or false if the key already existed in the collection.
To find the corresponding data for an existing key in the set,
`set_find(set_t *set, char *key)` is called. And lastly `set_delete` is used
to delete the entire set module.  

## Limitations
  - Cannot insert a set item with a NULL piece of data or a NULL key
  - Cannot create a hashtable module with a delete function that points to NULL
  - The delete function need to be able to handle the data passed into
    the module by the data, checking if the deleteitem ptr actually points to
    a valid function is beyond the scope of this module

## Implementation
The hashtable `hashtable_t` module is implemented as an array of set pointers.
Each set represents all the keys that hash into that slot. If each elements
contains a NULL pointer than the hashtable is empty. 


## Test Program
Exit Codes:
  0 - Success
  1 - Malloc Fail
