//二叉查找树：最大值，最小值，前驱，后继，查找，插入，删除
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

struct __bst_node{
    int key;
    struct __bst_node* parent;
    struct __bst_node* left;
    struct __bst_node* right;
};

typedef struct __bst_node bst_node;
// preassume that the root is not null
bst_node* max_node(bst_node * root)
{
    /* if (root-> right == NULL) */
    /* { */
    /* 	return root; */
    /* } */
    /* return max_node(root->right); */
    bst_node* max = root;
    while(max->right)
    {
	max = max->right;
    }
    return max;
}
bst_node* min_node(bst_node * root)
{
    bst_node* min = root;
    while(min->left)
    {
        min = min->left;
    }
    return min;
}
// preassume that the root is not null
bst_node* precursor_node(bst_node* current)
{
    bst_node* parent = current->parent;
    // 如果存在左孩子，则前驱为当前结点左子树中最大的那个结点
    if(current->left)
    {
	return max_node(current->left);
    }
    else if(parent)
    {
	// 如果当前结点是其父亲的右孩子，则该父亲是其前驱
	while(parent && parent->right != current)
	{
	    current = parent;
	    parent = parent->parent;
	}
	if(parent)
	    return parent;
	else
	    return NULL;
    }
    else
    {
	return NULL;
    }

}
// preassume that the root is not null
bst_node* successor_node(bst_node* current)
{
    bst_node* parent = current->parent;
    // 如果存在右孩子，则后继为当前结点右子树中最小的那个结点
    if(current->right)
    {
	return min_node(current->right);
    }
    else if(parent)
    {
	while(parent && parent->left != current)
	{
	    current = parent;
	    parent = parent->parent;
	}
	if (parent)
	    return parent;
	else 
	    return NULL;
    }
    else
    {
	return NULL;
    }
}
// preassume that the current is not null
bst_node* delete_node(bst_node* current)
{
    // 删除的情况分类
    // 叶结点，直接删除
    // 有一个子树的结点，将子树的根替换该结点
    // 有两个子树的结点，找到该结点的后继，用后继的key替换该结点的key，删除后继,
    // 其后继必定为其右子树的最靠左的那个结点，且该节点至多只有单一子树,且该单一子树是右子树
    // x标记待删除的结点，y标记待连接的子树
    // 返回删除结点后二叉树的根
    // 要习惯性得判断y是否有效
    bst_node* root = current;
    bst_node* x = current;
    bst_node* y = NULL;
    while(root->parent)
    {
	root = root->parent;
    }
    if(x->left == NULL)
    {
	y = x->right;
    }
    else if(x->right == NULL)
    {
	y = x->left;
    }
    else
    {
	x = successor_node(x);
	current->key = x->key;
	y = x->right;
    }
    if(x->parent == NULL)
    {
	root = y;
	// y maybe null
	if(y)
	{
	    y->parent = NULL;
	}
    }
    else if(x->parent->right == x)
    {
	x->parent->right = y;
	if(y)
	{
	    y->parent = x->parent;
	}
    }
    else // x->parent->left == x
    {
	x->parent->left = y;
	if(y)
	{
	    y->parent = x->parent;	
	}
    }
    free(x);
    return root;    
}
bst_node*  insert_node(bst_node* root, bst_node* x)
{
    // 如果root 为NULL,确保root 所指向的元素不为空
    if(root == NULL)
    {
	root = x;
	return root;
    }
    else if(x->key < root->key)
    {
	root->left = insert_node(root->left, x);
	// 判断x->parent是否为空，如果为空，则该次循环完成了对结点的插入，指定其父节点
	if(!x->parent)
	{
	    x->parent = root;
	}
    }
    else
    {
	root->right = insert_node(root->right, x);
	// 判断x->parent是否为空，如果为空，则该次循环完成了对结点的插入，指定其父节点
	if(!x->parent)
	{
	    x->parent = root;
	}
    }
    return root;
}
bst_node* search_node(bst_node* root, int key)
{
    if(root == NULL)
    {
	return NULL;
    }
    if(root->key == key)
    {
	return root;
    }
    else if (key > root->key)
    {
	search_node(root->right, key);
    }
    else 
    {
	search_node(root->left, key);
    }
}
void print_node(bst_node* x)
{
    if (x == NULL)
    {
	printf("no value\n");
	fflush(stdout);
	return ;
    }
    printf("%d\n", x->key);
    fflush(stdout);
}
// 中序遍历二叉查找树
void mid_traverse_node(bst_node* root)
{
    if(root)
    {
	mid_traverse_node(root->left);
	print_node(root);
	mid_traverse_node(root->right);
    }
}
void construct_node(bst_node* x, int value)
{
    // error here!!!
    //x = (bst_node*)malloc(sizeof(bst_node));
    x->parent = NULL;
    x->left = NULL;
    x->right = NULL;
    x->key = value;
}
void swap(int* a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
int random(int i, int length)
{
    //取i 到 n 之间的一个随机数 [i, n] 闭区间
    return (double)rand()/RAND_MAX * (length - i) + i;
}
void randomize_in_place(int array[], int length)
{
    int i;
    for(i = 0; i < length; i++)
    {
	swap(&array[i], &array[random(i, length-1)]);
    }    
}
void print_array(int array[], int length)
{
    int i;
    for(i = 0; i < length; i++)
    {
	printf("array[%d] = %d\n", i, array[i]);
    }
}
int main()
{
    int i;
    bst_node* root = NULL;
    // 利用原地随机化方法将其打乱
    int array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int length = sizeof(array)/sizeof(int);
    /* srand(GetTickCount()); */
    randomize_in_place(array, length);  
    print_array(array, length);  
    for (i = 0; i < length; i++)
    {
	bst_node* y = (bst_node*)malloc(sizeof(bst_node));
    	construct_node(y, array[i]);
    	root = insert_node(root, y);
	/* printf("%x\n", (unsigned int)root); */
    }
    mid_traverse_node(root);
    print_node(max_node(root));
    print_node(min_node(root));
    int s_value;
    scanf("%d", &s_value);
    fflush(stdin);
    while(s_value != -1)
    {
	bst_node* s_node = search_node(root, s_value);
	if (s_node)
	{
	    root = delete_node(s_node);
	}
	else
	{
	    printf("not in the bst tree\n");
	    fflush(stdout);
	}
	length--;
	mid_traverse_node(root);
	scanf("%d", &s_value);
	/* for(i = 0; i<length; i++) */
	/* { */
	/*     int search_key = random(0, length-1); */
	/*     bst_node* current_node = search_node(root, search_key); */
	/*     /\* bst_node* precursor = precursor_node(current_node); *\/ */
	/*     /\* bst_node* successor = successor_node(current_node); *\/ */
	/*     printf("the search key is %d\n", search_key); */
	/*     if(current_node->parent) */
	/* 	printf("the parent of %d is %d\n",current_node->key, current_node->parent->key); */
	/*     fflush(stdout); */
	/*     /\* if(precursor) *\/ */
	/*     /\*     printf("the precursor of %d is %d\n", current_node->key, precursor->key); *\/ */
	/*     /\* if(successor) *\/ */
	/*     /\*     printf("the successor of %d is %d\n", current_node->key, successor->key); *\/ */
	/* } */
    }
    return 0;
}
    
