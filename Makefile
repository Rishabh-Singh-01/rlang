# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

# Directories
SRC_DIR = .
OBJ_DIR = bin/obj
BIN_DIR = bin

# Source files
SRC = $(SRC_DIR)/main.c

# Object files - Correcting how we define object files to place them in bin/obj
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Output executable
EXEC = $(BIN_DIR)/exec

# Targets
all: run 

# Build the project
build: $(EXEC)

$(EXEC): $(OBJ)
	@mkdir -p $(BIN_DIR)  # Create bin directory if it doesn't exist
	$(CC) $(OBJ) -o $(EXEC)

# Rule for compiling source files into object files in bin/obj
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)  # Create bin/obj directory if it doesn't exist
	$(CC) $(CFLAGS) -c $< -o $@

# Run the project
run: clean build
	$(EXEC)

# Clean the build artifacts
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all build run clean
