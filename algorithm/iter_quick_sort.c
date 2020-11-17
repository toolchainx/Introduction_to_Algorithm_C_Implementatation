#include<stdio.h>
void quicksort(int a[10], int left, int right);
int partition(int a[10], int left, int right);
void quicksort(int a[10], int left,int right)
{
    int j;
    if(left<right)
    {
        j = partition(a, left, right);
        quicksort(a, left, j-1);
        quicksort(a, j+1, right);

    }
}

int partition(int a[10], int left, int right)
{
    int temp, pivot, i, j;
    pivot = left;
    i = left;
    j = right;
    while(i<j)
    {
        while((a[i]<=a[pivot]) && (i<right))
        {
            i++;
        }
        while(a[j]>a[pivot])
        {
            j--;
        }
        if(i<j)
        {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }

    temp = a[pivot];
    a[pivot] = a[j];
    a[j] = temp;
    return j;
}

int main()
{
    int a[10], n, i, j;
    printf("\nEnter the size of the array: ");
    scanf("%d", &n);
    printf("\nEnter the array elements: ");
    for(i=0; i<n; i++)
    {
        scanf("%d", &a[i]);
    }   
    quicksort(a, 0, n-1);
    printf("\nThe array after sorting:");
    for(i=0; i<n; i++)
    printf("\t%d",a[i]);
    printf("\n\n");
}
