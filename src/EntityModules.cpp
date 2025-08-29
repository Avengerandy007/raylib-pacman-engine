#include "../include/Tile.hpp"
#include "../include/Entity.hpp"
#include <map>
#include <iostream>
#include <cstddef>
#include <cstdint>
#include <memory>

/*  
 *	CONTROLLER CLASS
 */

Controller::Controller(uint16_t speed, uint8_t x, uint8_t y){
	m_speed = speed;
	X = x;
	Y = y;
	m_calledMoveThisFrame = false;
	dir.x = 0;
	dir.y = 0;
}

bool Controller::CheckWall(uint8_t& destx, uint8_t& desty){
	if (Tile::tileSet.matrix[destx][desty].m_containedEntity == nullptr && destx <= 19 && desty <= 19 && destx >= 0 && desty >= 0) return false;

	if (Tile::tileSet.matrix[destx][desty].m_containedEntity->typeId == WALL){
		std::cout << "HIT WALL\n";
		return true;
	}
	return false;

}

void Controller::Move(){

	if (dir.x == 0 && dir.y == 0) return;

	uint8_t destX, destY;

	destX = X + (dir.x * m_speed);
	destY = Y + (dir.y * m_speed);


	if(m_calledMoveThisFrame){
		m_calledMoveThisFrame = false;
		return;
	}

	if (destX > X || destY > Y){
		m_calledMoveThisFrame = true;
	}

	if (CheckWall(destX, destY)){
		m_calledMoveThisFrame = false;
		return;
	}

	Tile* destination = &Tile::tileSet.matrix[destX][destY];
	std::cout << "Created destination\n";
	if (destination->m_containedEntity != nullptr)
		if (CheckWall(destX, destY)) return;
	std::cout << "Checked wall\n";

	Tile* origin = &Tile::tileSet.matrix[X][Y];
	std::cout << "Created origin\n";

	if(origin->m_containedEntity == nullptr){
		std::cerr << "Origin has nullptr\n";
		return;
	}else if(destination->m_def == nullptr){
		std::cerr << "Tile at " << (int)destX << ", " << (int)destY << " has null rect\n";
		return;
	}else if (origin->m_containedEntity->rect == nullptr){
		std::cerr << "Origin rect is null\n";
		return;
	}

	X = destX;
	Y = destY;
	destination->m_containedEntity = std::move(origin->m_containedEntity);
	std::cout << "Moved entity\n";
	destination->m_containedEntity->rect = destination->m_def;
	std::cout << "Made entity rect = destination tile\n X = " << destination->m_containedEntity->rect->x << ", Y = " << destination->m_containedEntity->rect->y << "\n";
	std::cout << "Controller pos:\nX = " << (int)X << ", Y = " << (int)Y << "\n";
}

/* 
 *	TILE COLIDER CLASS
 */

bool TileCollider::Colliding(Tile& currentTile){
	if (currentTile.m_containedEntity != nullptr) return true;
	else return false;
}

/*
 *	IMAGE TEXTURE CLASS
 */

const std::string ImageTexture::path = "resources/";

ImageTexture::ImageTexture(){}

ImageTexture::ImageTexture(std::string fileName){
	if (fileName == "") return;
	std::cout << "Assigning " << fileName << " to this\n";
	std::string completePath = path + fileName;
	image = LoadImage(completePath.c_str());
	ImageResize(&image, 50, 50);
	texture = LoadTextureFromImage(image);
	UnloadImage(image);
}

void ImageTexture::Render(std::shared_ptr<Rectangle> rect){
	if(texture.id == 0) return;
	DrawTexture(texture, rect->x, rect->y, WHITE);
}

ImageTexture::~ImageTexture(){
	UnloadTexture(texture);
}

/*
 *	INPUT HANDLER CLASS
 */

void InputHandler::ProccesInput(Controller& controller){

	controller.dir.x = 0;
	controller.dir.y = 0;

	if(IsKeyPressed(KEY_LEFT)){
		controller.dir.x = -1;
		controller.dir.y = 0;
	}else if (IsKeyPressed(KEY_RIGHT)){
		controller.dir.x = 1;
		controller.dir.y = 0;
	}else if (IsKeyPressed(KEY_DOWN)){
		controller.dir.x = 0;
		controller.dir.y = 1;
	}else if (IsKeyPressed(KEY_UP)){
		controller.dir.x = 0;
		controller.dir.y = -1;
	}
}
