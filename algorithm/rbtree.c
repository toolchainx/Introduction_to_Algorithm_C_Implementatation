//implement the red-black tree
//插入操作完成，等待完成删除操作
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef enum { RED, BLACK } EColor;
typedef struct tag_rbtree
{
  struct tag_rbtree* left;
  struct tag_rbtree* right;
  struct tag_rbtree* parent;
  int key;
  EColor color;
}rbtree, *prbtree, *prbt_node, rbt_node;

// 定义一个哑元
prbtree nil;
//preassume that the x has a right child
prbtree rbt_left_rotate(prbtree T, prbtree x)
{
  prbtree y = x->right;
  x->right = y->left;
  // 注意判断每个指针是否为nil
  if (y->left != nil)
    {
      y->left->parent = x;    
    }
  y->parent = x->parent;
  if (x->parent != nil)
    {
      if (x->parent->left == x)
	{
	  x->parent->left = y;
	}
      else
	{
	  x->parent->right = y;
	}
    }
  else
    {
      T = y;
    }
  y->left = x;
  x->parent = y;
  return T;
}
//preassume that the y has a left child
prbtree rbt_right_rotate(prbtree T, prbtree y)
{
  // 先处理边界条件，再处理中间情况。y->parent 要 y来指出
  // 同时x->right 要x来指出，因此先处理这两种情况。
  // 每次下意识判断指针是否为空，可以使用assert辅助判断
  prbtree x = y->left;
  // 处理 x->right with y
  y->left = x->right;
  if(x->right != nil)
    {
      x->right->parent = y;
    }
  // 处理 y->parent with x
  x->parent = y->parent;
  if (y->parent != nil)
    {
      if (y->parent->left == y)
	{
	  y->parent->left = x;
	}
      else
	{
	  y->parent->right = x;
	}
    }
  else
    {
      T = x;
    }
  // 处理 x with y
  x->right = y;
  y->parent = x;
  return T;
}
/*保持红黑树的性质
 * 红黑树的那些性质可能被破坏？
 * 性质2：根节点是黑的，如果插入的结点是根节点，即未插入前红黑树是空树，
 * 则性质2被破坏
 * 性质4：如果一个结点是红色，则其子女都是黑的。如果插入结点后，该结点
 * 的父亲结点也是红色，则破坏了性质4.
 */
prbtree rbt_insert_fixup(prbtree T, prbtree z)
{
  prbtree y;
  while(z->parent->color == RED)
    {
      assert(z->parent != nil);
      // 如果z的父节点是其祖父结点的左子女
      assert(z->parent->parent != nil);
      if (z->parent == z->parent->parent->left)
	{
	  //y 记录其叔父结点
	  y = z->parent->parent->right;
	  // 不击穿 如果y所指向的结点的颜色是红色，case 1
	  if (y->color == RED)
	    {
	      // 更新z的同时更新y结点
	      // 将z->parent 和 y 染成黑色
	      // z->parent->parent染成红色
	      // z结点上升两层，指向其祖父，
	      // 要更新y结点吗？ 让其自动进入下一循环
	      z->parent->color = BLACK;
	      y->color = BLACK;
	      z->parent->parent->color = RED;
	      z = z->parent->parent;
	      // 更新了z结点后	      
	    }
	  // 如果y所指向的结点的颜色是黑色，case 2 or case3
	  else 
	    {
	      // 击穿 如果z所指向的结点是其父节点的右儿子 case 2
	      // 以z的父节点为轴，立即来一次左旋，将其转换为case 3
	      if (z == z->parent->right)
		{
		  // 旋转后重新获得根节点的指针
		  z = z->parent;
		  T = rbt_left_rotate(T,z);
		}
	      // 如果z所指向的结点是其父节点的左儿子 case 3
	      // 改变z->parent的颜色为黑色，z->parent->parent颜色为红色，以其祖父节点为轴，右旋，循环结束
	      if (z == z->parent->left)
		{
		  z->parent->color = BLACK;
		  z->parent->parent->color = RED;
		  T = rbt_right_rotate(T, z->parent->parent);
		}
	    }
	}
      // 如果z的父节点是其祖父结点的右子女
      else // z->parent == z->parent->parent->right
	{
	  // 交换左右子女，进行处理
	  // 记录其叔父结点
	  y = z->parent->parent->left;
	  // 如果y是红色 case 1
	  if (y->color == RED)
	    {
	      z->parent->color = BLACK;
	      y->color = BLACK;
	      z->parent->parent->color = RED;
	      z = z->parent->parent;
	    }
	  else // 如果y是黑色 case 2 或者 case 3
	    {
	      // 如果z是其父亲的左孩子，将其转换为右孩子 case 2
	      if (z == z->parent->left)
		{
		  z = z->parent;
		  T = rbt_right_rotate(T, z);
		}
	      // 现在z是其父亲的右孩子了，case 3
	      // 将其父亲染为黑色，其祖父染为红色，左旋
	      z->parent->color = BLACK;
	      z->parent->parent->color = RED;
	      T = rbt_left_rotate(T, z->parent->parent);
	    }
	}
    }
  T->color = BLACK;
  return T;
}
/* 插入一个结点
 * T为空的情况
 * T不为空的情况
 * 查找位置
 * 插入操作
 * 着色
 * 保持红黑性质
 */
