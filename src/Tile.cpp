#include "../include/Tile.hpp"
#include <cstdint>
#include <iostream>
#include <memory>

Matrix2<Tile, 20> Tile::tileSet;

void Tile::SetPosition(const uint8_t x, const uint8_t y, const uint8_t size) const{
	m_def->x = x * size;
	m_def->y = y * size;
	m_def->width = size;
	m_def->height = size;
}
