#include "../include/Update.hpp"
#include "../include/Tile.hpp"
#include <iostream>
#include <memory>
#define println(x) std::cout << x << "\n"

void InitRaylib(){
	InitWindow(1000, 1000, "Pacman");
	SetExitKey(KEY_NULL);
}

int main(){
	std::cout << "Hello World!" << std::endl;
	InitRaylib();
	println("Started raylib");
	Tile::InitTileSet();
	println("Created tiles");
	Tile::tileSet.matrix[0][0].m_containedEntity = std::make_unique<Entity>("Wall.png");
	Update();
	CloseWindow();
}