prbtree rbt_insert_node(prbtree T, prbtree z)
{
  prbtree y = nil;
  prbtree x = T;
  while(x != nil){
    // y保存父节点的位置
    y = x;
    if (z->key < x->key)
      {
	x = x->left;
      }
    else
      {
	x = x->right;
      }
  }
  z->parent = y;
  // 如果 y为哨兵，则z是根结点
  if (y == nil)
    {
      T = z;
    }
  else
    {
      // 插入操作
      if (z->key < y->key)
	{
	  y->left = z;
	}
      else
	{
	  y->right = z;
	}
    }
  //着色
  z->left = nil;
  z->right = nil;  
  z->color = RED;
  // 保持红黑性质
  T = rbt_insert_fixup(T, z);
  return T;  
}
/**
 * 获取红黑树中结点的最大值
 */
prbt_node rbt_maximum(prbt_node root)
{
     prbt_node max = root;
     while(max->right != nil)
     {
	  max = max->right;
     }
     return max;
}
/**
 * 获取红黑树中结点的最小值
 */
prbt_node rbt_minimum(prbt_node root)
{
     prbt_node min = root;
     while(min->left != nil)
     {
	  min = min->left;
     }
     return min;
}
/**
 * 获取红黑树中结点的前驱
 */
prbt_node rbt_precursor(prbt_node current)
{
     prbt_node parent = current->parent;
     if (current->left != nil)
     {
	  return rbt_maximum(current->left);
     }
     else if (parent != nil)
     {
	  while(parent != nil && parent->right != current)
	  {
	       current = parent;
	       parent = parent->parent;
	  }
	  if(parent != nil)
	  {
	       return parent;
	  }
	  else
	  {
	       return nil;
	  }
     }
     else
     {
	  return nil;
     }
}
/**
 * 获取红黑树中结点的后继
 */
prbt_node rbt_successor(prbt_node current)
{
     prbt_node parent = current->parent;
     if (current->right != nil)
     {
	  return rbt_minimum(current->right);
     }
     else if (parent != nil)
     {
	  while(parent != nil && parent->left != current)
	  {
	       current = parent;
	       parent = parent->parent;
	  }
	  if (parent != nil)
	  {
	       return parent;
	  }
	  else
	  {
	       return nil;
	  }
     }
     else
     {
	  return nil;
     }
}
/** 
 * 查找给定key的红黑书结点，返回其指针
 */
prbt_node rbt_search(prbt_node root, int key)
{
     // 利用迭代实现该函数
     while(root != nil && root->key != key)
     {
	  if (key < root->key)
	  {
	       root = root->left;
	  }
	  else
	  {
	       root = root->right;
	  }
     }
     return root;
}
/**
 * 删除结点后保持红黑树性质的函数
 */
