#include "../include/Tile.hpp"

Matrix2<Tile*> Tile::tileSet(20, 20);

void Tile::SetDef(uint8_t& x, uint8_t& y){
	bool parentBreak;
	for (; x < tileSet.matrix.size(); x++){
		if (parentBreak) break;
		y = 0;
		for (; y < tileSet.matrix[x].size(); y++){
			if (tileSet.matrix[x][y] == this){
				parentBreak = true;
				break;
			}
		}
	}
	}

Tile::Tile(){
	uint8_t x, y;
	SetDef(x, y);
	m_def.x = x * 50;
	m_def.y = y * 50;
	m_def.width = 50;
	m_def.height = 50;

}
