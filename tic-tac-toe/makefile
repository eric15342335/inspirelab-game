# cl -MD -GL -D_HAS_EXCEPTIONS=0 -GR- -O1 -Oy- -W4 -sdl -Iinclude include/oled_min.c Snake_Game.c user32.lib -Fe:snakegame.exe

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Iinclude -Wall -Wextra -flto -O3

# Libraries
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
    LDFLAGS = -framework AudioToolbox -framework CoreFoundation -framework ApplicationServices -pthread
else
    LDFLAGS =
endif

# Source and object files
SRCS = tic-tac-toe.c
SRCS += $(wildcard include/*.c)
ifneq ($(UNAME_S), Darwin)
SRCS := $(filter-out include/system_mac.c,$(SRCS))
endif
OBJS = $(SRCS:.c=.o)

# Output binary
TARGET = tic-tac-toe

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
