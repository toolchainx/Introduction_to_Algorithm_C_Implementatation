# 包含算法导论第二版伪代码的C语言实现

## 说明一
    每个算法包含4个文件，即XXX.h XXX.c XXX.mk XXX_test.c 文件，XXX为算法的名称，XXX_test.c 为测试算法有效性的文件，即main函数所在的文件。makefile为gnu make。使用auto-c-files.el(Emacs-Lisp代码)来生成这4个文件并载入相应的模板。auto_make_template.mk为makefile的模板。

## 说明二
    图的实现为邻接链表或者邻接矩阵。在对图进行测试时，使用的数据输入格式如下：
### 邻接矩阵(以数据输入文件adj_table.dat为例)

      // 顶点的索引均从0开始，连续索引
      0  // 图顶点的索引，用整数表示
      2  // 上一行所示的顶点的出度
      1 4  // 以上两行所示的顶点为源点，与之相连的邻接顶点
      1    // 第二个顶点的索引
      4
      0 2 3 4
      2
      2
      1 3
      3
      3
      1 2 4
      4
      3
      0 1 3 // 文件在最后一个数据终止，该行没有换行符

      函数adj_output()输出的结果为：

      5
      0 -> 1, weight: 0; 0 -> 4, weight: 0; 
      1 -> 0, weight: 0; 1 -> 4, weight: 0; 1 -> 3, weight: 0; 1 -> 2, weight: 0; 
      2 -> 1, weight: 0; 2 -> 3, weight: 0; 
      3 -> 1, weight: 0; 3 -> 4, weight: 0; 3 -> 2, weight: 0; 
      4 -> 0, weight: 0; 4 -> 3, weight: 0; 4 -> 1, weight: 0;

### 邻接矩阵(以数据输入文件all_pair_shortest_path.dat为例)

      5  // 顶点的个数，顶点索引为从0开始的连续索引，此处为0~4
      0 1 3  // edge: 0 -> 1 weight: 3
      0 2 8  // edge: 0 -> 2 weight: 8
      0 4 -4 // etc ...
      1 3 1
      1 4 7
      2 1 4
      3 0 2
      3 2 -5
      4 3 6 // 文件在最后一个数据终止，该行没有换行符
      函数print_adjmat()输出为：

      adj_mat_test all_pair_shortest_path.dat 
      |0   3   8   INF -4  |
      |INF 0   INF 1   7   |
      |INF 4   0   INF INF |
      |2   INF -5  0   INF |
      |INF INF INF 6   0   |

## 说明三

    对算法导论第二版里面的伪代码并没有完全实现，没有对练习题的答案进行代码实现。代码还有很多改进的地方，如一致的命名约定，一致的函数接口，设计的规范性等等。有些代码由于后来的改动，可能编译不能通过，将来有时间会进一步改进。开发环境Emacs for Windows + MinGW + GCC，该源码仅供学习讨论之用，如用于其它目的，维护者概不负责。欢迎对源码有兴趣的同学进行讨论:).
***
# 算法分类
  1. 排序算法
     * 堆排序		heap_sort
     * 快速排序		quick_sort
  2. 基本数据结构
     * 栈		stack
     * 队列		queue
     * 链表		list
     * 邻接链表		adj_table
     * 邻接矩阵		adj_mat
  3. 树
     * 二叉查找树		bst
     * 红黑树     	rbtree
  4. 堆
     * 二项堆		binomial_heap
     * Fibonacci堆	fib_heap
  5. 动态规划
     * 0-1 背包问题	knapsack
     * 最长公共子序列	lcs
  6. 贪心算法(待补充)
  7. 图算法
     * 广度优先搜索	bfs
     * 深度优先搜索	dfs
     * 拓扑排序		toplogical_sort
     * 强连通分支		scc
     * 最小生成树		mst_prim, mst_kruskal
     * 单源最短路径	single_source_shortest_path bellman_ford, dijkstra
     * 每对顶点间最短路径	all_pair_shortest_path, floyd_warshall, johnson
     * 有向图的传递闭包	transitive_closure    
     * 最大流		ford_fulkerson
      
