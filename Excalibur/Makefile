CC = x86_64-w64-mingw32-gcc

CC_FLAGS = -Wall -Wextra -Wno-unused-function -g
LD_FLAGS = -lglfw3 -lgdi32 -lglad -lopengl32 

INCLUDE_FLAGS = -I../Vendor/glfw/include \
				-I../Vendor/glad/include \
				-I../Vendor/stb/include \
				-Isrc

LIBRARY_FLAGS = -L../Vendor/glfw/lib \
				-L../Vendor/glad/lib

SRC_DIR = src
BIN_DIR = ../bin
OBJ_DIR = ../bin-int/Excalibur

SOURCES = $(shell find $(SRC_DIR) -name '*.c')
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))
TARGET = $(BIN_DIR)/Excalibur.exe

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CC_FLAGS) -c $< -o $@ $(INCLUDE_FLAGS)
$(TARGET): $(OBJECTS)
	$(CC) $(CC_FLAGS) $(OBJECTS) -o $@ $(LIBRARY_FLAGS) $(LD_FLAGS)

$(OBJECTS): | $(OBJ_DIR)
$(TARGET): | $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p `ls -d $(SRC_DIR)/*/ | cut -f2 -d'/' |  awk '{print "$(OBJ_DIR)/" $$0}' | tr '\n' ' '`
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

.PHONY: $(OBJ_DIR)
all: $(OBJ_DIR) $(TARGET)
