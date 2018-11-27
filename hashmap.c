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
    struct llnode *top = hm->map[bucket];
    if(top==NULL)//tests if there are any nodes in the bucket
    {
      printf("made it here\n");
      return -1;
    }
    struct llnode *iter = top;
    if(iter->next ==NULL)
    {
      printf("made it here 2\n");
      if(strcmp(iter->document_id,document_id)==0 && strcmp(iter->word,word)==0)//check for same document #
        {
            printf("the number of occurrences for %s %s is %i\n",word,document_id,iter->num_occurrences);  
            return iter->num_occurrences;//if they match, return the number of occurrences
        }
      iter = iter->next;
    }
    while(iter->next != NULL)//iterate through all nodes in the bucket
    {
      printf("made it here 3\n");
        if(strcmp(iter->document_id,document_id)==0 && strcmp(iter->word,word)==0)//check for same document #
        {
            printf("the number of occurrences for %s %s is %i\n",word,document_id,iter->num_occurrences);  
            return iter->num_occurrences;//if they match, return the number of occurrences
        }
        iter = iter->next;//keep iterating
    }
    if(strcmp(iter->document_id,document_id)==0 && strcmp(iter->word,word)==0)//check for same document #
    {
        printf("the number of occurrences for %s %s is %i\n",word,document_id,iter->num_occurrences);  
        return iter->num_occurrences;//if they match, return the number of occurrences
    }
    printf("there is no key value pair to match %s %s\n",word,document_id);
    return -1;
}
void hm_put(struct hashmap* hm, char* word, char* document_id, int num_occurrences)
{
    int bucket = hash(hm,word,document_id);
    printf("Hash # for %s is %i\n",word,bucket);
    //int bucket = 1; 
    struct llnode *head = hm->map[bucket];
    if(head == NULL)
    {
      printf("there is no first node in the bucket\n");
      head = (struct llnode*)malloc(sizeof(struct llnode));
      head->word = word;//initialize the data in b
      head->document_id = document_id;
      head->num_occurrences = num_occurrences;//now the combo exists once
      head->next = NULL;//no node comes after
      printf("added it: %s %s %i\n",head->word,head->document_id,head->num_occurrences);
      hm->num_elements++;//another lnode was added, so increment num_elements
      return;
    }
    struct llnode *iter = head;
    if(iter->next == NULL)
    {
      printf("I made it here\n");
      if(strcmp(iter->document_id,document_id)==0)
        {
            iter->num_occurrences = iter->num_occurrences + num_occurrences;//if the word and document id match, increment num_occurrences
            printf("incrementing num_occurrences to %i\n",iter->num_occurrences);
            return;
        }
        printf("adding to the linked list\n");
        iter->next = (struct llnode*)malloc(sizeof(struct llnode));
        iter = iter->next;
        iter->word = word;//initialize the data in b
        iter->document_id = document_id;
        iter->num_occurrences = num_occurrences;//now the combo exists once
        iter->next = NULL;//no node comes after
        printf("added it: %s %s %i\n",iter->word,iter->document_id,iter->num_occurrences);
        hm->num_elements++;//another lnode was added, so increment num_elements
      }
    //this loop iterates through all the nodes in each bucket and finds one with a matching document id
    while(iter->next!=NULL)
    {
      printf("iterating...\n");
        if(strcmp(iter->document_id,document_id)==0)
        {
            iter->num_occurrences = iter->num_occurrences + num_occurrences;//if the word and document id match, increment num_occurrences
            printf("incrementing num_occurrences to %i\n",iter->num_occurrences);
            return;
        }
        iter = iter->next;//otherwise, continue iterating through linked list
    }//if there is no node for that document, add one
   if(strcmp(iter->document_id,document_id)==0 && strcmp(iter->word,word)==0)//check for same document #
    {
        iter->num_occurrences = iter->num_occurrences +num_occurrences;//if the word and document id match, increment num_occurrences
        return;
    }
    printf("adding to the linked list\n");
    iter->next =(struct llnode*)malloc(sizeof(struct llnode));
    iter = iter->next;
    iter->word = word;//initialize the data in b
    iter->document_id = document_id;
    iter->num_occurrences = num_occurrences;//now the combo exists once
    iter->next = NULL;//no node comes after
    printf("added it: %s %s %i\n",iter->word,iter->document_id,iter->num_occurrences);
    hm->num_elements++;//another lnode was added, so increment num_elements
}
void hm_destroy(struct hashmap* hm)
{
    if(hm->map == NULL)
    {
      return;
    }
    int i;
    for(i=0; i<hm->num_buckets; i++)
    {
        struct llnode* iter;
        struct llnode* trail = hm->map[i];
        while(trail != NULL)
        {
          iter = trail->next;
          free(trail);
          trail = iter;
        }
        free(trail);
        free(iter);
        free(hm->map[i]);
    }
    free(hm->map);
    free(hm);
}
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
