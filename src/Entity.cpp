#include "../include/Entity.hpp"
#include "../include/Tile.hpp"
#include <iostream>
#include <memory>

TYPE_OF_INSTANCE instance;

/*
 *	WALL CLASS
 */

ImageTexture& Wall::Texture(){
	static ImageTexture texture("Wall.png");
	return texture;
}

Wall::Wall(){
	typeId = WALL;
}

void Wall::Update(){
	Texture().Render(rect);
}

/*
 *	PLAYER CLASS
 */

ImageTexture& Player::Texture(){
	static ImageTexture texture("Player.png");
	return texture;
}

Player::Player() : controller(1, 0, 0){}

Player::Player(uint8_t x, uint8_t y) : controller(1, x, y){
	typeId = PLAYER;
	score = 0;
}

void Player::HandleCollisions(Tile& currentTile){
	if (collider.Colliding(currentTile) && !controller.m_calledMoveThisFrame){
		switch(currentTile.m_containedEntity->typeId){
			case COIN:
				score++;
				currentTile.m_containedEntity = nullptr;
				break;
			default: break;
		}
	}
} 

void Player::Update(){
	Texture().Render(rect);
	if (instance == GAME){
		input.ProccesInput(controller);
		HandleCollisions(Tile::tileSet.matrix[(int)controller.X + (int)controller.dir.x][(int)controller.Y + (int)controller.dir.y]);
		controller.Move();
	}
}

/*
 *	COIN CLASS
 */

ImageTexture& Coin::Texture(){
	static ImageTexture texture("Coin.png");
	return texture;
}

Coin::Coin(){
	typeId = COIN;
}

void Coin::Update(){
	Texture().Render(rect);
}
