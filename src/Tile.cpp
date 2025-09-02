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
			tileSet.matrix[x][y].m_def = std::make_shared<Rectangle>();
			tileSet.matrix[x][y].SetPosition(x, y);
		}
	}
}

void Tile::SetPosition(uint8_t x, uint8_t y){
	m_def->x = x * 50;
	m_def->y = y * 50;
	m_def->width = 50;
	m_def->height = 50;
}

void Tile::SetEntityRectangles(){
	for (uint8_t i = 0; i < 20; i++){
		for(uint8_t k = 0; k < 20; k++){
			if (Tile::tileSet.matrix[i][k].m_containedEntity) Tile::tileSet.matrix[i][k].m_containedEntity->rect = Tile::tileSet.matrix[i][k].m_def;
			if (Tile::tileSet.matrix[i][k].m_coinContainer) Tile::tileSet.matrix[i][k].m_coinContainer->rect = Tile::tileSet.matrix[i][k].m_def;
		}
	}
	std::cout << "Finished setting all entity rectangles\n";
}
