#include <memory>
#include "Entity.hpp"
#include "Matrix.hpp"
class Tile{
	Rectangle m_def; //Definition of tile
public:
	std::unique_ptr<Entity>	m_containedEntity = std::make_unique<Entity>();
	static Matrix2<Tile> totalTiles;
};
