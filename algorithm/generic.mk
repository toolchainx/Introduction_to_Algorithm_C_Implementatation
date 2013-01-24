TARGETS = adj_list_test adj_mat_test all_pair_shortest_path_test bfs_test dag_shortest_path_test dfs_test dijkstra_test floyd_warshall_test ford_fulkerson_test johnson_test list_test single_source_shortest_path_test toplogical_sort_test transitive_closure_test binomial_heap bst disjoint_set_link fib_heap_test heap_sort in_perfect_shuffle knapsack lcs mst_kruskal mst_prim out_perfect_shuffle1 queue_test rbtree recsv_eight_queens recsv_eight_queens_bit recsv_to_iter transpose_adj_table_test scc sort_arr_idx_test

# 待修改的文件: scc 
CLEANTARGETS=$(TARGETS:=_clean)

all: $(TARGETS)
clean: $(CLEANTARGETS)

$(TARGETS) $(CLEANTARGETS):
	make -f Makefile.sub $@

.PHONY: all clean $(CLEANTARGETS)
