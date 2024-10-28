# Diretórios
SRC_DIR = src
BUILD_DIR = build
ASSETS_DIR = assets

# Nome do executável
TARGET = $(BUILD_DIR)/asteroids
WEB=

# Compilador e flags
CC = cc

CFLAGS = -Wall -Werror -Wpedantic -std=c99 -O3
LD_FLAGS=

LIBS = -lraylib

ifeq ($(WEB), 1)
	TARGET = $(BUILD_DIR)/index.html

	RAYLIB_DIR = web/raylib-5.0_webassembly

	CC=emcc
	CFLAGS+= -DPLATFORM_WEB -I$(RAYLIB_DIR)/include/
	LD_FLAGS = -s USE_GLFW=3 --preload-file $(ASSETS_DIR)
	LIBS=$(RAYLIB_DIR)/lib/libraylib.a
endif

# Busca todos os arquivos .c no diretório /src
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Gera os arquivos objeto no diretório /build
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Regra padrão: compilar e ligar
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS) $(LD_FLAGS)

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
