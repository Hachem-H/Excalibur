CC = x86_64-w64-mingw32-gcc

CC_FLAGS = -Wall -Wextra -g
LD_FLAGS = -static-libgcc -static -lgdi32

SRC_DIR = src
BIN_DIR = ../bin
OBJ_DIR = ../bin-int/Excalibur-Installer

SOURCES = $(shell find $(SRC_DIR) -name '*.c')
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

TARGET = $(BIN_DIR)/Excalibur-Installer.exe

EXCALIBUR_RC = Excalibur-Installer.rc
EXCALIBUR_OBJ = $(OBJ_DIR)/Excalibur-Installer.o

.PHONY: all

all: $(EXCALIBUR_OBJ) $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CC_FLAGS) -c $< -o $@ $(LD_FLAGS)

$(EXCALIBUR_OBJ): $(EXCALIBUR_RC)
	x86_64-w64-mingw32-windres $(EXCALIBUR_RC) -o $(EXCALIBUR_OBJ)

$(TARGET): $(OBJECTS) 
	$(CC) -mwindows $(CC_FLAGS) $^ $(EXCALIBUR_OBJ) -o $@ $(LD_FLAGS)

$(EXCALIBUR_OBJ): | $(OBJ_DIR)
$(OBJECTS): | $(OBJ_DIR)
$(TARGET): | $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

