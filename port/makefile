CC = gcc
CFLAGS = -flto -O3 -Wall -Wextra -pedantic -Wshadow -Wconversion -Wundef -Wswitch -g

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

.PHONY: all clean

all: test

test: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) test
