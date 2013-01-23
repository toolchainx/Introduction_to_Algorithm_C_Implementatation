# change your targets to your real targets
MINGW := MINGW32_NT-6.1
CC = gcc
OFLAG = -o 
CFLAGS = -Wall -g -DDEBUG
# get the dependent header files and change their name to source files
TARGET := target_to_change
FILES := $(filter %.c %.h, $(shell gcc -MM $(addsuffix .c, $(TARGET))))
SRCS := $(FILES:.h=.c)
DEPS := $(SRCS:.c=.d)
OBJECTS := $(SRCS:.c=.o)

ifdef SystemRoot
   ifeq ($(shell uname), ${MINGW})
      RM = rm -f
      FixPath = $1
   else
      RM = del /Q
      FixPath = $(subst /,\,$1)
   endif
else
   ifeq ($(shell uname), Linux)
      RM = rm -f
      FixPath = $1
   endif
endif


all: ${TARGET}

-include $(DEPS)
%.o:%.c
	$(CC) $(CFLAGS) -c -MMD $< -o $@

# specify the header files dependency here
# using the gcc -MM source.c option
${TARGET}: ${OBJECTS}
	${CC} $^ ${OFLAG} $@

.PHONY:clean
# the "$" is not needed before "FixPath"
clean:
	$(RM) $(call FixPath, ${OBJECTS} ${DEPS})
