CC = x86_64-w64-mingw32-gcc

CC_FLAGS = -Wall -Wextra
LD_FLAGS = -static-libgcc -static -lgdi32 -lole32 -lshell32 -lcomctl32 -luuid -lshlwapi

SRC_DIR = src
BIN_DIR = ../bin
OBJ_DIR = ../bin-int/Excalibur-KeyLog

SOURCES = $(shell find $(SRC_DIR) -name '*.c')
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

TARGET = $(BIN_DIR)/Excalibur-KeyLog.exe

include ../config.mk

ifeq ($(RELEASE),1)
	CC_FLAGS += -O2
else
	CC_FLAGS += -g
endif

.PHONY: all

all: $(EXCALIBUR_OBJ) $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CC_FLAGS) -c $< -o $@ $(LD_FLAGS)

$(TARGET): $(OBJECTS) 
	$(CC) -mwindows $(CC_FLAGS) $^ -o $@ $(LD_FLAGS)

$(OBJECTS): | $(OBJ_DIR)
$(TARGET): | $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

