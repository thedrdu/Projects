
# Compiler and linker options
CC = gcc
CFLAGS = -Wall -Wextra -I./include -I./lib/freetype-2.13.0/include -I./lib/stb -Iexternal
LDFLAGS = -lfreetype

# Source and object files
SRC = src/main.c src/bitmapreader.c
OBJ = $(SRC:src/%.c=obj/%.o)

# Target executable
TARGET = bin/asciiart

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean

build: clean all
