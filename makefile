# Compiler
CXX = x86_64-w64-mingw32-g++
#CXX = clang++

#Raylib lib path
RayLib = ./Raylib

ifeq ($(CXX),clang++)
# Linux deployment
CXXFLAGS = -std=c++20 -Wall -g $(RayLib --cflags)
LDFLAGS  = $(RayLib --libs)
else
# Windows deployment
CXXFLAGS = -std=c++20 -Wall -g -I$(RayLib)/include -static-libstdc++ -static-libgcc -DSDL_MAIN_HANDLED -O2 -DNDEBUG
LDFLAGS  = -L$(RayLib)/lib -lraylib -lopengl32 -lgdi32 -lwinmm -mconsole #-mwindows 
endif

# Files
SRCS := $(wildcard src/*.cpp)
OBJS := $(SRCS:.cpp=.o)
TARGET = Pacman

# Build app
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

# Compile .cpp to .o
src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(TARGET) $(OBJS)
