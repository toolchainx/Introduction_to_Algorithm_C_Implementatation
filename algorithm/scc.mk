CC = gcc
OFLAG = -o 
CFLAGS = -Wall -g
HEADERS = dfs.h list.h adj_table.h transpose_adj_table.h


.SUFFIXES : .o .c
.c.o:
	$(CC) $(CFLAGS) -c $<
all: scc

scc: scc.o dfs.o list.o adj_table.o transpose_adj_table.o $(HEADERS)
	$(CC) $(CFLAGS) scc.c dfs.c list.c adj_table.c transpose_adj_table.c \
	-o scc

clean: 
	del  scc.o dfs.o list.o adj_table.o transpose_adj_table.o
