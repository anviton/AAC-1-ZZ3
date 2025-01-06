# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS =

# Répertoires
SRC_DIR = src
UTILS_DIR = utils
BIN_DIR = bin

# Fichiers sources
SRC_FILES = main.c $(SRC_DIR)/chinese_postman.c $(UTILS_DIR)/graph.c
OBJ_FILES = $(SRC_FILES:.c=.o)

# Nom de l'exécutable
TARGET = $(BIN_DIR)/program

# Règle par défaut
all: $(TARGET)

# Compilation de l'exécutable
$(TARGET): $(OBJ_FILES) | $(BIN_DIR)
	$(CC) $(OBJ_FILES) -o $@ $(LDFLAGS)

# Compilation des fichiers objets
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Crée le répertoire bin s'il n'existe pas
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Nettoyage des fichiers générés
clean:
	rm -rf $(OBJ_FILES) $(TARGET)

# Nettoyage complet
dist-clean: clean
	rm -rf $(BIN_DIR)
