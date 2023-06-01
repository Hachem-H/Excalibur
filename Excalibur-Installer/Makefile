CXX = x86_64-w64-mingw32-g++

CXX_FLAGS = -Wall -Wextra -g
LD_FLAGS = -static-libstdc++ \
		   -static-libgcc \
		   -static

SRC_DIR = src
BIN_DIR = ../bin
OBJ_DIR = ../bin-int/Excalibur-Installer

SOURCES = $(shell find $(SRC_DIR) -name '*.cpp')
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))
TARGET = $(BIN_DIR)/Excalibur-Installer.exe

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@ $(LD_FLAGS)
$(TARGET): $(OBJECTS)
	$(CXX) $(CXX_FLAGS) $< -o $@ $(LD_FLAGS)

$(OBJECTS): | $(OBJ_DIR)
$(TARGET): | $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

all: $(TARGET)