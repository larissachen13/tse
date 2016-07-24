#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../set/set.h"
#include "hashtable.h"

void call_hashtable_insert(hashtable_t *ht, char **keys);
void call_hashtable_find(hashtable_t *ht, char *key);

//see testing file for what was tested 
int main() {

  //create a hashtable of size 5
  hashtable_t *hash = hashtable_new(3, &free);
  if (hash != NULL) {
    //insert 11 keys into the hashtable of size 3 to assure collision
    printf("Creating a hash table...\n");
    char* key_list[] = {"a", "b", "b", "c", "d", "e", "f", "g", "g", NULL};
    call_hashtable_insert(hash, key_list);

    printf("\nNow testing the find function\n");
    call_hashtable_find(hash, "a");
    call_hashtable_find(hash, "b");
    call_hashtable_find(hash, "bb");

    hashtable_delete(hash);
  }
}

/*
*testing function that calls hashtable_insert successively in order to build
*a hashtable based on the array of keys passed in  ...also prints out outcome
*messages indicating if the insertion was successful
*/
void call_hashtable_insert(hashtable_t *ht, char **keys){
  for (int i = 0; i < 10; i++) {
    int *data = malloc(sizeof(int));
    *data =  i;
    if(hashtable_insert(ht, keys[i], data)) {
      printf("Inserted <key, data> pair <%s, %d> \n", keys[i], *data);
    } else {
      free(data); //free the data that is not successfully inserted
    }
  }
}

/*
*testing function that calls hashtable_find in order to find a particular
*key in the ht hashtable...also prints out outcome messages indicating
*if the insert was successful
*/
void call_hashtable_find(hashtable_t *ht, char *key) {
  void *data;
  if ((data = hashtable_find(ht, key))) {
    printf("Found <key, data> pair <%s, %d> \n", key, *(int*)data);
  } else {
    printf("Key %s not found\n", key);
  }
}
