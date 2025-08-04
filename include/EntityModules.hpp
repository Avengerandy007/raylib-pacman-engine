#pragma once
#include "../Raylib/include/raylib.h"
#include <bits/types/FILE.h>
#include <memory>
#include <string>

class Controller{
	int speed;
public:
	Vector2 dir;

	void Move(Vector2& pos);
};

class TileCollider{
public:
	bool Colliding(std::unique_ptr<Rectangle> myRect);
};

class ImageTexture{
	std::string path;
	Texture2D texture;
public:
	ImageTexture();
	void Render(Rectangle rect);
	~ImageTexture();
};

class InputHandler{
public:
	void ChangeDirection(Vector2& dir);
};
