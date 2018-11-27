#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"

void testWithoutIO(void);
void readFile(void);
void testWithoutIO(void)
{
  struct hashmap *hm = hm_create(7);
  printf("___________________________________________________________\n");
  printf("TEST 1: test adding to hashmap without file I/O\n");
  printf("created hashmap of size %i\n", hm->num_buckets);
  hm_put(hm,"word","doc",2);//tests adding a word to an empty bucket
  hm_put(hm,"word","doc",5);
  hm_put(hm,"word","doc2",3);//tests adding another document to a bucket
  hm_put(hm,"wordy","doc2",4);//tests adding another word to a different bucket
  printf("End of add test\n");
  printf("___________________________________________________________\n");
  printf("TEST 2: test get without file I/O\n");
  printf("%i\n",hm_get(hm,"word","doc"));
  printf("%i\n",hm_get(hm,"word","doc2"));
  printf("%i\n",hm_get(hm,"wordy","doc2"));
  printf("%i\n",hm_get(hm,"bleh","doc"));
  printf("End of get test\n");
  printf("___________________________________________________________\n");
  hm_destroy(hm);
}
void readFile(void)
{
  
  
}



int main(void)
{
  testWithoutIO();  
}
