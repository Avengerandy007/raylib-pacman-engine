#include "../include/Tile.hpp"
#include <memory>

Matrix2<std::shared_ptr<Tile>, 20> Tile::tileSet;

void Tile::SetDef(uint8_t& x, uint8_t& y){
	bool parentBreak;
	for (; x < tileSet.matrix.size(); x++){
		if (parentBreak) break;
		y = 0;
		for (; y < tileSet.matrix[x].size(); y++){
			tileSet.matrix[x][y] = std::make_shared<Tile>();
			if (tileSet.matrix[x][y].get() == this){
				parentBreak = true;
				break;
			}
		}
	}
	}

Tile::Tile(){
	uint8_t x = 0, y = 0;
	SetDef(x, y);
	m_def.x = x * 50;
	m_def.y = y * 50;
	m_def.width = 50;
	m_def.height = 50;

}
