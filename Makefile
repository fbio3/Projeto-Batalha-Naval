CC = gcc
CFLAGS = -Wall -Wextra -g -I./src
SRC_DIR = src
OBJ_DIR = obj
# Nome do executável final
BIN = batalha_naval

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))


all: $(BIN)

$(BIN): $(OBJS)
	@echo "Ligando o executavel..."
	$(CC) $(CFLAGS) -o $@ $^
	@echo "Sucesso! Execute com: ./$(BIN) ou make run"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compilando $<..."
	$(CC) $(CFLAGS) -c -o $@ $<

# --- Utilitários ---

clean:
	@echo "Limpando arquivos..."
	rm -rf $(OBJ_DIR) $(BIN) $(BIN).exe

run: all
	@echo "Iniciando o jogo..."
	./$(BIN)

.PHONY: all clean run