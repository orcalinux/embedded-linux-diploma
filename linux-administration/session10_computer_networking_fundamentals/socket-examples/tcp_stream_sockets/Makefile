# Compiler and flags
CC      = gcc
CFLAGS  = -Wall -Wextra -I./include

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Targets (final binaries)
TARGETS = tcp_sender tcp_receiver

# Source files
SRC_SENDER   = $(SRC_DIR)/tcp_sender.c
SRC_RECEIVER = $(SRC_DIR)/tcp_receiver.c
SRC_COMMON   = $(SRC_DIR)/common.c

# Object files (go under obj/)
OBJ_SENDER   = $(OBJ_DIR)/tcp_sender.o
OBJ_RECEIVER = $(OBJ_DIR)/tcp_receiver.o
OBJ_COMMON   = $(OBJ_DIR)/common.o

# ANSI color codes for fancy output
GREEN  = \033[1;32m
YELLOW = \033[1;33m
BLUE   = \033[1;34m
RESET  = \033[0m

# Default target
all: $(TARGETS)

# "tcp_sender" and "tcp_receiver" are aliases for the final binaries in bin/
tcp_sender:   $(BIN_DIR)/tcp_sender
tcp_receiver: $(BIN_DIR)/tcp_receiver

# Link final executables in bin/
$(BIN_DIR)/tcp_sender: $(OBJ_SENDER) $(OBJ_COMMON) | $(BIN_DIR)
	@printf "$(BLUE)[LINK]$(RESET)  $@\n"
	@$(CC) $(CFLAGS) -o $@ $^

$(BIN_DIR)/tcp_receiver: $(OBJ_RECEIVER) $(OBJ_COMMON) | $(BIN_DIR)
	@printf "$(BLUE)[LINK]$(RESET)  $@\n"
	@$(CC) $(CFLAGS) -o $@ $^

# Compile .c files into .o under obj/
# The | $(OBJ_DIR) ensures the obj directory exists first (order-only dependency).
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@printf "$(GREEN)[CC]$(RESET)    $< -> $@\n"
	@$(CC) $(CFLAGS) -c -o $@ $<

# Ensure that obj/ and bin/ exist
$(OBJ_DIR):
	@mkdir -p $@
	@printf "$(YELLOW)Created directory: $(RESET)$@\n"

$(BIN_DIR):
	@mkdir -p $@
	@printf "$(YELLOW)Created directory: $(RESET)$@\n"

# Clean up build artifacts
clean:
	@printf "$(YELLOW)Cleaning files...$(RESET)\n"
	@rm -rf $(OBJ_DIR) $(BIN_DIR)

# Help target
help:
	@echo "Usage: make [target]"
	@echo "Targets:"
	@echo "  all            Build all programs (default)"
	@echo "  tcp_sender     Compile TCP sender program"
	@echo "  tcp_receiver   Compile TCP receiver program"
	@echo "  clean          Remove compiled files and directories"
	@echo "  help           Show this help message"

# Mark certain targets as phony to avoid naming collisions
.PHONY: all clean help tcp_sender tcp_receiver
