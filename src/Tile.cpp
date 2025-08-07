#include "../include/Tile.hpp"
#include <cstdint>
#include <iostream>
#include <memory>

Matrix2<Tile, 20> Tile::tileSet;

void Tile::InitTileSet(){
	uint8_t x = 0, y = 0;
	for (; x < tileSet.matrix.size(); x++){
		y = 0;
		for (; y < tileSet.matrix[x].size(); y++){
			//std::cout << "Iterating over tile at " << x << ", " << y << "\n";
			tileSet.matrix[x][y].SetPosition(x, y);
		}
	}
}

void Tile::SetPosition(uint8_t x, uint8_t y){
	m_def.x = x * 50;
	m_def.y = y * 50;
	m_def.width = 50;
	m_def.height = 50;
	//std::cout << "Tile constructed\n";
}
