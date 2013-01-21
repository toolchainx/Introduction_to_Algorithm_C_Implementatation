CC = gcc
OFLAG = -o 
CFLAGS = -Wall -g
OBJECTS = target.o

all: target

%.o:%.c %.h
	$(CC) $(CFLAGS) -c $< -o $@
# specify the header files dependency here
# using the gcc -MM source.c option

target: ${OBJECTS} 
	${CC} $^ ${OFLAG} $@

.PHONY:clean
clean: 
	-del ${OBJECTS} target
