#include "sort_arr_idx.h"

void rvs_arr(int* arr, int num)
{
    int i;
    for (i = 0; i < num/2; i++) {
	swap(arr[i], arr[num - 1 - i]);
    }
}
int cmp(const void* a, const void* b)
{
    // type cast
    ValIdxPair* l = (ValIdxPair*)a;
    ValIdxPair* r = (ValIdxPair*)b;
    return (l->val > r->val);
}

// arr and seq is int array with num elems
void sort_arr_idx(const int* arr, int num, int* seq)
{
    int i;
    ValIdxPair* pl = (ValIdxPair*)malloc(num * sizeof(*pl));
    for (i = 0; i < num; i++) {
	pl[i].val = arr[i];
	pl[i].idx = i;
    }
    qsort(pl, num, sizeof(*pl), cmp);
    for (i = 0; i < num; i++) {
	seq[i] = pl[i].idx;
    }
}
