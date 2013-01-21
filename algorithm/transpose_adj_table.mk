CC = gcc
OFLAG = -o 
CFLAGS = -Wall -g
HEADERS = adj_table.h

.SUFFIXES : .o .c
.c.o:
	$(CC) $(CFLAGS) -c $<
all: transpose_adj_table

transpose_adj_table: transpose_adj_table.o adj_table.o $(HEADERS)
	$(CC) $(CFLAGS) transpose_adj_table.c adj_table.c $(OFLAG) \
	transpose_adj_table
