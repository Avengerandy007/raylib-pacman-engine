#pragma once
#include "../Raylib/include/raylib.h"
#include <memory>
class Entity{
	std::unique_ptr<Rectangle> rect = std::make_unique<Rectangle>();
public:
	virtual void Update();
};
