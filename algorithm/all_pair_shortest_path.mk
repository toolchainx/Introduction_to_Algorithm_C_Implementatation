CC = gcc
OFLAG = -o 
CFLAGS = -Wall -g -DDEBUG
OBJECTS = all_pair_shortest_path_test.o all_pair_shortest_path.o \
	 adj_mat.o include/require.o

all: all_pair_shortest_path_test

%.o:%.c %.h
	$(CC) $(CFLAGS) -c $< $(OFLAG) $@
all_pair_shortest_path_test.o: all_pair_shortest_path.h
all_pair_shortest_path_test: ${OBJECTS} 
	${CC} $^ ${OFLAG} $@

.PHONY:clean
clean: 
	-del ${OBJECTS} all_pair_shortest_path_test
