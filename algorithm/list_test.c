#include <stdio.h>
#include <stdlib.h>
#include "list.h"




int main(int argc, char *argv[])
{
    List list = NULL;
    int arr[] = {1, 3, 5 ,7 ,8, 10};
    int i;
    for (i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
	list = list_insert(list, arr[i]);
    }
    print_list(list);
    // freeList(list);
    return 0;
}
