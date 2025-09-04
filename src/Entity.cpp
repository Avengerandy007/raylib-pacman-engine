#include "../include/Entity.hpp"
#include "../include/Tile.hpp"
#include <chrono>
#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

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

uint32_t Player::score = 0;

Player::Player() : controller(1, 0, 0){}

Player::Player(uint8_t x, uint8_t y) : controller(1, x, y){
	typeId = PLAYER;
	score = 0;
}

void Player::HandleCollisions(Tile& currentTile){
	if (currentTile.m_coinContainer && !controller.m_calledMoveThisFrame){
		currentTile.m_coinContainer = nullptr;
		score++;
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

uint8_t Coin::coinCount = 0;

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
	framesSinceLastMove = 0;
}

ImageTexture& Ghost::Texture(){
	static ImageTexture texture("Ghost.png");
	return texture;
}

Ghost::Ghost(uint8_t x, uint8_t y) : controller(1, x, y){
	typeId = GHOST;
	framesSinceLastMove = 0;
}

void Ghost::DecideDirections(){
	std::cout << "Calculating direction\n";
	controller.dir.y = 0;
	controller.dir.x = 0;
	Player* player = nullptr;
	std::cout << "Reset dir\n";
	for (uint8_t i = 0; i < 20; i++){
		for (uint8_t k = 0; k < 20; k++){
			if (!Tile::tileSet.matrix[i][k].m_containedEntity) continue;
			else if (Tile::tileSet.matrix[i][k].m_containedEntity->typeId == PLAYER){
				player = dynamic_cast<Player*>(Tile::tileSet.matrix[i][k].m_containedEntity.get());
				std::cout << "Player found\n";
				break;
			}
		}
	}

	if(player == nullptr) return;

	if (player->controller.X > controller.X){

		if (!Tile::tileSet.matrix[controller.X + 1][controller.Y].m_containedEntity || Tile::tileSet.matrix[controller.X + 1][controller.Y].m_containedEntity->typeId != WALL)
			controller.dir.x = 1;
		else{
			if (controller.Y > player->controller.Y) controller.dir.y = -1;
			else controller.dir.y = 1;
		}

	}else if(player->controller.X < controller.X){
		
		if (!Tile::tileSet.matrix[controller.X - 1][controller.Y].m_containedEntity || Tile::tileSet.matrix[controller.X - 1][controller.Y].m_containedEntity->typeId != WALL)
			controller.dir.x = -1;
		else{
			if (controller.Y > player->controller.Y) controller.dir.y = -1;
			else controller.dir.y = 1;
		}
	}
	else if (player->controller.Y > controller.Y){

		if (!Tile::tileSet.matrix[controller.X][controller.Y + 1].m_containedEntity || Tile::tileSet.matrix[controller.X][controller.Y + 1].m_containedEntity->typeId != WALL){
			controller.dir.y = 1;
		}else{
			if (controller.X > player->controller.X) controller.dir.x = -1;
			else controller.dir.x = 1;
		}

	}else if (player->controller.Y < controller.Y){

		if (!Tile::tileSet.matrix[controller.X][controller.Y - 1].m_containedEntity || Tile::tileSet.matrix[controller.X][controller.Y - 1].m_containedEntity->typeId != WALL){
			controller.dir.y = -1;
		}else{
			if (controller.X > player->controller.X) controller.dir.x = -1;
			else controller.dir.x = 1;
		}

	}

}

void Ghost::Update(){
	Texture().Render(rect);
	framesSinceLastMove++;
	if (instance == GAME && framesSinceLastMove >= 30){
		DecideDirections();
		std::cout << "Dir x = " << (int)controller.dir.x << " y = " << (int)controller.dir.y << "\n";
		controller.Move();
		framesSinceLastMove = 0;
	}
}
