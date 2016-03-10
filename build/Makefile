# Where to find user code.
USER_DIR = ..
CC=gcc
#CPPFLAGS += -isystem $(USER_DIR)/src
CPPFLAGS += -g -Wall -Wextra -DNO__UT__

TESTS = thread_test

#.PHONY : all
all : $(TESTS)

clean :
	rm -rf $(USER_DIR)/src/*.o
	rm -rf $(TESTS)

# Builds a sample test.
SRCS := $(wildcard $(USER_DIR)/src/*.c)
OBJS := $(SRCS:.c=.o)

.c:.o
	$(CC) $(CPPFLAGS) -c 

$(TESTS) : $(OBJS)
	$(CC) $(CPPFLAGS) -lpthread $^ -o $@
