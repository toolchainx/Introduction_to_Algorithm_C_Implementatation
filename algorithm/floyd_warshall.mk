# change the "target" to your real target use M-% or C-M-%
CC = gcc
OFLAG = -o 
CFLAGS = -Wall -g
OBJECTS = floyd_warshall_test.o ./include/require.o floyd_warshall.o \
	 adj_mat.o

all: floyd_warshall_test

%.o:%.c %.h
	$(CC) $(CFLAGS) -c $< -o $@
# specify the header files dependency here
# using the gcc -MM source.c option
floyd_warshall_test.o:floyd_warshall.h include/require.h adj_mat.h
floyd_warshall.o:include/require.h adj_mat.h
adj_mat.o:include/require.h
floyd_warshall_test: ${OBJECTS} 
	${CC} $^ ${OFLAG} $@

.PHONY:clean
clean: 
	-del ${OBJECTS} floyd_warshall_test
