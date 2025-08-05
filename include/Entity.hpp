#pragma once
#include "../Raylib/include/raylib.h"
#include <memory>
class Entity{
public:
	std::unique_ptr<Rectangle> rect = std::make_unique<Rectangle>();
	virtual void Update();
};
