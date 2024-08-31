# Nome do executável
TARGET = asteroids

# Diretórios
SRC_DIR = src
BUILD_DIR = build

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Werror -Wpedantic -std=c99 -O3
LIBS = -lraylib

# Busca todos os arquivos .c no diretório /src
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Gera os arquivos objeto no diretório /build
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Regra padrão: compilar e ligar
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

# Compila os arquivos .c em arquivos .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Cria o diretório /build caso não exista
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Limpeza
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Executa o jogo
run: $(TARGET)
	./$(TARGET)

.PHONY: clean run
