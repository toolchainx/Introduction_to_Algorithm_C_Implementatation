# for Win32
# Under Unix/Linux like system you need substitute the "\\" to "/"
# and get rid of the "exe" extention
CC := gcc
OFLAG = -o 
CFLAGS = -Wall -g
OBJECTS = dag_shortest_path.o dag_shortest_path_test.o \
	single_source_shortest_path.o adj_table.o print_path.o \
	toplogical_sort.o  dfs.o list.o  include\\require.o

all: dag_shortest_path_test
# $< 代表依赖的第一对象（文件或者模式）
%.o:%.c %.h
	$(CC) $(CFLAGS) -c $< -o $@
dag_shortest_path_test.o: adj_table.h print_path.h toplogical_sort.h \
			dfs.h list.h include\\require.h
print_path.o: adj_table.h include\\require.h
toplogical_sort.o: dfs.h adj_table.h list.h include\\require.h
dfs.o: adj_table.h include\\require.h

dag_shortest_path_test: ${OBJECTS} 
	${CC} -Wall $^ ${OFLAG} $@

.PHONY:clean
clean: 
	-del ${OBJECTS} dag_shortest_path_test.exe
