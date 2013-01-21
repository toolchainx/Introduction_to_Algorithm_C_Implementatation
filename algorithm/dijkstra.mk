# to be filled...
CC = gcc
OFLAG = -o 
CFLAGS = -Wall -g
OBJECTS = dijkstra_test.o dijkstra.o include/require.o adj_table.o \
 fib_heap.o single_source_shortest_path.o print_path.o

all: dijkstra_test

%.o:%.c %.h
	$(CC) $(CFLAGS) -c $<
dijkstra_test.o: dijkstra.h include/require.h adj_table.h \
 fib_heap.h single_source_shortest_path.h print_path.h
dijkstra.o: include/require.h adj_table.h \
 fib_heap.h single_source_shortest_path.h print_path.h
single_source_shortest_path.o:include/require.h adj_table.h print_path.h
print_path.o:adj_table.h

dijkstra_test: ${OBJECTS} 
	${CC} $^ ${OFLAG} $@

.PHONY:clean
clean: 
	-del ${OBJECTS} dijkstra_test
