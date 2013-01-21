# to be modified...
CC := gcc
OFLAG = -o 
CFLAGS = -Wall -g
HEADERS = adj_table.h print_path.h
OBJECTS = adj_table.o print_path.o single_source_shortest_path.o

all: single_source_shortest_path
$(OBJECTS): %.o:%.c $(HEADERS)
	$(CC) -c $(CFLAGS) $< -o $@

single_source_shortest_path: ${OBJECTS} 
	${CC} ${CFLAGS} $^ ${OFLAG} $@

.PHONY:clean
clean: 
	-del ${OBJECTS}
