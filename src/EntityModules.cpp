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

Controller::Controller(uint16_t speed){
	m_speed = speed;
}

bool Controller::CheckWall(uint8_t x, uint8_t y){
	x += dir.x * m_speed;
	y += dir.y * m_speed;
	if (dynamic_cast<Entity*>(Tile::tileSet.matrix[x][y].m_containedEntity.get())){
		X = x;
		Y = y;
		return false;
	}else return true;
}

void Controller::Move(){
	Tile* origin = &Tile::tileSet.matrix[X][Y];
	if (CheckWall(X, Y)) return;
	Tile* destination = &Tile::tileSet.matrix[X][Y];
	destination->m_containedEntity = std::move(origin->m_containedEntity);
	destination->m_containedEntity->rect = std::make_shared<Rectangle>(destination->m_def);
}

/* 
 *	TILE COLIDER CLASS
 */

bool TileCollider::Colliding(std::unique_ptr<Tile> currentTile){
	if (currentTile->m_containedEntity != nullptr) return true;
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

void InputHandler::ChangeDirection(Vector2 &dir){
	if(IsKeyPressed(KEY_LEFT)){
		dir.x = -1;
		dir.y = 0;
	}else if (IsKeyPressed(KEY_RIGHT)){
		dir.x = 1;
		dir.y = 0;
	}else if (IsKeyPressed(KEY_DOWN)){
		dir.x = 0;
		dir.y = 1;
	}else if (IsKeyPressed(KEY_UP)){
		dir.x = 0;
		dir.y = -1;
	}
}
