CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99
SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/%.o)
TARGET = build/base

all: $(TARGET)

# Linkowanie koncowego programu
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)
	
# Kompilacja plikow .c do .o
build/%.o: src/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

# Czyszczenie plikow wynikowych
clean:
	rm -rf build

.PHONY: all clean
