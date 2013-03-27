#include "bucket_sort.h"
#include <stdio.h>
#include <stdlib.h>
void bucket_list_dtor(BNode** B, int n);
void bucket_insert(BNode** B, int n, int x);
static BNode* insert_sort(BNode* l);
void bucket_sort_concat(BNode** B, int n, int* A);


void bucket_sort(int* A, int n)
{
    BNode** B = (BNode**)calloc(n , sizeof(BNode*));

    int i;
    for (i = 0; i < n; i++) {
	// insert A[i] into list B[A[i] % n]
	bucket_insert(B, n, A[i]);
    }
    for (i = 0; i < n; i++) {
	//sort list B[i] with insertion sort
	B[i] = insert_sort(B[i]);
    }
    // concatenate the lists B[0], B[1], ..., B[n-1] together in order
    bucket_sort_concat(B, n, A);
    bucket_list_dtor(B, n);
}
void bucket_sort_concat(BNode** B, int n, int* A)
{
    int i, j = 0;
    for (i = 0; i < n; i++) {
	BNode* pb = B[i];
	while(pb != NULL)
	{
	    A[j++] = pb->key;
	    pb = pb->next;
	}
    }
}

static BNode* insert_sort(BNode* l)
{
    BNode* lsort = NULL;
    while(l != NULL)
    {
	BNode* pb_before = NULL;
	BNode* pb = lsort;
	while(pb != NULL)
	{
	    if (l->key < pb->key)
	    {
		// insert l before pb
		BNode* x = l;
		l = l->next;
		x->next = pb;
		if (pb_before == NULL)
		{
		    lsort = x;
		}
		else
		{
		    pb_before->next = x;
		}
		break;
	    }
	    pb_before = pb;
	    pb = pb->next;
	}
	if (pb == NULL)
	{
	    BNode* x = l;
	    l = l->next;
	    x->next = NULL;
	    if (pb_before != NULL)
	    {
		pb_before->next = x;
	    }
	    else
	    {
		lsort = x;
	    }
	}
    }
    return lsort;
}
void bucket_insert(BNode** B, int n, int x)
{
    int quotient = x / n;
    // insert into B[quotient]
    BNode* pb = (BNode *)malloc(sizeof(BNode));
    pb->key = x;
    pb->next = B[quotient];
    B[quotient] = pb;
}

void bucket_list_dtor(BNode** B, int n)
{
    int i;
    for (i = 0; i < n; i++) {
	while(B[i] != NULL)
	{
	    BNode* pb = B[i];
	    B[i] = pb->next;
	    free(pb);
	}
    }
}
