# Compiler Configuration
CC = gcc

ifeq ($(DEBUG), 1)
	CFLAGS = -O2 -Wall -Wextra -Wpedantic -std=gnu89 -g3 # -fsanitize=address,undefined
else
	CFLAGS = -O2 -Wall --ansi -DNDEBUG
endif

LDFLAGS = -lm 
CFLAGS  = -Iinclude

# Binary name and path
BUILD_FOLDER = build
BINARY_NAME  = Assembler
TARGET_BUILD = $(join $(join $(BUILD_FOLDER) , / ) , $(BINARY_NAME))
# Project files
SOURCES = $(shell find ./source/ -name "*.c" -type f)
OBJECTS = $(SOURCES:.c=.o) 

.PHONY: clean binary_folder

all: binary_folder $(BINARY_NAME)

# Compiling all projects files
$(BINARY_NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET_BUILD) $(LDFLAGS)

# Generates object files
%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

# Creating a binary folder if it doesn't exist
binary_folder:
	mkdir -p $(BUILD_FOLDER)

# Cleaning up all objects and binary
clean:
	find . -name "*.o" -type f -delete
	rm -r -f $(BUILD_FOLDER)

