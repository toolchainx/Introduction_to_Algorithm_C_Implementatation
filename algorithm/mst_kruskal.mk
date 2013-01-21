CC = gcc
OFLAG = -o 
CFLAGS = -Wall -g
OBJECTS = disjoint_set_forest.o mst_kruskal.o

all: mst_kruskal

%.o:%.c %.h
	$(CC) $(CFLAGS) -c $< -o $@
mst_kruskal.o:disjoint_set_forest.h

mst_kruskal: ${OBJECTS} 
	${CC} $^ ${OFLAG} $@

.PHONY:clean
clean: 
	-del ${OBJECTS} mst_kruskal
