# change the "target" to your real target use M-% or C-M-%
# add the c files used in SRCS
CC = gcc
OFLAG = -o 
CFLAGS = -Wall -g -DDEBUG
# get the dependent header files and change their name to source files
FILES := $(filter %.c %.h, $(shell gcc -MM johnson_test.c))
SRCS := $(FILES:.h=.c)
# SRCS = johnson_test.c johnson.c include/require.c adj_table.c \
#  adj_mat.c single_source_shortest_path.c print_path.c dijkstra.c \
#  fib_heap.c
DEPS := $(SRCS:.c=.d)

# 此处为变量的高级用法，将SRCS中所有的.c文件变成.o文件并保存为变量OBJECTS
OBJECTS := $(SRCS:.c=.o)

ifdef SystemRoot
   RM = del /Q
   FixPath = $(subst /,\,$1)
else
   ifeq ($(shell uname), Linux)
      RM = rm -f
      FixPath = $1
   endif
endif

all: johnson_test

-include $(DEPS)
%.o:%.c
	$(CC) $(CFLAGS) -c -MMD $< -o $@

# specify the header files dependency here
# using the gcc -MM source.c option
johnson_test: ${OBJECTS}
	${CC} $^ ${OFLAG} $@

.PHONY:clean
# 注意call 后面的表达式不用加$符号
clean:
	$(RM) $(call FixPath, ${OBJECTS} ${DEPS})
