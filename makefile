# Compiler and base flags
CC = gcc
CFLAGS = -Wall -Wextra -pthread -g

# Directories
SRC_DIR = src
BUILD_DIR = build

# Project files
TARGET = port_scanner
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/scanner.c $(SRC_DIR)/threads.c $(SRC_DIR)/utils.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

asan: CFLAGS += -fsanitize=address -fno-omit-frame-pointer
asan: clean all

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean asan