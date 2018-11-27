#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct hashmap* hm_create(int num_buckets)
{
    struct hashmap* hm = (struct hashmap*)malloc(sizeof(struct hashmap));
    hm->map = (struct llnode**)malloc(sizeof(struct llnode));
    hm->num_buckets = num_buckets;
    hm->num_elements = 0;
    return hm;
}
int hm_get(struct hashmap* hm, char* word, char* document_id)
{
    int bucket = hash(hm,word,document_id);//the index array of the bucket
    if(bucket>=hm->num_buckets)
    {
      return -1;
    }
    struct llnode *a = hm->map[bucket];
    struct llnode *b = a;
    if(b==NULL)
    {
      printf("b==null\n");
       printf("there is no key value pair to match %s %s 1\n",word,document_id);
      return -1;
    }
    if(b->next == NULL)
    {
      printf("b->next == NULL\n");
      if(strcmp(b->document_id,document_id)==0 && strcmp(b->word,word)==0)//check for same document #
        {
          printf("the number of occur for %s %s is %i\n",word,document_id,b->num_occurrences);    
          return b->num_occurrences;//if they match, return the number of occurrences
        }
      printf("there is no key value pair to match %s %s 2\n",word,document_id);
      return -1;
    }
    while(b->next != NULL)//iterate through all nodes in the bucket
    {
        printf("iterating...\n");
        if(strcmp(b->document_id,document_id)==0 && strcmp(b->word,word)==0)//check for same document #
        {
          printf("the number of occur for %s %s is %i\n",word,document_id,b->num_occurrences);  
          return b->num_occurrences;//if they match, return the number of occurrences
        }
        b = b->next;//keep iterating
    }
    if(strcmp(b->document_id,document_id)==0 && strcmp(b->word,word)==0)//check for same document #
        {
          printf("the number of occur for %s %s is %i\n",word,document_id,b->num_occurrences);    
          return b->num_occurrences;//if they match, return the number of occurrences
        }
    printf("there is no key value pair to match %s %s 3\n",word,document_id);
    return -1;//if there is no match, return -1 to show error
}
void hm_put(struct hashmap* hm, char* word, char* document_id, int num_occurrences)
{
    int bucket = hash(hm,word,document_id);
    printf("Hash # for %s is %i\n",word,bucket);
    //int bucket = 1; 
    struct llnode *a = hm->map[bucket];
    struct llnode *c = a;
    if(c == NULL)
    {
      printf("there is no first node in the bucket\n");
      c = (struct llnode*)malloc(sizeof(struct llnode));
      c->word = word;//initialize the data in b
      c->document_id = document_id;
      c->num_occurrences = num_occurrences;//now the combo exists once
      c->next = NULL;//no node comes after
      printf("added it: %s %s %i\n",c->word,c->document_id,c->num_occurrences);
      hm->num_elements++;//another lnode was added, so increment num_elements
      return;
    }
    if(c->next == NULL)
    {
      printf("I made it here\n");
      if(strcmp(c->document_id,document_id)==0)
        {
            c->num_occurrences = c->num_occurrences + num_occurrences;//if the word and document id match, increment num_occurrences
            return;
        }
        printf("adding to the linked list\n");
        c->next = (struct llnode*)malloc(sizeof(struct llnode));
        c->next->word = word;//initialize the data in b
        c->next->document_id = document_id;
        c->next->num_occurrences = num_occurrences;//now the combo exists once
        c->next->next = NULL;//no node comes after
        printf("added it: %s %s %i\n",c->next->word,c->next->document_id,c->next->num_occurrences);
        hm->num_elements++;//another lnode was added, so increment num_elements
      }
    //this loop iterates through all the nodes in each bucket and finds one with a matching document id
    while(c->next!=NULL)
    {
      printf("iterating...\n");
        if(strcmp(c->document_id,document_id)==0)
        {
            c->num_occurrences = c->num_occurrences + num_occurrences;//if the word and document id match, increment num_occurrences
            return;
        }
        c = c->next;//otherwise, continue iterating through linked list
    }//if there is no node for that document, add one
   if(strcmp(c->document_id,document_id)==0 && strcmp(c->word,word)==0)//check for same document #
        {
          printf("the number of occur for %s %s is %i\n",word,document_id,b->num_occurrences);    
          c->num_occurrences = c->num_occurrences +num_occurrences;//if they match, return the number of occurrences
        }
    printf("adding to the linked list\n");
    c->next =(struct llnode*)malloc(sizeof(struct LNode));
    c->next->word = word;//initialize the data in b
    c->next->document_id = document_id;
    c->next->num_occurrences = num_occurrences;//now the combo exists once
    c->next->next = NULL;//no node comes after
    printf("added it: %s %s %i\n",c->next->word,c->next->document_id,c->next->num_occurrences);
    hm->num_elements++;//another lnode was added, so increment num_elements
}
/*void hm_destroy(struct hashmap* hm)
{
    
}*/
int hash(struct hashmap* hm, char* word, char* document_id)
{
    int i;
    int sum;
    char* getRidOfDumbError = document_id;
    for(i=0; i<(int)strlen(word); i++)
    {
        sum = sum + word[i];
    }
    sum = sum%hm->num_buckets;
    getRidOfDumbError++;
    return sum;
}
//void hm_remove(struct hashmap* hm, char* word, char* document_id)
//{

//}
