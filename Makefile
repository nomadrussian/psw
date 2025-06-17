.PHONY: clean

SRC_DIR = src
BIN_DIR = bin

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)%.c, $(BIN_DIR)%.o, $(SRC))
BIN = $(BIN_DIR)/cli_psw
LAUNCHER = psw

CC = gcc -std=c23 -Wall -Wextra -Werror 

all: $(BIN_DIR) $(BIN) $(LAUNCHER)

# Generating bin directory if doesn't exist
$(BIN_DIR):
	@mkdir -p $(BIN_DIR) 

# Compiling and linking
$(BIN): $(OBJ)
	@$(CC) $(OBJ) -o $(BIN)
	@rm $(OBJ)
	@chmod +x $(BIN)

# Compiling into object files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) -c $< -o $@

# Generating simple bash launcher
$(LAUNCHER):
	@touch $(LAUNCHER)
	@echo "#!/bin/sh" > $(LAUNCHER)
	@chmod +x $(LAUNCHER)
	@echo "./$(BIN)" > $(LAUNCHER)

clean:
	@rm -f $(LAUNCHER)
	@rm -rf $(BIN_DIR)

