#include "../include/Entity.hpp"
#include "../include/Tile.hpp"
#include <chrono>
#include <cstdint>
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

/*
 *	GHSOT CLASS
 */

Ghost::Ghost() : controller(1, 0, 0){
	typeId = GHOST;
}

ImageTexture& Ghost::Texture(){
	static ImageTexture texture("Ghost.png");
	return texture;
}

Ghost::Ghost(uint8_t x, uint8_t y) : controller(1, x, y){
	typeId = GHOST;
}

void Ghost::DecideDirections(){
	std::cout << "Calculating direction\n";
	controller.dir.y = 0;
	controller.dir.x = 0;
	std::cout << "Reset dir\n";
	for (uint8_t k = 0; k < 20; k++){
		if (!Tile::tileSet.matrix[controller.X][k].m_containedEntity);
		else if (Tile::tileSet.matrix[controller.X][k].m_containedEntity->typeId == PLAYER){
			if (k > controller.Y) controller.dir.y = 1;
			else controller.dir.y = -1;
			std::cout << "Player found\n";
			break;
		}
		std::cout << "Searching on K\n";
	}

	std::cout << "Direction on y = " << controller.dir.y << "\n";

	if (controller.dir.y == 0){
		for (uint8_t i = 0; i < 20; i++){
			if (!Tile::tileSet.matrix[i][controller.Y].m_containedEntity);
			else if (Tile::tileSet.matrix[i][controller.Y].m_containedEntity->typeId == PLAYER){
				if (i > controller.X) controller.dir.x = 1;
				else controller.dir.x = -1;
				std::cout << "Player found\n";
				break;
			}
			std::cout << "Searching on I\n";
		}
	}

	std::cout << "Direction on x = " << controller.dir.x << "\n";
	
	if (controller.dir.x != 0 || controller.dir.y != 0) return;
	while (controller.dir.x == 0 || controller.dir.y == 0){
		std::cout << "Trying to randomize\n";
		auto now = std::chrono::system_clock::now();
		std::cout << "Got current time for x\n";
		uint32_t seed = std::chrono::time_point_cast<std::chrono::milliseconds>(now).time_since_epoch().count();
		std::cout << "Made seed for x\n";
		controller.dir.x = controller.X > 15 ? -1 : (seed * seed) % 2;
		std::cout << "Calculated x = " << controller.dir.x << "\n";
		if (controller.dir.x != 0) break;
		now = std::chrono::system_clock::now();
		std::cout << "Got current time for y\n";
		seed = std::chrono::time_point_cast<std::chrono::milliseconds>(now).time_since_epoch().count();
		std::cout << "Made seed for y\n";
		controller.dir.y = controller.Y > 15 ? -1 : (seed * seed) % 2;
		std::cout << "Calculated y = " << controller.dir.y << "\n";
	}
}

void Ghost::Update(){
	Texture().Render(rect);
	if (instance == GAME){
		DecideDirections();
		std::cout << "Dir x = " << (int)controller.dir.x << " y = " << (int)controller.dir.y << "\n";
		controller.Move();
	}
}
