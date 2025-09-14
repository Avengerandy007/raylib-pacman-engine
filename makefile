# Compiler
CXX = g++
#CXX = clang++

#Raylib lib path
RayLib = ./Raylib

ifeq ($(CXX),clang++)
# Linux deployment
CXXFLAGS = -std=c++20 -Wall -g $(RayLib --cflags)
#LDFLAGS  = $(RayLib --libs)
else
# Windows deployment
CXXFLAGS = -std=c++20 -Wall -g -I$(RayLib)/include -O2 -DNDEBUG
#LDFLAGS  = -L$(RayLib)/lib -lraylib -lopengl32 -lgdi32 -lwinmm -mconsole #-mwindows 
endif

# Files & directories
SRCS := $(wildcard src/*.cpp)
BUILD_DIR := build
OBJS := $(patsubst src/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
TARGET = libpacman.a

# Default rule
all: $(TARGET)

# Ensure build directory exists
$(BUILD_DIR):
ifeq ($(OS),Windows_NT)
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
else
	@mkdir -p $(BUILD_DIR)
endif

# Compile .cpp -> .o
$(BUILD_DIR)/%.o: src/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build static library
$(TARGET): $(OBJS)
	ar rcs $@ $(OBJS)

# Clean
clean:
ifeq ($(OS),Windows_NT)
	-rmdir /s /q $(BUILD_DIR)
	-del $(TARGET)
else
	rm -rf $(BUILD_DIR) $(TARGET)
endif
