# Compiler
CXX = x86_64-w64-mingw32-g++
#CXX = clang++

#Raylib lib path
RayLib = ./Raylib

ifeq ($(CXX),clang++)
# Linux deployment
CXXFLAGS = -std=c++20 -Wall -g $(RayLib --cflags)
#LDFLAGS  = $(RayLib --libs)
else
# Windows deployment
CXXFLAGS = -std=c++20 -Wall -g -I$(RayLib)/include -static-libstdc++ -static-libgcc -O2 -DNDEBUG
#LDFLAGS  = -L$(RayLib)/lib -lraylib -lopengl32 -lgdi32 -lwinmm -mconsole #-mwindows 
endif

# Files & directories
SRCS := $(wildcard src/*.cpp)
BUILD_DIR := build
OBJS := $(patsubst src/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
TARGET = libpacman.a

# Default rule
all: $(TARGET)

# Build static library
$(TARGET): $(OBJS)
	ar rcs $@ $(OBJS)

# Compile .cpp to .o (in build dir)
$(BUILD_DIR)/%.o: src/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET)
