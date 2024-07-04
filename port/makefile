# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Iinclude -Wall -Wextra -Werror -g

# Libraries
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
    LDFLAGS = -lncurses -framework AudioToolbox -framework CoreFoundation
else ifeq ($(UNAME_S), Darwin)
    LDFLAGS = -lncurses -framework AudioToolbox -framework CoreFoundation
else
    LDFLAGS =
endif

# Source and object files
SRCS = Snake_Game.c
SRCS += $(wildcard include/*.c)
ifneq ($(UNAME_S), Darwin)
SRCS := $(filter-out include/system_mac.c, $(SRCS))
endif
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
