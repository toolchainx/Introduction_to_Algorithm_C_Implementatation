CC = gcc
OFLAG = -o 
CFLAGS = -Wall -g 
HEADERS = adj_table.h dfs.h
OBJECTS = adj_table.o dfs.o dfs_test.o


# all be the first
all: dfs_test


%.o:%.c %.h
	$(CC) $(CFLAGS) -c $<
dfs.o:adj_table.h
dfs_test.o:dfs.h


dfs_test: $(OBJECTS)
	$(CC) $^ $(OFLAG) $@

.PHONY:clean
clean:
	-del $(OBJECTS) dfs_test
