# Compiler and flags
CC      = gcc
CFLAGS  = -Wall -Wextra -I./include

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Targets (final binaries)
TARGETS = udp_receiver udp_sender

# Source files
SRC_RECEIVER = $(SRC_DIR)/udp_receiver.c
SRC_SENDER   = $(SRC_DIR)/udp_sender.c
SRC_COMMON   = $(SRC_DIR)/common.c

# Object files
OBJ_RECEIVER = $(OBJ_DIR)/udp_receiver.o
OBJ_SENDER   = $(OBJ_DIR)/udp_sender.o
OBJ_COMMON   = $(OBJ_DIR)/common.o

# ANSI color codes for fancy output
GREEN  = \033[1;32m
YELLOW = \033[1;33m
BLUE   = \033[1;34m
RESET  = \033[0m

# Default target
all: $(TARGETS)

# "udp_receiver" and "udp_sender" are aliases for the final binaries in bin/
udp_receiver: $(BIN_DIR)/udp_receiver
udp_sender:   $(BIN_DIR)/udp_sender

# Link final executables in bin/
$(BIN_DIR)/udp_receiver: $(OBJ_RECEIVER) $(OBJ_COMMON) | $(BIN_DIR)
	@printf "$(BLUE)[LINK]$(RESET)  $@\n"
	@$(CC) $(CFLAGS) -o $@ $^

$(BIN_DIR)/udp_sender: $(OBJ_SENDER) $(OBJ_COMMON) | $(BIN_DIR)
	@printf "$(BLUE)[LINK]$(RESET)  $@\n"
	@$(CC) $(CFLAGS) -o $@ $^

# Compile .c files into .o under obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@printf "$(GREEN)[CC]$(RESET)    $< -> $@\n"
	@$(CC) $(CFLAGS) -c -o $@ $<

# Ensure obj/ and bin/ exist
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
	@echo "  all             Build all programs (default)"
	@echo "  udp_receiver    Compile the UDP receiver"
	@echo "  udp_sender      Compile the UDP sender"
	@echo "  clean           Remove compiled files and directories"
	@echo "  help            Show this help message"

# Mark certain targets as phony
.PHONY: all clean help udp_receiver udp_sender
