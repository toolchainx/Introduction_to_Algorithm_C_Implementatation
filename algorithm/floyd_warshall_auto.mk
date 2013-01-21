# change the "target" to your real target use M-% or C-M-%
CC = gcc
OFLAG = -o 
CFLAGS = -Wall -g
SRCS = floyd_warshall_test.c include/require.c floyd_warshall.c \
	 adj_mat.c
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

all: floyd_warshall_test

-include $(DEPS)
%.o:%.c
	$(CC) $(CFLAGS) -c -MMD $< -o $@

# specify the header files dependency here
# using the gcc -MM source.c option
floyd_warshall_test: ${OBJECTS}
	${CC} $^ ${OFLAG} $@

.PHONY:clean
# 注意call 后面的表达式不用加$符号
clean:
	$(RM) $(call FixPath, ${OBJECTS} ${DEPS})
