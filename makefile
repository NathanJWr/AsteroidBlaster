EXE = game

SRC_DIR = src
OBJ_DIR = obj
CC = g++

SRC = $(wildcard $(SRC_DIR)/*.cc)
OBJ = $(SRC:$(SRC_DIR)/%.cc=$(OBJ_DIR)/%.o)

CPPFLAGS += -Iinclude 
CFLAGS += -Wall -Werror -std=c++17 -pedantic-errors -g
LDFLAGS += -Llib
LDLIBS += -lSDL2 -lSDL2_image -lSDL2_ttf

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(EXE)
