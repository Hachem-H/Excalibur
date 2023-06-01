
CC = x86_64-w64-mingw32-gcc

CC_FLAGS = -Wall -Wextra -g
LD_FLAGS = -lglfw3 -lgdi32

INCLUDE_FLAGS = -I../Vendor/glfw/include
LIBRARY_FLAGS = -L../Vendor/glfw/lib

SRC_DIR = src
BIN_DIR = ../bin
OBJ_DIR = ../bin-int/Excalibur

SOURCES = $(shell find $(SRC_DIR) -name '*.c')
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))
TARGET = $(BIN_DIR)/Excalibur.exe

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CC_FLAGS) -c $< -o $@ $(INCLUDE_FLAGS)
$(TARGET): $(OBJECTS)
	$(CC) $(CC_FLAGS) $< -o $@ $(LIBRARY_FLAGS) $(LD_FLAGS)

$(OBJECTS): | $(OBJ_DIR)
$(TARGET): | $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

all: $(TARGET)