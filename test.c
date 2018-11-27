#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"

void testWithoutIO(void);
//void readFile(char* input_file, struct hashmap *hm);
void readFile2(char* input_file, struct hashmap *hm);
void readFile3(char* input_file);
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
  printf("%i\n",hm_get(hm,"word","doc"));//test that everything was inputted correctly
  printf("%i\n",hm_get(hm,"word","doc2"));
  printf("%i\n",hm_get(hm,"longword","doc2"));
  printf("%i\n",hm_get(hm,"longword","doc3"));//test a document that does not exist
  //printf("%i\n",hm_get(hm,"bleh","doc"));//test a word that does not exist
  printf("End of get test\n");
  printf("___________________________________________________________\n");
  printf("TEST 3: does my destroy function work?\n");
  hm_destroy(hm);
  printf("___________________________________________________________\n");
}
/*void readFile(char* input_file, struct hashmap *hm)
{
  printf("I made it into readFile method\n");
  FILE *fptr;
  char curr;
  fptr = fopen(input_file, "r");
  printf("opened the file\n");
  curr = fgetc(fptr);
  char* arr[100][50];
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
      arr[i][k++] = curr;
      index++;
    }
    fptr++;
    curr = fgetc(fptr);
  }
  fclose(fptr);
}*/
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
    printf(" \n");
    if(curr == EOF)
    {
      return;
    }
  }
  printf("\n");
}
int main(void)
{
  testWithoutIO();
  
 // struct hashmap *hm = hm_create(17);
  //printf("I made a hashmap\n");
  /*readFile3("input1.txt");
  readFile3("input2.txt");
  readFile3("input3.txt");*/
  
  /*readFile2("input1.txt",hm);
  readFile2("input2.txt",hm);
  readFile2("input3.txt",hm);*/
  
}

