CC = x86_64-w64-mingw32-gcc

CC_FLAGS = -Wall -Wextra
LD_FLAGS = -static-libgcc -static -lgdi32 -lole32 -lshell32 -luuid

SRC_DIR = src
BIN_DIR = ../bin
OBJ_DIR = ../bin-int/Excalibur-Installer

SOURCES = $(shell find $(SRC_DIR) -name '*.c')
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

TARGET = $(BIN_DIR)/Excalibur-Installer.exe

RELEASE = 0
ATTACK = 1

ifeq ($(ATTACK),1)
	CC_FLAGS += -DEX_ATTACK
endif

ifeq ($(RELEASE),1)
	CC_FLAGS += -O2
else
	CC_FLAGS += -g
endif

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

