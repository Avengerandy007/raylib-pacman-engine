#pragma once
#include "../Raylib/include/raylib.h"
#include <memory>
class Entity{
public:
	std::shared_ptr<Rectangle> rect = std::make_shared<Rectangle>();
	//virtual void Update(); Temporarily commented because I couldn't build properly with it.
	void Update();
};
