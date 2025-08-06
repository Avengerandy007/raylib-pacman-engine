#pragma once
#include <memory>
#include "Entity.hpp"
#include "Matrix.hpp"
class Tile{
	void SetDef(uint8_t& x, uint8_t& y);
public:
	Rectangle m_def; //Definition of tile
	std::unique_ptr<Entity>	m_containedEntity = std::make_unique<Entity>();
	Tile();
	static Matrix2<std::shared_ptr<Tile>, 20> tileSet;
};