prbt_node rbt_delete_fixup(prbtree T, prbt_node x)
{
     prbt_node w;
     // 当x!=T且x的颜色为黑时循环继续
     while(x != T && x->color == BLACK)
     {
	  // 如果x是其父结点左孩子
	  if (x == x->parent->left)
	  {
	       w = x->parent->right;
	       // 击穿 case 1
	       // 如果w的颜色是红色，则x->parent的颜色必定为黑色
	       // w必定不是叶结点
	       if (w->color == RED)
	       {
		    // 交换w和x->parent的颜色
		    // 对x->parent进行一次左旋
		    // 使case 1 转变成case 2、3、4
		    w->color = BLACK;
		    x->parent->color = RED;
		    T = rbt_left_rotate(T, x->parent);
		    w = x->parent->right;
	       }
	       // case 2
	       // 此时w必定是黑色
	       // 如果w的左右孩子都是黑色
	       // 改变颜色，循环结束或x指针上升一层
	       if (w->left->color == BLACK && w->right->color == BLACK)
	       {
		    w->color = RED;
		    x = x->parent;
	       }
	       else 
	       {
		    // 如果w的右孩子是黑色，则w的左孩子是红色
		    // case 3
		    // 交换w和其左孩子的颜色，对w进行一次右旋
		    // 最终使w的右孩子是红色,转换成case 4
		    if (w->right->color == BLACK)
		    {
			 w->color = RED;
			 w->left->color = BLACK;
			 T = rbt_right_rotate(T, w);
			 w = x->parent->right;
		    }
		    // case 4
		    // w的右孩子是红色，w的左孩子的颜色未知
		    // 交换x->parent 和 w的颜色，
		    // 将w的右孩子赋值为黑色，对x->parent进行一次左旋
		    w->color = x->parent->color;
		    x->parent->color = BLACK;
		    w->right->color = BLACK;
		    T = rbt_left_rotate(T, x->parent);
		    x = T;		    
	       }
	  }
	  // 如果x是x->parent的右孩子，对称处理
	  else
	  {
	       w = x->parent->left;
	       // case 1
	       if (w->color == RED)
	       {
		    w->color = BLACK;
		    x->parent->color = RED;
		    T = rbt_right_rotate(T, x->parent);
		    w = x->parent->left;
	       }
	       // case 2
	       if (w->right->color == BLACK && w->left->color == BLACK)
	       {
		    w->color = RED;
		    x = x->parent;
	       }
	       else
	       {
		    // case 3
		    if (w->left->color == BLACK)
		    {
			 w->color = RED;
			 w->right->color = BLACK;
			 T = rbt_left_rotate(T, w);
			 w = x->parent->left;
		    }
		    // case 4
		    w->color = x->parent->color;
		    x->parent->color = BLACK;
		    w->left->color = BLACK;
		    T = rbt_right_rotate(T, x->parent);
		    x = T;		    
	       }
	  }
     }
     x->color = BLACK;
     return T;
}
// 删除一个结点
// 考虑的情况
// 空树:该情况不可能出现，因为y已经指向树中的某一结点
// 只有一个根节点的树
// 有多个结点的树
prbtree rbt_delete_node(prbtree T, prbt_node z)
{
     // y指向要删除的结点
     prbt_node y;
     prbt_node x;
     if (z->left == nil || z->right == nil)
     {
	  y = z;
     }
     else
     {
	  y = rbt_successor(z);
     }
     // x 指向要连接的子树
     if (y->left != nil)
     {
	  x = y->left;
     }
     else
     {
	  x = y->right;
     }
     x->parent = y->parent;
     if (y->parent == nil)
     {
	  T = x;
     }
     else if (y->parent->left == y)
     {
	  y->parent->left = x;
     }
     else
     {
	  y->parent->right = x;
     }
// 如果y != z 则y为z的后继结点，将z的key赋值为y的key
     if (y != z)
     {
	  z->key = y->key;
	  // 将z的卫星数据赋值为y的卫星数据
	  // ...
     }
     if (y->color == BLACK)
     {
	  T = rbt_delete_fixup(T, x);
     }
     return T;
}
void print_node(prbt_node x)
{
  if (x == nil)
    {
      printf("no value\n");
      fflush(stdout);
      return ;
    }
  printf("value = %d\n", x->key);
  switch(x->color)
    {
    case RED:
      printf ("COLOR = RED\n");
      break;
    case BLACK:
      printf ("COLOR = BLACK\n");
      break;
    default:
      printf ("NO COLOR\n");
    }
  fflush(stdout);
}
void mid_traverse_node(prbt_node root)
{
  if(root != nil)
    {
      mid_traverse_node(root->left);
      print_node(root);
      mid_traverse_node(root->right);
    }
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

void construct_node(prbt_node x, int value)
{
    // error here!!!
    //x = (bst_node*)malloc(sizeof(bst_node));
    x->parent = NULL;
    x->left = NULL;
    x->right = NULL;
    x->key = value;
    x->color = RED;
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
  // 测试方法：
  // 插入10个元素，遍历该元素，打印
  int i;
  prbtree root;
  nil =(prbtree)malloc(sizeof(rbtree));
  nil->color = BLACK;
  root = nil;
  int array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int length = sizeof(array)/sizeof(int);
  /* srand(GetTickCount()); */
  randomize_in_place(array, length);  
  print_array(array, length);  
  fflush(stdout);
  for (i = 0; i < length; i++)
    {
      prbtree y = (prbtree)malloc(sizeof(rbt_node));
      construct_node(y, array[i]);
      // print_node(y);
      root = rbt_insert_node(root, y);
      printf ("the %dth iteration\n",i + 1);
      mid_traverse_node(root);
      /* print_node(root); */
      /* printf("%x\n", (unsigned int)root); */
    }
  // mid_traverse_node(root);
  // 测试删除操作
  randomize_in_place(array, length);
  print_array(array, length);
  fflush(stdout);
  for (i = 0; i < length; ++i)
  {
       prbt_node x = rbt_search(root, array[i]);
       root = rbt_delete_node(root, x);
       printf ("the number %d deleted\n",array[i]);
       printf ("the %dth iteration\n",i + 1);
       mid_traverse_node(root);
  }
  return 0;
}
