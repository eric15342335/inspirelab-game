# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Iinclude -Wall -Wextra -Werror -O1

# Libraries
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
    LDFLAGS = -lncurses
else ifeq ($(UNAME_S), Darwin)
    LDFLAGS = -lncurses
else
    LDFLAGS =
endif

# Source and object files
SRCS = Snake_Game.c
OBJS = $(SRCS:.c=.o)

# Output binary
TARGET = myprogram

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)

# Compiling
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean