#include "../include/EntityModules.hpp"
#include "../include/Tile.hpp"
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
	if (dynamic_cast<Entity*>(Tile::tileSet.matrix[x][y]->m_containedEntity.get())){
		X = x;
		Y = y;
		return false;
	}else return true;
}

void Controller::Move(){
	std::shared_ptr<Tile> origin = Tile::tileSet.matrix[X][Y];
	if (CheckWall(X, Y)) return;
	std::shared_ptr<Tile> destination = Tile::tileSet.matrix[X][Y];
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

const std::string ImageTexture::path = "data/";

ImageTexture::ImageTexture(std::string fileName){
	std::string completePath = path + fileName;
	image = LoadImage(completePath.c_str());
	ImageResize(&image, 50, 50);
	texture = LoadTextureFromImage(image);
	UnloadImage(image);
	
}

void ImageTexture::Render(std::shared_ptr<Rectangle> rect){
	DrawTexture(texture, rect->x, rect->y, WHITE);
}

ImageTexture::~ImageTexture(){
	UnloadTexture(texture);
}
