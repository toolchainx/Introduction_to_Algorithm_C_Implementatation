#include "chained_hash.h"
#include <stdio.h>
#include <stdlib.h>


CNode** chained_hash_init(int n)
{
    return (CNode **)calloc(n , sizeof(CNode *));
}

void chained_hash_dtor(CNode** pcnArr, int n)
{
    int i;
    for (i = 0; i < n; i++) {
	CNode* pl = pcnArr[i];
	while(pl != NULL)
	{
	    CNode* pl_next = pl->next;
	    free(pl);
	    pl = pl_next;
	}
    }
    free(pcnArr);
}

CNode* chained_hash_search(CNode** pcnArr, int k)
{
    // search key
    // return NULL if failed
    int i = k % MODE_NUM;
    CNode* pcn = pcnArr[i];
    // infinite loop
    while(pcn != NULL && pcn->key != k)
    {
	pcn = pcn->next;
    }
    return pcn;
}
// search before insert
CNode* chained_hash_insert(CNode** pcnArr, int k)
{
    CNode* tmp = chained_hash_search(pcnArr, k);
    if (tmp != NULL)
    {
	return tmp;
    }
    else
    {
	int idx = k % MODE_NUM;
	CNode* pcn = pcnArr[idx];
	CNode* newpcn = (CNode* )malloc(sizeof(CNode));
	newpcn->key = k;
	newpcn->next = pcn;
	newpcn->prev = NULL;
	if (pcn != NULL)
	{
	    pcn->prev = newpcn;
	}
	pcnArr[idx] = newpcn;
	return newpcn;
    }
}

void chained_hash_delete(CNode** pcnArr, CNode* pcn)
{
    // if the first number of the chain deleted?
    CNode* before_pcn = pcn->prev;
    CNode* pcn_next = pcn->next;
    if (before_pcn != NULL)
    {
	before_pcn->next = pcn_next;
    }
    else // the first number of the chain deleted.
    {
	pcnArr[pcn->key % MODE_NUM] = pcn_next;	
    }
    if (pcn_next != NULL)
    {
	pcn_next->prev = before_pcn;
    }
    free(pcn);
}

void chained_hash_output_test(CNode** pcnArr, int n)
{
    int i;
    for (i = 0; i < n; i++) {
	CNode* pcn = pcnArr[i];
	printf("the %d line\n", i);
	while(pcn != NULL)
	{
	    printf("%d ", pcn->key);
	    pcn = pcn->next;
	}
	printf("\n");
	// output backward
    }
}
