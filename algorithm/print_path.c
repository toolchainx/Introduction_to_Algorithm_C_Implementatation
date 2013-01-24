#include "print_path.h"

void print_arr(int point)
{
    printf("%d ", point);
}
// 打印两点间的最短路径所经过的中间点
void print_path(AdjList* graph, int* parent, int start, int end)
{
    if (start == end)
    {
	print_arr(start);
    }
    else if (parent[end] == NILVALUE)
    {
	printf("no path from %d to %d exist\n", start, end);
    }
    else
    {
	print_path(graph, parent, start, parent[end]);
	print_arr(end);
    }
}
