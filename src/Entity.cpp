#include "../include/Entity.hpp"

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

Player::Player() : controller(1, 0, 0){
	typeId = PLAYER;
}

void Player::Update(){
	Texture().Render(rect);
	if (instance == GAME) input.ProccesInput(controller);
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
