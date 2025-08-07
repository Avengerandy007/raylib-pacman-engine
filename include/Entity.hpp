#pragma once
#include "../Raylib/include/raylib.h"
#include "EntityModules.hpp"
#include <memory>
#include <string>

class Entity{
public:
	std::shared_ptr<Rectangle> rect = std::make_shared<Rectangle>();
	ImageTexture texture;
	virtual void Update();
	Entity(std::string textureName);
};
