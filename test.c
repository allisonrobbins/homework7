#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashmap.h"


void readFile2(char* input_file, struct hashmap *hm);
void readFile3(char* input_file, struct hashmap *hm);
void hm_print(struct hashmap* hm);
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
void readFile3(char* input_file,struct hashmap *hm)
{
  printf("reading file %s\n",input_file);
  FILE *fptr;
  char line[256];
  char* word;
  fptr = fopen(input_file, "r");
  if(fptr == NULL)
  {
    return;
  }
  fgets(line,256,fptr);
  word = strtok(line, " ");
  while(word!=NULL)
  {
    hm_put(hm,word,input_file,1);
    word = strtok(line, " ");
  }
  fclose(fptr);
}

void hm_print(struct hashmap* hm)
{
  int i;
  struct llnode* iter;
  printf("printing hashmap\n");
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  for(i=0; i<hm->num_buckets; i++)
  {
    iter = hm->map[i];
    printf("Bucket number %i:\n",i);
    printf("\n");
    if(iter==NULL)
    {
      printf("There is nothing in the bucket\n");
      printf("\n");
    }
    while(iter!=NULL)
    {
      char* wrd = iter->word;
      printf("Word = %s, Document ID = %s, Number of Occurrences = %i\n",wrd,iter->document_id,iter->num_occurrences);
      iter = iter->next;
    }
    printf("\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  }
}
int main(void)
{
  printf("___________________________________________________________\n");
  printf("Create the hashmap and input files:\n");
  struct hashmap *hm = hm_create(17);
  printf("I made a hashmap\n");
  readFile3("input1.txt",hm);
  hm_print(hm);
  /*readFile3("input2.txt",hm);
  hm_print(hm);
  readFile2("input3.txt",hm);
  hm_print(hm);
  printf("___________________________________________________________\n");
  printf("Test get ~you~ from input2.txt (should be 6): %d\n", hm_get(hm, "you", "input2"));
	hm_remove(hm, "you", "input2");
	printf("After remove: test get \"homework\" from D3.txt (should be -1): %d\n", hm_get(hm, "you", "input2"));
	printf("After remove: \"homework\" -> num_elements: %d\n", hm->num_elements);
printf("___________________________________________________________\n");
	hm_destroy(hm);
  printf("\n");
  printf("___________________________________________________________\n");
*/
}

