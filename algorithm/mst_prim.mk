CC = gcc
OFLAG = -o 
CFLAGS = -Wall -g
HEADERS = adj_table.h fib_heap.h

.SUFFIXES : .o .c
.c.o:
	$(CC) $(CFLAGS) -c $<
all: mst_prim

mst_prim: mst_prim.o fib_heap.o adj_table.o $(HEADERS)
	$(CC) $(CFLAGS) mst_prim.c fib_heap.c adj_table.c $(OFLAG) \
	mst_prim

clean: 
	del mst_prim.o fib_heap.o adj_table.o
