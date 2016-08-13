/*
 * querier
 * See README.md for more usage details
 *
 * Larissa, July 2016
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>
#include "../lib/set/set.h"
#include "../lib/bag/bag.h"
#include "../lib/counters/counters.h"
#include "../lib/hashtable/hashtable.h"
#include "../lib/memory/memory.h"
#include "../common/index.h"
#include "../common/web.h"
#include "../common/word.h"
#include "../common/webpage.h"
#include "../common/file.h"

typedef struct doc doc_t;
typedef struct doc {
  int doc;
  int count;
} doc_t;

int tokenize(char **tokenized, char *query);
int isValidToken(char *str);
bool printAndValidate(char **query, int queryLen);
void printError(int errorFlag, char *oper1, char *oper2);
counters_t *combineQueries(index_t *index, char **tokenized, int numToken);
counters_t *andSequence(index_t *index, char **tokens, int beg, int end);
counters_t *ctrsMultiply(counters_t *mult1, counters_t *mult2);
counters_t *ctrsPlus(counters_t *sum, counters_t *prod);
void ctrAddEach(void *arg, int key, int count);
void ctrMultiplyEach(void *arg, int key, int count);
void ctrs_size(void *arg, int key, int count);
void ctrs_populate(void *arg, int key, int count);
void sortAndPrint(counters_t *toSort, char *dir);
int compare(const void *a, const void *b);
int min(int x, int y);

int main (int argc, char* argv[]) {
  const int MAX = 500;
  FILE *indexfile;
  char *dir;
  char *queries[MAX];
  int numQueries, numToken;
  char *query;
  char *tokenized[MAX];
  bool error;

  // validate command-line
  if (argc != 3) {
  printf("Usage Error: Invalid number of arguments. ./querier [pageDirectory]");
  printf("[indexFilename]\n");
  exit(1);
  }

  if (!is_pageDirectory(argv[1])) {
    printf("Invalid Argument: Directory %s wasn't produced by crawler program\n", argv[1]);
    exit(1);
  } else {
    dir = argv[1];
  }

  indexfile = fopen(argv[2], "r");
  if(indexfile == NULL) {
    printf("Invalid Argument: Cannot read file %s\n", argv[2]);
    exit(1);
  } else {
    fclose(indexfile);
  }

  // store all the queries in an array
  numQueries = 0;
  while((query = readline(stdin)) != NULL) {
    queries[numQueries] = query;
    numQueries++;
  }

  // Loop through each query
  for (int i = 0; i < numQueries; i++) {

    // tokenize the query
    error = false;
    numToken = tokenize(tokenized, queries[i]);
    if (numToken == -1) // returns -1 if encounters 'bad character'
      error = true;
    if (!error) {
      if(!printAndValidate(tokenized, numToken)) {  // returns false if there are literal "and"/"or" errors 
        error = true;
      }

      if (!error) {
        indexfile = fopen(argv[2], "r");
        index_t *index = assertp(hashtable_new(100000, &deleteCounter), "hashtable");
        index_load(index, indexfile);
        fclose(indexfile);

        // combine the counters
        counters_t *docs = combineQueries(index, tokenized, numToken);

        // sort and print docs counter
        sortAndPrint(docs, dir);

        //clean up
        if (docs != NULL)
          counters_delete(docs);
        hashtable_delete(index);
        for (int i = 0; i < numQueries; i++) {
          if (queries[i] != NULL)
            free(queries[i] );
        }
      }
    }
  }
}

int tokenize(char **tokenized, char *query) {
  char *token;
  char c;
  int numToken = 0;

  token = strtok(query, " \t");
  while (token) {
    if ((c = isValidToken(token)) == 0) { // returns 0 if token is valid
      tokenized[numToken] = token;
      numToken++;
    }
    else {
      printf("Error: bad character '%c' in query.\n", c);
      return -1;
    }
    token = strtok(NULL, " \t");
  }
  return numToken;
}

int isValidToken(char *str) {
  char c;
  for (int i = 0; i < strlen(str); i++) {
    c = str[i];
    //check if char is not a leter
    if ((c <'A' || c > 'z') || (c < 'a' && c > 'Z') )
      return c;
    str[i] = tolower(c);
  }
  return 0;
}

bool printAndValidate(char **query, int queryLen) {
  bool prevWasOper = true;
  int errorFlag = 0;  // 1 = operator was first, 2 = consecutive operators,
                      // 3 = operator was last
  char op1[3];      // store the certain operators here
  char op2[3];

  // loop through each token printing it and looking for errors
  printf("Query:");
  for (int i = 0; i < queryLen; i++) {
    printf(" %s", query[i]);

    // only run logic if an error has not been found yet
    if (errorFlag == 0) {
      // current token is operator
      if((strcmp("or", query[i])) == 0 || (strcmp("and", query[i]) == 0)) {
        //previous token was operator also
        if (prevWasOper) {
          if (i == 0) { // trigger flag 1
            errorFlag = 1;
            strcpy(op1, query[i]);
          } else {  // trigger flag 2
            errorFlag = 2;
            strcpy(op2, query[i]);
          }
          prevWasOper = false;
        } else {
        // previous token was not an operator, save this operator
          strcpy(op1, query[i]);
          prevWasOper = true;
        }
      } else {
      // current token isn't operator
        prevWasOper = false;
      }
    }
  }
  if (prevWasOper) {  //last token was operator, trigger flag 3
    errorFlag = 3;
    strcpy(op1, query[queryLen-1]);
  }

  printf("\n");
  if (errorFlag) {  // if there's an error print it
    printError(errorFlag, op1, op2);
    return false;
  }
  return true;
}

void printError(int errorFlag, char *oper1, char *oper2) {
  if(errorFlag == 1) {  // handle if operator was first token
    printf("Error: '%s' cannot be first\n", oper1);
  }
  else if (errorFlag == 2) { // handle if two operators in a row
    printf("Error: '%s' and '%s' cannot be adjacent\n", oper1, oper2);
  }
  else {  // handle if operator was last
    printf("Error: '%s' cannot be last\n", oper1);
  }
}

counters_t *combineQueries(index_t *index, char **tokenized, int numToken) {
  counters_t *sum = assertp(counters_new(), "counters");
  counters_t *prod;
  int began = 0;
  for (int i = 0; i <= numToken; i++) {
    if ((i == numToken)|| (strcmp(tokenized[i], "or"))== 0) {
      prod = andSequence(index, tokenized, began, i - 1);
      began = i + 1;
      ctrsPlus(sum, prod);
    }
  }
  return sum;
}

counters_t *andSequence(index_t *index, char **tokens, int beg, int end){
  // set base counter to ctr for first word in sequence
  counters_t *prod = hashtable_find(index, tokens[beg]);
  for (int i = beg + 1; i <= end; i++) {
    if ((strcmp(tokens[i], "and")) != 0) {
      prod = ctrsMultiply(prod, hashtable_find(index, tokens[i])); // handle null multiply case
    }
  }
  return prod;
}

counters_t *ctrsPlus(counters_t *sum, counters_t *prod) {
  // iterate over the 2nd set and add into 1st
  counters_iterate(prod, &ctrAddEach, sum);
  return sum;
}

void ctrAddEach(void *arg, int key, int count) {
  counters_t *sum;
  sum = (counters_t *)arg;
  counters_set(sum, key, count + counters_get(sum, key));
}

counters_t *ctrsMultiply(counters_t *mult1, counters_t *mult2) {
//iterate over 2nd counter searching in 1st counter
  counters_t *operands[] = { mult1, mult2 };
  counters_iterate(mult2, &ctrMultiplyEach, operands);
  return mult2;
}

void ctrMultiplyEach(void *arg, int key, int count) {
  counters_t **ops;
  ops = (counters_t **)arg;

  // find in first counter
  int inFirst = counters_get(ops[0], key);
  // update second counter
  counters_set(ops[1], key, min(count, inFirst));
}

void sortAndPrint(counters_t *toSort, char *dir) {
  doc_t *sortedDocs;
  char *filename;
  int doc, count;
  char *url;

  //iterate to find out size
  int numMatches = 0;
  counters_iterate(toSort, &ctrs_size, &numMatches);

  if (numMatches != 0) {
      sortedDocs = malloc(numMatches*sizeof(doc_t));
      counters_iterate(toSort, &ctrs_populate, &sortedDocs);
      sortedDocs = sortedDocs-numMatches;
      qsort(sortedDocs, numMatches, sizeof(doc_t), compare);
  } else {
    sortedDocs = NULL;
  }
  printf("Matches %d documents (ranked): \n", numMatches);
  //print each match
  for (int i = 0; i < numMatches; i++) {
    doc = sortedDocs[i].doc;
    count = sortedDocs[i].count;
    filename = malloc(strlen(dir)+ (int)log10(doc) + 10);
    sprintf(filename, "%s/%d", dir, doc);
    FILE *docFile = fopen(filename, "r");
    if (docFile != NULL) {
      url = readline(docFile);
      printf("score  %d doc\t%d: %s\n", count, doc, url);
      if (url != NULL)
        free(url);
    }
    fclose(docFile);
    free(filename);
  }
  if (sortedDocs != NULL) {
    free(sortedDocs);
  }
}

void ctrs_size(void *arg, int key, int count) {
  int *i;
  i = (int *)arg;

  if (count != 0)
    (*i)++;
}

void ctrs_populate(void *arg, int key, int count) {
  doc_t **docPointer;
  docPointer = (doc_t **)arg;
  if (count != 0) {
    (*docPointer)->doc = key;
    (*docPointer)->count = count;
    *docPointer = *docPointer + 1;
  }
}

int compare(const void *a, const void *b) {
  doc_t *x = (doc_t *) a;
  doc_t *y = (doc_t *) b;
  return (y->count - x->count);
}

int min(int x, int y) {
  if (x < y)
    return x;
  return y;
}
