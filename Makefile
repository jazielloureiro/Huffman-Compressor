# Compiler
CC = gcc

# Make directory command
MAKE = mkdir -p

# Remove command
RM = rm -rf

# Binary
BIN = hc

# Directories
SOURCE_DIR = src
OBJECTS_DIR = .obj

# Files
SOURCE_C = $(wildcard $(SOURCE_DIR)/*.c)
SOURCE_H = $(filter-out $(SOURCE_DIR)/main.h, $(SOURCE_C:.c=.h))
OBJECTS = $(SOURCE_C:$(SOURCE_DIR)/%.c=$(OBJECTS_DIR)/%.o)

$(BIN): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

$(OBJECTS_DIR)/%.o: $(SOURCE_DIR)/%.c $(SOURCE_H) | $(OBJECTS_DIR)
	$(CC) -c $< -o $@

$(OBJECTS_DIR):
	$(MAKE) $(OBJECTS_DIR)

clean:
	$(RM) $(OBJECTS_DIR) $(BIN)
