#include <stdio.h>
#include "chained_hash.h"
#define length(A) ((sizeof(A))/(sizeof(A[0])))
int main(int argc, char *argv[])
{

    int input[] = {10,21,45,22,7,2,67,19,13,45,12,  11,18,16,17,100,201,20,101};
    int len = length(input);
    int i;
    CNode** pcnArr= chained_hash_init(MODE_NUM);
    for (i = 0; i < len; i++) {
	chained_hash_insert(pcnArr, input[i]);
    }
    printf("insert complete\n");
    chained_hash_output_test(pcnArr, MODE_NUM);
    fflush(stdout);
    CNode* test1 = chained_hash_search(pcnArr, 17);
    /* if (test1 != NULL) */
    /* { */
    /* 	printf("%d", test1->key); */
    /* 	if (test1->next != NULL) */
    /* 	{ */
    /* 	    printf("%d", test1->next->key); */
    /* 	} */
    /* 	if (test1->prev != NULL) */
    /* 	{ */
    /* 	    printf("%d", test1->prev->key); */
    /* 	}	 */
    /* } */
    chained_hash_output_test(pcnArr, MODE_NUM);
    fflush(stdout);
    chained_hash_delete(pcnArr, test1);
    chained_hash_output_test(pcnArr, MODE_NUM);
    fflush(stdout);
    CNode* test2 = chained_hash_search(pcnArr, 17);
    if (test2 != NULL)
    {
	printf("%d", test2->key);
	if (test2->next != NULL)
	{
	    printf("%d", test2->next->key);
	}
	if (test2->prev != NULL)
	{
	    printf("%d", test2->prev->key);
	}
    }
    CNode* test3 = chained_hash_search(pcnArr, 99);
    if (test3 != NULL)
    {
	printf("%d", test3->key);
	if (test3->next != NULL)
	{
	    printf("%d", test3->next->key);
	}
	if (test3->prev != NULL)
	{
	    printf("%d", test3->prev->key);
	}
    }
    CNode* test4 = chained_hash_insert(pcnArr, 99);
    chained_hash_output_test(pcnArr, MODE_NUM);
    fflush(stdout);
    /* if (test4 != NULL) */
    /* { */
    /* 	printf("%d", test4->key); */
    /* 	if (test4->next != NULL) */
    /* 	{ */
    /* 	    printf("%d", test4->next->key); */
    /* 	} */
    /* 	if (test4->prev != NULL) */
    /* 	{ */
    /* 	    printf("%d", test4->prev->key); */
    /* 	} */
    /* } */
    chained_hash_dtor(pcnArr, MODE_NUM);
    return 0;
}
