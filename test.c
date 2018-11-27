#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"

void testWithoutIO(void);
void readFile2(char* input_file, struct hashmap *hm);
void readFile3(char* input_file);
void hm_print(struct hashmap* hm);
void testWithoutIO(void)
{
  struct hashmap *hm = hm_create(8);
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
  printf("%i\n",hm_get(hm,"word","doc"));//test that everything was inputted correctly
  printf("%i\n",hm_get(hm,"word","doc2"));
  printf("%i\n",hm_get(hm,"longword","doc2"));
  printf("%i\n",hm_get(hm,"longword","doc3"));//test a document that does not exist
  //printf("%i\n",hm_get(hm,"bleh","doc"));//test a word that does not exist
  printf("End of get test\n");
  printf("___________________________________________________________\n");
  printf("TEST 3: does my destroy function work?\n");
  //hm_destroy(hm);
  printf("I'm not even gonna try\n");
  printf("___________________________________________________________\n");
  printf("TEST 4: remove\n");
  hm_remove(hm,"word","doc");
  printf("it worked\n");
  printf("%i\n",hm_get(hm,"word","doc"));//test if its really gone
  printf("___________________________________________________________\n");
}
void readFile2(char* input_file,struct hashmap *hm)
{
  FILE *fptr;
  int i;
  char curr;
  fptr = fopen(input_file, "r");
  //printf("opened file %s\n",input_file);
  while(curr!=EOF)
  {
    //printf("Starting to read a new word\n");
    char arr[50];
    curr = (char)fgetc(fptr);
    int k=0;
    while(curr!=' ' && curr!= EOF)
    {
      arr[k++] = curr;
      curr = (char)fgetc(fptr);
    }
    arr[k] = 0;
    hm_put(hm,arr,input_file,1);
    for(i=0; i<k; i++)
    {
      printf("%c",arr[i]);
    }
    printf(" \n");
    if(curr == EOF)
    {
      return;
    }
  }
  printf("\n");
}
void readFile3(char* input_file)
{
  FILE *fptr;
  int i;
  char curr;
  fptr = fopen(input_file, "r");
  //printf("opened file %s\n",input_file);
  while(curr!=EOF)
  {
    //printf("Starting to read a new word\n");
    char arr[50];
    curr = (char)fgetc(fptr);
    int k=0;
    while(curr!=' ' && curr!= EOF)
    {
      arr[k++] = curr;
      curr = (char)fgetc(fptr);
    }
    arr[k] = 0;
    for(i=0; i<k; i++)
    {
      printf("%c",arr[i]);
    }
    printf(" ");
    if(curr == EOF)
    {
      printf("\n");
      return;
    }
  }
}
void hm_print(struct hashmap* hm)
{
  int i;
  struct llnode* iter;
  for(i=0; i<hm->num_buckets; i++)
  {
    struct llnode* headBucket = hm->map[i];
    printf("Bucket number %i:\n",i);
    iter = headBucket;
    while(iter!=NULL)
    {
      printf("Word = %s, Document ID = %s, Number of Occurrences = %i\n",iter->word,iter->document_id,iter->num_occurrences);
      iter = iter->next;
    }
  }
}
int main(void)
{
  //testWithoutIO();
  
  
 /* readFile3("input1.txt");
  printf("\n");
  readFile3("input2.txt");
  printf("\n");
  readFile3("input3.txt");
  printf("\n");*/
  printf("___________________________________________________________\n");
  printf("IO test with hashmap\n");
  struct hashmap *hm = hm_create(17);
  printf("I made a hashmap\n");
  readFile2("input1.txt",hm);
  readFile2("input2.txt",hm);
  readFile2("input3.txt",hm);
  printf("___________________________________________________________\n");
  hm_print(hm);
  printf("___________________________________________________________\n");
}

