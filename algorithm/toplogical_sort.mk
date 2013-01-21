CC := gcc
OFLAG = -o 
CFLAGS = -Wall -g
HEADERS = list.h adj_table.h dfs.h toplogical_sort.h
OBJECTS = list.o adj_table.o dfs.o toplogical_sort.o \
	 toplogical_sort_test.o

all: toplogical_sort_test

%.o:%.c %.h
	$(CC) $(CFLAGS) -c $<
dfs.o:adj_table.h
toplogical_sort.o:adj_table.h dfs.h list.h

toplogical_sort_test: $(OBJECTS)
	$(CC) $^ $(OFLAG) $@
.PHONY:clean
clean: 
	-del ${OBJECTS} toplogical_sort_test
