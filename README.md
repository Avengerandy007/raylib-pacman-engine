# About
This is the repository for the static library required for the level editor and the actual game.

# Build instructions

## Prerequisites
- MinGW g++ (make sure to add this to your systems PATH if you don't want to change the makefile)
- make

## Instructions
1. Cd into cloned repo dir.

### If you don't have G++ in your sys PATH
  1. Open the makefile
    
  2. Change the following line
``` Make
CXX = x86_64-w64-mingw32-g++
``` 
  to point to your G++ path
  
___
  
2. Run make
