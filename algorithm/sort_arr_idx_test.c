#include "sort_arr_idx.h"

int main(int argc, char *argv[])
{
    int num = 8;
    int arr[] = {1, 2, 3, 4, 6, 5, 7, 8};
    int* seq = (int *)malloc(num * sizeof(int));
    sort_arr_idx(arr, num, seq);
    rvs_arr(seq, num);
    printf("arr :\n");
    array_print(arr, num);
    printf("seq :\n");
    array_print(seq, num);
    return 0;
}
