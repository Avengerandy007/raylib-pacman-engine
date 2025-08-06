#pragma once
#include "../Raylib/include/raylib.h"
#include "Tile.hpp"
#include <cstdint>
#include <memory>
#include <string>

class Controller{
	uint16_t m_speed;
	bool CheckWall(uint8_t x, uint8_t y);
	uint8_t X, Y;
public:
	Vector2 dir;
	Controller(uint16_t speed);
	void Move();
};

class TileCollider{
public:
	bool Colliding(std::unique_ptr<Tile> currentTile);
};

class ImageTexture{
	static const std::string path;
	Image image;
	Texture2D texture;
public:
	ImageTexture(std::string fileName);
	void Render(std::shared_ptr<Rectangle> rect);
	~ImageTexture();
};

class InputHandler{
public:
	void ChangeDirection(Vector2& dir);
};
