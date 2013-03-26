#ifndef _CHAINED_HASH_H_
#define _CHAINED_HASH_H_

typedef struct Clist_tag {
    int key;
    struct Clist_tag* next;
    struct Clist_tag* prev;
} CNode;

#define MODE_NUM    10


void chained_hash_delete(CNode** pcnArr, CNode* pcn);
CNode* chained_hash_search(CNode** pcnArr, int k);
void chained_hash_dtor(CNode** pcnArr, int n);
CNode** chained_hash_init(int n);
CNode* chained_hash_insert(CNode** pcnArr, int k);
void chained_hash_output_test(CNode** pcnArr, int n);
#endif /* _CHAINED_HASH_H_ */
