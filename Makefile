# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c99 -MMD -MP

# Directories
SRC_DIR = src
BUILD_DIR = build

# Source files
SRC = $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJ = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Dependency files
DEPS = $(OBJ:.o=.d)

# Executable
TARGET = $(BUILD_DIR)/simple_graphical_engine

# Libraries
LIBS = -lX11

# Default target
all: $(TARGET)

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Link the executable
$(TARGET): $(BUILD_DIR) $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIBS)

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Run the program
run: $(TARGET)
	./$(TARGET)

# Debug mode
debug: CFLAGS += -g
debug: clean all

# Clean the build directory
clean:
	rm -rf $(BUILD_DIR)

# Include dependency files
-include $(DEPS)

.PHONY: all clean run debug
