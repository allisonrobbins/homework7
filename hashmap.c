#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct hashmap* hm_create(int num_buckets)
{
    struct hashmap* hm = (struct hashmap*)malloc(sizeof(struct hashmap));
    hm->map = (struct llnode**)malloc(sizeof(struct llnode*)*num_buckets);
    hm->num_buckets = num_buckets;
    hm->num_elements = 0;
    int i;
    for(i=0;i<num_buckets;i++)
    {
        hm->map[i] = NULL;
    }
    return hm;
}
int hm_get(struct hashmap* hm, char* word, char* document_id)
{
    int i;
    for(i=0; i<hm->num_buckets; i++)
    {
        if(0==strcmp(word, hm->map[i]))
        {
            break;
        }
    }
    if(i >= hm->num_buckets)
    {
        return -1;
    }
    struct lnode* a = hm->map[i];
    a=a->next;
    while(a->next!=NULL)
    {
         if(0==strcmp(a->document_id,document_id))
         {
            return a->num_occurrences;
         }
         a=a->next;
    }
    return -1;
}
void hm_put(struct hashmap* hm, char* word, char* document_id, int num_occurrences)
{
    int i;
    for(i=0; i<hm->num_buckets; i++)
    {
        if(0==strcmp(word, hm->map[i]->word))
        {
            break;
        }
    }
    if(i >= hm->num_buckets)
    {
        //create a bucket
    }
    struct lnode* a = hm->map[i];
    a=a->next;
    while(a->next!=NULL)
    {
         if(0==strcmp(a->document_id,document_id))
         {
            a->num_occurrences++;
            return;
         }
         a=a->next;
    }
    a->next = (struct lnode*)malloc(sizeof(struct lnode));
    a->next->document_id = document_id;
    a->next->word = word;
    a->next->num_occurrences = 1;
    a->next->next = NULL;
}
void hm_destroy(struct hashmap* hm)
{

}
int hash(struct hashmap* hm, char* word, char* document_id)
{

}
void hm_remove(struct hashmap* hm, char* word, char* document_id)
{

}