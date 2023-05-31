CC = x86_64-w64-mingw32-gcc

CC_FLAGS = -Wall -Wextra -g
LD_FLAGS = -lglfw3 -lgdi32

INCLUDE_FLAGS = -IVendor/glfw/include
LIBRARY_FLAGS = -LVendor/glfw/lib

SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = bin-int
BOOT_DIR = boot

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))
TARGET = $(BIN_DIR)/Application.exe

.PHONY: boot all

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

boot:
	nasm -f bin -o $(BIN_DIR)/boot.bin $(BOOT_DIR)/boot.asm
	xxd -i $(BIN_DIR)/boot.bin > $(SRC_DIR)/Boot.h
clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)

