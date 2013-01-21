# change the "target" to your real target use M-% or C-M-%

CC = gcc
OFLAG = -o 
CFLAGS = -Wall -g
OBJECTS = adj_mat_test.o adj_mat.c include/require.o

all: adj_mat_test

%.o:%.c %.h
	$(CC) $(CFLAGS) -c $< -o $@
# specify the header files dependency here
# using the gcc -MM source.c option

adj_mat_test.o:adj_mat.h

adj_mat_test: ${OBJECTS} 
	${CC} $^ ${OFLAG} $@

.PHONY:clean
clean: 
	-del ${OBJECTS} adj_mat_test
