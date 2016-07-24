# COUNTERS module
#### Larissa Chen July 18, 2016

## Compiling
compiling: `make`

## Usage
running the test program: `counterstest`

## About the Counters Module
A Counter data structure is a collection of items that have a key and
counter associated with every entry. A Counter can be created with
`counters_new(void) `. Upon creating a new Counter, one can add keys using
`counters_add(counters_t *ctrs, int key)`. A new key is initiated with its
counter value set at 0, and every successive add of that key increments
its counter accordingly. Keys are restricted to be positive or zero
integers only. Any insert of a negative key is ignored. To retrieve the counter
for a key, use `counters_get(counters_t *ctrs, int key)`, which returns
`0` if the key was not found or is not valid. To delete an existing
Counter, use `counters_delete(counters_t *ctrs)`.

## Implementation
The count `counters_t`data structure is maintained as a linked list.
Each member is a ctritem that holds a key and a pointer to the next member.
An empty list is denoted by the pointer `counters_t->head` being NULL.

## Limitations
  - Cannot insert a counters item with a negative key
  
## Test Program
Exit Codes:
  0 - Success
  1 - Malloc Fail
