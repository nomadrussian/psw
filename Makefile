.PHONY: clean

SRC_DIR = src
BIN_DIR = bin

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

CC = gcc -O0 -Wall -Wextra -Werror

BIN = $(BIN_DIR)/cli_psw
LAUNCHER = psw

all: $(BIN_DIR) $(BIN) $(LAUNCHER)

# Generating bin directory if doesn't exist
$(BIN_DIR):
	@mkdir -p $(BIN_DIR) 

# Compiling
$(BIN):
	@$(CC) $(SRC) -o $(BIN)
	@chmod +x $(BIN)

# Generating simple bash launcher
$(LAUNCHER):
	@touch $(LAUNCHER)
	@echo "#!/bin/sh" > $(LAUNCHER)
	@chmod +x $(LAUNCHER)
	@echo "./$(BIN)" > $(LAUNCHER)

clean:
	@rm -f $(LAUNCHER)
	@rm -rf $(BIN_DIR)

