#pragma once
#include "../Raylib/include/raylib.h"
#include "EntityModules.hpp"
#include <memory>
#include <string>

class Entity{
public:
	std::shared_ptr<Rectangle> rect = std::make_shared<Rectangle>();
	virtual void Update() = 0;
};

class Wall : public Entity{
	ImageTexture texture = ImageTexture("Wall.png");
public:
	void Update() override;
};
