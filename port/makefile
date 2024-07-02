CC = gcc
CFLAGS = -flto -O3 -Wall -Wextra -pedantic -Wshadow -Wconversion -Wundef -Wswitch -g

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

.PHONY: all clean msvc

all: test

test: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

msvc:
	cl oled_min.c test.c -MP -O1 -Oy- -MD -GL -D_HAS_EXCEPTIONS=0 -GR-

clean:
	rm -f $(OBJS) test
