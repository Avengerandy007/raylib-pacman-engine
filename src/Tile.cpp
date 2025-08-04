#include "../include/Tile.hpp"
#include <algorithm>

Matrix2<Tile*> Tile::tileSet(20, 20);

void Tile::SetDef(){
	int x = 0, y = 0;
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
	m_def.x = x * 50;
	m_def.y = y * 50;
	m_def.width = 50;
	m_def.height = 50;
}

Tile::Tile(){
	SetDef();
}
