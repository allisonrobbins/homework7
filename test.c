#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"

void testWithoutIO(void);
void readFile(char* input_file, struct hashmap *hm);
void testWithoutIO(void)
{
  struct hashmap *hm = hm_create(7);
  printf("___________________________________________________________\n");
  printf("TEST 1: test adding to hashmap without file I/O\n");
  printf("created hashmap of size %i\n", hm->num_buckets);
  hm_put(hm,"word","doc",2);//tests adding a word to an empty bucket
  hm_put(hm,"word","doc",5);
  hm_put(hm,"word","doc2",3);//tests adding another document to a bucket
  hm_put(hm,"longword","doc2",4);//tests adding another word to a different bucket
  printf("End of add test\n");
  printf("___________________________________________________________\n");
  printf("TEST 2: test get without file I/O\n");
  printf("%i\n",hm_get(hm,"word","doc"));
  printf("%i\n",hm_get(hm,"word","doc2"));
  printf("%i\n",hm_get(hm,"longword","doc2"));
  printf("%i\n",hm_get(hm,"bleh","doc"));
  printf("End of get test\n");
  printf("___________________________________________________________\n");
  hm_destroy(hm);
}
void readFile(char* input_file, struct hashmap *hm)
{
  printf("I made it into readFile method\n");
  FILE *fptr;
  char curr;
  fptr = fopen(input_file, "r");
  printf("opened the file\n");
  curr = fgetc(fptr);
  char* word;
  int index=0;
  printf("got first char\n");
  while(curr != EOF)
  {
    printf("current char is %c\n",curr);
    if(curr ==' ')
    {
      printf("curr is a ' '\n");
      hm_put(hm,word,input_file,1);
      index = 0;
      word = NULL;
    }
    else
    {
      printf("current word is %s\n",word);
      word[index] = curr;
      index++;
    }
    fptr++;
    curr = fgetc(fptr);
  }
  fclose(fptr);
}
int main(void)
{
  testWithoutIO();
  struct hashmap *hm = hm_create(7);
  printf("I made a hashmap\n");
  //readFile("input1.txt",hm);
  //readFile("input2.txt",hm);
  //readFile("input3.txt",hm);
}
