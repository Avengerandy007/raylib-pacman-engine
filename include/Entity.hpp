#pragma once
#include "../Raylib/include/raylib.h"
#include <memory>
class Entity{
public:
	std::shared_ptr<Rectangle> rect = std::make_shared<Rectangle>();
	virtual void Update();
};
