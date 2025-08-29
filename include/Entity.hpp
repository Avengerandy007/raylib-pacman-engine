#pragma once
#include "../Raylib/include/raylib.h"
#include "EntityModules.hpp"
#include <memory>
#include <string>

enum TypeId{
	EMPTY = 0,
	WALL = 1,
	PLAYER = 2,
	COIN = 3,
};

enum TYPE_OF_INSTANCE{
	LEVEL_EDITOR,
	GAME,
};

extern TYPE_OF_INSTANCE instance;

class Entity{
public:
	std::shared_ptr<Rectangle> rect;
	TypeId typeId; 
	virtual void Update() = 0;
};

class Wall : public Entity{
public:
	static ImageTexture& Texture();
	Wall();
	void Update() override;
};

class Coin : public Entity{
public:
	static ImageTexture& Texture();
	Coin();
	void Update() override;
};

class Player : public Entity{
	TileCollider collider;
	InputHandler input;
public:
	Controller controller;
	static ImageTexture& Texture();
	Player();
	void Update() override;
};
