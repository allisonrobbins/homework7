#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"

void testWithoutIO(void);
void testWithoutIO(void)
{
  struct hashmap *hm = hm_create(7);
  printf("___________________________________________________________\n");
  printf("TEST 1: test adding to hashmap without file I/O\n");
  printf("created hashmap of size %i\n", hm->num_buckets);
  hm_put(hm,"word","doc",2);
  hm_put(hm,"word","doc2",3);
  hm_put(hm,"wordy","doc2",4);
  printf("End of add test\n");
  printf("___________________________________________________________\n");
}

int main(void)
{
  testWithoutIO();  
}
