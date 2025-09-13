#include "../include/Tile.hpp"
#include <cstdint>
#include <iostream>
#include <memory>

Matrix2<Tile, 20> Tile::tileSet;

void Tile::InitTileSet(const uint8_t tileSize, const uint16_t setSize){
	uint8_t x = 0, y = 0;
	for (; x < setSize; x++){
		y = 0;
		for (; y < setSize; y++){
			tileSet.matrix[x][y].m_def = std::make_shared<Rectangle>();
			tileSet.matrix[x][y].SetPosition(x, y, tileSize);
		}
	}
}

void Tile::SetPosition(uint8_t x, uint8_t y, uint8_t size) const{
	m_def->x = x * size;
	m_def->y = y * size;
	m_def->width = size;
	m_def->height = size;
}

void Tile::SetEntityRectangles(const uint16_t matrixSize){
	for (uint8_t i = 0; i < matrixSize; i++){
		for(uint8_t k = 0; k < matrixSize; k++){
			if (Tile::tileSet.matrix[i][k].m_containedEntity) Tile::tileSet.matrix[i][k].m_containedEntity->rect = Tile::tileSet.matrix[i][k].m_def;
			if (Tile::tileSet.matrix[i][k].m_coinContainer) Tile::tileSet.matrix[i][k].m_coinContainer->rect = Tile::tileSet.matrix[i][k].m_def;
		}
	}
	std::cout << "Finished setting all entity rectangles\n";
}
