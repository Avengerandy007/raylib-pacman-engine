#pragma once
#include "../Raylib/include/raylib.h"
#include "EntityModules.hpp"
#include <memory>
#include <string>

class Entity{
public:
	std::shared_ptr<Rectangle> rect = std::make_shared<Rectangle>();
	int typeId; 
	/* Separate id for each subseqent inherited class
	 * typeId = 0 -> null
	 * typeId = 1 -> wall
	 */
	virtual void Update() = 0;
};

class Wall : public Entity{
	ImageTexture texture = ImageTexture("Wall.png");
public:
	Wall();
	void Update() override;
};
