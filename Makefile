# Makefile pour Parking Intelligent

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I.
TARGET = parking.exe
SOURCES = main.c gestion_voitures.c menu_logique.c statistiques.c
OBJECTS = $(SOURCES:.c=.o)

# ----------------------------------------------------------------------
# Règle par défaut (Compilation complète)
# ----------------------------------------------------------------------
all: $(TARGET)

# Compilation du programme
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "a Compilation reussie ! Lancez avec: ./$(TARGET)"

# Compilation des fichiers objets
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# ----------------------------------------------------------------------
# Nettoyage (Compatible Windows/MinGW)
# ----------------------------------------------------------------------
clean:
	@echo "v Nettoyage des fichiers et repertoires..."
	-DEL /Q $(OBJECTS) $(TARGET)
	-DEL /Q traces\*.txt traces\*.png
	-RMDIR /S /Q obj
	-RMDIR /S /Q bin

# ----------------------------------------------------------------------
# Commandes Utilitaires
# ----------------------------------------------------------------------
# Recompilation complete
rebuild: clean all

# Test rapide
test: all
	./$(TARGET)

# Afficher l'aide
help:
	@echo "Commandes disponibles:"
	@echo "     make         - Compile le programme"
	@echo "     make clean   - Supprime les fichiers compiles"
	@echo "     make rebuild - Recompile tout"
	@echo "     make test    - Compile et lance le programme"

.PHONY: all clean rebuild test help