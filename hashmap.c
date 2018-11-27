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
    int bucket = hash(hm,word,document_id);
    printf("Hash # for %s is %i\n",word,bucket);
    struct llnode *top = hm->map[bucket];
    if(top==NULL)//tests if there are any nodes in the bucket
    {
      printf("made it here 1\n");
      //return -1;
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
void hm_put(struct hashmap* hm, char* word, char* document_id, int num_occurrences){
	int bucket = hash(hm, word, document_id);
  printf("Adding word: %s doc: %s to bucket %i\n",word,document_id,bucket);
	struct llnode* headBucket = hm->map[bucket];
	if (headBucket == NULL) {
		struct llnode* new_node = (struct llnode*) malloc(sizeof(struct llnode));
		hm->map[bucket] = new_node;
		new_node->word = word;
		new_node->document_id = document_id;
		new_node->num_occurrences = num_occurrences;
    printf("Added to the front of bucket %i\n",bucket);
    hm->num_elements += 1;
	}
	else {
		struct llnode* curr = headBucket;
		struct llnode* prev = headBucket;
		while (curr != NULL) {
			if (strcmp(curr->word, word) == 0 && strcmp(curr->document_id, document_id) == 0) {
				curr->num_occurrences += num_occurrences;
				printf("after update number of occur in hm_put: %s %d\n", word, curr->num_occurrences);
				return;
			}
			prev = curr;
			curr = curr->next;
		}
		/* Add node to end of list */
    printf("adding to the end of bucket %i\n",bucket);
		struct llnode* new_node = (struct llnode*) malloc(sizeof(struct llnode));
		new_node->word = word;
		new_node->document_id = document_id;
		new_node->num_occurrences = num_occurrences;
		prev->next = new_node;
		/* Increment num_elements */
		hm->num_elements += 1;
	}
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
    char* a;
    int i;
    int sum = 0;
    char* getRidOfDumbError = document_id;
    for(a = word; *a!='\0'; a++)
    {
      i = (int) *a;
      sum = sum + i;
    }
    sum = sum%hm->num_buckets;
    getRidOfDumbError++;
    return sum;
}
//void hm_remove(struct hashmap* hm, char* word, char* document_id)
//{

//}

