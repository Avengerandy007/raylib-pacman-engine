#pragma once
#include "../Raylib/include/raylib.h"
#include "EntityModules.hpp"
#include <memory>
#include <string>

enum TypeId{
	EMPTY = 0,
	WALL = 1,
};

class Entity{
public:
	std::shared_ptr<Rectangle> rect = std::make_shared<Rectangle>();
	TypeId typeId; 
	virtual void Update() = 0;
};

class Wall : public Entity{
public:
	static ImageTexture& Texture();
	Wall();
	void Update() override;
};
