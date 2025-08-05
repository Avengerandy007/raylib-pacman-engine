#include "../include/EntityModules.hpp"
#include "../include/Tile.hpp"
#include <cstdint>
#include <memory>

/*  
 *	CONTROLLER CLASS
 */

Controller::Controller(uint16_t speed){
	m_speed = speed;
}

bool Controller::CheckWall(uint8_t x, uint8_t y){
	x += dir.x * m_speed;
	y += dir.y * m_speed;
	if (Tile::tileSet.matrix[x][y]->m_containedEntity != nullptr){
		X = x;
		Y = y;
		return false;
	}else return true;
}

void Controller::Move(){
	Tile* origin = Tile::tileSet.matrix[X][Y];
	if (CheckWall(X, Y)) return;
	Tile* destination = Tile::tileSet.matrix[X][Y];
	destination->m_containedEntity = std::move(origin->m_containedEntity);
	destination->m_containedEntity->rect = std::make_unique<Rectangle>(destination->m_def);
}
