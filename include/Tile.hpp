#pragma once
#include <memory>
#include "Entity.hpp"
#include "Matrix.hpp"
class Tile{
	Rectangle m_def; //Definition of tile
	void SetDef();
public:
	std::unique_ptr<Entity>	m_containedEntity = std::make_unique<Entity>();
	Tile();
	static Matrix2<Tile*> tileSet;
};
